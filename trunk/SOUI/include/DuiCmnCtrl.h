/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       DuiCmnCtrl.h
 * @brief      ͨ�ÿؼ�
 * @version    v1.0      
 * @author     soui      
 * @date       2014-05-28
 * 
 * Describe    ���ļ��ж����˺ܶ�ͨ�ÿؼ�:��̬�ı��������ӣ���ť����ѡ��ť��
 */

#pragma once
#include "duiwnd.h"
#include "DuiPanel.h"
#include "duiwndnotify.h"
#include "Accelerator.h"

namespace SOUI
{
/**
 * @class      CDuiSpacing
 * @brief      �ո�ؼ���
 * 
 * Describe    �ո�ؼ���
 * Usage       <spacing width=xx />
 */
class SOUI_EXP CDuiSpacing : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiSpacing, "spacing")
public:
    // Do nothing
    void OnPaint(CDCHandle dc){}

protected:
    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()
};

/**
 * @class      CDuiStatic
 * @brief      ��̬�ı��ؼ���
 * 
 * Describe    ��̬�ı��ؼ���֧�ֶ��У��ж�������ʱ��\n����ǿ�ƻ���
 * Usage       <text>inner text example</text>
 */
class SOUI_EXP CDuiStatic : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiStatic, "text")
public:
    /**
     * CDuiStatic::CDuiStatic
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiStatic():m_bMultiLines(0),m_nLineInter(5)
    {
        m_bMsgTransparent=TRUE;
        m_style.SetAttribute("align","left");
    }
    /**
     * CDuiStatic::DuiDrawText
     * @brief    �����ı�
     * @param    HDC hdc -- �����豸���         
     * @param    LPCTSTR pszBuf -- �ı������ַ���         
     * @param    int cchText -- �ַ�������         
     * @param    LPRECT pRect -- ָ����νṹRECT��ָ��         
     * @param    UINT uFormat --  ���ĵĻ���ѡ��         
     *
     * Describe  ��DrawText��װ
     */    
    virtual void DuiDrawText(HDC hdc,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat);

protected:
    int m_bMultiLines;  /**< �Ƿ���������ʾ */  
    int m_nLineInter;   /**< ���� �д����� */

    SOUO_ATTRIBUTES_BEGIN()
    DUIWIN_INT_ATTRIBUTE("multilines", m_bMultiLines, FALSE)
    DUIWIN_INT_ATTRIBUTE("interhei", m_nLineInter, FALSE)
    SOUI_ATTRIBUTES_END()
};

/**
 * @class      CDuiLink
 * @brief      �����ӿؼ���
 * 
 * Describe    Only For Header Drag Test
 * Usage       <link>inner text example</link>
 */
class SOUI_EXP CDuiLink : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiLink, "link")

public:
    /**
     * CDuiLink::CDuiLink
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiLink()
    {
        m_style.SetAttribute("align","left");
    }

protected:
    /**
     * CDuiLink::OnAttributeFinish
     * @brief    ����xml��������
     *
     * Describe  ����xml�ļ������������
     */
    virtual void OnAttributeFinish(pugi::xml_node xmlNode);
    /**
     * CDuiLink::DuiDrawText
     * @brief    �����ı�
     * @param    HDC hdc -- �����豸���         
     * @param    LPCTSTR pszBuf -- �ı������ַ���         
     * @param    int cchText -- �ַ�������         
     * @param    LPRECT pRect -- ָ����νṹRECT��ָ��         
     * @param    UINT uFormat --  ���ĵĻ���ѡ��         
     *
     * Describe  ��DrawText��װ
     */
    virtual void DuiDrawText(HDC hdc,LPCTSTR pszBuf,int cchText,LPRECT pRect,UINT uFormat);

    /**
     * CDuiLink::OnDuiSetCursor
     * @brief    ���ù����ʽ��λ��
     * @param    CPoint &pt -- ���ù��λ��
     *
     * Describe  �����ڲ�����ع����ʽ
     */
    virtual BOOL OnDuiSetCursor(const CPoint &pt);

    void OnLButtonDown(UINT nFlags,CPoint pt);
    void OnLButtonUp(UINT nFlags,CPoint pt);
    void OnMouseMove(UINT nFlags,CPoint pt);
    void OnMouseHover(WPARAM wParam, CPoint ptPos);

    WND_MSG_MAP_BEGIN()
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSEHOVER(OnMouseHover)
    WND_MSG_MAP_END()

    CRect m_rcText;  /**< �ı���ʾ����λ�� */
};

/**
 * @class      CDuiButton
 * @brief      ��ť�ؼ���
 * 
 * Describe    ͨ������ID��click�¼� Use id attribute to process click event
 * Usage       <button id=xx>inner text example</button>
 */
class SOUI_EXP CDuiButton : public CDuiWindow
    , public IAcceleratorTarget
    , public ITimelineHandler
{
    SOUI_CLASS_NAME(CDuiButton, "button")
public:
    /**
     * CDuiButton::CDuiButton
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiButton();
protected:
    /**
     * CDuiLink::NeedRedrawWhenStateChange
     * @brief    ״̬�仯��Ҫ�ػ�
     *
     * Describe  ����ť״̬�����仯ʱ����Ҫ���»��� Ĭ�Ϸ���TRUE
     */
    virtual BOOL NeedRedrawWhenStateChange()
    {
        return TRUE;
    }
    /**
     * CDuiLink::OnGetDuiCode
     * @brief    ��ñ���
     *
     * Describe  ���غ궨��DUIC_WANTCHARS������ҪWM_CHAR��Ϣ
     */
    virtual UINT OnGetDuiCode()
    {
        return DUIC_WANTCHARS;
    }

    /**
     * CDuiLink::OnAcceleratorPressed
     * @brief    ���ټ�����
     * @param    CAccelerator& accelerator -- ���ټ���ؽṹ��
     *
     * Describe  ������ټ���Ӧ��Ϣ
     */
    virtual bool OnAcceleratorPressed(const CAccelerator& accelerator);
protected:
    /**
     * CDuiLink::GetDesiredSize
     * @brief    ��������Ĵ�Сֵ
     * @param    LPRECT pRcContainer -- ���ݴ������
     *
     * Describe  �������ݴ�����δ�С��������ʺϵĴ�С
     */
    virtual CSize GetDesiredSize(LPRECT pRcContainer);

    virtual void OnStateChanged(DWORD dwOldState,DWORD dwNewState);
    
    void OnPaint(CDCHandle dc);

    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

    void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

    void OnDestroy();

    void OnSize(UINT nType, CSize size);

    BOOL OnEraseBkgnd(CDCHandle dc){return TRUE;}

    HRESULT OnAttrAccel(CDuiStringA strAccel,BOOL bLoading);

protected:
    virtual void OnNextFrame();
    void StopCurAnimate();

    DWORD  m_accel;
    BOOL   m_bAnimate;    /**< ������־ */
    BYTE   m_byAlphaAni;  /**< ����״̬ */
public:
    SOUO_ATTRIBUTES_BEGIN()
        DUIWIN_CUSTOM_ATTRIBUTE("accel",OnAttrAccel)
        DUIWIN_INT_ATTRIBUTE("animate", m_bAnimate, FALSE)
    SOUI_ATTRIBUTES_END()

    WND_MSG_MAP_BEGIN()
        MSG_WM_PAINT(OnPaint)
        MSG_WM_ERASEBKGND(OnEraseBkgnd)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_KEYDOWN(OnKeyDown)
        MSG_WM_KEYUP(OnKeyUp)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_SIZE(OnSize)
    WND_MSG_MAP_END()
};

class SOUI_EXP CDuiImageBtnWnd : public CDuiButton
{
    SOUI_CLASS_NAME(CDuiImageBtnWnd, "imgbtn")
public:
    CDuiImageBtnWnd()
    {
        m_bTabStop=FALSE;
    }
};

//////////////////////////////////////////////////////////////////////////
// Image Control
// Use src attribute specify a resource id
//
// Usage: <img skin="skin" sub="0"/>
//
class SOUI_EXP CDuiImageWnd : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiImageWnd, "img")
public:
    CDuiImageWnd();

    virtual ~CDuiImageWnd();

    void OnPaint(CDCHandle dc);

    BOOL SetSkin(CDuiSkinBase *pSkin,int nSubID=0);

    BOOL SetIcon(int nSubID);

    CDuiSkinBase * GetSkin(){return m_pSkin;}
protected:
    virtual CSize GetDesiredSize(LPRECT pRcContainer);

    BOOL m_bManaged;
    int m_nSubImageID;
    CDuiSkinBase *m_pSkin;
    //BOOL m_bCalc;

    SOUO_ATTRIBUTES_BEGIN()
    DUIWIN_SKIN_ATTRIBUTE("skin", m_pSkin, TRUE)
    DUIWIN_INT_ATTRIBUTE("sub", m_nSubImageID, FALSE)
    SOUI_ATTRIBUTES_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()
};


class SOUI_EXP CDuiAnimateImgWnd : public CDuiWindow, public ITimelineHandler
{
    SOUI_CLASS_NAME(CDuiAnimateImgWnd, "animateimg")
public:
    CDuiAnimateImgWnd();
    virtual ~CDuiAnimateImgWnd() {}

    void Start();

    void Stop();

    BOOL IsPlaying(){return m_bPlaying;}
protected:
    virtual CSize GetDesiredSize(LPRECT pRcContainer);
    virtual void OnNextFrame();

    void OnPaint(CDCHandle dc);

    void OnShowWindow(BOOL bShow, UINT nStatus);
    void OnDestroy();

    WND_MSG_MAP_BEGIN()
        MSG_WM_PAINT(OnPaint)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_SHOWWINDOW(OnShowWindow)
    WND_MSG_MAP_END()

    SOUO_ATTRIBUTES_BEGIN()
    DUIWIN_SKIN_ATTRIBUTE("skin", m_pSkin, TRUE)
    DUIWIN_UINT_ATTRIBUTE("speed", m_nSpeed, FALSE)
    DUIWIN_UINT_ATTRIBUTE("autostart", m_bAutoStart, FALSE)
    SOUI_ATTRIBUTES_END()

protected:
    CDuiSkinBase *m_pSkin;
    int              m_nSpeed;
    int              m_iCurFrame;
    BOOL          m_bAutoStart;
    BOOL          m_bPlaying;
};
//////////////////////////////////////////////////////////////////////////
// Progress Control
// Use id attribute to process click event
//
// Usage: <progress bgskin=xx posskin=xx min=0 max=100 value=10,showpercent=0/>
//

class SOUI_EXP CDuiProgress : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiProgress, "progress")
public:
    CDuiProgress();

    BOOL SetValue(int nValue);

    int GetValue(){return m_nValue;}

    void SetRange(int nMin,int nMax);

    void GetRange(int *pMin,int *pMax);

    BOOL IsVertical(){return m_bVertical;}
protected:

    virtual CSize GetDesiredSize(LPRECT pRcContainer);

    void OnPaint(CDCHandle dc);

    int m_nMinValue;
    int m_nMaxValue;
    int m_nValue;

    BOOL m_bShowPercent;
    BOOL    m_bVertical;

    CDuiSkinBase *m_pSkinBg;
    CDuiSkinBase *m_pSkinPos;

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()

    SOUO_ATTRIBUTES_BEGIN()
    DUIWIN_SKIN_ATTRIBUTE("bgskin", m_pSkinBg, TRUE)
    DUIWIN_SKIN_ATTRIBUTE("posskin", m_pSkinPos, TRUE)
    DUIWIN_INT_ATTRIBUTE("min", m_nMinValue, FALSE)
    DUIWIN_INT_ATTRIBUTE("max", m_nMaxValue, FALSE)
    DUIWIN_INT_ATTRIBUTE("value", m_nValue, FALSE)
    DUIWIN_UINT_ATTRIBUTE("vertical", m_bVertical, FALSE)
    DUIWIN_UINT_ATTRIBUTE("showpercent", m_bShowPercent, FALSE)
    SOUI_ATTRIBUTES_END()
};


//////////////////////////////////////////////////////////////////////////
// Line Control
// Simple HTML "HR" tag
//
// Usage: <hr style=solid size=1 crbg=.../>
//
class SOUI_EXP CDuiLine : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiLine, "hr")

public:

    CDuiLine();

    // Do nothing
    void OnPaint(CDCHandle dc);
protected:
    int m_nPenStyle;
    int m_nLineSize;
    BOOL m_bLineShadow;
    COLORREF m_crShadow;
    enum HRMODE{
        HR_HORZ=0,
        HR_VERT,
        HR_TILT,
    }m_mode;

    SOUO_ATTRIBUTES_BEGIN()
    DUIWIN_INT_ATTRIBUTE("size", m_nLineSize, FALSE)
    DUIWIN_UINT_ATTRIBUTE("shadow", m_bLineShadow, FALSE)
    DUIWIN_COLOR_ATTRIBUTE("crshadow", m_crShadow, FALSE)
    DUIWIN_ENUM_ATTRIBUTE("mode", HRMODE, FALSE)
        DUIWIN_ENUM_VALUE("vertical", HR_VERT)
        DUIWIN_ENUM_VALUE("horizon", HR_VERT)
        DUIWIN_ENUM_VALUE("tilt", HR_VERT)
    DUIWIN_ENUM_END(m_mode)
    DUIWIN_ENUM_ATTRIBUTE("style", int, FALSE)
    DUIWIN_ENUM_VALUE("solid", PS_SOLID)             // default
    DUIWIN_ENUM_VALUE("dash", PS_DASH)               /* -------  */
    DUIWIN_ENUM_VALUE("dot", PS_DOT)                 /* .......  */
    DUIWIN_ENUM_VALUE("dashdot", PS_DASHDOT)         /* _._._._  */
    DUIWIN_ENUM_VALUE("dashdotdot", PS_DASHDOTDOT)   /* _.._.._  */
    DUIWIN_ENUM_END(m_nPenStyle)
    SOUI_ATTRIBUTES_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()
};

//////////////////////////////////////////////////////////////////////////
// Check Box
//
// Usage: <check state=4>This is a check-box</check>
//
class SOUI_EXP CDuiCheckBox : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiCheckBox, "check")

    enum
    {
        CheckBoxSpacing = 4,
    };

public:

    CDuiCheckBox();

    void OnPaint(CDCHandle dc);
protected:

    CDuiSkinBase *m_pSkin;
    CDuiSkinBase *m_pFocusSkin;

    UINT _GetDrawState();
    CRect GetCheckRect();

    virtual CSize GetDesiredSize(LPRECT pRcContainer);

    virtual void GetTextRect(LPRECT pRect);

    virtual BOOL NeedRedrawWhenStateChange()
    {
        return TRUE;
    }

    virtual UINT OnGetDuiCode()
    {
        return DUIC_WANTCHARS;
    }

    virtual void DuiDrawFocus(HDC dc);

    void OnLButtonDown(UINT nFlags, CPoint point);

    void OnLButtonUp(UINT nFlags, CPoint point);

    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

    SOUO_ATTRIBUTES_BEGIN()
        DUIWIN_SKIN_ATTRIBUTE("skin", m_pSkin, FALSE)
        DUIWIN_SKIN_ATTRIBUTE("focusskin", m_pFocusSkin, FALSE)
    SOUI_ATTRIBUTES_END()

    WND_MSG_MAP_BEGIN()
        MSG_WM_PAINT(OnPaint)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_KEYDOWN(OnKeyDown)
    WND_MSG_MAP_END()
};

//////////////////////////////////////////////////////////////////////////
// Icon Control
// Use src attribute specify a resource id
//
// Usage: <icon src=xx size="16"/>
//
class SOUI_EXP CDuiIconWnd : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiIconWnd, "icon")
public:
    CDuiIconWnd();

    virtual BOOL Load(pugi::xml_node xmlNode);

    void OnPaint(CDCHandle dc);

    HICON AttachIcon(HICON hIcon);

    void LoadIconFile( LPCTSTR lpFIleName );
protected:
    virtual CSize GetDesiredSize(LPRECT pRcContainer);

    void _ReloadIcon();

    HICON m_theIcon;
    CDuiStringT m_strIconName;
    CDuiStringT m_strCurIconName;
    int m_nSize;

    SOUO_ATTRIBUTES_BEGIN()
    DUIWIN_TSTRING_ATTRIBUTE("src", m_strIconName, FALSE)
    DUIWIN_INT_ATTRIBUTE("size", m_nSize, FALSE)
    SOUI_ATTRIBUTES_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()
};

//////////////////////////////////////////////////////////////////////////
// Radio Box
//
// Usage: <radio state=1>This is a check-box</radio>
//
class SOUI_EXP CDuiRadioBox : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiRadioBox, "radio")

    enum
    {
        RadioBoxSpacing = 4,
    };

public:

    CDuiRadioBox();


    void OnPaint(CDCHandle dc);

protected:

    // CDuiRadioBoxTheme m_theme;
    CDuiSkinBase *m_pSkin;
    CDuiSkinBase *m_pFocusSkin;

    UINT _GetDrawState();
    CRect GetRadioRect();
    virtual void GetTextRect(LPRECT pRect);

    virtual CSize GetDesiredSize(LPRECT pRcContainer);

    virtual BOOL NeedRedrawWhenStateChange();

    virtual void DuiDrawFocus(HDC dc);

    virtual UINT OnGetDuiCode()
    {
        return 0;
    }

    virtual BOOL IsSiblingsAutoGroupped() {return TRUE;}

    void OnLButtonDown(UINT nFlags, CPoint point);

    void OnSetDuiFocus();


    SOUO_ATTRIBUTES_BEGIN()
    DUIWIN_SKIN_ATTRIBUTE("skin", m_pSkin, FALSE)
    DUIWIN_SKIN_ATTRIBUTE("focusskin", m_pFocusSkin, FALSE)
    SOUI_ATTRIBUTES_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    MSG_WM_SETFOCUS_EX(OnSetDuiFocus)
    WND_MSG_MAP_END()
};


class SOUI_EXP CDuiToggle : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiToggle, "togglectrl")
public:
    CDuiToggle();

    void SetToggle(BOOL bToggle,BOOL bUpdate=TRUE);

    BOOL GetToggle();
protected:
    void OnPaint(CDCHandle dc);
    void OnLButtonUp(UINT nFlags,CPoint pt);
    virtual CSize GetDesiredSize(LPRECT pRcContainer);
    virtual BOOL NeedRedrawWhenStateChange(){return TRUE;}

    SOUO_ATTRIBUTES_BEGIN()
    DUIWIN_INT_ATTRIBUTE("toggled", m_bToggled, TRUE)
    DUIWIN_SKIN_ATTRIBUTE("skin", m_pSkin, TRUE)
    SOUI_ATTRIBUTES_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    MSG_WM_LBUTTONUP(OnLButtonUp)
    WND_MSG_MAP_END()
protected:
    BOOL m_bToggled;
    CDuiSkinBase *m_pSkin;
};

//<group crline1="b8d5e2" crline2="999999">group text</>
class SOUI_EXP CDuiGroup : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiGroup, "group")
public:
    CDuiGroup();

protected:
    void OnPaint(CDCHandle dc);
    COLORREF m_crLine1,m_crLine2;
    int         m_nRound;
public:
    SOUO_ATTRIBUTES_BEGIN()
    DUIWIN_COLOR_ATTRIBUTE("crline1", m_crLine1, FALSE)
    DUIWIN_COLOR_ATTRIBUTE("crline2", m_crLine2, FALSE)
    DUIWIN_INT_ATTRIBUTE("round",m_nRound,FALSE)
    SOUI_ATTRIBUTES_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()
};

}//namespace SOUI
