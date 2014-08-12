/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       Swnd.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    SOUI����DUI����ģ��
*/

#pragma once
#include "SWindowMgr.h"
#include "SwndContainer-i.h"

#include "helper/STimerEx.h"
#include "helper/SwndMsgCracker.h"

#include "event/EventSubscriber.h"
#include "event/events.h"
#include "event/EventSet.h"
#include <OCIdl.h>
#include "SwndLayout.h"
#include "res.mgr/SStylePool.h"
#include "res.mgr/SSkinPool.h"

namespace SOUI
{

    /////////////////////////////////////////////////////////////////////////
    enum {NormalShow=0,ParentShow=1};    //�ṩWM_SHOWWINDOW��Ϣʶ���Ǹ�������ʾ����Ҫ��ʾ������
    enum {NormalEnable=0,ParentEnable=1};    //�ṩWM_ENABLE��Ϣʶ���Ǹ����ڿ��û���ֱ�Ӳ�����ǰ����

#define SC_WANTARROWS     0x0001      /* Control wants arrow keys         */
#define SC_WANTTAB        0x0002      /* Control wants tab keys           */
#define SC_WANTRETURN     0x0004      /* Control wants return keys        */
#define SC_WANTCHARS      0x0008      /* Want WM_CHAR messages            */
#define SC_WANTALLKEYS    0xFFFF      /* Control wants all keys           */
#define SC_WANTSYSKEY     0x80000000    /* System Key */

    class SOUI_EXP STimerID
    {
    public:
        DWORD    Swnd:24;        //���ھ��,������ھ������24λ��Χ������ʹ�����ַ�ʽ���ö�ʱ��
        DWORD    uTimerID:7;        //��ʱ��ID��һ���������֧��128����ʱ����
        DWORD    bSwndTimer:1;    //����ͨ�ö�ʱ���ı�־����־Ϊ1ʱ����ʾ�ö�ʱ��ΪSWND��ʱ��

        STimerID(SWND hWnd,char id)
        {
            SASSERT(hWnd<0x00FFFFFF && id>=0);
            bSwndTimer=1;
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

    typedef enum tagGW_CODE
    {
        GSW_FIRSTCHILD=0,
        GSW_LASTCHILD,
        GSW_PREVSIBLING,
        GSW_NEXTSIBLING,
        GSW_PARENT,
        GSW_OWNER,
    } GW_CODE;

    typedef struct tagSWNDMSG
    {
        UINT uMsg;
        WPARAM wParam;
        LPARAM lParam;
    } SWNDMSG,*PSWNDMSG;

    /**
    * @class     SWindow
    * @brief     SOUI���ڻ��� 
    * 
    * Describe   SOUI���ڻ���,ʵ�ִ��ڵĻ����ӿ�
    */
    class SOUI_EXP SWindow : public SObject
        , public SMsgHandleState
        , public TObjRefImpl2<IObjRef,SWindow>
    {
        SOUI_CLASS_NAME(SWindow, L"window")
            friend class SwndLayout;
    public:
        SWindow();

        virtual ~SWindow();

    protected:
        SWND m_hSWnd;       /**< ���ھ�� */

        ISwndContainer *m_pContainer;/**< �������� */
        SEventSet   m_evtSet;/**< �����¼����� */

        SWindow *m_pOwner;  /**< ����Owner���¼��ַ�ʱ������¼�����Owner���� */
        SWindow *m_pParent; /**< ������ */
        SWindow *m_pFirstChild;/**< ��һ�Ӵ��� */
        SWindow *m_pLastChild;/**< ��󴰿� */
        SWindow *m_pNextSibling;/**< ǰһ�ֵܴ��� */
        SWindow *m_pPrevSibling; /**< ��һ�ֵܴ��� */
        UINT    m_nChildrenCount;  /**< �Ӵ������� */

        SWNDMSG        *m_pCurMsg;  /**< ��ǰ���ڴ���Ĵ�����Ϣ */

        CRect m_rcWindow;       /**< �����������е�λ�� */

        SStringW m_strName;     /**< �������� */
        int     m_nID;          /**< ����ID */

        SwndStyle m_style;      /**< ����Style����һ�鴰������ */
        SStringT m_strText;     /**< �������� */
        SStringT m_strToolTipText;/**< ����ToolTip */

        DWORD m_dwState;        /**< ����״̬ */
        DWORD m_bVisible:1;        /**< ���ڿɼ�״̬ */
        DWORD m_bDisplay:1;        /**< ��������ʱ�Ƿ�ռλ����ռλʱ�������²��� */
        DWORD m_bDisable:1;        /**< ���ڽ���״״̬ */
        DWORD m_bClipClient:1;     /**< ���ڻ���ʱ��clip�ͻ�������ı�־,����clip�������Ӽ�������ֻ�ڻ��ƿ����߳��ͻ���ʱ������*/
        DWORD m_bMsgTransparent:1; /**< ������Ϣ��־ TRUE-��������Ϣ */
        DWORD m_bFocusable:1;      /**< ���ڿɻ�ý����־ */
        DWORD m_bUpdateLocked:1;   /**< ��ʱ�������£������󣬲�����������Invalidate */
        DWORD m_bCacheDraw:1;      /**< ֧�ִ������ݵ�Cache��־ */
        DWORD m_bDirty:1;          /**< ���洰�����־ */

        BYTE m_byAlpha;         /**< ����͸����,ֻ�������ã�֧�������ڿؼ� */

        ISkinObj * m_pBgSkin;   /**< ����skin */
        ISkinObj * m_pNcSkin;   /**< �ǿͻ���skin */
        ULONG_PTR m_uData;      /**< ���ڵ�����λ,����ͨ��GetUserData��� */

        SwndLayout    m_layout; /**< ���ֶ��� */

        int           m_nMaxWidth;    /**< �Զ������Сʱ�����ڵ������ */

        CAutoRefPtr<IRenderTarget> m_cachedRT;/**< ���洰�ڻ��Ƶ�RT */
#ifdef _DEBUG
        DWORD m_nMainThreadId;  /**< �������߳�ID */
#endif
    public:

        //////////////////////////////////////////////////////////////////////////
        // Method Define

        /**
        * GetTextAlign
        * @brief    ����ı��Ķ����־
        * @return   UINT 
        *
        * Describe  ����ı��Ķ����־
        */
        UINT GetTextAlign();    

        /**
        * GetPositionType
        * @brief    ��ô��ڲ�������
        * @return   DWORD 
        *
        * Describe  ��ô��ڲ�������
        */
        DWORD GetPositionType();

        /**
        * SetPositionType
        * @brief    ���ò�������
        * @param    DWORD dwPosType --  ��������
        * @param    DWORD dwMask --  ��������mask
        * @return   void 
        *
        * Describe  
        */    
        void SetPositionType(DWORD dwPosType, DWORD dwMask = 0xFFFFFFFF);


        /**
         * SetFixSize
         * @brief    ���ô��ڴ�С
         * @param    int nWid --  ���ڿ��
         * @param    int nHei --  ���ڸ߶�
         * @return   void 
         *
         * Describe  
         */
        void SetFixSize(int nWid,int nHei);

        /**
        * GetWindowRect
        * @brief    ��ô����������е�λ��
        * @param    [out] LPRECT prect --  ���ھ���
        * @return   void 
        *
        * Describe  
        */    
        void GetWindowRect(LPRECT prect);

        /**
        * GetClientRect
        * @brief    ��ô��ڵĿͻ���
        * @param    [out] LPRECT pRect --  ���ھ���
        * @return   void 
        *
        * Describe  
        */
        virtual void GetClientRect(LPRECT pRect);

        /**
        * GetWindowText
        * @brief    ��ô����ı�
        * @return   SStringT 
        *
        * Describe  
        */
        SStringT GetWindowText();

        /**
        * SetWindowText
        * @brief    ���ô����ı�
        * @param    LPCTSTR lpszText --  �����ı�
        * @return   void 
        *
        * Describe  
        */
        void SetWindowText(LPCTSTR lpszText);


        /**
        * SSendMessage
        * @brief    ��SWND������������Ϣ
        * @param    UINT Msg --  ��Ϣ����
        * @param    WPARAM wParam --  ����1
        * @param    LPARAM lParam --  ����2
        * @param [out] BOOL * pbMsgHandled -- ��Ϣ�����־ 
        * @return   LRESULT ��Ϣ����״̬����������Ϣ����
        *
        * Describe  
        */
        LRESULT SSendMessage(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0,BOOL *pbMsgHandled=NULL);

        /**
        * GetCurMsg
        * @brief    ��õ�ǰ���ڴ������Ϣ
        * @return   PSWNDMSG 
        *
        * Describe  
        */
        PSWNDMSG GetCurMsg()
        {
            return m_pCurMsg;
        }

        /**
        * Move
        * @brief    �������ƶ���ָ��λ��
        * @param    LPRECT prect --  
        * @return   void 
        *
        * Describe  �ƶ��󣬴��ڵĲ��ֱ�־�Զ���ΪPos_Float
        */
        void Move(LPRECT prect);

        /**
        * Move
        * @brief    �������ƶ���ָ��λ��
        * @param    int x --  left
        * @param    int y --  top
        * @param    int cx --  width
        * @param    int cy --  height
        * @return   void 
        *
        * Describe 
        * @see     Move(LPRECT prect)
        */
        void Move(int x,int y, int cx=-1,int cy=-1);


        // Get SWindow state
        DWORD GetState(void);

        // Modify SWindow state
        DWORD ModifyState(DWORD dwStateAdd, DWORD dwStateRemove,BOOL bUpdate=FALSE);

        /**
        * GetUserData
        * @brief    ��userdata
        * @return   ULONG_PTR 
        *
        * Describe  
        */
        ULONG_PTR GetUserData();
        /**
        * SetUserData
        * @brief    ����userdata
        * @param    ULONG_PTR uData --  ԭ����userdata
        * @return   ULONG_PTR 
        *
        * Describe  
        */
        ULONG_PTR SetUserData(ULONG_PTR uData);

        /**
        * SetTimer
        * @brief    ���ô��ڶ�ʱ��������һ��IDΪ0-127��SWND��ʱ��
        * @param    char id --  ��ʱ��ID
        * @param    UINT uElapse --  ��ʱ(MS)
        * @return   BOOL 
        *
        * Describe  �ο�::SetTimer
        */
        BOOL SetTimer(char id,UINT uElapse);

        /**
        * KillTimer
        * @brief    ɾ��һ��SWND��ʱ��
        * @param    char id --  ��ʱ��ID
        * @return   void 
        *
        * Describe  
        */
        void KillTimer(char id);

        /**
        * SetTimer2
        * @brief    ���ú�����ʱ����ģ��һ�����ݴ��ڶ�ʱ��
        * @param    UINT_PTR id --  ��ʱ��ID
        * @param    UINT uElapse --  ��ʱ(MS)
        * @return   BOOL 
        *
        * Describe  ����SetTimerֻ֧��0-127�Ķ�ʱ��ID��SetTimer2�ṩ��������timerid
        *           �ܹ�ʹ��SetTimerʱ��������SetTimer2����KillʱЧ�ʻ�Ƚϵ�
        */
        BOOL SetTimer2(UINT_PTR id,UINT uElapse);

        /**
        * KillTimer2
        * @brief    ɾ��һ��SetTimer2���õĶ�ʱ��
        * @param    UINT_PTR id --  
        * @return   void 
        *
        * Describe  ��Ҫö�ٶ�ʱ���б�
        */
        void KillTimer2(UINT_PTR id);

        /**
        * GetSwnd
        * @brief    ��ô��ھ��
        * @return   SWND 
        *
        * Describe  
        */
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

        ISwndContainer *GetContainer();

        void SetContainer(ISwndContainer *pContainer);

        void SetOwner(SWindow *pOwner);

        SWindow *GetOwner();

        BOOL IsMsgTransparent();

        SwndStyle& GetStyle();

        LPCWSTR GetName(){return m_strName;}
        void SetName(LPCWSTR pszName){m_strName=pszName;}

        int GetID(){return m_nID;}
        void SetID(int nID){m_nID=nID;}

        /**
        * FindChildByID
        * @brief    ͨ��ID���Ҷ�Ӧ���Ӵ���
        * @param    int nID --  ����ID
        * @return   SWindow* 
        *
        * Describe  
        */
        SWindow* FindChildByID(int nID);

        /**
        * FindChildByID2
        * @brief    FindChildByID��ģ���֧࣬������ת��
        * @param    int nID --  ����ID
        * @return   T* 
        *
        * Describe  
        */
        template<class T>
        T* FindChildByID2(int nID)
        {
            SWindow *pTarget = FindChildByID(nID);
            if(!pTarget || !pTarget->IsClass(T::GetClassName()))
            {
                SASSERT(pTarget);
                return NULL;
            }
            return (T*)pTarget;
        }

        /**
        * FindChildByName
        * @brief    ͨ�����ֲ����Ӵ���
        * @param    LPCWSTR pszName --  ����name����
        * @return   SWindow* 
        *
        * Describe  
        */
        SWindow* FindChildByName(LPCWSTR pszName);

        template<class T>
        T* FindChildByName2(LPCWSTR pszName)
        {
            SWindow *pTarget = FindChildByName(pszName);
            if(!pTarget || !pTarget->IsClass(T::GetClassName()))
            {
                SASSERT(pTarget);
                return NULL;
            }
            return (T*)pTarget;
        }

        /**
        * CreateChildren
        * @brief    ��XML�����Ӵ���
        * @param    LPCWSTR pszXml --  �Ϸ���utf16����XML�ַ���
        * @return   SWindow * �����ɹ��ĵ����һ������
        *
        * Describe  
        */
        SWindow *CreateChildren(LPCWSTR pszXml);

        void Invalidate();
        void InvalidateRect(LPRECT lprect);
        void InvalidateRect(const CRect& rect);
        void LockUpdate();
        void UnlockUpdate();
        BOOL IsUpdateLocked();
        void BringWindowToTop();

    public:
        //////////////////////////////////////////////////////////////////////////
        // Virtual functions

        /**
        * IsSiblingsAutoGroupped
        * @brief    ͬ�ര���Զ������־
        * @return   BOOL 
        *
        * Describe  ��Ҫ�Ǹ�RadioButton�õ�
        */
        virtual BOOL IsSiblingsAutoGroupped(){return FALSE;}

        /**
        * GetSelectedSiblingInGroup
        * @brief    �����һ��group��ѡ��״̬�Ĵ���
        * @return   SWindow * 
        *
        * Describe  ����group�еĴ���ʱ����NULL
        */
        virtual SWindow * GetSelectedSiblingInGroup(){return NULL;}

        virtual void OnSetCaretValidateRect(LPCRECT lpRect)
        {
            CRect rcClient;
            GetClientRect(&rcClient);
            CRect rcIntersect;
            rcIntersect.IntersectRect(&rcClient,lpRect);
            if(GetParent()) GetParent()->OnSetCaretValidateRect(&rcIntersect);
        }
        // Set current cursor, when hover
        virtual BOOL OnSetCursor(const CPoint &pt);

        // Get tooltip Info
        virtual BOOL OnUpdateToolTip(SWND hCurTipHost,SWND &hNewTipHost,CRect &rcTip,SStringT &strTip);

        virtual void OnStateChanged(DWORD dwOldState,DWORD dwNewState) {}

        virtual BOOL CreateChildren(pugi::xml_node xmlNode);
        // Create SWindow from xml element
        virtual BOOL InitFromXml(pugi::xml_node xmlNode);

        virtual SStringW tr(const SStringW &strSrc);

        virtual SWND SwndFromPoint(CPoint ptHitTest, BOOL bOnlyText);

        virtual BOOL FireEvent(EventArgs &evt);

        SEventSet * GetEventSet(){return &m_evtSet;}

        virtual UINT OnGetDlgCode();

        virtual BOOL IsFocusable();

        virtual BOOL OnNcHitTest(CPoint pt);

        virtual BOOL IsClipClient()
        {
            return m_bClipClient;
        }


        /**
        * UpdateChildrenPosition
        * @brief    �����Ӵ���λ��
        * @return   void 
        *
        * Describe  
        */
        virtual void UpdateChildrenPosition();

    public:
        /**
        * RedrawRegion
        * @brief    �����ڼ��Ӵ������ݻ��Ƶ�RenderTarget
        * @param    IRenderTarget * pRT --  ��ȾĿ��RT
        * @param    IRegion * pRgn --  ��Ⱦ����ΪNULLʱ��Ⱦ��������
        * @return   void 
        *
        * Describe  
        */
        void RedrawRegion(IRenderTarget *pRT, IRegion *pRgn);

        /**
        * GetRenderTarget
        * @brief    ��ȡһ����SWND��������Ӧ���ڴ�DC
        * @param    const LPRECT pRc --  RT��Χ
        * @param    DWORD gdcFlags --  ͬOLEDCFLAGS
        * @param    BOOL bClientDC --  ������client����
        * @return   IRenderTarget * 
        *
        * Describe  ʹ��ReleaseRenderTarget�ͷ�
        */
        IRenderTarget * GetRenderTarget(const LPRECT pRc=NULL,DWORD gdcFlags=0,BOOL bClientDC=TRUE);


        /**
        * ReleaseRenderTarget
        * @brief    
        * @param    IRenderTarget * pRT --  �ͷ���GetRenderTarget��ȡ��RT
        * @return   void 
        *
        * Describe  
        */
        void ReleaseRenderTarget(IRenderTarget *pRT);

        /**
        * PaintBackground
        * @brief    �����ڵı�������
        * @param    IRenderTarget * pRT --  Ŀ��RT
        * @param    LPRECT pRc --  Ŀ��λ��
        * @return   void 
        *
        * Describe  Ŀ��λ�ñ����ڴ���λ����
        */
        void PaintBackground(IRenderTarget *pRT,LPRECT pRc);

        /**
        * PaintForeground
        * @brief    �����ڵ�ǰ������
        * @param    IRenderTarget * pRT --  Ŀ��RT
        * @param    LPRECT pRc --  Ŀ��λ��
        * @return   void 
        *
        * Describe  Ŀ��λ�ñ����ڴ���λ����,��������ǰ���ڵ��Ӵ���
        */
        void PaintForeground(IRenderTarget *pRT,LPRECT pRc);


        /**
        * AnimateWindow
        * @brief    ���ڶ���Ч��
        * @param    DWORD dwTime --  ִ��ʱ��
        * @param    DWORD dwFlags --  ִ��ģʽ
        * @return   BOOL 
        *
        * Describe  
        */
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

        SWindow *GetWindow(int uCode);    

        /**
        * BeforePaint
        * @brief    ΪRT׼���õ�ǰ���ڵĻ�ͼ����
        * @param    IRenderTarget * pRT --  
        * @param    SPainter & painter --  
        * @return   void 
        *
        * Describe  
        */
        void BeforePaint(IRenderTarget *pRT, SPainter &painter);

        /**
        * AfterPaint
        * @brief    �ָ���BeforePaint���õ�RT״̬
        * @param    IRenderTarget * pRT --  
        * @param    SPainter & painter --  
        * @return   void 
        *
        * Describe  
        */
        void AfterPaint(IRenderTarget *pRT, SPainter &painter);

        /**
        * BeforePaintEx
        * @brief    ΪDC׼���õ�ǰ���ڵĻ�ͼ����,�Ӷ��㴰�ڿ�ʼ����
        * @param    IRenderTarget * pRT --  ��ȾRT
        * @return   void 
        *
        * Describe  һ��Ӧ�ú�CreateRanderTarget���ʹ��
        */
        void BeforePaintEx(IRenderTarget *pRT);

        /**
        * FireCommand
        * @brief    ����ڵ�EVT_CMD�¼�
        * @return   BOOL-- true:EVT_CMD�¼�������
        *
        * Describe  
        */
        BOOL FireCommand();

        /**
        * FireCtxMenu
        * @brief    �����ݲ˵��¼�
        * @param    CPoint pt --  �����λ��
        * @return   BOOL -- true:�ⲿ�����˿�ݲ˵��¼�
        *
        * Describe  
        */
        BOOL FireCtxMenu(CPoint pt);
    protected:
        /**
         * IsCacheDirty
         * @brief    ��ѯCache��Dirty��־
         * @return   bool -- true��ʾCache�Ѿ�Dirty
         * Describe  
         */    
        bool IsCacheDirty() const  {return m_bCacheDraw&&m_bDirty;}

        /**
         * MarkCacheDirty
         * @brief    ���Cache��Dirty��־
         * @param    bool bDirty --  Dirty��־
         * @return   void
         * Describe  
         */    
        void MarkCacheDirty(bool bDirty) {m_bDirty = bDirty;}

        /**
         * IsDrawToCache
         * @brief    �鿴��ǰ�Ƿ��ǰѴ������ݻ��Ƶ�cache��
         * @return   bool -- true���Ƶ�cache�ϡ�
         * Describe  
         */    
        bool IsDrawToCache() const {return m_bCacheDraw;}

        /**
         * GetCachedRenderTarget
         * @brief    ���Cache�������ݵ�RenderTarget
         * @return   IRenderTarget * -- Cache�������ݵ�RenderTarget
         * Describe  
         */    
        IRenderTarget * GetCachedRenderTarget(){return m_cachedRT;}

        void TestMainThread();

        /**
        * GetChildrenLayoutRect
        * @brief    ����Ӵ��ڵĲ��ֿռ�
        * @return   CRect 
        *
        * Describe  
        */
        virtual CRect GetChildrenLayoutRect();

        /**
        * ClearLayoutState
        * @brief    ����Ӵ��ڵĲ���״̬��־
        * @return   void 
        *
        * Describe  
        */
        void ClearLayoutState();

        /**
        * GetDesiredSize
        * @brief    ��û��ָ�����ڴ�Сʱ��ͨ����Ƥ�����㴰�ڵ�������С
        * @param    LPRECT pRcContainer --  ����λ��
        * @return   CSize 
        *
        * Describe  
        */
        virtual CSize GetDesiredSize(LPRECT pRcContainer);

        /**
        * GetNextVisibleWindow
        * @brief    ���ָ�����ڵ���һ���ɼ�����
        * @param    SWindow * pWnd --  �ο�����
        * @param    const CRect & rcDraw --  Ŀ�����
        * @return   SWindow * ��һ���ɼ�����
        *
        * Describe  
        */
        static SWindow *GetNextVisibleWindow(SWindow *pWnd,const CRect &rcDraw);

        typedef enum _PRSTATE{
            PRS_LOOKSTART=0,    //���ҿ�ʼ����
            PRS_DRAWING,        //������Ⱦ��
            PRS_MEETEND         //����ָ���Ľ�������
        } PRSTATE;

        static  BOOL _PaintRegion( IRenderTarget *pRT, IRegion *pRgn,SWindow *pWndCur,SWindow *pStart,SWindow *pEnd,PRSTATE & prState );

        virtual BOOL NeedRedrawWhenStateChange();
        virtual void GetTextRect(LPRECT pRect);
        virtual void DrawText(IRenderTarget *pRT,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat);
        virtual void DrawFocus(IRenderTarget *pRT);

        void DrawDefFocusRect(IRenderTarget *pRT,CRect rc);
        void DrawAniStep(CRect rcFore,CRect rcBack,IRenderTarget *pRTFore,IRenderTarget * pRTBack,CPoint ptAnchor);
        void DrawAniStep( CRect rcWnd,IRenderTarget *pRTFore,IRenderTarget * pRTBack,BYTE byAlpha);

    protected:
        //////////////////////////////////////////////////////////////////////////
        // Message Handler

        /**
        * SwndProc
        * @brief    Ĭ�ϵ���Ϣ������
        * @param    UINT uMsg --  ��Ϣ����
        * @param    WPARAM wParam --  ����1
        * @param    LPARAM lParam --  ����2
        * @param    LRESULT & lResult --  ��Ϣ����ֵ
        * @return   BOOL �Ƿ񱻴���
        *
        * Describe  ����Ϣӳ�����û�д������Ϣ����ú�������
        */
        virtual BOOL SwndProc(UINT uMsg,WPARAM wParam,LPARAM lParam,LRESULT & lResult)
        {
            return FALSE;
        }

        LRESULT OnWindowPosChanged(LPRECT lpRcContainer);

        int OnCreate(LPVOID);

        void OnSize(UINT nType, CSize size);

        void OnDestroy();

        BOOL OnEraseBkgnd(IRenderTarget *pRT);

        void OnPaint(IRenderTarget *pRT);

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

        //////////////////////////////////////////////////////////////////////////
        // ���Դ�����
        HRESULT OnAttrPos(const SStringW& strValue, BOOL bLoading);
        HRESULT OnAttrVisible(const SStringW& strValue, BOOL bLoading);
        HRESULT OnAttrEnable(const SStringW& strValue, BOOL bLoading);
        HRESULT OnAttrDisplay(const SStringW& strValue, BOOL bLoading);
        HRESULT OnAttrCache(const SStringW& strValue, BOOL bLoading);
        HRESULT OnAttrSkin(const SStringW& strValue, BOOL bLoading);
        HRESULT OnAttrClass(const SStringW& strValue, BOOL bLoading);

        SOUI_MSG_MAP_BEGIN()
            MSG_WM_PAINT_EX(OnPaint)
            MSG_WM_ERASEBKGND_EX(OnEraseBkgnd)
            MSG_WM_NCPAINT_EX(OnNcPaint)
            MSG_WM_CREATE(OnCreate)
            MSG_WM_SIZE(OnSize)
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
        WND_MSG_MAP_END_BASE()  //��Ϣ���������ഫ�ݣ�����ʹ��WND_MSG_MAP_END_BASE������WND_MSG_MAP_END

        SOUI_ATTRS_BEGIN()
            ATTR_INT(L"id",m_nID,FALSE)
            ATTR_STRINGW(L"name",m_strName,FALSE)
            ATTR_CUSTOM(L"skin", OnAttrSkin)        //ֱ�ӻ��Ƥ������
            ATTR_SKIN(L"ncskin", m_pNcSkin, TRUE)   //ֱ�ӻ��Ƥ������
            ATTR_CUSTOM(L"class", OnAttrClass)      //���style
            ATTR_CHAIN(m_style)                     //֧�ֶ�style�е����Զ���
            ATTR_INT(L"data", m_uData, 0 )
            ATTR_CUSTOM(L"enable", OnAttrEnable)
            ATTR_CUSTOM(L"visible", OnAttrVisible)
            ATTR_CUSTOM(L"show", OnAttrVisible)
            ATTR_CUSTOM(L"pos", OnAttrPos)
            ATTR_CUSTOM(L"cache", OnAttrCache)
            ATTR_CUSTOM(L"display", OnAttrDisplay)
            ATTR_I18NSTRT(L"tip", m_strToolTipText, FALSE)  //ʹ�����԰�����
            ATTR_INT(L"msgTransparent", m_bMsgTransparent, FALSE)
            ATTR_INT(L"maxWidth",m_nMaxWidth,FALSE)
            ATTR_INT(L"clipClient",m_bClipClient,FALSE)
            ATTR_INT(L"focusable",m_bFocusable,FALSE)
            ATTR_ENUM_BEGIN(L"pos2type",POS2TYPE,FALSE)
                ATTR_ENUM_VALUE(L"leftTop",POS2_LEFTTOP)
                ATTR_ENUM_VALUE(L"center",POS2_CENTER)
                ATTR_ENUM_VALUE(L"righTtop",POS2_RIGHTTOP)
                ATTR_ENUM_VALUE(L"leftBottom",POS2_LEFTBOTTOM)
                ATTR_ENUM_VALUE(L"rightBottom",POS2_RIGHTBOTTOM)
            ATTR_ENUM_END(m_layout.pos2Type)
            ATTR_INT(L"sep", m_layout.nSepSpace, FALSE)
            ATTR_INT(L"alpha",m_byAlpha,TRUE)
        SOUI_ATTRS_END()

    };
}//namespace SOUI