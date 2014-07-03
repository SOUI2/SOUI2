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

#include "gdialpha.h"
#include "event/EventSubscriber.h"
#include "event/events.h"
#include "event/EventSet.h"
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
    DWORD    Swnd:24;        //���ھ��,������ھ������24λ��Χ������ʹ�����ַ�ʽ���ö�ʱ��
    DWORD    uTimerID:7;        //��ʱ��ID��һ���������֧��128����ʱ����
    DWORD    bDuiTimer:1;    //����ͨ�ö�ʱ���ı�־����־Ϊ1ʱ����ʾ�ö�ʱ��ΪDUI��ʱ��

    STimerID(SWND hWnd,char id)
    {
        ASSERT(hWnd<0x00FFFFFF && id>=0);
        bDuiTimer=1;
        Swnd=hWnd;
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
    SPainter(): crOld(CR_INVALID)
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
    , public TObjRefImpl2<IObjRef,SWindow>
{
    SOUI_CLASS_NAME(SWindow, L"window")
    friend class SLayout;
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
    SEventSet   m_evtSet;

    SWND m_hSWnd;
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

    ISkinObj * m_pBgSkin;   //����skin
    ISkinObj * m_pNcSkin;   //�ǿͻ���skin
    
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

    // Get SWindow rect(position in container)
    void GetRect(LPRECT prect);

    virtual void GetClient(LPRECT pRect);

    void GetDlgPosition(DUIWND_POSITION *pPos);
    // Get inner text
    SStringT GetWindowText();
    // Set inner text
    BOOL SetWindowText(LPCTSTR lpszText);

    void TestMainThread();

    // Send a message to DuiWindow
    LRESULT SendMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0,BOOL *pbMsgHandled=NULL);

    PSWNDMSG GetCurMsg()
    {
        return m_pCurMsg;
    }

    // Move DuiWindow to new place
    void Move(LPRECT prect);

    void Move(int x,int y, int cx=-1,int cy=-1);

    // Set current cursor, when hover
    virtual BOOL OnSetCursor(const CPoint &pt);

    // Get tooltip Info
    virtual BOOL OnUpdateToolTip(SWND hCurTipHost,SWND &hNewTipHost,CRect &rcTip,SStringT &strTip);

    // Get DuiWindow state
    DWORD GetState(void);

    // Modify SWindow state
    DWORD ModifyState(DWORD dwStateAdd, DWORD dwStateRemove,BOOL bUpdate=FALSE);

    ULONG_PTR GetUserData();
    ULONG_PTR SetUserData(ULONG_PTR uData);

    //************************************
    // Method:    SetTimer
    // Function:  ���ô��ڶ�ʱ��������һ��IDΪ0-127��DUI��ʱ��
    // Access:    public
    // Returns:   BOOL
    // Parameter: char id
    // Parameter: UINT uElapse
    // remark:
    //************************************
    BOOL SetTimer(char id,UINT uElapse);

    //************************************
    // Method:    KillTimer
    // Function:  ɾ��һ��SWND��ʱ��
    // Access:    public
    // Returns:   void
    // Parameter: char id
    // remark:
    //************************************
    void KillTimer(char id);

    //************************************
    // Method:    SetTimerEx
    // Function:  ���ú�����ʱ����ģ��һ�����ݴ��ڶ�ʱ��
    // Access:    public
    // Returns:   BOOL
    // Parameter: UINT_PTR id
    // Parameter: UINT uElapse
    // remark: �ܹ�ʹ��SetDuiTimerʱ��������SetDuiTimerEx����KillʱЧ�ʻ�Ƚϵ�
    //************************************
    BOOL SetTimerEx(UINT_PTR id,UINT uElapse);

    //************************************
    // Method:    KillTimerEx
    // Function:  ɾ��һ��SetDuiTimerEx���õĶ�ʱ��
    // Access:    public
    // Returns:   void
    // Parameter: UINT_PTR id
    // remark: ��Ҫö�ٶ�ʱ���б�
    //************************************
    void KillTimerEx(UINT_PTR id);

    SWND GetSwnd();


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
    SWindow *CreateChildren(LPCWSTR pszXml);

    void Invalidate();
    void InvalidateRect(LPRECT lprect);
    void InvalidateRect(const CRect& rect);
    void LockUpdate();
    void UnlockUpdate();
    BOOL IsUpdateLocked();
    void BringWindowToTop();

public:
    //ͬ��ؼ��Զ������־,��Ҫ�Ǹ�RadioButton�õġ�
    virtual BOOL IsSiblingsAutoGroupped(){return FALSE;}
    
    //�����һ��group��ѡ��״̬�Ĵ��ڣ�����group�еĴ���ʱ��Ϊ��ǰ����
    virtual SWindow * GetSelectedSiblingInGroup(){return this;}
    
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

    virtual SWND SwndFromPoint(CPoint ptHitTest, BOOL bOnlyText);

    virtual BOOL FireEvent(EventArgs &evt);
    
    bool subscribeEvent(const DWORD dwEventID, const SlotFunctorBase & subscriber)
    {
        return m_evtSet.subscribeEvent(dwEventID,subscriber);
    }

    bool unsubscribeEvent( const DWORD dwEventID, const SlotFunctorBase & subscriber )
    {
        return m_evtSet.unsubscribeEvent(dwEventID,subscriber);
    }
    
    bool isEventMuted(void) const
    {
        return m_evtSet.isMuted();
    }

    void    setEventMute(bool bMute)
    {
        return m_evtSet.setMutedState(bMute);
    }
    
    virtual UINT OnGetDlgCode();

    virtual BOOL IsTabStop();

    virtual BOOL OnNcHitTest(CPoint pt);

    virtual BOOL IsClipClient()
    {
        return m_bClipClient;
    }


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
    CRect        m_rcGetRT;
    DWORD        m_gdcFlags;
    BOOL         m_bClipRT;
    //����GetRenderTargetʱRT�е����弰��ɫ
    CAutoRefPtr<IRenderObj> m_oldFont;
    COLORREF     m_oldColor;
public:
    SWND GetCapture();
    SWND SetCapture();
    BOOL ReleaseCapture();
    
    void SetFocus();
    void KillFocus();

    SWindow *GetCheckedRadioButton();

    void CheckRadioButton(SWindow * pRadioBox);

    BOOL SetItemVisible(UINT uItemID, BOOL bVisible);

    BOOL IsItemVisible(UINT uItemID, BOOL bCheckParent = FALSE);
    BOOL GetItemCheck(UINT uItemID);

    BOOL SetItemCheck(UINT uItemID, BOOL bCheck);
    BOOL EnableItem(UINT uItemID, BOOL bEnable);
    BOOL IsItemEnable(UINT uItemID, BOOL bCheckParent = FALSE);

    SWindow *GetWindow(int uCode);    

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
    LRESULT FireCommand();
    LRESULT FireCtxMenu(CPoint pt);

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
    virtual void DrawText(IRenderTarget *pRT,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat);
    virtual void DrawFocus(IRenderTarget *pRT);

    void DrawDefFocusRect(IRenderTarget *pRT,CRect rc);
    void DrawAniStep(CRect rcFore,CRect rcBack,IRenderTarget *pRTFore,IRenderTarget * pRTBack,CPoint ptAnchor);
    void DrawAniStep( CRect rcWnd,IRenderTarget *pRTFore,IRenderTarget * pRTBack,BYTE byAlpha);
    //////////////////////////////////////////////////////////////////////////
    // Message Handler

    //************************************
    // Method:    SwndProc
    // Function:  Ĭ�ϵ���Ϣ������
    // Access:    virtual public
    // Returns:   BOOL
    // Parameter: UINT uMsg
    // Parameter: WPARAM wParam
    // Parameter: LPARAM lParam
    // Parameter: LRESULT & lResult
    // remark: ����Ϣӳ�����û�д������Ϣ����ú�������
    //************************************
    virtual BOOL SwndProc(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT & lResult)
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

    void OnSetFocus();
    void OnKillFocus();

    HRESULT OnAttrPos(const SStringW& strValue, BOOL bLoading);
    HRESULT OnAttrState(const SStringW& strValue, BOOL bLoading);

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
        MSG_WM_SETFOCUS_EX(OnSetFocus)
        MSG_WM_KILLFOCUS_EX(OnKillFocus)
    WND_MSG_MAP_END_BASE()
    
    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"id",m_nID,FALSE)
        ATTR_STRINGW(L"name",m_strName,FALSE)
        ATTR_SKIN(L"skin", m_pBgSkin, TRUE)//ֱ�ӻ��Ƥ������
        ATTR_SKIN(L"ncskin", m_pNcSkin, TRUE)//ֱ�ӻ��Ƥ������
        ATTR_STYLE(L"class", m_style, TRUE)    //���style
        ATTR_CHAIN(m_style)                    //֧�ֶ�style�е����Զ���
        ATTR_INT(L"data", m_uData, 0 )
        ATTR_CUSTOM(L"state", OnAttrState)
        ATTR_STRINGT(L"href", m_strLinkUrl, FALSE)
        ATTR_STRINGT(L"tip", m_strToolTipText, FALSE)
        ATTR_CUSTOM(L"pos", OnAttrPos)
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