#include "souistd.h"
#include "core/SWnd.h"
#include "helper/color.h"

namespace SOUI
{
    typedef enum _PRSTATE{
        PRS_LOOKSTART=0,    //���ҿ�ʼ����
        PRS_DRAWING,        //������Ⱦ��
        PRS_MEETEND            //����ָ���Ľ�������
    } PRSTATE;

    BOOL _PaintRegion( IRenderTarget *pRT, IRegion *pRgn,SWindow *pWndCur,SWindow *pStart,SWindow *pEnd,PRSTATE & prState )
    {
        RECT rcWnd;
        pWndCur->GetRect(&rcWnd);
        if (!pWndCur->IsVisible(TRUE) || (!pRgn->IsEmpty() && !pRgn->RectInRegion(&rcWnd)))
        {
            return FALSE;
        }
        if(prState == PRS_DRAWING && pWndCur == pEnd)
        {
            prState=PRS_MEETEND;
        }

        if(prState == PRS_MEETEND)
        {
            return FALSE;
        }

        if(prState == PRS_LOOKSTART && pWndCur==pStart)
        {
            prState=PRS_DRAWING;//��ʼ���л���
        }

        PRSTATE prsBack=prState;    //���浱ǰ�Ļ���״̬,�ڵݹ������������״̬���ж��Ƿ���Ҫ���Ʒǿͻ���

        CRect rcClient;
        pWndCur->GetClient(&rcClient);
        if(pRgn->IsEmpty() || pRgn->RectInRegion(rcClient))
        {//�ػ�ͻ���
            CRgn rgnOldClip;
            if(prsBack == PRS_DRAWING)
            {
                if(pWndCur->IsClipClient())
                {
                    pRT->PushClipRect(&rcClient);
                }
                pWndCur->SendSwndMessage(WM_ERASEBKGND, (WPARAM)pRT);
                pWndCur->SendSwndMessage(WM_PAINT, (WPARAM)pRT);
            }

            SPainter painter;

            pWndCur->BeforePaint(pRT, painter);    //���Ӵ��ڼ̳и����ڵ�����

            SWindow *pChild=pWndCur->GetWindow(GSW_FIRSTCHILD);
            while(pChild)
            {
                if(pChild==pEnd) break;
                _PaintRegion(pRT,pRgn,pChild,pStart,pEnd,prState);
                if(prState == PRS_MEETEND)
                    break;
                pChild=pChild->GetWindow(GSW_NEXTSIBLING);
            }

            pWndCur->AfterPaint(pRT, painter);
            if(prsBack == PRS_DRAWING && pWndCur->IsClipClient())
            {
                pRT->PopClip();
            }
        }
        if(prsBack == PRS_DRAWING) 
            pWndCur->SendSwndMessage(WM_NCPAINT, (WPARAM)pRT);//ncpaint should be placed in tail of paint link

        return prState==PRS_DRAWING || prState == PRS_MEETEND;
    }
    
//////////////////////////////////////////////////////////////////////////
// SWindow Implement
//////////////////////////////////////////////////////////////////////////

SWindow::SWindow()
    : m_hSWnd(SWindowMgr::NewWindow(this))
    , m_nID(0)
    , m_pContainer(NULL)
    , m_pParent(NULL),m_pFirstChild(NULL),m_pLastChild(NULL),m_pNextSibling(NULL),m_pPrevSibling(NULL)
    , m_nChildrenCount(0)
    , m_dwState(WndState_Normal)
    , m_bMsgTransparent(FALSE)
    , m_bVisible(TRUE)
    , m_bDisplay(TRUE)
    , m_bDisable(FALSE)
    , m_nSepSpace(2)
    , m_nMaxWidth(-1)
    , m_bUpdateLocked(FALSE)
    , m_bClipClient(FALSE)
    , m_bTabStop(FALSE)
    , m_uData(0)
    , m_pOwner(NULL)
    , m_pCurMsg(NULL)
    , m_pBgSkin(NULL)
    , m_pNcSkin(NULL)
    , m_bClipRT(FALSE)
    , m_gdcFlags(-1)
    , m_byAlpha(0xFF)
#ifdef _DEBUG
    , m_nMainThreadId( ::GetCurrentThreadId() ) // ��ʼ��������̲߳�һ�������߳�
#endif
{
    ClearLayoutState();
    m_evtSet.addEvent(EventCmd::EventID);
}

SWindow::~SWindow()
{
    SWindowMgr::DestroyWindow(m_hSWnd);
}


// Get align
UINT SWindow::GetTextAlign()
{
    return m_style.GetTextAlign() ;
}

// Get position type
DWORD SWindow::GetPositionType()
{
    return m_dlgpos.uPositionType;
}

// Set position type
void SWindow::SetPositionType(DWORD dwPosType, DWORD dwMask /*= 0xFFFFFFFF*/)
{
    m_dlgpos.uPositionType = (m_dlgpos.uPositionType & ~dwMask) | (dwPosType & dwMask);
}

// Get SWindow rect(position in container)
void SWindow::GetRect(LPRECT prect)
{
    ASSERT(prect);
    prect->left     = m_rcWindow.left;
    prect->top      = m_rcWindow.top;
    if(m_bDisplay || m_bVisible)
    {
        prect->right    = m_rcWindow.right;
        prect->bottom   = m_rcWindow.bottom;
    }else
    {
        prect->right=prect->left;
        prect->bottom=prect->top;
    }
}

void SWindow::GetClient(LPRECT pRect)
{
    ASSERT(pRect);
    *pRect=m_rcWindow;
    pRect->left+=m_style.m_nMarginX;
    pRect->right-=m_style.m_nMarginX;
    pRect->top+=m_style.m_nMarginY;
    pRect->bottom-=m_style.m_nMarginY;
}

void SWindow::GetDlgPosition(SWND_POSITION *pPos)
{
    if (pPos)
        memcpy(pPos, &m_dlgpos, sizeof(SWND_POSITION));
}

// Get inner text
SStringT SWindow::GetWindowText()
{
    return m_strText;
}

// Get tooltip text
BOOL SWindow::OnUpdateToolTip(SWND hCurTipHost,SWND &hNewTipHost,CRect &rcTip,SStringT &strTip)
{
    if(m_hSWnd==hCurTipHost) return FALSE;
    hNewTipHost=m_hSWnd;
    GetRect(&rcTip);
    strTip=m_strToolTipText;
    return TRUE;
}

BOOL SWindow::SetWindowText(LPCTSTR lpszText)
{
    m_strText = lpszText;
    if(IsVisible(TRUE)) Invalidate();
    if ((m_dlgpos.uPositionType & (SizeX_FitContent | SizeY_FitContent)) && (4 != m_dlgpos.nCount))
    {
        OnWindowPosChanged(NULL);
        if(IsVisible(TRUE)) Invalidate();
    }
    return TRUE;
}

void SWindow::TestMainThread()
{
#ifdef DEBUG
    // ���㿴�����������ʱ���Ҳ��ҵĸ����㣬��������߳���ˢ����
    // ����һ����Σ�յ�����
    DWORD dwCurThreadID = GetCurrentThreadId();

    BOOL bOK = (m_nMainThreadId == dwCurThreadID); // ��ǰ�̺߳͹������ʱ���߳�һ��

    ASSERT(bOK);
#endif
}


// Send a message to SWindow
LRESULT SWindow::SendSwndMessage(UINT Msg, WPARAM wParam /*= 0*/, LPARAM lParam /*= 0*/,BOOL *pbMsgHandled/*=NULL*/)
{
    LRESULT lResult = 0;

    if ( Msg < WM_USER
            && Msg != WM_DESTROY
            && Msg != WM_CLOSE
       )
    {
        TestMainThread();
    }
    AddRef();
    SWNDMSG msgCur= {Msg,wParam,lParam};
    SWNDMSG *pOldMsg=m_pCurMsg;
    m_pCurMsg=&msgCur;

    BOOL bOldMsgHandle=IsMsgHandled();//������һ����Ϣ�Ĵ���״̬

    SetMsgHandled(FALSE);

    ProcessSwndMessage(Msg, wParam, lParam, lResult);

    if(pbMsgHandled) *pbMsgHandled=IsMsgHandled();

    SetMsgHandled(bOldMsgHandle);//�ָ���һ����Ϣ�Ĵ���״̬

    m_pCurMsg=pOldMsg;
    Release();
    return lResult;
}

// Move SWindow to new place
//
void SWindow::Move(LPRECT prect)
{
    ASSERT(prect);
    TestMainThread();

    if(m_rcWindow.EqualRect(prect)) return;

    m_rcWindow = prect;
    m_dlgpos.uPositionType = (m_dlgpos.uPositionType & ~Position_Mask)|Pos_Float;//ʹ��Move�󣬳������Զ����㴰������
    OnWindowPosChanged(NULL);
}

void SWindow::Move(int x,int y, int cx/*=-1*/,int cy/*=-1*/)
{
    if(cx==-1) cx=m_rcWindow.Width();
    if(cy==-1) cy=m_rcWindow.Height();
    CRect rcNew(x,y,x+cx,y+cy);
    Move(&rcNew);
}

// Set current cursor, when hover
BOOL SWindow::OnSetCursor(const CPoint &pt)
{
    HCURSOR hCur = ::LoadCursor(NULL, m_style.m_lpCursorName);
    ::SetCursor(hCur);
    return TRUE;
}

// Get SWindow state
DWORD SWindow::GetState(void)
{
    return m_dwState;
}

// Modify SWindow state
DWORD SWindow::ModifyState(DWORD dwStateAdd, DWORD dwStateRemove,BOOL bUpdate/*=FALSE*/)
{
    DWORD dwOldState = m_dwState;

    TestMainThread();

    m_dwState &= ~dwStateRemove;
    m_dwState |= dwStateAdd;

    OnStateChanged(dwOldState,m_dwState);
    if(bUpdate && NeedRedrawWhenStateChange()) InvalidateRect(m_rcWindow);
    return dwOldState;
}

ULONG_PTR SWindow::GetUserData()
{
    return m_uData;
}

ULONG_PTR SWindow::SetUserData(ULONG_PTR uData)
{
    ULONG_PTR uOld=m_uData;
    m_uData=uData;
    return uOld;
}

BOOL SWindow::SetTimer(char id,UINT uElapse)
{
    STimerID timerID(m_hSWnd,id);
    return ::SetTimer(GetContainer()->GetHostHwnd(),DWORD(timerID),uElapse,NULL);
}

void SWindow::KillTimer(char id)
{
    STimerID timerID(m_hSWnd,id);
    ::KillTimer(GetContainer()->GetHostHwnd(),DWORD(timerID));
}


BOOL SWindow::SetTimer2( UINT_PTR id,UINT uElapse )
{
    return STimer2::SetTimer(m_hSWnd,id,uElapse);
}

void SWindow::KillTimer2( UINT_PTR id )
{
    STimer2::KillTimer(m_hSWnd,id);
}

SWND SWindow::GetSwnd()
{
    return m_hSWnd;
}


SWindow *SWindow::GetParent()
{
    return m_pParent;
}


SWindow * SWindow::GetTopLevelParent()
{
    SWindow *pParent=this;
    while(pParent->GetParent()) pParent=pParent->GetParent();
    return pParent;
}

void SWindow::SetParent(SWindow *pParent)
{
    if(m_pParent)
    {
        m_pParent->RemoveChild(this);
        m_pParent=NULL;
    }
    m_pParent=pParent;
    //����Parent��״̬����ʼ���Լ���״̬
    if(!m_pParent) return;
    m_pParent->InsertChild(this);
    if(m_pParent->IsVisible(TRUE) && m_bVisible)
        ModifyState(0,WndState_Invisible);
    else
        ModifyState(WndState_Invisible,0);
}

BOOL SWindow::DestroyChild(SWindow *pChild)
{
    if(this != pChild->GetParent()) return FALSE;
    pChild->Invalidate();
    pChild->SendSwndMessage(WM_DESTROY);
    RemoveChild(pChild);
    pChild->Release();
    return TRUE;
}

UINT SWindow::GetChildrenCount()
{
    return m_nChildrenCount;
}

SWindow * SWindow::GetChild(int nID)
{
    SWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        if(pChild->GetID()==nID) return pChild;
        pChild=pChild->m_pNextSibling;
    }
    return NULL;
}

void SWindow::SetChildContainer(SWindow *pChild)
{
    pChild->SetContainer(GetContainer());
}

void SWindow::InsertChild(SWindow *pNewChild,SWindow *pInsertAfter/*=ICWND_LAST*/)
{
    pNewChild->m_pParent=this;
    pNewChild->m_pPrevSibling=pNewChild->m_pNextSibling=NULL;
    SetChildContainer(pNewChild);

    if(pInsertAfter==m_pLastChild) pInsertAfter=ICWND_LAST;

    if(pInsertAfter==ICWND_LAST)
    {
        //insert window at head
        pNewChild->m_pPrevSibling=m_pLastChild;
        if(m_pLastChild) m_pLastChild->m_pNextSibling=pNewChild;
        else m_pFirstChild=pNewChild;
        m_pLastChild=pNewChild;
    }
    else if(pInsertAfter==ICWND_FIRST)
    {
        //insert window at tail
        pNewChild->m_pNextSibling=m_pFirstChild;
        if(m_pFirstChild) m_pFirstChild->m_pPrevSibling=pNewChild;
        else m_pLastChild=pNewChild;
        m_pFirstChild=pNewChild;
    }
    else
    {
        //insert window at middle
        ASSERT(pInsertAfter->m_pParent == this);
        ASSERT(m_pFirstChild && m_pLastChild);
        SWindow *pNext=pInsertAfter->m_pNextSibling;
        ASSERT(pNext);
        pInsertAfter->m_pNextSibling=pNewChild;
        pNewChild->m_pPrevSibling=pInsertAfter;
        pNewChild->m_pNextSibling=pNext;
        pNext->m_pPrevSibling=pNewChild;
    }
    m_nChildrenCount++;
}

BOOL SWindow::RemoveChild(SWindow *pChild)
{
    if(this != pChild->GetParent()) return FALSE;
    SWindow *pPrevSib=pChild->m_pPrevSibling;
    SWindow *pNextSib=pChild->m_pNextSibling;
    if(pPrevSib) pPrevSib->m_pNextSibling=pNextSib;
    else m_pFirstChild=pNextSib;
    if(pNextSib) pNextSib->m_pPrevSibling=pPrevSib;
    else m_pLastChild=pPrevSib;
    pChild->m_pParent=NULL;
    m_nChildrenCount--;
    return TRUE;
}

BOOL SWindow::IsChecked()
{
    return WndState_Check == (m_dwState & WndState_Check);
}

BOOL SWindow::IsDisabled(BOOL bCheckParent /*= FALSE*/)
{
    if(bCheckParent) return m_dwState & WndState_Disable;
    else return m_bDisable;
}

BOOL SWindow::IsVisible(BOOL bCheckParent /*= FALSE*/)
{
    if(bCheckParent) return (0 == (m_dwState & WndState_Invisible));
    else return m_bVisible;
}

//��ΪNotifyInvalidateRectֻ�д��ڿɼ�ʱ��֪ͨˢ�£������ڴ��ڿɼ�״̬�ı�ǰ��ִ��һ��֪ͨ��
void SWindow::SetVisible(BOOL bVisible,BOOL bUpdate/*=FALSE*/)
{
    if(bUpdate) InvalidateRect(m_rcWindow);
    SendSwndMessage(WM_SHOWWINDOW,bVisible);
    if(bUpdate) InvalidateRect(m_rcWindow);
}

void SWindow::EnableWindow( BOOL bEnable,BOOL bUpdate)
{
    SendSwndMessage(WM_ENABLE,bEnable);
    if(bUpdate) InvalidateRect(m_rcWindow);
}

void SWindow::SetCheck(BOOL bCheck)
{
    if (bCheck)
        ModifyState(WndState_Check, 0,TRUE);
    else
        ModifyState(0, WndState_Check,TRUE);
}

BOOL SWindow::NeedRedrawParent()
{
    return (GetContainer()->IsTranslucent() || !m_pBgSkin || (m_style.m_crBg == CR_INVALID));
}


LPCTSTR SWindow::GetLinkUrl()
{
    return m_strLinkUrl;
}

ISwndContainer *SWindow::GetContainer()
{
    return m_pContainer;
}

void SWindow::SetContainer(ISwndContainer *pContainer)
{
    m_pContainer=pContainer;
    SWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        pChild->SetContainer(pContainer);
        pChild=pChild->m_pNextSibling;
    }
}

void SWindow::SetOwner(SWindow *pOwner)
{
    m_pOwner=pOwner;
}

SWindow *SWindow::GetOwner()
{
    return m_pOwner;
}

BOOL SWindow::IsMsgTransparent()
{
    return m_bMsgTransparent;
}

// add by dummyz@126.com
SwndStyle& SWindow::GetStyle()
{
    return m_style;
}


SWindow* SWindow::FindChildByID(int id)
{
    SWindow *pChild = m_pFirstChild;
    while(pChild)
    {
        if (pChild->GetID() == id)
            return pChild;
        SWindow *pChildFind=pChild->FindChildByID(id);
        if(pChildFind) return pChildFind;
        pChild=pChild->m_pNextSibling;
    }
    return NULL;
}

SWindow* SWindow::FindChildByName( LPCWSTR pszName )
{
    if(!pszName) return NULL;

    SWindow *pChild = m_pFirstChild;
    while(pChild)
    {
        if (!pChild->m_strName.IsEmpty() && wcscmp(pChild->m_strName, pszName)==0)
            return pChild;
        SWindow *pChildFind=pChild->FindChildByName(pszName);
        if(pChildFind) return pChildFind;
        pChild=pChild->m_pNextSibling;
    }
    return NULL;
}

BOOL SWindow::CreateChildren(pugi::xml_node xmlNode)
{
    for (pugi::xml_node xmlChild=xmlNode.first_child(); xmlChild; xmlChild=xmlChild.next_sibling())
    {
        if(xmlChild.type() != pugi::node_element) continue;
        SWindow *pChild = SApplication::getSingleton().CreateWindowByName(xmlChild.name());
        if(!pChild)
        {//�ڴ��ڲ�����֧��include��ǩ
            if(_wcsicmp(xmlChild.name(),L"include")==0)
            {
                pugi::xml_document xmlDoc;
                SStringT strName=S_CW2T(xmlChild.attribute(L"src").value());
                if(LOADXML(xmlDoc,strName,RT_LAYOUT))
                {
                    CreateChildren(xmlDoc);
                }else
                {
                    ASSERT(FALSE);
                }

            }
            continue;
        }

        InsertChild(pChild);
        pChild->InitFromXml(xmlChild);
    }
    return TRUE;
}


SStringW SWindow::tr( const SStringW &strSrc )
{
    if(m_strName.IsEmpty()) return TR(strSrc,GetContainer()->GetHostName());
    else return TR(strSrc,m_strName);
}

// Create SWindow from xml element
BOOL SWindow::InitFromXml(pugi::xml_node xmlNode)
{
    ASSERT(m_pContainer);
    if (!xmlNode)
    {
        return FALSE;
    }

    m_strText = S_CW2T(tr(xmlNode.text().get()));   //ʹ�����԰����롣

    if (!m_strText.IsEmpty())
    {
        m_strText.TrimRight(0x0a).TrimLeft(0x0a);
        m_strText.TrimRight(0x0d).TrimLeft(0x0d);
        m_strText.TrimRight(0x20).TrimLeft(0x20);
        if (!m_strText.IsEmpty()) BUILDSTRING(m_strText);
    }

    m_dlgpos.nCount = 0;
    m_dlgpos.uPositionType = 0;
    SObject::InitFromXml(xmlNode);

    //����style��ָ����Ƥ�����ԣ�����Ƥ����owner���ԣ���styleû��owner���ԣ������Ҫ�����Լ�����ɺ��ѯƤ�����Ʋ����� hjx:2012.1.15
    if(m_pBgSkin==NULL && !m_style.m_strSkinName.IsEmpty())
        m_pBgSkin=GETSKIN(m_style.m_strSkinName);
    if(m_pNcSkin==NULL && !m_style.m_strNcSkinName.IsEmpty())
        m_pNcSkin=GETSKIN(m_style.m_strNcSkinName);

    if(!m_bVisible || (m_pParent && !m_pParent->IsVisible(TRUE)))
        ModifyState(WndState_Invisible, 0);

    if (4 != m_dlgpos.nCount)
    {
        SStringW strValue = xmlNode.attribute(L"width").value();
        int nValue =_wtoi(strValue);

        if (0 == nValue && L"full" == strValue && 0 == m_dlgpos.nCount)
        {
            m_rcWindow.right = 0;
            m_dlgpos.uPositionType = (m_dlgpos.uPositionType & ~SizeX_Mask) | SizeX_FitParent;
        }
        else
        {
            if (nValue > 0)
            {
                m_rcWindow.right = nValue;
                m_dlgpos.uSpecifyWidth = nValue;
                m_dlgpos.uPositionType = (m_dlgpos.uPositionType & ~SizeX_Mask) | SizeX_Specify;
            }
            else
            {
                m_rcWindow.right = 0;
                m_dlgpos.uPositionType = (m_dlgpos.uPositionType & ~SizeX_Mask) | SizeX_FitContent;
            }
        }

        strValue = xmlNode.attribute(L"height").value();
        nValue =_wtoi(strValue);
        if (0 == nValue && L"full" == strValue)
        {
            m_rcWindow.bottom = 0;
            m_dlgpos.uPositionType = (m_dlgpos.uPositionType & ~SizeY_Mask) | SizeY_FitParent;
        }
        else
        {
            if (nValue > 0)
            {
                m_rcWindow.bottom = nValue;
                m_dlgpos.uSpecifyHeight = nValue;
                m_dlgpos.uPositionType = (m_dlgpos.uPositionType & ~SizeY_Mask) | SizeY_Specify;
            }
            else
            {
                m_rcWindow.bottom = 0;
                m_dlgpos.uPositionType = (m_dlgpos.uPositionType & ~SizeY_Mask) | SizeY_FitContent;
            }
        }

    }

    if(0!=SendSwndMessage(WM_CREATE))
    {
        if(m_pParent)    m_pParent->DestroyChild(this);
        return FALSE;
    }
    CreateChildren(xmlNode);
    return TRUE;
}

SWindow * SWindow::CreateChildren(LPCWSTR pszXml)
{
    pugi::xml_document xmlDoc;
    if(!xmlDoc.load_buffer(pszXml,wcslen(pszXml),pugi::parse_default,pugi::encoding_utf16)) return NULL;
    SWindow * pLastChild=m_pLastChild;//���浱ǰ�����һ���Ӵ���
    BOOL bLoaded=CreateChildren(xmlDoc);
    if(!bLoaded) return NULL;
    OnWindowPosChanged(NULL);
    return m_pLastChild;
}

// Hittest children
SWND SWindow::SwndFromPoint(CPoint ptHitTest, BOOL bOnlyText)
{
    if (!m_rcWindow.PtInRect(ptHitTest)) return NULL;

    CRect rcClient;
    GetClient(&rcClient);

    if(!rcClient.PtInRect(ptHitTest))
        return m_hSWnd;    //ֻ�����λ�ڿͻ���ʱ���ż��������Ӵ���
    
    SWND swndChild = NULL;

    SWindow *pChild=m_pLastChild;
    while(pChild)
    {
        if (pChild->IsVisible(TRUE) && !pChild->IsMsgTransparent())
        {
            swndChild = pChild->SwndFromPoint(ptHitTest, bOnlyText);

            if (swndChild) return swndChild;
        }

        pChild=pChild->m_pPrevSibling;
    }

    return m_hSWnd;
}

BOOL SWindow::NeedRedrawWhenStateChange()
{
    if (m_pBgSkin && !m_pBgSkin->IgnoreState())
    {
        return TRUE;
    }
    return m_style.GetStates()>1;
}

BOOL SWindow::RedrawRegion(IRenderTarget *pRT, IRegion *pRgn)
{
    PRSTATE prState=PRS_LOOKSTART;
    return _PaintRegion(pRT,pRgn,this,this,NULL,prState);
}

void SWindow::Invalidate()
{
    CRect rcClient;
    GetClient(&rcClient);
    InvalidateRect(rcClient);
}

void SWindow::InvalidateRect(LPRECT lprect)
{
    if (lprect)
    {
        CRect rect = *lprect;
        InvalidateRect(rect);
    }
}

void SWindow::InvalidateRect(const CRect& rect)
{
    if(!IsVisible(TRUE)) return ;
    BOOL bUpdateLocked=FALSE;
    SWindow *pWnd=this;
    while(pWnd && !bUpdateLocked)
    {
        bUpdateLocked=pWnd->IsUpdateLocked();
        pWnd=pWnd->GetParent();
    }
    if (!bUpdateLocked)
    {
        GetContainer()->OnRedraw(rect);
    }
}

void SWindow::LockUpdate()
{
    m_bUpdateLocked=TRUE;
}

void SWindow::UnlockUpdate()
{
    m_bUpdateLocked=FALSE;
}

BOOL SWindow::IsUpdateLocked()
{
    return m_bUpdateLocked;
}

void SWindow::BringWindowToTop()
{
    SWindow *pParent=GetParent();
    if(!pParent) return;
    pParent->RemoveChild(this);
    pParent->InsertChild(this);
}

BOOL SWindow::FireEvent(EventArgs &evt)
{
    m_evtSet.FireEvent(evt);
    if(evt.handled != 0) return TRUE;

    if(GetOwner()) return GetOwner()->FireEvent(evt);
    return GetContainer()->OnFireEvent(evt);
}

LRESULT SWindow::OnWindowPosChanged(LPRECT lpRcContainer)
{
    LRESULT lRet=0;
    if(!(m_dlgpos.uPositionType & Pos_Float))    
    {//���ڲ���ʹ��Moveֱ��ָ��������,���������λ��
        lRet=SwndLayout::CalcPosition(this,lpRcContainer,m_dlgpos,m_rcWindow);
    }
    if(lRet==0)
    {
        SendSwndMessage(WM_NCCALCSIZE);//����ǿͻ�����С

        CRect rcClient;
        GetClient(&rcClient);
        SendSwndMessage(WM_SIZE,0,MAKELPARAM(rcClient.Width(),rcClient.Height()));

        UpdateChildrenPosition();
    }
    return lRet;
}

int SWindow::OnCreate( LPVOID )
{
    return 0;
}

void SWindow::OnDestroy()
{
    //destroy children windows
    SWindow *pChild=m_pFirstChild;
    while (pChild)
    {
        SWindow *pNextChild=pChild->m_pNextSibling;
        pChild->SendSwndMessage(WM_DESTROY);
        pChild->Release();

        pChild=pNextChild;
    }
    m_pFirstChild=m_pLastChild=NULL;
    m_nChildrenCount=0;
}

// Draw background default
BOOL SWindow::OnEraseBkgnd(IRenderTarget *pRT)
{
    CRect rcClient;
    GetClient(&rcClient);
    if (!m_pBgSkin)
    {
        COLORREF crBg = m_style.m_crBg;

        if (CR_INVALID != crBg)
        {
            pRT->FillSolidRect(&rcClient,crBg);
        }
    }
    else
    {
        int nState=0;
        
        if(GetState()&WndState_Disable)
        {
            nState=3;
        }
        else if(GetState()&WndState_Check || GetState()&WndState_PushDown)
        {
            nState=2;
        }else if(GetState()&WndState_Hover)
        {
            nState=1;
        }
        if(nState>=m_pBgSkin->GetStates()) nState=0;
        m_pBgSkin->Draw(pRT, rcClient, nState,m_byAlpha); 
    }
    return TRUE;
}

void SWindow::BeforePaint(IRenderTarget *pRT, SPainter &painter)
{
    IFontPtr pFont = m_style.GetTextFont(IIF_STATE4(m_dwState,0,1,2,3));
    if(pFont) 
        pRT->SelectObject(pFont,(IRenderObj**)&painter.pOldPen);
    
    COLORREF crTxt = m_style.GetTextColor(IIF_STATE4(m_dwState,0,1,2,3));
    if(crTxt != CR_INVALID)
        painter.crOld = pRT->SetTextColor(crTxt);
}

void SWindow::BeforePaintEx(IRenderTarget *pRT)
{
    SWindow *pParent=GetParent();
    if(pParent) pParent->BeforePaintEx(pRT);
    SPainter painter;
    BeforePaint(pRT,painter);
    //todo:hjx
}

void SWindow::AfterPaint(IRenderTarget *pRT, SPainter &painter)
{
    if(painter.pOldPen) pRT->SelectObject(painter.pOldPen);
    if(painter.crOld!=CR_INVALID) pRT->SetTextColor(painter.crOld);
}

// Draw inner text default and focus rect
void SWindow::OnPaint(IRenderTarget *pRT)
{
    SPainter painter;

    BeforePaint(pRT, painter);

    CRect rcText;
    GetTextRect(rcText);
    DrawText(pRT,m_strText, m_strText.GetLength(), rcText, GetTextAlign());

    //draw focus rect
    if(GetContainer()->SwndGetFocus()==m_hSWnd)
    {
        DrawFocus(pRT);
    }

    AfterPaint(pRT, painter);
}

void SWindow::OnNcPaint(IRenderTarget *pRT)
{
    if(m_style.m_nMarginX!=0 || m_style.m_nMarginY!=0)
    {
        BOOL bGetRT = pRT==0;
        if(bGetRT) pRT=GetRenderTarget(&m_rcWindow,OLEDC_OFFSCREEN,FALSE);//���Զ�������

        CRect rcClient;
        SWindow::GetClient(&rcClient);
        pRT->SaveClip(NULL);
        pRT->ExcludeClipRect(&rcClient);

        if(bGetRT) PaintBackground(pRT,&m_rcWindow);

        int nState=0;
        if(WndState_Hover & m_dwState) nState=1;
        if(m_pNcSkin)
        {
            if(nState>=m_pNcSkin->GetStates()) nState=0;
            m_pNcSkin->Draw(pRT,m_rcWindow,nState,m_byAlpha);
        }
        else
        {
            COLORREF crBg = m_style.m_crBorder;
            if (CR_INVALID != crBg)
            {
                pRT->FillSolidRect(&m_rcWindow,crBg);
            }
        }
        if(bGetRT) PaintForeground(pRT,&m_rcWindow);
        pRT->PopClip();
        if(bGetRT) ReleaseRenderTarget(pRT);
    }
}

CSize SWindow::CalcSize(LPRECT pRcContainer)
{
    CSize sz;
    if(m_dlgpos.uPositionType & SizeX_Specify)
        sz.cx=m_dlgpos.uSpecifyWidth;
    else if(m_dlgpos.uPositionType & SizeX_FitParent)
        sz.cx=pRcContainer->right-pRcContainer->left;
    if(m_dlgpos.uPositionType & SizeY_Specify)
        sz.cy=m_dlgpos.uSpecifyHeight;
    else if(m_dlgpos.uPositionType & SizeY_FitParent)
        sz.cy=pRcContainer->bottom-pRcContainer->top;
    if((m_dlgpos.uPositionType & SizeX_FitContent) || (m_dlgpos.uPositionType & SizeY_FitContent) && m_dlgpos.nCount!=4)
    {
        CSize szDesire=GetDesiredSize(pRcContainer);    
        if(m_dlgpos.uPositionType & SizeX_FitContent)
            sz.cx=szDesire.cx;
        if(m_dlgpos.uPositionType & SizeY_FitContent)
            sz.cy=szDesire.cy;
    }
    return sz;
}


CSize SWindow::GetDesiredSize(LPRECT pRcContainer)
{
    ASSERT((m_dlgpos.uPositionType & SizeX_FitContent) || (m_dlgpos.uPositionType & SizeY_FitContent));


    int nTestDrawMode = GetTextAlign() & ~(DT_CENTER | DT_RIGHT | DT_VCENTER | DT_BOTTOM);

    CRect rcTest (0,0,0x7FFF,0x7FFF);
    if(m_nMaxWidth!=-1)
    {
        rcTest.right=m_nMaxWidth;
        nTestDrawMode|=DT_WORDBREAK;
    }
    
    CAutoRefPtr<IRenderTarget> pRT;
    GETRENDERFACTORY->CreateRenderTarget(&pRT,1,1);
    BeforePaintEx(pRT);
    DrawText(pRT,m_strText, m_strText.GetLength(), rcTest, nTestDrawMode | DT_CALCRECT);

    return rcTest.Size();
}

void SWindow::GetTextRect( LPRECT pRect )
{
    GetClient(pRect);
}

void SWindow::DrawText(IRenderTarget *pRT,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat)
{
    pRT->DrawText(pszBuf,cchText,pRect,uFormat,m_byAlpha);
}

void SWindow::DrawFocus(IRenderTarget *pRT)
{
    CRect rcFocus;
    GetTextRect(&rcFocus);
    if(IsTabStop())    DrawDefFocusRect(pRT,rcFocus);
}


void SWindow::DrawDefFocusRect(IRenderTarget *pRT,CRect rcFocus )
{
    rcFocus.DeflateRect(2,2);
    CAutoRefPtr<IPen> pPen,oldPen;
    pRT->CreatePen(PS_DOT,RGBA(88,88,88,m_byAlpha),1,&pPen);
    pRT->SelectObject(pPen,(IRenderObj**)&oldPen);
    pRT->DrawRectangle(&rcFocus);    
    pRT->SelectObject(oldPen);
}

UINT SWindow::OnGetDlgCode()
{
    return 0;
}

BOOL SWindow::IsTabStop()
{
    return m_bTabStop;
}

BOOL SWindow::OnDefKeyDown(UINT nChar, UINT nFlags)
{
    SWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        if(pChild->OnDefKeyDown(nChar,nFlags)) return TRUE;
        pChild=pChild->m_pNextSibling;
    }
    return FALSE;
}

void SWindow::OnShowWindow(BOOL bShow, UINT nStatus)
{
    if(nStatus == ParentShow)
    {
        if(bShow && !IsVisible(FALSE)) bShow=FALSE;
    }
    else
    {
        m_bVisible=bShow;
    }
    if(bShow && m_pParent)
    {
        bShow=m_pParent->IsVisible(TRUE);
    }

    if (bShow)
        ModifyState(0, WndState_Invisible);
    else
        ModifyState(WndState_Invisible, 0);

    SWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        pChild->SendSwndMessage(WM_SHOWWINDOW,bShow,ParentShow);
        pChild=pChild->GetWindow(GSW_NEXTSIBLING);
    }
    if(!IsVisible(TRUE) && m_hSWnd == GetContainer()->SwndGetFocus())
    {
        GetContainer()->OnSetSwndFocus(NULL);
    }

    if(!m_bDisplay)
    {
        SWindow *pParent=GetParent();
        if(pParent) pParent->UpdateChildrenPosition();
    }
}


void SWindow::OnEnable( BOOL bEnable,UINT nStatus )
{
    if(nStatus == ParentEnable)
    {
        if(bEnable && IsDisabled(FALSE)) bEnable=FALSE;
    }
    else
    {
        m_bDisable=!bEnable;
    }
    if(bEnable && m_pParent)
    {
        bEnable=!m_pParent->IsDisabled(TRUE);
    }

    if (bEnable)
        ModifyState(0, WndState_Disable);
    else
        ModifyState(WndState_Disable, WndState_Hover);

    SWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        pChild->SendSwndMessage(WM_ENABLE,bEnable,ParentEnable);
        pChild=pChild->GetWindow(GSW_NEXTSIBLING);
    }
    if(IsDisabled(TRUE) && m_hSWnd == GetContainer()->SwndGetFocus())
    {
        GetContainer()->OnSetSwndFocus(NULL);
    }
}

void SWindow::OnLButtonDown(UINT nFlags,CPoint pt)
{
    if(m_bTabStop) SetFocus();
    SetCapture();
    ModifyState(WndState_PushDown, 0,TRUE);
}

void SWindow::OnLButtonUp(UINT nFlags,CPoint pt)
{
    ReleaseCapture();
    if(!m_rcWindow.PtInRect(pt)) return;

    ModifyState(0, WndState_PushDown,TRUE);

    LPCTSTR lpszUrl = GetLinkUrl();
    if (lpszUrl && lpszUrl[0])
    {
        ::ShellExecute(NULL, _T("open"), lpszUrl, NULL, NULL, SW_SHOWNORMAL);
    }
    else if (GetID() || GetName())
    {
        FireCommand();
    }
}

void SWindow::OnRButtonDown( UINT nFlags, CPoint point )
{
    FireCtxMenu(point);
}

void SWindow::OnMouseHover(WPARAM wParam, CPoint ptPos)
{
    if(GetCapture()==m_hSWnd)
        ModifyState(WndState_PushDown,0,FALSE);
    ModifyState(WndState_Hover, 0,TRUE);
    OnNcPaint(0);
}

void SWindow::OnMouseLeave()
{
    if(GetCapture()==m_hSWnd)
        ModifyState(0,WndState_PushDown,FALSE);
    ModifyState(0,WndState_Hover,TRUE);
    OnNcPaint(0);
}

BOOL SWindow::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
    BOOL bRet=FALSE;
    if(m_pParent) bRet=(BOOL)m_pParent->SendSwndMessage(WM_MOUSEWHEEL,MAKEWPARAM(nFlags,zDelta),MAKELPARAM(pt.x,pt.y));
    return bRet;
}

HRESULT SWindow::OnAttrState( const SStringW& strValue, BOOL bLoading )
{
    int nState=0;
    ::StrToIntExW(strValue,STIF_SUPPORT_HEX,&nState);
    m_dwState=nState;
    if(m_dwState & WndState_Invisible) m_bVisible=FALSE;
    if(m_dwState & WndState_Disable) m_bDisable=TRUE;
    return S_FALSE;
}


HRESULT SWindow::OnAttrPos(const SStringW& strValue, BOOL bLoading)
{
    if (strValue.IsEmpty()) return E_FAIL;
    if(!bLoading) InvalidateRect(m_rcWindow);
    ClearLayoutState();
    SwndLayout::StrPos2SwndPos(strValue,m_dlgpos);
    if(!bLoading) OnWindowPosChanged(NULL);
    return S_FALSE;
}


CRect SWindow::GetChildrenLayoutRect()
{
    CRect rcRet;
    GetClient(rcRet);//ͨ���Ƿǿͻ���������tab�����Ŀؼ���һ����
    return rcRet;
}


void SWindow::ClearLayoutState()
{
    if(m_dlgpos.uPositionType & Pos_Float) return;

    m_rcWindow.left=m_rcWindow.top=m_rcWindow.right=m_rcWindow.bottom=POS_INIT;
}

void SWindow::UpdateChildrenPosition()
{
    SList<SWindow*> lstWnd;
    SWindow *pChild=GetWindow(GSW_FIRSTCHILD);
    while(pChild)
    {
        pChild->ClearLayoutState();
        lstWnd.AddTail(pChild);
        pChild=pChild->GetWindow(GSW_NEXTSIBLING);
    }
    SwndLayout::CalcChildrenPosition(this,&lstWnd);
    Invalidate();
}

void SWindow::OnSetFocus()
{
    InvalidateRect(m_rcWindow);
}

void SWindow::OnKillFocus()
{
    InvalidateRect(m_rcWindow);
}

IRenderTarget * SWindow::GetRenderTarget(const LPRECT pRc/*=NULL*/,DWORD gdcFlags/*=0*/,BOOL bClientDC/*=TRUE*/)
{
    ASSERT(m_gdcFlags==-1);
    if(bClientDC)
        GetClient(&m_rcGetRT);
    else
        m_rcGetRT=m_rcWindow;
    
    
    if(gdcFlags!=OLEDC_NODRAW)
    {//��DC�����ڸ����ڵĿɼ�����
        SWindow *pParent=GetParent();
        while(pParent)
        {
            CRect rcParent;
            pParent->GetClient(&rcParent);
            m_rcGetRT.IntersectRect(m_rcGetRT,rcParent);
            pParent=pParent->GetParent();
        }
    }

    m_gdcFlags=gdcFlags;
    m_bClipRT=FALSE;
    if(pRc)
    {
        m_rcGetRT.IntersectRect(pRc,&m_rcGetRT);
        m_bClipRT=!m_rcGetRT.EqualRect(pRc);
    }
    IRenderTarget *pRT=GetContainer()->OnGetRenderTarget(m_rcGetRT,gdcFlags);
    if(m_bClipRT)
    {
        pRT->PushClipRect(&m_rcGetRT,RGN_COPY);
    }
    if(gdcFlags&OLEDC_PAINTBKGND)
        PaintBackground(pRT,&m_rcGetRT);
        
    m_oldFont=pRT->GetCurrentObject(OT_FONT);
    m_oldColor=pRT->GetTextColor();
    //��ø������б�
    SList<SWindow*> lstParent;
    SWindow *pParent=GetParent();
    while(pParent)
    {
        lstParent.AddHead(pParent);
        pParent=pParent->GetParent();
    }
    POSITION pos=lstParent.GetHeadPosition();
    while(pos)
    {
        SWindow *pWnd=lstParent.GetNext(pos);
        SPainter painter;
        pWnd->BeforePaint(pRT,painter);
    }
    return pRT;
}

void SWindow::ReleaseRenderTarget(IRenderTarget *pRT)
{
    if(m_gdcFlags & OLEDC_PAINTBKGND) //���˱������Զ���ǰ��
        PaintForeground(pRT,&m_rcGetRT);
    if(m_bClipRT)
        pRT->PopClip();
    
    pRT->SelectObject(m_oldFont);
    pRT->SetTextColor(m_oldColor);
    m_oldFont=NULL;
    m_oldColor=CR_INVALID;
    
    GetContainer()->OnReleaseRenderTarget(pRT,m_rcGetRT,m_gdcFlags);
    
    m_bClipRT=FALSE;
    m_gdcFlags=-1;
}

SWND SWindow::GetCapture()
{
    return GetContainer()->OnGetSwndCapture();
}

SWND SWindow::SetCapture()
{
    return GetContainer()->OnSetSwndCapture(m_hSWnd);
}

BOOL SWindow::ReleaseCapture()
{
    return GetContainer()->OnReleaseSwndCapture();
}

void SWindow::SetFocus()
{
    GetContainer()->OnSetSwndFocus(m_hSWnd);
}

void SWindow::KillFocus()
{
    if(GetContainer()->SwndGetFocus()==m_hSWnd)
    {
        GetContainer()->OnSetSwndFocus(NULL);
    }
}

SWindow *SWindow::GetCheckedRadioButton()
{
    SWindow *pChild=m_pFirstChild;
    while(pChild)
    {
        if(pChild->IsClass(L"radio") && pChild->IsChecked())
        {
            return pChild;
        }
        pChild=pChild->m_pNextSibling;
    }
    return NULL;
}

void SWindow::CheckRadioButton(SWindow * pRadioBox)
{
    SWindow *pChecked=GetCheckedRadioButton();
    if(pChecked == pRadioBox) return;
    if(pChecked)
    {
        pChecked->ModifyState(0,WndState_Check,TRUE);
    }
    pRadioBox->ModifyState(WndState_Check,0,TRUE);
}


BOOL SWindow::SetItemVisible(UINT uItemID, BOOL bVisible)
{
    SWindow *pWnd = FindChildByID(uItemID);

    if (pWnd)
    {
        pWnd->SetVisible(bVisible,TRUE);
        return TRUE;
    }

    return FALSE;
}

BOOL SWindow::IsItemVisible(UINT uItemID, BOOL bCheckParent /*= FALSE*/)
{
    SWindow *pWnd = FindChildByID(uItemID);

    if (pWnd)
        return pWnd->IsVisible(bCheckParent);

    return FALSE;
}

BOOL SWindow::GetItemCheck(UINT uItemID)
{
    SWindow *pWnd = FindChildByID(uItemID);

    if (pWnd)
        return pWnd->IsChecked();

    return FALSE;
}

BOOL SWindow::SetItemCheck(UINT uItemID, BOOL bCheck)
{
    SWindow *pWnd = FindChildByID(uItemID);

    if (pWnd)
    {
        if (bCheck)
            pWnd->ModifyState(WndState_Check, 0);
        else
            pWnd->ModifyState(0, WndState_Check);

        pWnd->InvalidateRect(pWnd->m_rcWindow);

        return TRUE;
    }

    return FALSE;
}

BOOL SWindow::EnableItem(UINT uItemID, BOOL bEnable)
{
    SWindow *pWnd = FindChildByID(uItemID);

    if (pWnd)
    {
        if (bEnable)
            pWnd->ModifyState(0, WndState_Disable);
        else
            pWnd->ModifyState(WndState_Disable, WndState_Hover);

        pWnd->InvalidateRect(pWnd->m_rcWindow);
        return TRUE;
    }

    return FALSE;
}

BOOL SWindow::IsItemEnable(UINT uItemID, BOOL bCheckParent /*= FALSE*/)
{
    SWindow *pWnd = FindChildByID(uItemID);

    if (pWnd)
        return !pWnd->IsDisabled(bCheckParent);

    return FALSE;
}

BOOL SWindow::OnNcHitTest(CPoint pt)
{
    return FALSE;
}

SWindow * SWindow::GetWindow(int uCode)
{
    SWindow *pRet=NULL;
    switch(uCode)
    {
    case GSW_FIRSTCHILD:
        pRet=m_pFirstChild;
        break;
    case GSW_LASTCHILD:
        pRet=m_pLastChild;
        break;
    case GSW_PREVSIBLING:
        pRet=m_pPrevSibling;
        break;
    case GSW_NEXTSIBLING:
        pRet=m_pNextSibling;
        break;
    case GSW_OWNER:
        pRet=m_pOwner;
        break;
    case GSW_PARENT:
        pRet=m_pParent;
        break;
    }
    return pRet;
}


void SWindow::PaintBackground(IRenderTarget *pRT,LPRECT pRc )
{
    CRect rcDraw=m_rcWindow;
    if(pRc) rcDraw.IntersectRect(rcDraw,pRc);
    pRT->PushClipRect(&rcDraw);
    
    SWindow *pTopWnd=GetTopLevelParent();
    CAutoRefPtr<IRegion> pRgn;
    GETRENDERFACTORY->CreateRegion(&pRgn);
    pRgn->CombineRect(&rcDraw,RGN_COPY);
    
    pRT->FillSolidRect(&rcDraw,0);//���������alphaֵ
    PRSTATE prState=PRS_LOOKSTART;
    _PaintRegion(pRT,pRgn,pTopWnd,pTopWnd,this,prState);
    pRT->PopClip();
}

void SWindow::PaintForeground( IRenderTarget *pRT,LPRECT pRc )
{
    CRect rcDraw=m_rcWindow;
    if(pRc) rcDraw.IntersectRect(rcDraw,pRc);

    SWindow *pStart=GetNextVisibleWindow(this,rcDraw);

    if(pStart)
    {
        PRSTATE prState=PRS_LOOKSTART;
        CAutoRefPtr<IRegion> pRgn;
        GETRENDERFACTORY->CreateRegion(&pRgn);
        pRgn->CombineRect(&rcDraw,RGN_COPY);
        pRT->PushClipRect(&rcDraw);
        _PaintRegion(pRT,pRgn,this,pStart,NULL,prState);
        pRT->PopClip();
    }
}


SWindow * SWindow::GetNextVisibleWindow( SWindow *pWnd ,const CRect &rcDraw)
{
    if(!pWnd) return NULL;
    SWindow *pNextSibling=pWnd->GetWindow(GSW_NEXTSIBLING);
    if(pNextSibling && pNextSibling->IsVisible(TRUE) && !(pNextSibling->m_rcWindow & rcDraw).IsRectEmpty())
        return pNextSibling;
    else if (pNextSibling)    return GetNextVisibleWindow(pNextSibling,rcDraw);
    else return GetNextVisibleWindow(pWnd->GetParent(),rcDraw);
}

void SWindow::DrawAniStep( CRect rcFore,CRect rcBack,IRenderTarget * pRTFore,IRenderTarget * pRTBack,CPoint ptAnchor)
{
    IRenderTarget * pRT=GetRenderTarget(rcBack,OLEDC_OFFSCREEN,FALSE);
    pRT->BitBlt(&rcBack,pRTBack,rcBack.left,rcBack.top,SRCCOPY);
    pRT->BitBlt(&rcFore,pRTFore,ptAnchor.x,ptAnchor.y,SRCCOPY);
    PaintForeground(pRT,rcBack);//��ǰ��
    ReleaseRenderTarget(pRT);
}

void SWindow::DrawAniStep( CRect rcWnd,IRenderTarget * pRTFore,IRenderTarget * pRTBack,BYTE byAlpha)
{
    IRenderTarget * pRT=GetRenderTarget(rcWnd,OLEDC_OFFSCREEN,FALSE);
    if(byAlpha>0 && byAlpha<255)
    {
        pRT->BitBlt(&rcWnd,pRTBack,rcWnd.left,rcWnd.top,SRCCOPY);
        IBitmap *pBmp = (IBitmap*)pRTFore->GetCurrentObject(OT_BITMAP);
        pRT->DrawBitmap(&rcWnd,pBmp,rcWnd.left,rcWnd.top,byAlpha);
    }else if(byAlpha==0)
    {
        pRT->BitBlt(&rcWnd,pRTBack,rcWnd.left,rcWnd.top,SRCCOPY);
    }else if(byAlpha==255)
    {
        pRT->BitBlt(&rcWnd,pRTFore,rcWnd.left,rcWnd.top,SRCCOPY);
    }
    PaintForeground(pRT,rcWnd);//��ǰ��
    ReleaseRenderTarget(pRT);
}

BOOL SWindow::AnimateWindow(DWORD dwTime,DWORD dwFlags )
{
    if(dwFlags & AW_HIDE)
    {
        if(!IsVisible(TRUE))
            return FALSE;
    }else
    {//������ʾ����ʱ����������㴰�ڣ�ͬʱ������һ�㴰��Ӧ�ÿɼ�
        if(IsVisible(TRUE))
            return FALSE;
        SWindow *pParent=GetParent();
        if(!pParent) return FALSE;
        if(!pParent->IsVisible(TRUE)) return FALSE;
    }
    CRect rcWnd;
    GetRect(&rcWnd);

    CAutoRefPtr<IRegion> rgn;
    GETRENDERFACTORY->CreateRegion(&rgn);
    rgn->CombineRect(&rcWnd,RGN_COPY);

    IRenderTarget *pRT=GetRenderTarget(rcWnd,OLEDC_NODRAW,FALSE);
    CAutoRefPtr<IRenderTarget> pRTBefore;
    GETRENDERFACTORY->CreateRenderTarget(&pRTBefore,rcWnd.Width(),rcWnd.Height());
    pRTBefore->OffsetViewportOrg(-rcWnd.left,-rcWnd.top);

    //��Ⱦ���ڱ仯ǰ״̬
    PaintBackground(pRT,rcWnd);
    RedrawRegion(pRT,rgn);
    pRTBefore->BitBlt(&rcWnd,pRT,rcWnd.left,rcWnd.top,SRCCOPY);
    
    //���´��ڿɼ���
    SetVisible(!(dwFlags&AW_HIDE),FALSE);
    //���ڱ仯��
    CAutoRefPtr<IRenderTarget> pRTAfter;
    GETRENDERFACTORY->CreateRenderTarget(&pRTAfter,rcWnd.Width(),rcWnd.Height());
    pRTAfter->OffsetViewportOrg(-rcWnd.left,-rcWnd.top);

    PaintBackground(pRT,rcWnd);
    RedrawRegion(pRT,rgn);
    pRTAfter->BitBlt(&rcWnd,pRT,rcWnd.left,rcWnd.top,SRCCOPY);

    ReleaseRenderTarget(pRT);

    int nSteps=dwTime/10;
    if(dwFlags & AW_HIDE)
    {//hide
        if(dwFlags& AW_SLIDE)
        {
            CRect rcNewState(rcWnd);
            LONG  x1 = rcNewState.left;
            LONG  x2 = rcNewState.left;
            LONG  y1 = rcNewState.top;
            LONG  y2 = rcNewState.top;
            LONG * x =&rcNewState.left;
            LONG * y =&rcNewState.top;

            if(dwFlags & AW_HOR_POSITIVE)
            {//left->right:move left
                x1=rcNewState.left,x2=rcNewState.right;
                x=&rcNewState.left;
            }else if(dwFlags & AW_HOR_NEGATIVE)
            {//right->left:move right
                x1=rcNewState.right,x2=rcNewState.left;
                x=&rcNewState.right;
            }
            if(dwFlags & AW_VER_POSITIVE)
            {//top->bottom
                y1=rcNewState.top,y2=rcNewState.bottom;
                y=&rcNewState.top;
            }else if(dwFlags & AW_VER_NEGATIVE)
            {//bottom->top
                y1=rcNewState.bottom,y2=rcNewState.top;
                y=&rcNewState.bottom;
            }
            LONG xStepLen=(x2-x1)/nSteps;
            LONG yStepLen=(y2-y1)/nSteps;

            CPoint ptAnchor;
            for(int i=0;i<nSteps;i++)
            {
                *x+=xStepLen;
                *y+=yStepLen;
                ptAnchor=rcWnd.TopLeft();
                if(dwFlags & AW_HOR_NEGATIVE)
                {//right->left:move right
                    ptAnchor.x=rcWnd.right-rcNewState.Width();
                }
                if(dwFlags & AW_VER_NEGATIVE)
                {
                    ptAnchor.y=rcWnd.bottom-rcNewState.Height();
                }
                DrawAniStep(rcNewState,rcWnd,pRTBefore,pRTAfter,ptAnchor);
                Sleep(10);
            }
            DrawAniStep(CRect(),rcWnd,pRTBefore,pRTAfter,rcWnd.TopLeft());
            return TRUE;
        }else if(dwFlags&AW_CENTER)
        {
            CRect rcNewState(rcWnd);
            int xStep=rcNewState.Width()/(2*nSteps);
            int yStep=rcNewState.Height()/(2*nSteps);
            for(int i=0;i<nSteps;i++)
            {
                rcNewState.DeflateRect(xStep,yStep);
                DrawAniStep(rcNewState,rcWnd,pRTBefore,pRTAfter,rcNewState.TopLeft());
                Sleep(10);
            }
            DrawAniStep(CRect(),rcWnd,pRTBefore,pRTAfter,rcWnd.TopLeft());
            return TRUE;
        }else if(dwFlags&AW_BLEND)
        {
            BYTE byAlpha=255;
            BYTE byStepLen=255/nSteps;
            for(int i=0;i<nSteps;i++)
            {
                DrawAniStep(rcWnd,pRTBefore,pRTAfter,byAlpha);
                Sleep(10);
                byAlpha-=byStepLen;
            }
            DrawAniStep(rcWnd,pRTBefore,pRTAfter,0);
            return TRUE;
        }
        return FALSE;
    }else
    {//show
        if(dwFlags& AW_SLIDE)
        {
            CRect rcNewState(rcWnd);
            LONG  x1 = rcNewState.left;
            LONG  x2 = rcNewState.left;
            LONG  y1 = rcNewState.top;
            LONG  y2 = rcNewState.top;
            LONG * x =&rcNewState.left;
            LONG * y =&rcNewState.top;

            if(dwFlags & AW_HOR_POSITIVE)
            {//left->right:move right
                x1=rcNewState.left,x2=rcNewState.right;
                rcNewState.right=rcNewState.left,x=&rcNewState.right;
            }else if(dwFlags & AW_HOR_NEGATIVE)
            {//right->left:move left
                x1=rcNewState.right,x2=rcNewState.left;
                rcNewState.left=rcNewState.right,x=&rcNewState.left;
            }
            if(dwFlags & AW_VER_POSITIVE)
            {//top->bottom
                y1=rcNewState.top,y2=rcNewState.bottom;
                rcNewState.bottom=rcNewState.top,y=&rcNewState.bottom;
            }else if(dwFlags & AW_VER_NEGATIVE)
            {//bottom->top
                y1=rcNewState.bottom,y2=rcNewState.top;
                rcNewState.top=rcNewState.bottom,y=&rcNewState.top;
            }
            LONG xStepLen=(x2-x1)/nSteps;
            LONG yStepLen=(y2-y1)/nSteps;

            CPoint ptAnchor;
            for(int i=0;i<nSteps;i++)
            {
                *x+=xStepLen;
                *y+=yStepLen;
                ptAnchor=rcWnd.TopLeft();
                if(dwFlags & AW_HOR_POSITIVE)
                {//left->right:move left
                    ptAnchor.x=rcWnd.right-rcNewState.Width();
                }
                if(dwFlags & AW_VER_POSITIVE)
                {
                    ptAnchor.y=rcWnd.bottom-rcNewState.Height();
                }
                DrawAniStep(rcNewState,rcWnd,pRTBefore,pRTAfter,ptAnchor);
                Sleep(10);
            }
            DrawAniStep(rcWnd,rcWnd,pRTBefore,pRTAfter,rcWnd.TopLeft());
            return TRUE;
        }else if(dwFlags&AW_CENTER)
        {
            CRect rcNewState(rcWnd);
            int xStep=rcNewState.Width()/(2*nSteps);
            int yStep=rcNewState.Height()/(2*nSteps);
            rcNewState.left=rcNewState.right=(rcNewState.left+rcNewState.right)/2;
            rcNewState.top=rcNewState.bottom=(rcNewState.top+rcNewState.bottom)/2;
            for(int i=0;i<nSteps;i++)
            {
                rcNewState.InflateRect(xStep,yStep);
                DrawAniStep(rcNewState,rcWnd,pRTBefore,pRTAfter,rcNewState.TopLeft());
                Sleep(10);
            }
            DrawAniStep(rcWnd,rcWnd,pRTBefore,pRTAfter,rcWnd.TopLeft());
            return TRUE;
        }else if(dwFlags&AW_BLEND)
        {
            BYTE byAlpha=0;
            BYTE byStepLen=255/nSteps;
            for(int i=0;i<nSteps;i++)
            {
                DrawAniStep(rcWnd,pRTBefore,pRTAfter,byAlpha);
                Sleep(10);
                byAlpha+=byStepLen;
            }
            DrawAniStep(rcWnd,pRTBefore,pRTAfter,255);
            return TRUE;
        }
        return FALSE;
    }
}

BOOL SWindow::FireCommand()
{
    EventCmd evt(this);
    return FireEvent(evt);
}

BOOL SWindow::FireCtxMenu( CPoint pt )
{
    EventCtxMenu evt(this);
    evt.pt=pt;
    FireEvent(evt);
    return evt.bCancel;
}

}//namespace SOUI
