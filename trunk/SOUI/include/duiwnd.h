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
#include "duiref.h"
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
#define DUIC_WANTRETURN        0x0004        /* Control wants return keys        */
#define DUIC_WANTCHARS      0x0008      /* Want WM_CHAR messages            */
#define DUIC_WANTALLKEYS    0xFFFF      /* Control wants all keys           */
#define DUIC_WANTSYSKEY        0x80000000    /* System Key */
class SOUI_EXP CDuiTimerID
{
public:
    DWORD    hDuiWnd:24;        //���ھ��,������ھ������24λ��Χ������ʹ�����ַ�ʽ���ö�ʱ��
    DWORD    uTimerID:7;        //��ʱ��ID��һ���������֧��128����ʱ����
    DWORD    bDuiTimer:1;    //����ͨ�ö�ʱ���ı�־����־Ϊ1ʱ����ʾ�ö�ʱ��ΪDUI��ʱ��

    CDuiTimerID(HDUIWND hWnd,char id)
    {
        DUIASSERT(hWnd<0x00FFFFFF && id>=0);
        bDuiTimer=1;
        hDuiWnd=hWnd;
        uTimerID=id;
    }
    CDuiTimerID(DWORD dwID)
    {
        memcpy(this,&dwID,sizeof(DWORD));
    }
    operator DWORD &() const
    {
        return *(DWORD*)this;
    }
};

#define ICWND_FIRST    ((CDuiWindow*)-1)
#define ICWND_LAST    NULL

class SOUI_EXP DuiDCPaint
{
public:
    DuiDCPaint()
        : bDuiModeChanged(FALSE)
        , nOldDuiMode(OPAQUE)
        , bFontChanged(FALSE)
        , hftOld(NULL)
        , bTextColorChanged(FALSE)
        , crOld(CLR_INVALID)
        , bBgColorChanged(FALSE)
        , crOldBg(CLR_INVALID)
    {
    }
    BOOL     bDuiModeChanged;
    int      nOldDuiMode;
    BOOL     bFontChanged;
    HFONT    hftOld;
    BOOL     bTextColorChanged;
    COLORREF crOld;
    BOOL     bBgColorChanged;
    COLORREF crOldBg;
    CRect    rcClient;
};



//////////////////////////////////////////////////////////////////////////
// CDuiWindow
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

class SOUI_EXP CDuiWindow : public CDuiObject
    , public CDuiEventSet
    , public CDuiRef
{
    SOUI_CLASS_NAME(CDuiWindow, "window")
    friend class CDuiLayout;
public:
    CDuiWindow();

    virtual ~CDuiWindow();
    virtual void OnFinalRelease();

    typedef struct tagDUIMSG
    {
        UINT uMsg;
        WPARAM wParam;
        LPARAM lParam;
    } DUIMSG,*PDUIMSG;
protected:
    HDUIWND m_hDuiWnd;
    IDuiContainer *m_pContainer;
    CDuiWindow *m_pOwner;
    CDuiWindow *m_pParent,*m_pFirstChild, *m_pLastChild, *m_pNextSibling,*m_pPrevSibling;    //�������ṹ
    UINT    m_nChildrenCount;
    DUIMSG        *m_pCurMsg;

    UINT m_uCmdID;
    CDuiStringA    m_strName;

    CRect m_rcWindow;

    DuiStyle m_style;
    CDuiStringT m_strInnerText;
    DWORD m_dwState;
    CDuiStringT m_strLinkUrl;
    BOOL m_bMsgTransparent;        //�������û�������־
    BOOL m_bVisible;            //�ɼ�״̬
    BOOL m_bDisplay;            //����ʱ�Ƿ�ռλ����ռλʱ�������²��֡�
    BOOL m_bDisable;            //����״̬
    CDuiStringT m_strToolTipText;
    int     m_nSepSpace;    //�Զ��Ű��ˮƽ�ո�
    BOOL m_bClipClient;
    BOOL m_bTabStop;
    BYTE m_byAlpha;        //����͸����,ֻ�������ã�֧�������ڿؼ���

    CDuiSkinBase * m_pBgSkin;
    CDuiSkinBase * m_pNcSkin;

    DUIWND_POSITION m_dlgpos;

    int                m_nMaxWidth;    //�Զ������Сʱʹ��
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
    LPCTSTR GetInnerText();


    // Set inner text
    HRESULT SetInnerText(LPCTSTR lpszText);

    VOID TestMainThread();

    // Send a message to DuiWindow
    LRESULT DuiSendMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0,BOOL *pbMsgHandled=NULL);

    PDUIMSG GetCurDuiMsg()
    {
        return m_pCurMsg;
    }

    // Move DuiWindow to new place
    void Move(LPRECT prect);

    void Move(int x,int y, int cx=-1,int cy=-1);

    // Set current cursor, when hover
    virtual BOOL OnDuiSetCursor(const CPoint &pt);

    // Get tooltip Info
    virtual BOOL OnUpdateToolTip(HDUIWND hCurTipHost,HDUIWND &hNewTipHost,CRect &rcTip,CDuiStringT &strTip);

    // Get DuiWindow state
    DWORD GetState(void);

    // Modify DuiWindow state
    DWORD ModifyState(DWORD dwStateAdd, DWORD dwStateRemove,BOOL bUpdate=FALSE);

    // Get Command ID
    UINT GetCmdID();
    void SetCmdID(UINT uNewID);

    ULONG_PTR GetUserData();
    ULONG_PTR SetUserData(ULONG_PTR uData);

    LPCSTR GetName(){ return m_strName.IsEmpty()?NULL:(LPCSTR)m_strName;}
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

    HDUIWND GetDuiHwnd();


    CDuiWindow *GetParent();

    void SetParent(CDuiWindow *pParent);

    CDuiWindow *GetTopLevelParent();

    BOOL DestroyChild(CDuiWindow *pChild);

    UINT GetChildrenCount();

    CDuiWindow * GetChild(UINT uCmdID);

    virtual void SetChildContainer(CDuiWindow *pChild);

    void InsertChild(CDuiWindow *pNewChild,CDuiWindow *pInsertAfter=ICWND_LAST);

    BOOL RemoveChild(CDuiWindow *pChild);

    BOOL IsChecked();

    BOOL IsDisabled(BOOL bCheckParent = FALSE);

    BOOL IsVisible(BOOL bCheckParent = FALSE);
    void SetVisible(BOOL bVisible,BOOL bUpdate=FALSE);

    void EnableWindow( BOOL bEnable,BOOL bUpdate=FALSE);

    void SetCheck(BOOL bCheck);

    BOOL NeedRedrawParent();

    LPCTSTR GetLinkUrl();

    IDuiContainer *GetContainer();

    void SetContainer(IDuiContainer *pContainer);

    void SetOwner(CDuiWindow *pOwner);

    CDuiWindow *GetOwner();

    BOOL IsMsgTransparent();

    DuiStyle& GetStyle();

    
    //************************************
    // Method:    FindChildByCmdID, ͨ��ID���Ҷ�Ӧ���Ӵ���
    // Access:    public 
    // Returns:   CDuiWindow*
    // Qualifier:
    // Parameter: UINT uCmdID
    //************************************
    CDuiWindow* FindChildByCmdID(UINT uCmdID);

    template<class T>
    T FindChildByCmdID2(UINT uCmdID)
    {
        return dynamic_cast<T>(FindChildByCmdID(uCmdID));
    }

    //************************************
    // Method:    FindChildByName��ͨ�����ֲ����Ӵ���
    // Access:    public 
    // Returns:   CDuiWindow*
    // Qualifier:
    // Parameter: LPCSTR pszName
    //************************************
    CDuiWindow* FindChildByName(LPCSTR pszName);

    template<class T>
    T FindChildByName2(LPCSTR pszName)
    {
        return dynamic_cast<T>(FindChildByName(pszName));
    }

    // ��XML�����Ӵ���
    // LPCSTR utf8Xml: utf8 �����XML��
    // return : ��������һ������
    CDuiWindow *LoadXmlChildren(LPCSTR utf8Xml);

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

    virtual BOOL LoadChildren(pugi::xml_node xmlNode);
    // Create DuiWindow from xml element
    virtual BOOL Load(pugi::xml_node xmlNode);

    virtual HDUIWND DuiGetHWNDFromPoint(CPoint ptHitTest, BOOL bOnlyText);

    virtual LRESULT DuiNotify(LPDUINMHDR pnms);

    virtual UINT OnGetDuiCode();

    virtual BOOL IsTabStop();

    virtual BOOL OnDuiNcHitTest(CPoint pt);


    virtual BOOL IsClipClient()
    {
        return m_bClipClient;
    }

    virtual void OnAttributeChanged(const CDuiStringA & strAttrName,BOOL bLoading,HRESULT hRet);

    //************************************
    // Method:    UpdateChildrenPosition :�����Ӵ���λ��
    // FullName:  SOUI::CDuiWindow::UpdateChildrenPosition
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
    BOOL RedrawRegion(CDCHandle& dc, CRgn& rgn);

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
    HDC GetDuiDC(const LPRECT pRc=NULL,DWORD gdcFlags=0,BOOL bClientDC=TRUE);


    //************************************
    // Method:    ReleaseDuiDC
    // Function:  �ͷ���GetDuiDC��ȡ��DC
    // Access:    public
    // Returns:   void
    // Parameter: HDC hdc
    // remark:
    //************************************
    void ReleaseDuiDC(HDC hdc);

    //************************************
    // Method:    PaintBackground
    // Function:  �����ڵı�������
    // Access:    public
    // Returns:   void
    // Parameter: HDC hdc Ŀ��DC
    // Parameter: LPRECT pRc Ŀ��λ��
    // remark:    Ŀ��λ�ñ����ڴ���λ����
    //************************************
    void PaintBackground(HDC hdc,LPRECT pRc);

    //************************************
    // Method:    PaintForeground
    // Function:  �����ڵ�ǰ������,��������ǰ���ڵ��Ӵ���
    // Access:    public
    // Returns:   void
    // Parameter: HDC hdc Ŀ��DC
    // Parameter: LPRECT pRc Ŀ��λ��
    // remark:    Ŀ��λ�ñ����ڴ���λ����
    //************************************
    void PaintForeground(HDC hdc,LPRECT pRc);


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
    static BOOL _PaintRegion(CDCHandle& dc, CRgn& rgn,CDuiWindow *pWndCur,CDuiWindow *pStart,CDuiWindow *pEnd,CDuiWindow::PRSTATE & prState);


    CRect        m_rcGetDC;
    DWORD        m_gdcFlags;
    int            m_nSaveDC;
public:
    HDUIWND GetDuiCapture();
    HDUIWND SetDuiCapture();

    BOOL ReleaseDuiCapture();
    void SetDuiFocus();
    void KillDuiFocus();

    CDuiWindow *GetCheckedRadioButton();

    void CheckRadioButton(CDuiWindow * pRadioBox);

    BOOL SetItemVisible(UINT uItemID, BOOL bVisible);

    BOOL IsItemVisible(UINT uItemID, BOOL bCheckParent = FALSE);
    BOOL GetItemCheck(UINT uItemID);

    BOOL SetItemCheck(UINT uItemID, BOOL bCheck);
    BOOL EnableItem(UINT uItemID, BOOL bEnable);
    BOOL IsItemEnable(UINT uItemID, BOOL bCheckParent = FALSE);

    CDuiWindow *GetDuiWindow(int uCode);    

    //************************************
    // Method:    BeforePaint
    // Function:  ΪDC׼���õ�ǰ���ڵĻ�ͼ����
    // Access:    public
    // Returns:   void
    // Parameter: CDCHandle & dc
    // Parameter: DuiDCPaint & DuiDC
    // remark:
    //************************************
    void BeforePaint(CDCHandle &dc, DuiDCPaint &DuiDC);

    //************************************
    // Method:    AfterPaint
    // Function:  �ָ���BeforePaint���õ�DC״̬
    // Access:    public
    // Returns:   void
    // Parameter: CDCHandle & dc
    // Parameter: DuiDCPaint & DuiDC
    // remark:
    //************************************
    void AfterPaint(CDCHandle &dc, DuiDCPaint &DuiDC);

    //************************************
    // Method:    BeforePaintEx
    // Function:  ΪDC׼���õ�ǰ���ڵĻ�ͼ����,�Ӷ��㴰�ڿ�ʼ����
    // Access:    public
    // Returns:   int ��ǰ��DC����
    // Parameter: CDCHandle & dc
    // remark: ʹ��ǰʹ��SaveDC������״̬��ʹ�ú����RestoreDC���ָ�״̬
    //************************************
    void BeforePaintEx(CDCHandle &dc);

    BOOL IsMsgHandled() const;

    void SetMsgHandled(BOOL bHandled);

protected:
    BOOL m_bMsgHandled;

    SOUO_ATTRIBUTES_BEGIN()
        DUIWIN_SKIN_ATTRIBUTE("skin", m_pBgSkin, TRUE)//ֱ�ӻ��Ƥ������
        DUIWIN_SKIN_ATTRIBUTE("ncskin", m_pNcSkin, TRUE)//ֱ�ӻ��Ƥ������
        DUIWIN_STRING_ATTRIBUTE("name",m_strName,FALSE)
        DUIWIN_STYLE_ATTRIBUTE("class", m_style, TRUE)    //���style
        DUIWIN_CHAIN_ATTRIBUTE(m_style)                    //֧�ֶ�style�е����Զ���
        DUIWIN_INT_ATTRIBUTE("id", m_uCmdID, FALSE)
        DUIWIN_INT_ATTRIBUTE("data", m_uData, 0 )
        DUIWIN_CUSTOM_ATTRIBUTE("state", OnAttributeState)
        DUIWIN_TSTRING_ATTRIBUTE("href", m_strLinkUrl, FALSE)
        DUIWIN_TSTRING_ATTRIBUTE("tip", m_strToolTipText, FALSE)
        DUIWIN_CUSTOM_ATTRIBUTE("pos", OnAttributePosition)
        DUIWIN_INT_ATTRIBUTE("show", m_bVisible,FALSE)
        DUIWIN_INT_ATTRIBUTE("display", m_bDisplay,FALSE)
        DUIWIN_INT_ATTRIBUTE("msgtransparent", m_bMsgTransparent, FALSE)
        DUIWIN_INT_ATTRIBUTE("sep", m_nSepSpace, FALSE)
        DUIWIN_INT_ATTRIBUTE("maxwidth",m_nMaxWidth,FALSE)
        DUIWIN_INT_ATTRIBUTE("clipclient",m_bClipClient,FALSE)
        DUIWIN_INT_ATTRIBUTE("tabstop",m_bTabStop,FALSE)
        DUIWIN_ENUM_ATTRIBUTE("pos2type",POS2TYPE,FALSE)
            DUIWIN_ENUM_VALUE("lefttop",POS2_LEFTTOP)
            DUIWIN_ENUM_VALUE("center",POS2_CENTER)
            DUIWIN_ENUM_VALUE("righttop",POS2_RIGHTTOP)
            DUIWIN_ENUM_VALUE("leftbottom",POS2_LEFTBOTTOM)
            DUIWIN_ENUM_VALUE("rightbottom",POS2_RIGHTBOTTOM)
        DUIWIN_ENUM_END(m_dlgpos.pos2Type)
        DUIWIN_INT_ATTRIBUTE("alpha",m_byAlpha,TRUE)
    SOUI_ATTRIBUTES_END()

protected:
    LRESULT NotifyCommand();
    LRESULT NotifyContextMenu(CPoint pt);

    //************************************
    // Method:    GetChildrenLayoutRect :�����Ӵ��ڵ��Ű�ռ�
    // FullName:  SOUI::CDuiWindow::GetChildrenLayoutRect
    // Access:    virtual protected 
    // Returns:   CRect
    // Qualifier:
    //************************************
    virtual CRect GetChildrenLayoutRect();

    void ClearLayoutState();

    //************************************
    // Method:    GetDesiredSize: ��û��ָ�����ڴ�Сʱ��ͨ����Ƥ�����㴰�ڵ�������С
    // FullName:  SOUI::CDuiWindow::GetDesiredSize
    // Access:    virtual protected 
    // Returns:   CSize
    // Qualifier:
    // Parameter: LPRECT pRcContainer
    //************************************
    virtual CSize GetDesiredSize(LPRECT pRcContainer);

    //************************************
    // Method:    CalcSize �����㴰�ڴ�С
    // FullName:  SOUI::CDuiWindow::CalcSize
    // Access:    protected 
    // Returns:   CSize
    // Qualifier:
    // Parameter: LPRECT pRcContainer
    //************************************
    CSize CalcSize(LPRECT pRcContainer);

    //************************************
    // Method:    GetNextVisibleWindow ���ָ�����ڵ���һ���ɼ�����
    // FullName:  SOUI::CDuiWindow::GetNextVisibleWindow
    // Access:    protected static 
    // Returns:   CDuiWindow *    :��һ���ɼ�����
    // Qualifier:
    // Parameter: CDuiWindow * pWnd    :�ο�����
    // Parameter: const CRect &rcDraw:Ŀ�����
    //************************************
    static CDuiWindow *GetNextVisibleWindow(CDuiWindow *pWnd,const CRect &rcDraw);

    virtual BOOL NeedRedrawWhenStateChange();
    virtual void GetTextRect(LPRECT pRect);
    virtual void DuiDrawText(HDC hdc,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat);
    virtual void DuiDrawFocus(HDC dc);

    void DuiDrawDefFocusRect(CDCHandle dc,CRect rc);
    void DrawAniStep(CRect rcFore,CRect rcBack,HDC dcFore,HDC dcBack,CPoint ptAnchor);
    void DrawAniStep( CRect rcWnd,HDC dcFore,HDC dcBack,BYTE byAlpha);
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
    BOOL OnEraseBkgnd(CDCHandle dc);

    // Draw inner text default
    void OnPaint(CDCHandle dc);


    //************************************
    // Method:    OnNcPaint
    // Function:  draw non-client area
    // Access:    protected
    // Returns:   void
    // Parameter: CDCHandle dc
    // remark:
    //************************************
    void OnNcPaint(CDCHandle dc);

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

    HRESULT OnAttributePosition(const CDuiStringA& strValue, BOOL bLoading);
    HRESULT OnAttributeState(const CDuiStringA& strValue, BOOL bLoading);

    WND_MSG_MAP_BEGIN()
        MSG_WM_ERASEBKGND(OnEraseBkgnd)
        MSG_WM_PAINT(OnPaint)
        MSG_WM_NCPAINT_EX(OnNcPaint)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_DUIWINPOSCHANGED(OnWindowPosChanged)
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
};
}//namespace SOUI