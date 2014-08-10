#include "souistd.h"
#include "control/SComboBox.h"


namespace SOUI
{

// CComboEdit
CComboEdit::CComboEdit( SComboBoxBase *pOwner )
{
    SetOwner(pOwner);
}

void CComboEdit::OnMouseHover( WPARAM wParam, CPoint ptPos )
{
    __super::OnMouseHover(wParam,ptPos);
    GetOwner()->SSendMessage(WM_MOUSEHOVER,wParam,MAKELPARAM(ptPos.x,ptPos.y));
}

void CComboEdit::OnMouseLeave()
{
    __super::OnMouseLeave();
    GetOwner()->SSendMessage(WM_MOUSELEAVE);
}

void CComboEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    SWindow *pOwner = GetOwner();
    if (pOwner && (nChar == VK_DOWN || nChar == VK_ESCAPE))
    {
        pOwner->SSendMessage(WM_KEYDOWN, nChar, MAKELONG(nFlags, nRepCnt));
        return;
    }

    SetMsgHandled(FALSE);
}

BOOL CComboEdit::FireEvent(EventArgs & evt)
{
    if(evt.GetEventID()==EVT_RE_NOTIFY)
    {//ת��richedit��txNotify��Ϣ
        evt.idFrom=GetOwner()->GetID();
        evt.nameFrom=GetOwner()->GetName();
    }
    return __super::FireEvent(evt);
}


//////////////////////////////////////////////////////////////////////////
// SComboBoxBase
SComboBoxBase::SComboBoxBase(void)
:m_pSkinBtn(GETBUILTINSKIN(SKIN_SYS_DROPBTN))
,m_pEdit(NULL)
,m_bDropdown(TRUE)
,m_nDropHeight(200)
,m_dwBtnState(WndState_Normal)
,m_iAnimTime(200)
,m_pDropDownWnd(NULL)
,m_iInitSel(-1)
{
    m_bFocusable=TRUE;
    m_style.SetAttribute(L"align",L"left",TRUE);
    m_style.SetAttribute(L"valign",L"middle",TRUE);

    m_evtSet.addEvent(EventCBSelChange::EventID);
    m_evtSet.addEvent(EventRENotify::EventID);
}

SComboBoxBase::~SComboBoxBase(void)
{
}


BOOL SComboBoxBase::CreateChildren( pugi::xml_node xmlNode )
{
    SASSERT(m_pSkinBtn);
    //����edit����
    if(!m_bDropdown)
    {
        SIZE szBtn=m_pSkinBtn->GetSkinSize();
        m_pEdit=new CComboEdit(this);
        InsertChild(m_pEdit);
        pugi::xml_node xmlEditStyle=xmlNode.child(L"editstyle");
        if(xmlEditStyle)
            m_pEdit->InitFromXml(xmlEditStyle);
        else
            m_pEdit->SSendMessage(WM_CREATE);
        SStringW strPos;
        strPos.Format(L"0,0,-%d,-0",szBtn.cx);
        m_pEdit->SetAttribute(L"pos",strPos,TRUE);
        m_pEdit->SetID(IDC_CB_EDIT);

    }
    return CreateListBox(xmlNode);
}


void SComboBoxBase::GetDropBtnRect(LPRECT prc)
{
    SIZE szBtn=m_pSkinBtn->GetSkinSize();
    GetClientRect(prc);
    prc->left=prc->right-szBtn.cx;
}

void SComboBoxBase::GetTextRect( LPRECT pRect )
{
    GetClientRect(pRect);
    SIZE szBtn=m_pSkinBtn->GetSkinSize();
    pRect->right-=szBtn.cx;
}

void SComboBoxBase::OnPaint(IRenderTarget * pRT )
{
    SPainter painter;

    BeforePaint(pRT, painter);
    if(GetCurSel() != -1 && m_pEdit==NULL)
    {
        CRect rcText;
        GetTextRect(rcText);
        SStringT strText=GetWindowText();
        DrawText(pRT,strText, strText.GetLength(), rcText, GetTextAlign());
    }
    //draw focus rect
    if(GetContainer()->SwndGetFocus()==m_hSWnd)
    {
        DrawFocus(pRT);
    }
    AfterPaint(pRT, painter);
    CRect rcBtn;
    GetDropBtnRect(&rcBtn);
    m_pSkinBtn->Draw(pRT,rcBtn,IIF_STATE3(m_dwBtnState,WndState_Normal,WndState_Hover,WndState_PushDown));
}

void SComboBoxBase::OnLButtonDown( UINT nFlags,CPoint pt )
{
    SetFocus();
    DropDown();
}

void SComboBoxBase::OnMouseMove( UINT nFlags,CPoint pt )
{
    if(m_dwBtnState==WndState_PushDown) return;

    __super::OnMouseHover(nFlags,pt);
    CRect rcBtn;
    GetDropBtnRect(&rcBtn);
    if(rcBtn.PtInRect(pt))
    {
        m_dwBtnState=WndState_Hover;
        InvalidateRect(rcBtn);
    }else if(m_dwBtnState==WndState_Hover)
    {
        m_dwBtnState=WndState_Normal;
        InvalidateRect(rcBtn);
    }
}

void SComboBoxBase::OnMouseLeave()
{
    if(m_dwBtnState==WndState_PushDown) return;

    if(GetState()&WndState_Hover) 
        __super::OnMouseLeave();
    if(m_dwBtnState==WndState_Hover)
    {
        m_dwBtnState=WndState_Normal;
        CRect rcBtn;
        GetDropBtnRect(&rcBtn);
        InvalidateRect(rcBtn);
    }
}

void SComboBoxBase::OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags )
{    
    if ( nChar == VK_DOWN)
        DropDown();
}

void SComboBoxBase::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if (!m_bDropdown)
    {
        CComboEdit *pEdit = static_cast<CComboEdit *>(FindChildByID(IDC_CB_EDIT));
        if (pEdit)
            pEdit->SSendMessage(WM_CHAR, nChar, MAKELONG(nFlags, nRepCnt));
        return;
    }
}

UINT SComboBoxBase::OnGetDlgCode()
{        
    return SC_WANTARROWS;
}

BOOL SComboBoxBase::IsFocusable()
{
    if (m_bDropdown && m_bFocusable)
        return TRUE;
    return FALSE;
}


SWindow* SComboBoxBase::GetDropDownOwner()
{
    return this;
}


void SComboBoxBase::OnDropDown( SDropDownWnd *pDropDown )
{
    m_dwBtnState=WndState_PushDown;
    CRect rcBtn;
    GetDropBtnRect(&rcBtn);
    InvalidateRect(rcBtn);
    ((CSimpleWnd*)pDropDown)->SetCapture();
}

void SComboBoxBase::OnCloseUp(SDropDownWnd *pDropDown,UINT uCode)
{
    if (!m_bDropdown && m_pEdit)
    {
        m_pEdit->SetFocus();
        m_pEdit->SetSel(MAKELONG(0,-1));
    }

    m_dwBtnState = WndState_Normal;
    m_pDropDownWnd=NULL;
    CRect rcBtn;
    GetDropBtnRect(&rcBtn);
    InvalidateRect(rcBtn);
    ModifyState(0,WndState_Hover,TRUE);
    CPoint pt;
    GetCursorPos(&pt);
    ScreenToClient(GetContainer()->GetHostHwnd(),&pt);
    ::PostMessage(GetContainer()->GetHostHwnd(),WM_MOUSEMOVE,0,MAKELPARAM(pt.x,pt.y));

    if(uCode==IDOK)
    {
        OnSelChanged();
    }

}

BOOL SComboBoxBase::CalcPopupRect( int nHeight,CRect & rcPopup )
{
    CRect rcWnd;
    GetWindowRect(&rcWnd);
    ClientToScreen(GetContainer()->GetHostHwnd(),(LPPOINT)&rcWnd);
    ClientToScreen(GetContainer()->GetHostHwnd(),((LPPOINT)&rcWnd)+1);

    HMONITOR hMonitor = ::MonitorFromWindow(GetContainer()->GetHostHwnd(), MONITOR_DEFAULTTONULL);
    CRect rcMonitor;
    if (hMonitor)
    {
        MONITORINFO mi = {sizeof(MONITORINFO)};
        ::GetMonitorInfo(hMonitor, &mi);
        rcMonitor = mi.rcMonitor;
    }
    else
    {
        rcMonitor.right   =   GetSystemMetrics(   SM_CXSCREEN   );   
        rcMonitor.bottom  =   GetSystemMetrics(   SM_CYSCREEN   );
    }
    if(rcWnd.bottom+nHeight<=rcMonitor.bottom)
    {
        rcPopup = CRect(rcWnd.left,rcWnd.bottom,rcWnd.right,rcWnd.bottom+nHeight);
        return TRUE;
    }else
    {
        rcPopup = CRect(rcWnd.left,rcWnd.top-nHeight,rcWnd.right,rcWnd.top);
        return FALSE;
    }
}


void SComboBoxBase::DropDown()
{
    if(m_dwBtnState==WndState_PushDown) return;

    if(!m_pDropDownWnd)
    {
        m_pDropDownWnd = new SDropDownWnd(this);
        CRect rcPopup;
        BOOL bDown=CalcPopupRect(GetListBoxHeight(),rcPopup);
        m_pDropDownWnd->Create(rcPopup,0);
        m_pDropDownWnd->AnimateHostWindow(m_iAnimTime,AW_SLIDE|(bDown?AW_VER_POSITIVE:AW_VER_NEGATIVE));
    }
}

void SComboBoxBase::CloseUp()
{
    if(m_pDropDownWnd)
    {
        m_pDropDownWnd->EndDropDown(IDCANCEL);
    }
}

void SComboBoxBase::OnDestroy()
{
    CloseUp();
    __super::OnDestroy();
}

BOOL SComboBoxBase::FireEvent(EventArgs &evt)
{
    if(evt.idFrom == IDC_DROPDOWN_LIST)
    {
        SASSERT(m_pDropDownWnd);
        const MSG *pMsg=m_pDropDownWnd->GetCurrentMessage();
        if(evt.GetEventID()==EventLBSelChanged::EventID)
        {
            OnSelChanged();
            if(pMsg->message != WM_KEYDOWN)
                CloseUp();
            return TRUE;
        }
    }
    return __super::FireEvent(evt);
}

void SComboBoxBase::OnSelChanged()
{
    EventCBSelChange evt(this);
    FireEvent(evt);
}

//////////////////////////////////////////////////////////////////////////
SComboBox::SComboBox()
:m_pListBox(NULL)
{

}

SComboBox::~SComboBox()
{
    if(m_pListBox)
    {
        m_pListBox->SSendMessage(WM_DESTROY);
        delete m_pListBox;
    }
}

BOOL SComboBox::CreateListBox( pugi::xml_node xmlNode )
{
    SASSERT(xmlNode);
    //�����б�ؼ�
    m_pListBox=new SListBox;
    m_pListBox->SetContainer(GetContainer());

    m_pListBox->InitFromXml(xmlNode.child(L"liststyle"));
    m_pListBox->SetAttribute(L"pos", L"0,0,-0,-0", TRUE);
    m_pListBox->SetAttribute(L"hottrack",L"1",TRUE);
    m_pListBox->SetOwner(this);    //chain notify message to combobox
    m_pListBox->SetID(IDC_DROPDOWN_LIST);

    //��ʼ���б�����
    pugi::xml_node xmlNode_Items=xmlNode.parent().child(L"items");
    if(xmlNode_Items)
    {
        pugi::xml_node xmlNode_Item=xmlNode_Items.child(L"item");
        while(xmlNode_Item)
        {
            SStringT strText=S_CW2T(xmlNode_Item.attribute(L"text").value());
            int iIcon=xmlNode_Item.attribute(L"icon").as_int(0);
            LPARAM lParam=xmlNode_Item.attribute(L"data").as_int(0);
            m_pListBox->AddString(strText,iIcon,lParam);
            xmlNode_Item=xmlNode_Item.next_sibling(L"item");
        }
    }

    if(m_iInitSel!=-1)
    {
        SetCurSel(m_iInitSel);
    }
    return TRUE;
}

int SComboBox::GetListBoxHeight()
{
    int nDropHeight=m_nDropHeight;
    if(GetCount()) 
    {
        int nItemHeight=m_pListBox->GetItemHeight();
        nDropHeight = min(nDropHeight,nItemHeight*GetCount()+m_pListBox->GetStyle().m_nMarginY*2);
    }
    return nDropHeight;    
}

void SComboBox::OnDropDown( SDropDownWnd *pDropDown)
{
    __super::OnDropDown(pDropDown);
    pDropDown->InsertChild(m_pListBox);
    pDropDown->UpdateChildrenPosition();

    m_pListBox->SetVisible(TRUE);
    m_pListBox->SetFocus();
    m_pListBox->EnsureVisible(GetCurSel());
}

void SComboBox::OnCloseUp( SDropDownWnd *pDropDown ,UINT uCode)
{
    pDropDown->RemoveChild(m_pListBox);
    m_pListBox->SetVisible(FALSE);
    m_pListBox->SetContainer(GetContainer());
    __super::OnCloseUp(pDropDown,uCode);
}

void SComboBox::OnSelChanged()
{
    m_pListBox->GetCurSel();
    if(m_pEdit)
    {
        SStringT strText=GetLBText(m_pListBox->GetCurSel());
        m_pEdit->GetEventSet()->setMutedState(true);
        m_pEdit->SetWindowText(S_CT2W(strText));
        m_pEdit->GetEventSet()->setMutedState(false);
    }
    Invalidate();
    __super::OnSelChanged();
}

//////////////////////////////////////////////////////////////////////////

SComboBoxEx::SComboBoxEx():m_uTxtID(0),m_uIconID(0),m_pListBox(NULL)
{

}

SComboBoxEx::~SComboBoxEx()
{
    if(m_pListBox)
    {
        m_pListBox->SSendMessage(WM_DESTROY);
        delete m_pListBox;
    }
}

BOOL SComboBoxEx::CreateListBox( pugi::xml_node xmlNode )
{
    SASSERT(xmlNode);
    //�����б�ؼ�
    m_pListBox=new SListBoxEx;
    m_pListBox->SetContainer(GetContainer());

    m_pListBox->InitFromXml(xmlNode.parent().child(L"liststyle"));
    m_pListBox->SetAttribute(L"pos", L"0,0,-0,-0", TRUE);
    m_pListBox->SetAttribute(L"hottrack",L"1",TRUE);
    m_pListBox->SetOwner(this);    //chain notify message to combobox
    m_pListBox->SetID(IDC_DROPDOWN_LIST);

    //��ʼ���б�����
    pugi::xml_node xmlNode_Items=xmlNode.parent().child(L"items");
    if(xmlNode_Items)
    {
        int nItems=0;
        pugi::xml_node xmlNode_Item=xmlNode_Items.child(L"item");
        while(xmlNode_Item)
        {
            nItems++;
            xmlNode_Item=xmlNode_Item.next_sibling(L"item");
        }

        m_pListBox->SetItemCount(nItems);
        int iItem=0;
        xmlNode_Item=xmlNode_Items.child(L"item");
        while(xmlNode_Item)
        {
            LPARAM lParam=xmlNode_Item.attribute(L"data").as_int(0);
            m_pListBox->SetItemData(iItem,lParam);
            SWindow *pWnd=m_pListBox->GetItemPanel(iItem);
            if(m_uTxtID!=0)
            {
                SWindow *pText=pWnd->FindChildByID(m_uTxtID);
                if(pText)
                {
                    SStringT strText=S_CW2T(xmlNode_Item.attribute(L"text").value());
                    pText->SetWindowText(strText);
                }
            }
            if(m_uIconID!=0)
            {
                SImageWnd * pImg = pWnd->FindChildByID2<SImageWnd>(m_uIconID);
                if(pImg) 
                {
                    int iIcon=xmlNode_Item.attribute(L"icon").as_int(0);
                    pImg->SetIcon(iIcon);
                }
            }
            iItem++;
            xmlNode_Item=xmlNode_Item.next_sibling(L"item");
        }
    }

    if(m_iInitSel!=-1)
    {
        SetCurSel(m_iInitSel);
    }
    return TRUE;
}

int SComboBoxEx::GetListBoxHeight()
{
    int nDropHeight=m_nDropHeight;
    if(GetCount()) 
    {
        int nItemHeight=m_pListBox->GetItemHeight();
        nDropHeight = min(nDropHeight,nItemHeight*GetCount()+m_pListBox->GetStyle().m_nMarginY*2);
    }
    return nDropHeight;    
}

void SComboBoxEx::OnDropDown( SDropDownWnd *pDropDown )
{
    __super::OnDropDown(pDropDown);
    pDropDown->InsertChild(m_pListBox);
    pDropDown->UpdateChildrenPosition();

    m_pListBox->SetVisible(TRUE);
    m_pListBox->SetFocus();
    m_pListBox->EnsureVisible(GetCurSel());
}

void SComboBoxEx::OnCloseUp( SDropDownWnd *pDropDown ,UINT uCode)
{
    pDropDown->RemoveChild(m_pListBox);
    m_pListBox->SetVisible(FALSE);
    m_pListBox->SetContainer(GetContainer());
    __super::OnCloseUp(pDropDown,uCode);
}

void SComboBoxEx::OnSelChanged()
{
    int iSel=m_pListBox->GetCurSel();
    if(m_pEdit)
    {
        SStringT strText=GetLBText(iSel);
        m_pEdit->GetEventSet()->setMutedState(true);
        m_pEdit->SetWindowText(S_CT2W(strText));
        m_pEdit->GetEventSet()->setMutedState(false);
    }
    Invalidate();
    __super::OnSelChanged();
}


}//namespace SOUI

