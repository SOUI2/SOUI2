//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiHostWnd
//    Description: Real Container of DuiWindow
//     Creator: ZhangXiaoxuan
//     Version: 2010.3.12 - 1.0 - Create
//                2011.6.18    1.1   huangjianxiong
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "duimsgfilter.h"
#include "DuiThreadActiveWndMgr.h"

#include "duiframe.h"
#include "control/duirealwnd.h"

#include "SimpleWnd.h"
#include "DuiFrameDropTarget.h"

#pragma warning(disable: 4996)

#define INITCODE_NOTSHOW    100

namespace SOUI
{

    class CDuiHostWnd;
    class CTranslucentHostWnd : public CSimpleWnd
    {
    public:
        CTranslucentHostWnd(CDuiHostWnd* pOwner):m_pOwner(pOwner)
        {
        }

        void OnPaint(CDCHandle dc);

        BEGIN_MSG_MAP_EX(CTranslucentHostWnd)
            MSG_WM_PAINT(OnPaint)
        END_MSG_MAP()
    private:
        CDuiHostWnd *m_pOwner;
    };

class CDuiTipCtrl;

class SOUI_EXP CDuiHostWnd
    : public CSimpleWnd
    , public SWindow
    , public CDuiFrame
    , protected IDuiRealWndHandler
{
    friend class CTranslucentHostWnd;
public:
    CDuiHostWnd(LPCTSTR pszResName = NULL);
    virtual ~CDuiHostWnd() {}

public:

    HWND Create(HWND hWndParent,int x,int y,int nWidth,int nHeight);
    HWND Create(HWND hWndParent,LPCTSTR lpWindowName, DWORD dwStyle,DWORD dwExStyle, int x, int y, int nWidth, int nHeight, LPVOID lpParam);
    BOOL InitFromXml(LPCTSTR pszXmlName);

    BOOL SetXml(LPSTR lpszXml,int nLen);

    BOOL SetXml(pugi::xml_node xmlNode);

    UINT_PTR DoModal(HWND hWndParent = NULL, LPRECT rect = NULL);

    BOOL AnimateHostWindow(DWORD dwTime,DWORD dwFlags);

    virtual void EndDialog(UINT uRetCode);
protected:
    UINT m_uRetCode;
    BOOL m_bExitModalLoop;
    SStringT m_strXmlLayout;
    int m_nIdleCount;

    // Tracking flag
    BOOL m_bTrackFlag;

    SStringW m_strName;    //���ڵ�name���ԣ���skin��owner��Ӧ
    CRect m_rcNC;

    DWORD m_dwDlgStyle;
    DWORD m_dwDlgExStyle;
    BOOL m_bResizable;
    CSize m_szMin;

    BOOL m_bTranslucent;    //���ڵİ�͸������
    BOOL m_bCaretShowing;    //��ǰ�в����������ʾ
    CAutoRefPtr<IBitmap>    m_bmpCaret; //��͸�������е�ģ������
    SIZE                    m_szCaret;  //�������С
    BOOL m_bCaretActive;    //ģ������������ʾ��־
    CPoint m_ptCaret;        //�����λ��
    CRect    m_rcValidateCaret;//������ʾ�������λ��

    BOOL m_bNeedRepaint;
    BOOL m_bNeedAllRepaint;

    CDuiTipCtrl    * m_pTipCtrl;

    CAutoRefPtr<IRegion>    m_rgnInvalidate;
    CAutoRefPtr<IRenderTarget> m_memRT;
    
protected:
    virtual BOOL OnIdle(int nCount);

    void _ModalMessageLoop();

    void _Redraw();

    virtual BOOL _PreTranslateMessage(MSG* pMsg);

    SArray<CDuiMessageFilter*> m_aMsgFilter;

private:
    CTranslucentHostWnd            m_dummyWnd;    //��͸������ʹ�õ�һ����ӦWM_PAINT��Ϣ�Ĵ���
protected:
    //////////////////////////////////////////////////////////////////////////
    // Message handler

    void OnPrint(CDCHandle dc, UINT uFlags);

    void OnPaint(CDCHandle dc);

    BOOL OnEraseBkgnd(CDCHandle dc);

    int OnCreate(LPCREATESTRUCT lpCreateStruct);

    void OnDestroy();

    void OnSize(UINT nType, CSize size);

    void OnMouseMove(UINT nFlags, CPoint point);

    void OnMouseLeave();

    void OnLButtonDown(UINT nFlags, CPoint point);
    void OnLButtonDblClk(UINT nFlags, CPoint point);

    BOOL OnSetCursor(HWND hWnd, UINT nHitTest, UINT message);

    void OnTimer(UINT_PTR idEvent);

    void OnDuiTimer(char cTimerID);

    void DrawCaret(CPoint pt);

    LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT OnKeyEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

    BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

    void OnActivate(UINT nState, BOOL bMinimized, HWND wndOther);

    //////////////////////////////////////////////////////////////////////////
    // CDuiContainer

    /*virtual */
    LRESULT OnDuiNotify(LPSNMHDR pHdr);

    /*virtual */
    CRect GetContainerRect();

    /*virtual */
    HWND GetHostHwnd();

    /*virtual */
    IRenderTarget * OnGetRenderTarget(const CRect & rc,DWORD gdcFlags);

    /*virtual */
    void OnReleaseRenderTarget(IRenderTarget * pRT,const CRect &rc,DWORD gdcFlags);

    /*virtual */
    void OnRedraw(const CRect &rc);

    /*virtual */
    BOOL OnReleaseDuiCapture();

    /*virtual */
    HSWND OnSetDuiCapture(HSWND hDuiWnd);

    /*virtual */
    HSWND GetDuiCapture();

    /*virtual */
    BOOL IsTranslucent();

    /*virtual */
    BOOL DuiCreateCaret(HBITMAP hBmp,int nWidth,int nHeight);

    /*virtual */
    BOOL DuiShowCaret(BOOL bShow);

    /*virtual */
    BOOL DuiSetCaretPos(int x,int y);

    /*virtual */
    BOOL DuiUpdateWindow();

    /*virtual */
    BOOL RegisterTimelineHandler(ITimelineHandler *pHandler);

    /*virtual */
    BOOL UnregisterTimelineHandler(ITimelineHandler *pHandler);
    
    //////////////////////////////////////////////////////////////////////////
    // IDuiRealWndHandler
    virtual HWND OnRealWndCreate(SRealWnd *pRealWnd);
    virtual BOOL OnRealWndInit(SRealWnd *pRealWnd);
    virtual void OnRealWndDestroy(SRealWnd *pRealWnd);
    virtual void OnRealWndSize(SRealWnd *pRealWnd);

    LRESULT OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam);

    void OnGetMinMaxInfo(LPMINMAXINFO lpMMI);

    BOOL OnNcActivate(BOOL bActive);

    UINT OnWndNcHitTest(CPoint point);

    void OnSetFocus(HWND wndOld);
    void OnKillFocus(HWND wndFocus);

    void OnClose();
    void OnOK();

    LRESULT OnMsgFilter(UINT uMsg,WPARAM wParam,LPARAM lParam);

    void OnSetCaretValidateRect( LPCRECT lpRect );

    void UpdateHost(CDCHandle dc,const CRect &rc);
    void UpdateLayerFromRenderTarget(IRenderTarget *pRT,BYTE byAlpha);
protected:

    SOUI_NOTIFY_MAP_BEGIN()
        SOUI_NOTIFY_ID_COMMAND(IDOK, OnOK)
        SOUI_NOTIFY_ID_COMMAND(IDCANCEL, OnClose)
    SOUI_NOTIFY_MAP_END()    

    BEGIN_MSG_MAP_EX(CDuiHostWnd)
        MSG_WM_SIZE(OnSize)
        MSG_WM_PRINT(OnPrint)
        MSG_WM_PAINT(OnPaint)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_ERASEBKGND(OnEraseBkgnd)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_MOUSEWHEEL(OnMouseWheel)
        MSG_WM_ACTIVATE(OnActivate)
        MSG_WM_SETFOCUS(OnSetFocus)
        MSG_WM_KILLFOCUS(OnKillFocus)
        MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseEvent)
        MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST, WM_KEYLAST, OnKeyEvent)
        MESSAGE_RANGE_HANDLER_EX(WM_IME_STARTCOMPOSITION,WM_IME_KEYLAST,OnKeyEvent)
        MESSAGE_HANDLER_EX(WM_IME_CHAR, OnKeyEvent)
        MSG_WM_SETCURSOR(OnSetCursor)
        MSG_WM_TIMER(OnTimer)
        MSG_WM_NCACTIVATE(OnNcActivate)
        MSG_WM_NCCALCSIZE(OnNcCalcSize)
        MSG_WM_NCHITTEST(OnWndNcHitTest)
        MSG_WM_GETMINMAXINFO(OnGetMinMaxInfo)
        MESSAGE_HANDLER_EX(UM_MSGFILTER,OnMsgFilter)
        MSG_WM_CLOSE(OnClose)
        MSG_SOUI_NOTIFY()
        REFLECT_NOTIFY_CODE(NM_CUSTOMDRAW)
    END_MSG_MAP()
};

}//namespace SOUI
