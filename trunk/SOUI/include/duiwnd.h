//////////////////////////////////////////////////////////////////////////
//   File Name: DuiWnd.h
// Description: DuiWindow Definition
//     Creator: Zhang Xiaoxuan
//     Version: 2009.04.28 - 1.0 - Create
//                2011.09.01 - 2.0 huang jianxiong
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "DuiWindowMgr.h"
#include "DuiTimerEx.h"
#include "DuiContainer-i.h"
#include "duimsgcracker.h"

#include "duiwndnotify.h"
#include "gdialpha.h"
#include "DuiEventSet.h"
#include <OCIdl.h>
#include "DuiLayout.h"

namespace SOUI
{

/////////////////////////////////////////////////////////////////////////
enum {NormalShow=0,ParentShow=1};    //�ṩWM_SHOWWINDOW��Ϣʶ���Ǹ�������ʾ����Ҫ��ʾ������
enum {NormalEnable=0,ParentEnable=1};    //�ṩWM_ENABLE��Ϣʶ���Ǹ����ڿ��û���ֱ�Ӳ�����ǰ����

#define DUIC_WANTARROWS     0x0001      /* Control wants arrow keys         */
#define DUIC_WANTTAB        0x0002      /* Control wants tab keys           */
#define DUIC_WANTRETURN     0x0004      /* Control wants return keys        */
#define DUIC_WANTCHARS      0x0008      /* Want WM_CHAR messages            */
#define DUIC_WANTALLKEYS    0xFFFF      /* Control wants all keys           */
#define DUIC_WANTSYSKEY     0x80000000    /* System Key */
class SOUI_EXP STimerID
{
public:
    DWORD    hDuiWnd:24;        //���ھ��,������ھ������24λ��Χ������ʹ�����ַ�ʽ���ö�ʱ��
    DWORD    uTimerID:7;        //��ʱ��ID��һ���������֧��128����ʱ����
    DWORD    bDuiTimer:1;    //����ͨ�ö�ʱ���ı�־����־Ϊ1ʱ����ʾ�ö�ʱ��ΪDUI��ʱ��

    STimerID(HSWND hWnd,char id)
    {
        ASSERT(hWnd<0x00FFFFFF && id>=0);
        bDuiTimer=1;
        hDuiWnd=hWnd;
        uTimerID=id;
    }
    STimerID(DWORD dwID)
    {
        memcpy(this,&dwID,sizeof(DWORD));
    }
    operator DWORD &() const
    {
        return *(DWORD*)this;
    }
};

#define ICWND_FIRST    ((SWindow*)-1)
#define ICWND_LAST    NULL

class SOUI_EXP SPainter
{
public:
    SPainter()
        : crOld(CR_INVALID)
    {
    }

    CAutoRefPtr<IFont> pOldPen;
    COLORREF          crOld;
};

class SOUI_EXP SMsgHandleState
{
public:
    SMsgHandleState():m_bMsgHandled(FALSE)
    {

    }

    BOOL IsMsgHandled() const
    {
        return m_bMsgHandled;
    }

    void SetMsgHandled(BOOL bHandled)
    {
        m_bMsgHandled = bHandled;
    }

    BOOL m_bMsgHandled;
};

//////////////////////////////////////////////////////////////////////////
// SWindow
//////////////////////////////////////////////////////////////////////////

typedef enum tagGDUI_CODE
{
    GDUI_FIRSTCHILD=0,
    GDUI_LASTCHILD,
    GDUI_PREVSIBLING,
    GDUI_NEXTSIBLING,
    GDUI_PARENT,
    GDUI_OWNER,
} GDUI_CODE;

class SOUI_EXP SWindow : public SObject
    , public SMsgHandleState
    , public SEventSet
    , public TObjRefImpl2<IObjRef,SWindow>
{
    SOUI_CLASS_NAME(SWindow, L"window")
    friend class CDuiLayout;
public:
    SWindow();

    virtual ~SWindow();

    typedef struct tagSWNDMSG
    {
        UINT uMsg;
        WPARAM wParam;
        LPARAM lParam;
    } SWNDMSG,*PSWNDMSG;
protected:
    HSWND m_hSWnd;
    ISwndContainer *m_pContainer;
    SWindow *m_pOwner;
    SWindow *m_pParent,*m_pFirstChild, *m_pLastChild, *m_pNextSibling,*m_pPrevSibling;    //�������ṹ
    UINT    m_nChildrenCount;
    SWNDMSG        *m_pCurMsg;

    CRect m_rcWindow;

    SStringW m_strName;
    int     m_nID;

    DuiStyle m_style;
    SStringT m_strText;
    DWORD m_dwState;
    SStringT m_strLinkUrl;
    BOOL m_bMsgTransparent;        //�������û�������־
    BOOL m_bVisible;            //�ɼ�״̬
    BOOL m_bDisplay;            //����ʱ�Ƿ�ռλ����ռλʱ�������²��֡�
    BOOL m_bDisable;            //����״̬
    SStringT m_strToolTipText;
    int     m_nSepSpace;    //�Զ��Ű��ˮƽ�ո�
    BOOL m_bClipClient;
    BOOL m_bTabStop;
    BYTE m_byAlpha;        //����͸����,ֻ�������ã�֧�������ڿؼ���

    ISkinObj * m_pBgSkin;
    ISkinObj * m_pNcSkin;

    DUIWND_POSITION m_dlgpos;
    int             m_nMaxWidth;    //�Զ������Сʱʹ��

    BOOL m_bUpdateLocked;//��ʱ��������
#ifdef _DEBUG
    DWORD m_nMainThreadId;
#endif
    ULONG_PTR m_uData;
public:

    //////////////////////////////////////////////////////////////////////////
    // Method Define

    // Get align
    UINT GetTextAlign();    
    // Get position type
    DWORD GetPositionType();

    // Set position type
    void SetPositionType(DWORD dwPosType, DWORD dwMask = 0xFFFFFFFF);

    void SetFixSize(int nWid,int nHei);
    void SetBkColor(COLORREF cr);

    // Get DuiWindow rect(position in container)
    void GetRect(LPRECT prect);

    virtual void GetClient(LPRECT pRect);

    void GetDlgPosition(DUIWND_POSITION *pPos);
    // Get inner text
    SStringT GetWindowText();


    // Set inner text
    BOOL SetWindowText(LPCTSTR lpszText);

    void TestMainThread();

    // Send a message to DuiWindow
    LRESULT DuiSendMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0,BOOL *pbMsgHandled=NULL);

    PSWNDMSG GetCurDuiMsg()
    {
        return m_pCurMsg;
    }

    // Move DuiWindow to new place
    void Move(LPRECT prect);

    void Move(int x,int y, int cx=-1,int cy=-1);

    // Set current cursor, when hover
    virtual BOOL OnSetCursor(const CPoint &pt);

    // Get tooltip Info
    virtual BOOL OnUpdateToolTip(HSWND hCurTipHost,HSWND &hNewTipHost,CRect &rcTip,SStringT &strTip);

    // Get DuiWindow state
    DWORD GetState(void);

    // Modify DuiWindow state
    DWORD ModifyState(DWORD dwStateAdd, DWORD dwStateRemove,BOOL bUpdate=FALSE);

    ULONG_PTR GetUserData();
    ULONG_PTR SetUserData(ULONG_PTR uData);

    //************************************
    // Method:    SetDuiTimer
    // Function:  ���ô��ڶ�ʱ��������һ��IDΪ0-127��DUI��ʱ��
    // Access:    public
    // Returns:   BOOL
    // Parameter: char id
    // Parameter: UINT uElapse
    // remark:
    //************************************
    BOOL SetDuiTimer(char id,UINT uElapse);

    //************************************
    // Method:    KillDuiTimer
    // Function:  ɾ��һ��DUI��ʱ��
    // Access:    public
    // Returns:   void
    // Parameter: char id
    // remark:
    //************************************
    void KillDuiTimer(char id);

    //************************************
    // Method:    SetDuiTimerEx
    // Function:  ���ú�����ʱ����ģ��һ�����ݴ��ڶ�ʱ��
    // Access:    public
    // Returns:   BOOL
    // Parameter: UINT_PTR id
    // Parameter: UINT uElapse
    // remark: �ܹ�ʹ��SetDuiTimerʱ��������SetDuiTimerEx����KillʱЧ�ʻ�Ƚϵ�
    //************************************
    BOOL SetDuiTimerEx(UINT_PTR id,UINT uElapse);

    //************************************
    // Method:    KillDuiTimerEx
    // Function:  ɾ��һ��SetDuiTimerEx���õĶ�ʱ��
    // Access:    public
    // Returns:   void
    // Parameter: UINT_PTR id
    // remark: ��Ҫö�ٶ�ʱ���б�
    //************************************
    void KillDuiTimerEx(UINT_PTR id);

    HSWND GetDuiHwnd();


    SWindow *GetParent();

    void SetParent(SWindow *pParent);

    SWindow *GetTopLevelParent();

    BOOL DestroyChild(SWindow *pChild);

    UINT GetChildrenCount();

    SWindow * GetChild(int nID);

    virtual void SetChildContainer(SWindow *pChild);

    void InsertChild(SWindow *pNewChild,SWindow *pInsertAfter=ICWND_LAST);

    BOOL RemoveChild(SWindow *pChild);

    BOOL IsChecked();

    BOOL IsDisabled(BOOL bCheckParent = FALSE);

    BOOL IsVisible(BOOL bCheckParent = FALSE);
    void SetVisible(BOOL bVisible,BOOL bUpdate=FALSE);

    void EnableWindow( BOOL bEnable,BOOL bUpdate=FALSE);

    void SetCheck(BOOL bCheck);

    BOOL NeedRedrawParent();

    LPCTSTR GetLinkUrl();

    ISwndContainer *GetContainer();

    void SetContainer(ISwndContainer *pContainer);

    void SetOwner(SWindow *pOwner);

    SWindow *GetOwner();

    BOOL IsMsgTransparent();

    DuiStyle& GetStyle();

    LPCWSTR GetName(){return m_strName;}
    void SetName(LPCWSTR pszName){m_strName=pszName;}

    int GetID(){return m_nID;}
    void SetID(int nID){m_nID=nID;}
    
    //************************************
    // Method:    FindChildByCmdID, ͨ��ID���Ҷ�Ӧ���Ӵ���
    // Access:    public 
    // Returns:   SWindow*
    // Qualifier:
    // Parameter: UINT uCmdID
    //************************************
    SWindow* FindChildByID(int nID);

    template<class T>
    T* FindChildByID2(int nID)
    {
        T* pRet= dynamic_cast<T *>(FindChildByID(nID));
        ASSERT(pRet);
        return pRet;
    }

    //************************************
    // Method:    FindChildByName��ͨ�����ֲ����Ӵ���
    // Access:    public 
    // Returns:   SWindow*
    // Qualifier:
    // Parameter: LPCSTR pszName
    //************************************
    SWindow* FindChildByName(LPCWSTR pszName);

    template<class T>
    T* FindChildByName2(LPCWSTR pszName)
    {
        T* pRet= dynamic_cast<T*>(FindChildByName(pszName));
        ASSERT(pRet);
        return pRet;
    }

    // ��XML�����Ӵ���
    // LPCWSTR pszXml: utf16�����XML��
    // return : ��������һ������
    SWindow *LoadXmlChildren(LPCWSTR pszXml);

    void NotifyInvalidate();
    void NotifyInvalidateRect(LPRECT lprect);
    void NotifyInvalidateRect(const CRect& rect);
    void LockUpdate();
    void UnlockUpdate();
    BOOL IsUpdateLocked();
    void BringWindowToTop();

    //ͬ��ؼ��Զ������־,��Ҫ�Ǹ�RadioButton�õġ�
    virtual BOOL IsSiblingsAutoGroupped(){return FALSE;}
public:
    //////////////////////////////////////////////////////////////////////////
    // Virtual functions
    virtual void OnSetCaretValidateRect(LPCRECT lpRect)
    {
        CRect rcClient;
        GetClient(&rcClient);
        CRect rcIntersect;
        rcIntersect.IntersectRect(&rcClient,lpRect);
        if(GetParent()) GetParent()->OnSetCaretValidateRect(&rcIntersect);
    }

    virtual void OnStateChanged(DWORD dwOldState,DWORD dwNewState) {}

    virtual BOOL CreateChildren(pugi::xml_node xmlNode);
    // Create SWindow from xml element
    virtual BOOL InitFromXml(pugi::xml_node xmlNode);

    virtual HSWND HswndFromPoint(CPoint ptHitTest, BOOL bOnlyText);

    virtual LRESULT DuiNotify(LPSNMHDR pnms);

    virtual UINT OnGetDlgCode();

    virtual BOOL IsTabStop();

    virtual BOOL OnNcHitTest(CPoint pt);

    virtual BOOL IsClipClient()
    {
        return m_bClipClient;
    }

    virtual void OnAttributeChanged(const SStringW & strAttrName,BOOL bLoading,HRESULT hRet);

    //************************************
    // Method:    UpdateChildrenPosition :�����Ӵ���λ��
    // FullName:  SOUI::SWindow::UpdateChildrenPosition
    // Access:    virtual protected 
    // Returns:   void
    // Qualifier:
    //************************************
    virtual void UpdateChildrenPosition();

public:
    //************************************
    // Method:    RedrawRegion
    // Function:  �����ڼ��Ӵ������ݻ��Ƶ�DC
    // Access:    public 
    // Returns:   BOOL
    // Qualifier:
    // Parameter: CDCHandle & dc
    // Parameter: CRgn & rgn
    //************************************
    BOOL RedrawRegion(IRenderTarget *pRT, IRegion *pRgn);

    //************************************
    // Method:    GetDuiDC
    // Function:  ��ȡһ����DUI��������Ӧ���ڴ�DC
    // Access:    public
    // Returns:   HDC
    // Parameter: LPRECT pRc - DC��Χ
    // Parameter: DWORD gdcFlags ͬOLEDCFLAGS
    // Parameter: BOOL bClientDC ������client����
    // remark: ʹ��ReleaseDuiDC�ͷ�
    //************************************
    IRenderTarget * GetRenderTarget(const LPRECT pRc=NULL,DWORD gdcFlags=0,BOOL bClientDC=TRUE);


    //************************************
    // Method:    ReleaseDuiDC
    // Function:  �ͷ���GetDuiDC��ȡ��DC
    // Access:    public
    // Returns:   void
    // Parameter: HDC hdc
    // remark:
    //************************************
    void ReleaseRenderTarget(IRenderTarget *pRT);

    //************************************
    // Method:    PaintBackground
    // Function:  �����ڵı�������
    // Access:    public
    // Returns:   void
    // Parameter: HDC hdc Ŀ��DC
    // Parameter: LPRECT pRc Ŀ��λ��
    // remark:    Ŀ��λ�ñ����ڴ���λ����
    //************************************
    void PaintBackground(IRenderTarget *pRT,LPRECT pRc);

    //************************************
    // Method:    PaintForeground
    // Function:  �����ڵ�ǰ������,��������ǰ���ڵ��Ӵ���
    // Access:    public
    // Returns:   void
    // Parameter: HDC hdc Ŀ��DC
    // Parameter: LPRECT pRc Ŀ��λ��
    // remark:    Ŀ��λ�ñ����ڴ���λ����
    //************************************
    void PaintForeground(IRenderTarget *pRT,LPRECT pRc);


    //************************************
    // Method:    AnimateWindow
    // Function:  ���ڶ���Ч��
    // Access:    public
    // Returns:   BOOL
    // Parameter: DWORD dwTime,ִ��ʱ��
    // Parameter: DWORD dwFlags,ִ��ģʽ
    // remark:
    //************************************
    BOOL AnimateWindow(DWORD dwTime,DWORD dwFlags);
protected:
    typedef enum _PRSTATE{
        PRS_LOOKSTART=0,    //���ҿ�ʼ����
        PRS_DRAWING,        //������Ⱦ��
        PRS_MEETEND            //����ָ���Ľ�������
    } PRSTATE;
    static BOOL _PaintRegion(IRenderTarget *pRT, IRegion *pRgn,SWindow *pWndCur,SWindow *pStart,SWindow *pEnd,SWindow::PRSTATE & prState);


    CRect        m_rcGetRT;
    DWORD        m_gdcFlags;
    BOOL         m_bClipRT;
public:
    HSWND GetDuiCapture();
    HSWND SetDuiCapture();

    BOOL ReleaseDuiCapture();
    void SetDuiFocus();
    void KillDuiFocus();

    SWindow *GetCheckedRadioButton();

    void CheckRadioButton(SWindow * pRadioBox);

    BOOL SetItemVisible(UINT uItemID, BOOL bVisible);

    BOOL IsItemVisible(UINT uItemID, BOOL bCheckParent = FALSE);
    BOOL GetItemCheck(UINT uItemID);

    BOOL SetItemCheck(UINT uItemID, BOOL bCheck);
    BOOL EnableItem(UINT uItemID, BOOL bEnable);
    BOOL IsItemEnable(UINT uItemID, BOOL bCheckParent = FALSE);

    SWindow *GetDuiWindow(int uCode);    

    //************************************
    // Method:    BeforePaint
    // Function:  ΪDC׼���õ�ǰ���ڵĻ�ͼ����
    // Access:    public
    // Returns:   void
    // Parameter: CDCHandle & dc
    // Parameter: SPainter & DuiDC
    // remark:
    //************************************
    void BeforePaint(IRenderTarget *pRT, SPainter &painter);

    //************************************
    // Method:    AfterPaint
    // Function:  �ָ���BeforePaint���õ�DC״̬
    // Access:    public
    // Returns:   void
    // Parameter: CDCHandle & dc
    // Parameter: SPainter & DuiDC
    // remark:
    //************************************
    void AfterPaint(IRenderTarget *pRT, SPainter &painter);

    //************************************
    // Method:    BeforePaintEx
    // Function:  ΪDC׼���õ�ǰ���ڵĻ�ͼ����,�Ӷ��㴰�ڿ�ʼ����
    // Access:    public
    // Returns:   int ��ǰ��DC����
    // Parameter: CDCHandle & dc
    // remark: ʹ��ǰʹ��SaveDC������״̬��ʹ�ú����RestoreDC���ָ�״̬
    //************************************
    void BeforePaintEx(IRenderTarget *pRT);

protected:
    LRESULT NotifyCommand();
    LRESULT NotifyContextMenu(CPoint pt);

    //************************************
    // Method:    GetChildrenLayoutRect :�����Ӵ��ڵ��Ű�ռ�
    // FullName:  SOUI::SWindow::GetChildrenLayoutRect
    // Access:    virtual protected 
    // Returns:   CRect
    // Qualifier:
    //************************************
    virtual CRect GetChildrenLayoutRect();

    void ClearLayoutState();

    //************************************
    // Method:    GetDesiredSize: ��û��ָ�����ڴ�Сʱ��ͨ����Ƥ�����㴰�ڵ�������С
    // FullName:  SOUI::SWindow::GetDesiredSize
    // Access:    virtual protected 
    // Returns:   CSize
    // Qualifier:
    // Parameter: LPRECT pRcContainer
    //************************************
    virtual CSize GetDesiredSize(LPRECT pRcContainer);

    //************************************
    // Method:    CalcSize �����㴰�ڴ�С
    // FullName:  SOUI::SWindow::CalcSize
    // Access:    protected 
    // Returns:   CSize
    // Qualifier:
    // Parameter: LPRECT pRcContainer
    //************************************
    CSize CalcSize(LPRECT pRcContainer);

    //************************************
    // Method:    GetNextVisibleWindow ���ָ�����ڵ���һ���ɼ�����
    // FullName:  SOUI::SWindow::GetNextVisibleWindow
    // Access:    protected static 
    // Returns:   SWindow *    :��һ���ɼ�����
    // Qualifier:
    // Parameter: SWindow * pWnd    :�ο�����
    // Parameter: const CRect &rcDraw:Ŀ�����
    //************************************
    static SWindow *GetNextVisibleWindow(SWindow *pWnd,const CRect &rcDraw);

    virtual BOOL NeedRedrawWhenStateChange();
    virtual void GetTextRect(LPRECT pRect);
    virtual void DuiDrawText(IRenderTarget *pRT,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat);
    virtual void DuiDrawFocus(IRenderTarget *pRT);

    void DuiDrawDefFocusRect(IRenderTarget *pRT,CRect rc);
    void DrawAniStep(CRect rcFore,CRect rcBack,IRenderTarget *pRTFore,IRenderTarget * pRTBack,CPoint ptAnchor);
    void DrawAniStep( CRect rcWnd,IRenderTarget *pRTFore,IRenderTarget * pRTBack,BYTE byAlpha);
    //////////////////////////////////////////////////////////////////////////
    // Message Handler

    //************************************
    // Method:    DuiWndProc
    // Function:  Ĭ�ϵ���Ϣ������
    // Access:    virtual public
    // Returns:   BOOL
    // Parameter: UINT uMsg
    // Parameter: WPARAM wParam
    // Parameter: LPARAM lParam
    // Parameter: LRESULT & lResult
    // remark: ����Ϣӳ�����û�д������Ϣ����ú�������
    //************************************
    virtual BOOL DuiWndProc(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT & lResult)
    {
        return FALSE;
    }

    LRESULT OnWindowPosChanged(LPRECT lpRcContainer);

    int OnCreate(LPVOID);

    void OnDestroy();

    // Draw background default
    BOOL OnEraseBkgnd(IRenderTarget *pRT);

    // Draw inner text default
    void OnPaint(IRenderTarget *pRT);


    //************************************
    // Method:    OnNcPaint
    // Function:  draw non-client area
    // Access:    protected
    // Returns:   void
    // Parameter: CDCHandle dc
    // remark:
    //************************************
    void OnNcPaint(IRenderTarget *pRT);

    BOOL OnDefKeyDown(UINT nChar, UINT nFlags);

    void OnShowWindow(BOOL bShow, UINT nStatus);

    void OnEnable(BOOL bEnable,UINT nStatus);

    void OnLButtonDown(UINT nFlags,CPoint pt);

    void OnLButtonUp(UINT nFlags,CPoint pt);
    
    void OnRButtonDown(UINT nFlags, CPoint point);

    void OnMouseMove(UINT nFlags,CPoint pt) {}

    void OnMouseHover(WPARAM wParam, CPoint ptPos);

    void OnMouseLeave();

    BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

    void OnSetDuiFocus();
    void OnKillDuiFocus();

    HRESULT OnAttributePosition(const SStringW& strValue, BOOL bLoading);
    HRESULT OnAttributeState(const SStringW& strValue, BOOL bLoading);

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_PAINT_EX(OnPaint)
        MSG_WM_ERASEBKGND_EX(OnEraseBkgnd)
        MSG_WM_NCPAINT_EX(OnNcPaint)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_WINPOSCHANGED_EX(OnWindowPosChanged)
        MSG_WM_SHOWWINDOW(OnShowWindow)
        MSG_WM_ENABLE_EX(OnEnable)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_RBUTTONDOWN(OnRButtonDown)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSEHOVER(OnMouseHover)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_MOUSEWHEEL(OnMouseWheel)
        MSG_WM_SETFOCUS_EX(OnSetDuiFocus)
        MSG_WM_KILLFOCUS_EX(OnKillDuiFocus)
    WND_MSG_MAP_END_BASE()
    
    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"id",m_nID,FALSE)
        ATTR_STRINGW(L"name",m_strName,FALSE)
        ATTR_SKIN(L"skin", m_pBgSkin, TRUE)//ֱ�ӻ��Ƥ������
        ATTR_SKIN(L"ncskin", m_pNcSkin, TRUE)//ֱ�ӻ��Ƥ������
        ATTR_STYLE(L"class", m_style, TRUE)    //���style
        ATTR_CHAIN(m_style)                    //֧�ֶ�style�е����Զ���
        ATTR_INT(L"data", m_uData, 0 )
        ATTR_CUSTOM(L"state", OnAttributeState)
        ATTR_STRINGT(L"href", m_strLinkUrl, FALSE)
        ATTR_STRINGT(L"tip", m_strToolTipText, FALSE)
        ATTR_CUSTOM(L"pos", OnAttributePosition)
        ATTR_INT(L"show", m_bVisible,FALSE)
        ATTR_INT(L"display", m_bDisplay,FALSE)
        ATTR_INT(L"msgtransparent", m_bMsgTransparent, FALSE)
        ATTR_INT(L"sep", m_nSepSpace, FALSE)
        ATTR_INT(L"maxwidth",m_nMaxWidth,FALSE)
        ATTR_INT(L"clipclient",m_bClipClient,FALSE)
        ATTR_INT(L"tabstop",m_bTabStop,FALSE)
        ATTR_ENUM_BEGIN(L"pos2type",POS2TYPE,FALSE)
            ATTR_ENUM_VALUE(L"lefttop",POS2_LEFTTOP)
            ATTR_ENUM_VALUE(L"center",POS2_CENTER)
            ATTR_ENUM_VALUE(L"righttop",POS2_RIGHTTOP)
            ATTR_ENUM_VALUE(L"leftbottom",POS2_LEFTBOTTOM)
            ATTR_ENUM_VALUE(L"rightbottom",POS2_RIGHTBOTTOM)
        ATTR_ENUM_END(m_dlgpos.pos2Type)
        ATTR_INT(L"alpha",m_byAlpha,TRUE)
    SOUI_ATTRS_END()

};
}//namespace SOUI