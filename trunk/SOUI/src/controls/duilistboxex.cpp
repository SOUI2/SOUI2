//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiListBoxEx
// Description: A DuiWindow Based ListBox Control. Can contain control as an item
//     Creator: Huang Jianxiong
//     Version: 2011.8.27 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once
#include "duistd.h"
#include "control/duilistboxex.h"
#include "DuiSystem.h"
#include "mybuffer.h"

#pragma warning(disable:4018)
#pragma warning(disable:4267)

namespace SOUI
{


SListBoxEx::SListBoxEx()
    : m_nItemHei(20)
    , m_iScrollSpeed(-1)
    , m_iSelItem(-1)
    , m_iHoverItem(-1)
    , m_pCapturedFrame(NULL)
    , m_pTemplPanel(NULL)
    , m_nItems(0)
    , m_pItemSkin(NULL)
    , m_crItemBg(CLR_INVALID)
    , m_crItemSelBg(RGB(0,0,128))
    , m_bVirtual(FALSE)
    , m_bItemRedrawDelay(TRUE)
{
    m_bTabStop=TRUE;
    addEvent(NM_LBITEMNOTIFY);
    addEvent(NM_ITEMMOUSEEVENT);
    addEvent(NM_GETLBDISPINFO);
    addEvent(NM_LBSELCHANGING);
    addEvent(NM_LBSELCHANGED);
}

SListBoxEx::~SListBoxEx()
{
}


void SListBoxEx::DeleteAllItems(BOOL bUpdate/*=TRUE*/)
{
    if(IsVirtual())
    {
        m_nItems=0;
    }
    else
    {
        for(int i=0; i<GetItemCount(); i++)
        {
            m_arrItems[i]->Release();
        }
        m_arrItems.RemoveAll();
    }
    m_iSelItem=-1;
    m_iHoverItem=-1;
    m_pCapturedFrame=NULL;
    ReleaseDuiCapture();

    SetViewSize(CSize(0,0));
    if(bUpdate) NotifyInvalidate();
}

void SListBoxEx::DeleteItem(int iItem)
{
    if(IsVirtual()) return;

    if(iItem<0 || iItem>=GetItemCount()) return;
    if(m_pCapturedFrame == m_arrItems[iItem])
    {
        m_pCapturedFrame=NULL;
        ReleaseDuiCapture();
    }

    m_arrItems[iItem]->Release();
    m_arrItems.RemoveAt(iItem);

    if(m_iSelItem==iItem) m_iSelItem=-1;
    else if(m_iSelItem>iItem) m_iSelItem--;
    if(m_iHoverItem==iItem) m_iHoverItem=-1;
    else if(m_iHoverItem>iItem) m_iHoverItem--;

    UpdatePanelsIndex(iItem,-1);

    CRect rcClient;
    SWindow::GetClient(&rcClient);
    CSize szView(rcClient.Width(),GetItemCount()*m_nItemHei);
    if(szView.cy>rcClient.Height()) szView.cx-=m_nSbWid;
    SetViewSize(szView);
}

int SListBoxEx::InsertItem(int iItem,pugi::xml_node xmlNode,DWORD dwData/*=0*/)
{
    if(IsVirtual()) return -1;

    SItemPanel *pItemObj=new SItemPanel(this,xmlNode,this);

    if(iItem==-1 || iItem>=GetItemCount())
    {
        iItem=GetItemCount();
    }
    pItemObj->SetItemData(dwData);
    pItemObj->Move(CRect(0,0,m_rcClient.Width(),m_nItemHei));
    if(m_pItemSkin) pItemObj->SetSkin(m_pItemSkin);
    pItemObj->SetColor(m_crItemBg,m_crItemSelBg);

    m_arrItems.InsertAt(iItem,pItemObj);

    if(m_iSelItem>=iItem) m_iSelItem++;
    if(m_iHoverItem>=iItem) m_iHoverItem++;

    UpdatePanelsIndex(iItem,-1);

    CRect rcClient;
    SWindow::GetClient(&rcClient);
    CSize szView(rcClient.Width(),GetItemCount()*m_nItemHei);
    if(szView.cy>rcClient.Height()) szView.cx-=m_nSbWid;
    SetViewSize(szView);

    return iItem;
}

int SListBoxEx::InsertItem(int iItem,LPCWSTR pszXml,DWORD dwData/*=0*/)
{
    if(IsVirtual()) return -1;

    if(!pszXml && !m_xmlTempl) return -1;
    if(pszXml)
    {
        SStringA strUtf8=DUI_CW2A(pszXml,CP_UTF8);
        pugi::xml_document xmlDoc;
        if(!xmlDoc.load_buffer((LPCSTR)strUtf8,strUtf8.GetLength(),pugi::parse_default,pugi::encoding_utf8)) return -1;
        return InsertItem(iItem,xmlDoc.first_child(),dwData);
    }else
    {
        return InsertItem(iItem,m_xmlTempl.first_child(),dwData);
    }
}

BOOL SListBoxEx::SetCurSel(int iItem)
{
    if(iItem<0 || iItem>=GetItemCount()) return FALSE;

    if(m_iSelItem==iItem) return FALSE;
    if(IsVirtual())
    {
        int nOldSel=m_iSelItem;
        m_iSelItem=iItem;
        if(IsVisible(TRUE))
        {
            if(nOldSel!=-1) RedrawItem(nOldSel);
            RedrawItem(m_iSelItem);
        }
    }else
    {
        int nOldSel=m_iSelItem;
        m_iSelItem=iItem;
        if(nOldSel!=-1)
        {
            m_arrItems[nOldSel]->ModifyItemState(0,DuiWndState_Check);
            if(IsVisible(TRUE)) RedrawItem(nOldSel);
        }
        m_arrItems[m_iSelItem]->ModifyItemState(DuiWndState_Check,0);
        if(IsVisible(TRUE)) RedrawItem(m_iSelItem);
    }
    return TRUE;
}

void SListBoxEx::EnsureVisible( int iItem )
{
    if(iItem<0 || iItem>=GetItemCount()) return;
    int iFirstVisible=(m_ptOrigin.y + m_nItemHei -1) / m_nItemHei;
    CRect rcClient;
    GetClient(&rcClient);
    int nVisibleItems=rcClient.Height()/m_nItemHei;
    if(iItem<iFirstVisible || iItem> iFirstVisible+nVisibleItems-1)
    {
        int nOffset=GetScrollPos(TRUE);
        if(iItem<iFirstVisible) nOffset=(iItem-iFirstVisible)*m_nItemHei;
        else nOffset=(iItem - iFirstVisible-nVisibleItems +1)*m_nItemHei;
        nOffset-=nOffset%m_nItemHei;//�õ�ǰ�иպ���ʾ
        OnScroll(TRUE,SB_THUMBPOSITION,nOffset + GetScrollPos(TRUE));
    }
}

int SListBoxEx::GetCurSel()
{
    return m_iSelItem;
}

int SListBoxEx::GetItemObjIndex(SWindow *pItemObj)
{
    SItemPanel * pItemPanel= dynamic_cast<SItemPanel *>(pItemObj);
    if (NULL == pItemPanel) return -1;
    return (int)pItemPanel->GetItemIndex();
}


SWindow * SListBoxEx::GetItemPanel(int iItem)
{
    if(iItem<0 || iItem>= GetItemCount()) return NULL;
    if(m_pTemplPanel) return m_pTemplPanel;
    else return m_arrItems[iItem];
}


LPARAM SListBoxEx::GetItemData(int iItem)
{
    DUIASSERT(iItem>=0 || iItem< GetItemCount());
    if(m_pTemplPanel) return 0;
    return m_arrItems[iItem]->GetItemData();
}

void SListBoxEx::SetItemData( int iItem,LPARAM lParam )
{
    DUIASSERT(iItem>=0 || iItem< GetItemCount());
    m_arrItems[iItem]->SetItemData(lParam);
}


BOOL SListBoxEx::SetItemCount(int nItems,LPCTSTR pszXmlTemplate)
{
    if(m_arrItems.GetCount()!=0) return FALSE;
    if(pszXmlTemplate)
    {
        SStringA strUtf8=DUI_CT2A(pszXmlTemplate,CP_UTF8);
        pugi::xml_document xmlDoc;
        if(!xmlDoc.load_buffer((LPCSTR)strUtf8,strUtf8.GetLength(),pugi::parse_default,pugi::encoding_utf8)) return FALSE;
        if(IsVirtual())
        {
            if(m_pTemplPanel)
            {
                m_pTemplPanel->DuiSendMessage(WM_DESTROY);
                m_pTemplPanel->Release();
            }
            m_pTemplPanel=new SItemPanel(this,xmlDoc,this);
            if(m_pItemSkin) m_pTemplPanel->SetSkin(m_pItemSkin);
        }else
        {
            if(m_pTemplPanel) delete m_pTemplPanel;
            m_xmlTempl.append_copy(xmlDoc.first_child());
        }

    }
    if(IsVirtual())
    {
        DUIASSERT(m_pTemplPanel);
        m_nItems=nItems;
        CRect rcClient;
        SWindow::GetClient(&rcClient);
        CSize szView(rcClient.Width(),GetItemCount()*m_nItemHei);
        if(szView.cy>rcClient.Height()) szView.cx-=m_nSbWid;
        SetViewSize(szView);
        GetClient(&rcClient);
        m_pTemplPanel->Move(0,0,rcClient.Width(),m_nItemHei);
        NotifyInvalidate();
        return TRUE;
    }else if(m_xmlTempl)
    {
        for(int i=0;i<nItems;i++)
        {
            InsertItem(i,m_xmlTempl.first_child());
        }
        return TRUE;
    }else
    {
        return FALSE;
    }

}

int SListBoxEx::GetItemCount()
{
    if(IsVirtual()) 
        return m_nItems;
    else
        return m_arrItems.GetCount();
}

void SListBoxEx::RedrawItem(int iItem)
{
    if(!IsVisible(TRUE)) return;
    CRect rcClient;
    GetClient(&rcClient);
    CRect rcItem=GetItemRect(iItem);
    CRect rcInter;
    rcInter.IntersectRect(&rcClient,&rcItem);
    if(rcInter.IsRectEmpty()) return;

    IRenderTarget * pRT=GetRenderTarget(&rcItem,OLEDC_PAINTBKGND);
    SPainter painter;
    BeforePaint(pRT,painter);

    DuiSendMessage(WM_ERASEBKGND,(WPARAM)pRT);
    OnDrawItem(pRT,rcItem,iItem);

    AfterPaint(pRT,painter);
    ReleaseRenderTarget(pRT);
}

//�Զ��޸�pt��λ��Ϊ��Ե�ǰ���ƫ����
int SListBoxEx::HitTest(CPoint &pt)
{
    CRect rcClient;
    GetClient(&rcClient);
    CPoint pt2=pt;
    pt2.y -= rcClient.top - m_ptOrigin.y;
    int nRet=pt2.y/m_nItemHei;
    if(nRet >= GetItemCount()) nRet=-1;
    else
    {
        pt.x-=rcClient.left;
        pt.y=pt2.y%m_nItemHei;
    }

    return nRet;
}

int SListBoxEx::GetScrollLineSize(BOOL bVertical)
{
    return m_iScrollSpeed >0 ? m_iScrollSpeed : m_nItemHei;
}

void SListBoxEx::OnPaint(IRenderTarget * pRT)
{
    SPainter duiDC;
    BeforePaint(pRT,duiDC);

    CRect rcClient;
    GetClient(&rcClient);
    pRT->PushClipRect(&rcClient,RGN_AND);
    int iFirstVisible=m_ptOrigin.y/m_nItemHei;
    int nPageItems=(m_rcClient.Height()+m_nItemHei-1)/m_nItemHei+1;

    CRect rcClip,rcInter;
    pRT->GetClipBound(&rcClip);

    for(int iItem = iFirstVisible; iItem<GetItemCount() && iItem <iFirstVisible+nPageItems; iItem++)
    {
        CRect rcItem(0,0,m_rcClient.Width(),m_nItemHei);
        rcItem.OffsetRect(0,m_nItemHei*iItem-m_ptOrigin.y);
        rcItem.OffsetRect(m_rcClient.TopLeft());
        rcInter.IntersectRect(&rcClip,&rcItem);
        if(!rcInter.IsRectEmpty())
            OnDrawItem(pRT,rcItem,iItem);
    }
    pRT->PopClip();
    AfterPaint(pRT,duiDC);
}


void SListBoxEx::OnSize( UINT nType, CSize size )
{
    __super::OnSize(nType,size);
    Relayout();
}

void SListBoxEx::OnDrawItem(IRenderTarget *pRT, CRect & rc, int iItem)
{
    if(IsVirtual())
    {//�����б���APP������ʾ
        DUIASSERT(m_pTemplPanel);
        DUINMGETLBDISPINFO nms;
        nms.hdr.hDuiWnd =m_hSWnd;
        nms.hdr.code    = NM_GETLBDISPINFO;
        nms.hdr.idFrom  = GetCmdID();
        nms.hdr.pszNameFrom= GetName();
        nms.bHover      = iItem == m_iHoverItem;
        nms.bSelect     = iItem == m_iSelItem;
        nms.nListItemID = iItem;
        nms.pItem = m_pTemplPanel;
        nms.pHostDuiWin   = this;

        m_pTemplPanel->LockUpdate();

        m_pTemplPanel->SetItemIndex(iItem);

        if(!nms.bSelect) m_pTemplPanel->GetFocusManager()->StoreFocusedView();
        else m_pTemplPanel->GetFocusManager()->RestoreFocusedView();

        DWORD dwState=0;
        if(nms.bHover) dwState|=DuiWndState_Hover;
        if(nms.bSelect) dwState|=DuiWndState_PushDown;
        m_pTemplPanel->ModifyItemState(dwState,-1);

        m_pTemplPanel->UnlockUpdate();

        LockUpdate();
        GetContainer()->OnDuiNotify((LPSNMHDR)&nms);
        UnlockUpdate();
        m_pTemplPanel->Draw(pRT,rc);
    }else
    {
        m_arrItems[iItem]->Draw(pRT,rc);
    }
}

BOOL SListBoxEx::LoadChildren(pugi::xml_node xmlNode)
{
    if(!xmlNode) return TRUE;

    pugi::xml_node xmlParent=xmlNode.parent();
    pugi::xml_node xmlTempl=xmlParent.child(L"template");
    pugi::xml_node xmlItems=xmlParent.child(L"items");

    if(!IsVirtual())
    {//��ͨ�б�
        if(xmlTempl) m_xmlTempl.append_copy(xmlTempl);

        if(xmlItems)
        {
            pugi::xml_node xmlItem=xmlItems.child(L"item");
            while(xmlItem)
            {
                int dwData=xmlItem.attribute(L"itemdata").as_int(0);
                InsertItem(-1,xmlItem,dwData);
                xmlItem=xmlItem.next_sibling(L"item");
            }
            SetCurSel(xmlItems.attribute(L"cursel").as_int(-1));
        }

        return TRUE;
    }else
    {//�����б�
        DUIASSERT(xmlTempl);
        m_pTemplPanel=new SItemPanel(this,xmlTempl,this);
        if(m_pItemSkin) m_pTemplPanel->SetSkin(m_pItemSkin);
        return TRUE;
    }
}


void SListBoxEx::NotifySelChange( int nOldSel,int nNewSel)
{
    DUINMLBSELCHANGE nms;
    nms.hdr.code=NM_LBSELCHANGING;
    nms.hdr.hDuiWnd=m_hSWnd;
    nms.hdr.idFrom=GetCmdID();
    nms.hdr.pszNameFrom=GetName();
    nms.nOldSel=nOldSel;
    nms.nNewSel=nNewSel;
    nms.uHoverID=0;
    if(nNewSel!=-1)
    {
        if(IsVirtual())
        {
            DUIASSERT(m_pTemplPanel);
            SWindow *pHover=DuiWindowMgr::GetWindow(m_pTemplPanel->GetDuiHover());
            if(pHover) nms.uHoverID=pHover->GetCmdID();
        }else
        {
            SWindow *pHover=DuiWindowMgr::GetWindow(m_arrItems[nNewSel]->GetDuiHover());
            if(pHover) nms.uHoverID=pHover->GetCmdID();
        }
    }

    if(S_OK!=DuiNotify((LPSNMHDR)&nms)) return ;

    m_iSelItem=nNewSel;
    if(nOldSel!=-1)
    {
        if(!m_pTemplPanel) m_arrItems[nOldSel]->ModifyItemState(0,DuiWndState_Check);
        RedrawItem(nOldSel);
    }
    if(m_iSelItem!=-1)
    {
        if(!m_pTemplPanel) m_arrItems[m_iSelItem]->ModifyItemState(DuiWndState_Check,0);
        RedrawItem(m_iSelItem);
    }

    nms.hdr.idFrom=GetCmdID();
    nms.hdr.code=NM_LBSELCHANGED;
    DuiNotify((LPSNMHDR)&nms);
}

void SListBoxEx::OnMouseLeave()
{
    __super::OnMouseLeave();
    if(m_iHoverItem!=-1)
    {
        int nOldHover=m_iHoverItem;
        m_iHoverItem=-1;
        if(IsVirtual())
        {
            DUIASSERT(m_pTemplPanel);
            RedrawItem(nOldHover);
            m_pTemplPanel->DoFrameEvent(WM_MOUSELEAVE,0,0);
        }
        else
            m_arrItems[nOldHover]->DoFrameEvent(WM_MOUSELEAVE,0,0);
    }
}

BOOL SListBoxEx::OnDuiSetCursor(const CPoint &pt)
{
    BOOL bRet=FALSE;
    if(m_pCapturedFrame)
    {
        CRect rcItem=m_pCapturedFrame->GetItemRect();
        bRet=m_pCapturedFrame->DoFrameEvent(WM_SETCURSOR,0,MAKELPARAM(pt.x-rcItem.left,pt.y-rcItem.top))!=0;
    }
    else if(m_iHoverItem!=-1)
    {
        CRect rcItem=GetItemRect(m_iHoverItem);
        if(IsVirtual())
        {
            DUIASSERT(m_pTemplPanel);
            bRet=m_pTemplPanel->DoFrameEvent(WM_SETCURSOR,0,MAKELPARAM(pt.x-rcItem.left,pt.y-rcItem.top))!=0;
        }else
        {
            bRet=m_arrItems[m_iHoverItem]->DoFrameEvent(WM_SETCURSOR,0,MAKELPARAM(pt.x-rcItem.left,pt.y-rcItem.top))!=0;
        }
    }
    if(!bRet)
    {
        bRet=__super::OnDuiSetCursor(pt);
    }
    return bRet;
}

void SListBoxEx::OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags )
{
    int  nNewSelItem = -1;
    SWindow *pOwner = GetOwner();
    if (pOwner && (nChar == VK_ESCAPE))
    {
        pOwner->DuiSendMessage(WM_KEYDOWN, nChar, MAKELONG(nFlags, nRepCnt));
        return;
    }

    if (nChar == VK_DOWN && m_iSelItem < GetItemCount() - 1)
        nNewSelItem = m_iSelItem+1;
    else if (nChar == VK_UP && m_iSelItem > 0)
        nNewSelItem = m_iSelItem-1;
    else if (pOwner && nChar == VK_RETURN)
        nNewSelItem = m_iSelItem;

    if(nNewSelItem!=-1)
    {
        EnsureVisible(nNewSelItem);
        NotifySelChange(m_iSelItem,nNewSelItem);
    }
}

void SListBoxEx::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    SWindow *pOwner = GetOwner();
    if (pOwner)
        pOwner->DuiSendMessage(WM_CHAR, nChar, MAKELONG(nFlags, nRepCnt));
}

UINT SListBoxEx::OnGetDuiCode()
{
    return DUIC_WANTALLKEYS;
}

void SListBoxEx::OnDestroy()
{
    DeleteAllItems(FALSE);
    if(IsVirtual())
    {
        DUIASSERT(m_pTemplPanel);
        m_pTemplPanel->DuiSendMessage(WM_DESTROY);
        m_pTemplPanel->Release();
        m_pTemplPanel=NULL;
    }
    __super::OnDestroy();
}

BOOL SListBoxEx::OnUpdateToolTip(HSWND hCurTipHost,HSWND &hNewTipHost,CRect &rcTip,SStringT &strTip)
{
    if(m_iHoverItem==-1)
        return __super::OnUpdateToolTip(hCurTipHost,hNewTipHost,rcTip,strTip);
    else if(IsVirtual())
        return m_pTemplPanel->OnUpdateToolTip(hCurTipHost,hNewTipHost,rcTip,strTip);
    else
        return m_arrItems[m_iHoverItem]->OnUpdateToolTip(hCurTipHost,hNewTipHost,rcTip,strTip);
}

void SListBoxEx::OnItemSetCapture(SItemPanel *pItem,BOOL bCapture )
{
    if(bCapture)
    {
        SetDuiCapture();
        m_pCapturedFrame=pItem;
    }
    else if(pItem==m_pCapturedFrame)
    {
        ReleaseDuiCapture();
        m_pCapturedFrame=NULL;
    }
}


CRect SListBoxEx::GetItemRect( int iItem )
{
    CRect rcClient;
    GetClient(&rcClient);
    CRect rcRet(CPoint(0,iItem*m_nItemHei),CSize(rcClient.Width(),m_nItemHei));
    rcRet.OffsetRect(rcClient.TopLeft()-m_ptOrigin);
    return rcRet;
}

BOOL SListBoxEx::OnItemGetRect(SItemPanel *pItem,CRect &rcItem )
{
    int iItem=pItem->GetItemIndex();
    rcItem=GetItemRect(iItem);
    return TRUE;
}

LRESULT SListBoxEx::OnMouseEvent( UINT uMsg,WPARAM wParam,LPARAM lParam )
{
    LRESULT lRet=0;
    CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
    if(m_pCapturedFrame)
    {
        CRect rcItem=m_pCapturedFrame->GetItemRect();
        pt.Offset(-rcItem.TopLeft());
        lRet = m_pCapturedFrame->DoFrameEvent(uMsg,wParam,MAKELPARAM(pt.x,pt.y));
    }
    else
    {
        if(m_bTabStop && (uMsg==WM_LBUTTONDOWN || uMsg== WM_RBUTTONDOWN || uMsg==WM_LBUTTONDBLCLK))
            SetDuiFocus();
        int iHover=HitTest(pt);
        if(iHover!=m_iHoverItem)
        {
            int nOldHover=m_iHoverItem;
            m_iHoverItem=iHover;
            if(nOldHover!=-1)
            {
                RedrawItem(nOldHover);
                if(!IsVirtual())
                {
                    m_arrItems[nOldHover]->DoFrameEvent(WM_MOUSELEAVE,0,0);
                }else
                {
                    DUIASSERT(m_pTemplPanel);
                    m_pTemplPanel->DoFrameEvent(WM_MOUSELEAVE,0,0);
                }
            }
            if(m_iHoverItem!=-1)
            {
                RedrawItem(m_iHoverItem);
                if(!IsVirtual())
                {
                    m_arrItems[m_iHoverItem]->DoFrameEvent(WM_MOUSEHOVER,wParam,MAKELPARAM(pt.x,pt.y));
                }else
                {
                    DUIASSERT(m_pTemplPanel);
                    m_pTemplPanel->DoFrameEvent(WM_MOUSEHOVER,wParam,MAKELPARAM(pt.x,pt.y));
                }
            }
        }
        if(uMsg==WM_LBUTTONDOWN && m_iSelItem!=-1 && m_iSelItem != m_iHoverItem && !IsVirtual())
        {//ѡ��һ�����е�ʱ��ԭ����ʧȥ����
            m_arrItems[m_iSelItem]->GetFocusManager()->SetFocusedHwnd(0);
        }
        if(m_iHoverItem!=-1)
        {
            if(!IsVirtual())
            {
                m_arrItems[m_iHoverItem]->DoFrameEvent(uMsg,wParam,MAKELPARAM(pt.x,pt.y));
            }else
            {
                DUIASSERT(m_pTemplPanel);
                m_pTemplPanel->DoFrameEvent(uMsg,wParam,MAKELPARAM(pt.x,pt.y));
            }
        }
    }
    if(uMsg==WM_LBUTTONUP && m_iHoverItem!=m_iSelItem)
        NotifySelChange(m_iSelItem,m_iHoverItem);
    return 0;
}

LRESULT SListBoxEx::OnKeyEvent( UINT uMsg,WPARAM wParam,LPARAM lParam )
{
    LRESULT lRet=0;
    if(m_pCapturedFrame)
    {
        lRet=m_pCapturedFrame->DoFrameEvent(uMsg,wParam,lParam);
        SetMsgHandled(m_pCapturedFrame->IsMsgHandled());
    }
    else if(m_iSelItem!=-1)
    {
        if(!IsVirtual())
        {
            lRet=m_arrItems[m_iSelItem]->DoFrameEvent(uMsg,wParam,lParam);
            SetMsgHandled(m_arrItems[m_iSelItem]->IsMsgHandled());
        }else
        {
            m_pTemplPanel->DoFrameEvent(uMsg,wParam,lParam);
            SetMsgHandled(m_pTemplPanel->IsMsgHandled());
        }
    }else
    {
        SetMsgHandled(FALSE);
    }
    return lRet;
}

//ͬ����SItemPanel�е�index���ԣ���ִ���˲��룬ɾ���Ȳ�����ʹ��
void SListBoxEx::UpdatePanelsIndex(UINT nFirst,UINT nLast)
{
    if(IsVirtual()) return;
    for(UINT i=nFirst;i<m_arrItems.GetCount() && i<nLast;i++)
    {
        m_arrItems[i]->SetItemIndex(i);
    }
}

void SListBoxEx::OnSetDuiFocus()
{
    __super::OnSetDuiFocus();
    if(IsVirtual())
    {
        m_pTemplPanel->DoFrameEvent(WM_SETFOCUS,0,0);
    }else
    {
        if(m_iSelItem!=-1) m_arrItems[m_iSelItem]->DoFrameEvent(WM_SETFOCUS,0,0);
    }
}

void SListBoxEx::OnKillDuiFocus()
{
    __super::OnKillDuiFocus();
    if(IsVirtual())
    {
        m_pTemplPanel->DoFrameEvent(WM_KILLFOCUS,0,0);
    }else
    {
        if(m_iSelItem!=-1) m_arrItems[m_iSelItem]->DoFrameEvent(WM_KILLFOCUS,0,0);
    }
    if(m_iSelItem!=-1) RedrawItem(m_iSelItem);
}

LRESULT SListBoxEx::OnNcCalcSize( BOOL bCalcValidRects, LPARAM lParam )
{
    LRESULT lRet=__super::OnNcCalcSize(bCalcValidRects,lParam);
    Relayout();
    return lRet;
}

void SListBoxEx::Relayout()
{
    if(IsVirtual())
    {
        DUIASSERT(m_pTemplPanel);
        m_pTemplPanel->Move(CRect(0,0,m_rcClient.Width(),m_nItemHei));
    }
    else
    {
        for(int i=0; i<GetItemCount(); i++)
            m_arrItems[i]->Move(CRect(0,0,m_rcClient.Width(),m_nItemHei));
    }

}

void SListBoxEx::OnViewOriginChanged( CPoint ptOld,CPoint ptNew )
{
    if(m_iSelItem!=-1 && GetContainer()->GetDuiFocus()==m_hSWnd)
    {//������Ҫ��������һ��ѡ���еĽ���״̬�����¹��λ��
        m_arrItems[m_iSelItem]->DoFrameEvent(WM_KILLFOCUS,0,0);
        m_arrItems[m_iSelItem]->DoFrameEvent(WM_SETFOCUS,0,0);
    }
}

BOOL SListBoxEx::OnMouseWheel( UINT nFlags, short zDelta, CPoint pt )
{
    return __super::OnMouseWheel(nFlags,zDelta,pt);
}
}//namespace SOUI