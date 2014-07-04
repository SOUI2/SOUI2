//////////////////////////////////////////////////////////////////////////
//  Class Name: CDuiHostWnd
//    Description: Real Container of DuiWindow
//     Creator: ZhangXiaoxuan
//     Version: 2010.3.12 - 1.0 - Create
//                2011.6.18    1.1   huangjianxiong
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "DuiThreadActiveWndMgr.h"

#include "duiframe.h"
#include "control/duirealwnd.h"

#include "SimpleWnd.h"
#include "rootwnd.h"
#include "SDropTargetDispatcher.h"
#include "event/eventcrack.h"

#pragma warning(disable: 4996)

#define INITCODE_NOTSHOW    100

namespace SOUI
{

    class SHostWnd;
    class CDummyWnd : public CSimpleWnd
    {
    public:
        CDummyWnd(SHostWnd* pOwner):m_pOwner(pOwner)
        {
        }

        void OnPaint(CDCHandle dc);

        BEGIN_MSG_MAP_EX(CDummyWnd)
            MSG_WM_PAINT(OnPaint)
        END_MSG_MAP()
    private:
        SHostWnd *m_pOwner;
    };

class STipCtrl;

class SOUI_EXP SHostWnd
    : public CSimpleWnd
    , public SwndContainerImpl
    , public SRootWindow
    , protected IDuiRealWndHandler
{
    friend class CDummyWnd;
public:
    SHostWnd(LPCTSTR pszResName = NULL);
    virtual ~SHostWnd();

public:
    SRootWindow * GetRoot(){return this;}
    CSimpleWnd * GetNative(){return this;}

    HWND Create(HWND hWndParent,int x,int y,int nWidth,int nHeight);
    HWND Create(HWND hWndParent,LPCTSTR lpWindowName, DWORD dwStyle,DWORD dwExStyle, int x, int y, int nWidth, int nHeight, LPVOID lpParam);

    BOOL SetXml(LPCTSTR pszXmlName);

    BOOL SetXml(LPCWSTR lpszXml,int nLen);

    BOOL AnimateHostWindow(DWORD dwTime,DWORD dwFlags);
protected:
    BOOL InitFromXml(pugi::xml_node xmlNode);
    void _Redraw();
    
    CDummyWnd            m_dummyWnd;    //��͸������ʹ�õ�һ����ӦWM_PAINT��Ϣ�Ĵ���
    
    SStringT m_strXmlLayout;

    // Tracking flag
    BOOL m_bTrackFlag;


    BOOL m_bCaretShowing;    //��ǰ�в����������ʾ
    CAutoRefPtr<IBitmap>    m_bmpCaret; //��͸�������е�ģ������
    SIZE                    m_szCaret;  //�������С
    BOOL m_bCaretActive;    //ģ������������ʾ��־
    CPoint m_ptCaret;        //�����λ��
    CRect    m_rcValidateCaret;//������ʾ�������λ��

    BOOL m_bNeedRepaint;
    BOOL m_bNeedAllRepaint;

    STipCtrl    * m_pTipCtrl;

    CAutoRefPtr<IRegion>    m_rgnInvalidate;
    CAutoRefPtr<IRenderTarget> m_memRT;
    
    
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

    void OnSwndTimer(char cTimerID);

    void DrawCaret(CPoint pt);

    LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

    LRESULT OnKeyEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

    BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

    void OnActivate(UINT nState, BOOL bMinimized, HWND wndOther);

    //////////////////////////////////////////////////////////////////////////
    // CDuiContainer

    /*virtual */
    BOOL OnFireEvent(EventArgs &evt);

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
    BOOL OnReleaseSwndCapture();

    /*virtual */
    SWND OnSetSwndCapture(SWND hDuiWnd);

    /*virtual */
    BOOL IsTranslucent();

    /*virtual */
    BOOL SwndCreateCaret(HBITMAP hBmp,int nWidth,int nHeight);

    /*virtual */
    BOOL SwndShowCaret(BOOL bShow);

    /*virtual */
    BOOL SwndSetCaretPos(int x,int y);

    /*virtual */
    BOOL SwndUpdateWindow();

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

    void OnSetCaretValidateRect( LPCRECT lpRect );

    void UpdateHost(CDCHandle dc,const CRect &rc);
    void UpdateLayerFromRenderTarget(IRenderTarget *pRT,BYTE byAlpha);
protected:
    virtual BOOL _HandleEvent(SOUI::EventArgs *pEvt){return FALSE;}

    BEGIN_MSG_MAP_EX(SHostWnd)
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
        MSG_WM_CLOSE(OnClose)
        REFLECT_NOTIFY_CODE(NM_CUSTOMDRAW)
    END_MSG_MAP()
};

}//namespace SOUI
