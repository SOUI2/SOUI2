//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiItemPanel
// Description: A Framework wrapping frame to be used in a duiwindow.
//     Creator: Huang Jianxiong
//     Version: 2011.10.20 - 1.0 - Create
//////////////////////////////////////////////////////////////////////////

#pragma  once
#include "duistd.h"
#include "duiItempanel.h"

#include "duiwndnotify.h"

#pragma warning(disable:4018)

namespace SOUI
{


SItemPanel::SItemPanel(SWindow *pFrameHost,pugi::xml_node xmlNode,IItemContainer *pItemContainer)
    :CSwndContainer(this)
    ,m_pFrmHost(pFrameHost)
    ,m_pItemContainer(pItemContainer)
    ,m_dwData(0)
    ,m_crBk(CLR_INVALID)
    ,m_crSelBk(RGB(0,0,128))
    ,m_lpItemIndex(-1)
{
    ASSERT(m_pFrmHost);
    if(!m_pItemContainer) m_pItemContainer=dynamic_cast<IItemContainer*>(m_pFrmHost);
    ASSERT(m_pItemContainer);
    SetContainer(this);
    if(xmlNode) InitFromXml(xmlNode);
}

void SItemPanel::OnFinalRelease()
{
    AddRef();//��ֹ�ظ�����ú���
    DuiSendMessage(WM_DESTROY);
    __super::OnFinalRelease();
}

LRESULT SItemPanel::DoFrameEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
{
    AddRef();

    if(!IsDisabled() && m_pBgSkin && m_pBgSkin->GetStates()>1)
    {
        switch(uMsg)
        {
        case WM_MOUSEHOVER: 
            ModifyState(DuiWndState_Hover,0,TRUE);
            break;
        case WM_MOUSELEAVE: 
            ModifyState(0,DuiWndState_Hover,TRUE);
            break;
        }
    }

    SetMsgHandled(FALSE);
    LRESULT lRet=__super::DoFrameEvent(uMsg,wParam,lParam);
    if(IsMsgHandled())
    {
        DUINMITEMMOUSEEVENT nms;
        nms.hdr.code=NM_ITEMMOUSEEVENT;
        nms.hdr.hDuiWnd=m_pFrmHost->GetSwnd();
        nms.hdr.idFrom=m_pFrmHost->GetID();
        nms.hdr.pszNameFrom= m_pFrmHost->GetName();
        nms.pItem=this;
        nms.uMsg=uMsg;
        nms.wParam=wParam;
        nms.lParam=lParam;
        m_pFrmHost->DuiNotify((LPSNMHDR)&nms);
    }
    Release();
    return lRet;
}

LRESULT SItemPanel::OnDuiNotify(LPSNMHDR pHdr)
{
    DUINMITEMNOTIFY nmsItem;
    nmsItem.hdr.code=NM_LBITEMNOTIFY;
    nmsItem.hdr.hDuiWnd=m_pFrmHost->GetSwnd();
    nmsItem.hdr.idFrom=m_pFrmHost->GetID();
    nmsItem.hdr.pszNameFrom=m_pFrmHost->GetName();
    nmsItem.pItem=this;
    nmsItem.pHostDuiWin=(SWindow*)m_pFrmHost;
    nmsItem.pOriginHdr=pHdr;
    return m_pFrmHost->DuiNotify((LPSNMHDR)&nmsItem);
}

CRect SItemPanel::GetContainerRect()
{
    CRect rcItem;
    m_pItemContainer->OnItemGetRect(this,rcItem);
    return rcItem;
}

IRenderTarget * SItemPanel::OnGetRenderTarget(const CRect & rc,DWORD gdcFlags)
{
    CRect rcItem=GetItemRect();
    CRect rcInvalid=rc;
    rcInvalid.OffsetRect(rcItem.TopLeft());
    IRenderTarget *pRT=m_pFrmHost->GetRenderTarget(rcInvalid,gdcFlags);
    if(gdcFlags & OLEDC_PAINTBKGND)
    {//����frmhost��GetDuiDCʱ���������frmHost�ı�����ע�����ֻ������������ǰ��,��Ϊitempanel����ǰ��
        m_pFrmHost->DuiSendMessage(WM_ERASEBKGND, (WPARAM)pRT);
    }
    pRT->OffsetViewportOrg(rcItem.left,rcItem.top);
    return pRT;
}

void SItemPanel::OnReleaseRenderTarget(IRenderTarget *pRT,const CRect &rc,DWORD gdcFlags)
{
    CRect rcItem=GetItemRect();
    pRT->OffsetViewportOrg(-rcItem.left,-rcItem.top);
    m_pFrmHost->ReleaseRenderTarget(pRT);
}

void SItemPanel::OnRedraw(const CRect &rc)
{
    if(m_pFrmHost->IsUpdateLocked()) return;

    CRect rcItem=GetItemRect();
    if(!rcItem.IsRectNull() && m_pFrmHost->IsVisible(TRUE))
    {
        if(m_pItemContainer->IsItemRedrawDelay())
        {
            CRect rc2(rc);
            rc2.OffsetRect(rcItem.TopLeft());
            rc2.IntersectRect(rc2,rcItem);
            m_pFrmHost->NotifyInvalidateRect(rc2);
        }else
        {
            IRenderTarget *pRT=OnGetRenderTarget(rc,OLEDC_PAINTBKGND);
            CAutoRefPtr<IRegion> rgn;
            GETRENDERFACTORY->CreateRegion(&rgn);
            rgn->CombineRect(&rc,RGN_COPY);
            RedrawRegion(pRT,rgn);
            OnReleaseRenderTarget(pRT,rc,OLEDC_PAINTBKGND);
        }
    }
}

BOOL SItemPanel::OnReleaseSwndCapture()
{
    if(!__super::OnReleaseSwndCapture()) return FALSE;
    m_pItemContainer->OnItemSetCapture(this,FALSE);
    return TRUE;
}

SWND SItemPanel::OnSetSwndCapture(SWND hDuiWNd)
{
    m_pItemContainer->OnItemSetCapture(this,TRUE);
    return __super::OnSetSwndCapture(hDuiWNd);
}

HWND SItemPanel::GetHostHwnd()
{
    return m_pFrmHost->GetContainer()->GetHostHwnd();
}

BOOL SItemPanel::IsTranslucent()
{
    return m_pFrmHost->GetContainer()->IsTranslucent();
}

BOOL SItemPanel::SwndCreateCaret( HBITMAP hBmp,int nWidth,int nHeight )
{
    return m_pFrmHost->GetContainer()->SwndCreateCaret(hBmp,nWidth,nHeight);
}

BOOL SItemPanel::SwndShowCaret( BOOL bShow )
{
    return m_pFrmHost->GetContainer()->SwndShowCaret(bShow);
}

BOOL SItemPanel::SwndSetCaretPos( int x,int y )
{
    CRect rcItem=GetItemRect();
    x+=rcItem.left,y+=rcItem.top;
    return m_pFrmHost->GetContainer()->SwndSetCaretPos(x,y);
}

BOOL SItemPanel::SwndUpdateWindow()
{
    return m_pFrmHost->GetContainer()->SwndUpdateWindow();
}

void SItemPanel::ModifyItemState(DWORD dwStateAdd, DWORD dwStateRemove)
{
    ModifyState(dwStateAdd,dwStateRemove,FALSE);
}

SWND SItemPanel::HswndFromPoint(POINT ptHitTest, BOOL bOnlyText)
{
    SWND hRet=__super::HswndFromPoint(ptHitTest,bOnlyText);
    if(hRet==m_hSWnd) hRet=NULL;
    return hRet;
}

void SItemPanel::Draw(IRenderTarget *pRT,const CRect & rc)
{
    if((m_dwState & DuiWndState_Check) && m_crSelBk != CLR_INVALID) SetBkColor(m_crSelBk);
    else SetBkColor(m_crBk);

    pRT->OffsetViewportOrg(rc.left,rc.top);
    CAutoRefPtr<IRegion> rgn;
    GETRENDERFACTORY->CreateRegion(&rgn);
    RedrawRegion(pRT,rgn);
    pRT->OffsetViewportOrg(-rc.left,-rc.top);
}

void SItemPanel::SetSkin(ISkinObj *pSkin)
{
    m_pBgSkin=pSkin;
}

void SItemPanel::SetColor(COLORREF crBk,COLORREF crSelBk)
{
    m_crBk=crBk;
    m_crSelBk=crSelBk;
}

BOOL SItemPanel::NeedRedrawWhenStateChange()
{
    return TRUE;
}

CRect SItemPanel::GetItemRect()
{
    CRect rcItem;
    m_pItemContainer->OnItemGetRect(this,rcItem);
    return rcItem;
}
void SItemPanel::SetItemCapture(BOOL bCapture)
{
    m_pItemContainer->OnItemSetCapture(this,bCapture);
}

void SItemPanel::SetItemData(LPARAM dwData)
{
    m_dwData=dwData;
}

LPARAM SItemPanel::GetItemData()
{
    return m_dwData;
}

BOOL SItemPanel::OnUpdateToolTip( SWND hCurTipHost,SWND &hNewTipHost,CRect &rcTip,SStringT &strTip )
{
    if(hCurTipHost==m_hHover) return FALSE;
    if(m_hHover==m_hSWnd) return FALSE;

    SWindow *pHover=DuiWindowMgr::GetWindow(m_hHover);
    if(!pHover || pHover->IsDisabled(TRUE))
    {
        hNewTipHost=NULL;
        return TRUE;
    }
    BOOL bRet=pHover->OnUpdateToolTip(hCurTipHost,hNewTipHost,rcTip,strTip);
    if(bRet)
    {
        CRect rcItem=GetItemRect();
        rcTip.OffsetRect(rcItem.TopLeft());
    }
    return bRet;
}

void SItemPanel::OnSetCaretValidateRect( LPCRECT lpRect )
{
    CRect rcClient;
    GetClient(&rcClient);
    CRect rcIntersect;
    rcIntersect.IntersectRect(&rcClient,lpRect);
    CRect rcItem=GetItemRect();
    rcIntersect.OffsetRect(rcItem.TopLeft());
    m_pFrmHost->OnSetCaretValidateRect(&rcIntersect);
}

BOOL SItemPanel::RegisterTimelineHandler( ITimelineHandler *pHandler )
{
    BOOL bRet=CSwndContainer::RegisterTimelineHandler(pHandler);
    if(bRet && m_lstTimelineHandler.GetCount()==1) m_pFrmHost->GetContainer()->RegisterTimelineHandler(this);
    return bRet;
}

BOOL SItemPanel::UnregisterTimelineHandler( ITimelineHandler *pHandler )
{
    BOOL bRet=CSwndContainer::UnregisterTimelineHandler(pHandler);
    if(bRet && m_lstTimelineHandler.IsEmpty()) m_pFrmHost->GetContainer()->UnregisterTimelineHandler(this);
    return bRet;
}
}//namespace SOUI