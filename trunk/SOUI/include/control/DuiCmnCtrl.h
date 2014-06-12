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

    SOUI_ATTRS_BEGIN()
    ATTR_INT("multilines", m_bMultiLines, FALSE)
    ATTR_INT("interhei", m_nLineInter, FALSE)
    SOUI_ATTRS_END()
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
     * @return   ����ֵBOOL �ɹ�--TRUE ʧ��--FALSE
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
     * @return   ����ֵBOOL �ɹ�--TRUE ʧ��--FALSE
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
     * @return   ����ֵBOOL �ɹ�--TRUE ʧ��--FALSE
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
    
    /**
     * CDuiLink::OnStateChanged
     * @brief    ״̬�ı䴦����
     * @param    DWORD dwOldState -- ��״̬
     * @param    DWORD dwNewState -- ��״̬
     *
     * Describe  ״̬�ı䴦����
     */
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
    
    /**
     * CDuiLink::StopCurAnimate
     * @brief    ֹͣ����
     *
     * Describe  ֹͣ����
     */
    void StopCurAnimate();

    DWORD  m_accel;
    BOOL   m_bAnimate;    /**< ������־ */
    BYTE   m_byAlphaAni;  /**< ����״̬ */
public:
    SOUI_ATTRS_BEGIN()
        ATTR_CUSTOM("accel",OnAttrAccel)
        ATTR_INT("animate", m_bAnimate, FALSE)
    SOUI_ATTRS_END()

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

/**
 * @class      CDuiImageBtnWnd
 * @brief      ͼƬ��ť��
 * 
 * Describe    ͼƬ��ť�࣬�̳�CDuiButton
 */
class SOUI_EXP CDuiImageBtnWnd : public CDuiButton
{
    SOUI_CLASS_NAME(CDuiImageBtnWnd, "imgbtn")
public:
    CDuiImageBtnWnd()
    {
        m_bTabStop=FALSE;
    }
};

/**
 * @class      CDuiImageWnd
 * @brief      ͼƬ�ؼ���
 * 
 * Describe    Image Control ͼƬ�ؼ���
 * Usage       Usage: <img skin="skin" sub="0"/>
 */
class SOUI_EXP CDuiImageWnd : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiImageWnd, "img")
public:
    /**
     * CDuiImageWnd::CDuiImageWnd
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiImageWnd();
    /**
     * CDuiImageWnd::~CDuiImageWnd
     * @brief    ��������
     *
     * Describe  ��������
     */
    virtual ~CDuiImageWnd();

    void OnPaint(CDCHandle dc);
    /**
     * CDuiImageWnd::SetSkin
     * @param    CDuiSkinBase *pSkin -- ��Դ
     * @param    int nSubID -- ��ԴID
     * @brief    ����Ƥ��
     * @return   ����ֵBOOL �ɹ�--TRUE ʧ��--FALSE
     *
     * Describe  ����Ƥ��
     */
    BOOL SetSkin(CDuiSkinBase *pSkin,int nSubID=0);
    /**
     * CDuiImageWnd::SetIcon
     * @param    int nSubID -- ��ԴID
     * @brief    ����ͼ��
     * @return   ����ֵBOOL �ɹ�--TRUE ʧ��--FALSE
     *
     * Describe  ����ͼ��
     */
    BOOL SetIcon(int nSubID);

    /**
     * CDuiImageWnd::GetSkin
     * @brief    ��ȡ��Դ
     * @return   ����ֵCDuiSkinBaseָ��
     *
     * Describe  ��ȡ��Դ
     */
    CDuiSkinBase * GetSkin(){return m_pSkin;}
protected:
    /**
     * CDuiImageWnd::GetDesiredSize
     * @brief    ��ȡԤ�ڴ�С
     * @param    LPRECT pRcContainer  --  ���ݾ��ο� 
     * @return   ����ֵ CSize���� 
     *
     * Describe  ���ݾ��εĴ�С����ȡԤ�ڴ�С(�����е㲻��)
     */
    virtual CSize GetDesiredSize(LPRECT pRcContainer);

    BOOL m_bManaged;  /**< ��ʱ���� */
    int m_nSubImageID;  /**< ��ԴͼƬID */
    CDuiSkinBase *m_pSkin;  /**< ��Դ���� */
    //BOOL m_bCalc;

    SOUI_ATTRS_BEGIN()
    ATTR_SKIN("skin", m_pSkin, TRUE)
    ATTR_INT("sub", m_nSubImageID, FALSE)
    SOUI_ATTRS_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()
};

/**
 * @class      CDuiAnimateImgWnd
 * @brief      ����ͼƬ����
 * 
 * Describe    �˴���֧�ֶ���Ч��
 */
class SOUI_EXP CDuiAnimateImgWnd : public CDuiWindow, public ITimelineHandler
{
    SOUI_CLASS_NAME(CDuiAnimateImgWnd, "animateimg")
public:    
    /**
     * CDuiAnimateImgWnd::CDuiImageWnd
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiAnimateImgWnd();

    /**
     * CDuiAnimateImgWnd::~CDuiAnimateImgWnd
     * @brief    ��������
     *
     * Describe  ��������
     */    
    virtual ~CDuiAnimateImgWnd() {}

    /**
     * CDuiAnimateImgWnd::Start
     * @brief    ��������
     *
     * Describe  ��������
     */  
    void Start();
    /**
     * CDuiAnimateImgWnd::Stop
     * @brief    ֹͣ����
     *
     * Describe  ֹͣ����
     */  
    void Stop();

    /**
     * CDuiAnimateImgWnd::IsPlaying
     * @brief    �ж϶�������״̬
     * @return   ����ֵ�Ƕ���״̬ TRUE -- ������
     *
     * Describe  �ж϶�������״̬
     */  
    BOOL IsPlaying(){return m_bPlaying;}
protected:
    /**
     * CDuiAnimateImgWnd::GetDesiredSize
     * @brief    ��ȡԤ�ڴ�С
     * @param    LPRECT pRcContainer  --  ���ݾ��ο� 
     * @return   ����ֵ CSize���� 
     *
     * Describe  ���ݾ��εĴ�С����ȡԤ�ڴ�С(�����е㲻��)
     */
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

    SOUI_ATTRS_BEGIN()
    ATTR_SKIN("skin", m_pSkin, TRUE)
    ATTR_UINT("speed", m_nSpeed, FALSE)
    ATTR_UINT("autostart", m_bAutoStart, FALSE)
    SOUI_ATTRS_END()

protected:
    CDuiSkinBase *m_pSkin;        /**< ��ʱ���� */
    int           m_nSpeed;       /**< �ٶ� */
    int           m_iCurFrame;    /**< ��ǰ֡ */
    BOOL          m_bAutoStart;   /**< �Ƿ��Զ����� */
    BOOL          m_bPlaying;     /**< �Ƿ������� */
};

/**
 * @class      CDuiProgress
 * @brief      ��������
 * 
 * Describe    ��������
 * Usage: <progress bgskin=xx posskin=xx min=0 max=100 value=10,showpercent=0/>
 */
class SOUI_EXP CDuiProgress : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiProgress, "progress")
public:
    /**
     * CDuiProgress::CDuiProgress
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiProgress();

    /**
     * CDuiProgress::SetValue
     * @brief    ���ý���������ֵ
     * @param    int nValue  --  ����ֵ 
     * @return   ����ֵ�� TRUE -- ���óɹ�
     *
     * Describe  ���ý���������ֵ
     */  
    BOOL SetValue(int nValue);
    /**
     * CDuiProgress::GetValue
     * @brief    ��ȡ����ֵ
     * @return   ����ֵ��int 
     *
     * Describe  ��ȡ����ֵ
     */  
    int GetValue(){return m_nValue;}

    /**
     * CDuiProgress::SetRange
     * @param    int nMin  --  ������Сֵ 
     * @param    int nMax  --  �������ֵ      
     * @brief    ���ý���ֵ��С��ֵ
     *
     * Describe  ���ý���ֵ
     */  
    void SetRange(int nMin,int nMax);
    /**
     * CDuiProgress::GetRange
     * @param    int nMin  --  ������Сֵ 
     * @param    int nMax  --  �������ֵ      
     * @brief    ��ȡ����ֵ��С��ֵ
     *
     * Describe  ��ȡ����ֵ
     */  
    void GetRange(int *pMin,int *pMax);
    /**
     * CDuiProgress::IsVertical
     * @brief    �жϽ������Ƿ�Ϊ��ֱ״̬
     * @return   ����ֵ�� TRUE -- ��ֱ״̬
     *
     * Describe  ��ȡ����ֵ
     */  
    BOOL IsVertical(){return m_bVertical;}
protected:
    /**
     * CDuiProgress::GetDesiredSize
     * @brief    ��ȡԤ�ڴ�С
     * @param    LPRECT pRcContainer  --  ���ݾ��ο� 
     * @return   ����ֵ CSize���� 
     *
     * Describe  ���ݾ��εĴ�С����ȡԤ�ڴ�С(�����е㲻��)
     */
    virtual CSize GetDesiredSize(LPRECT pRcContainer);

    void OnPaint(CDCHandle dc);

    int m_nMinValue; /**< ������Сֵ */
    int m_nMaxValue; /**< �������ֵ */
    int m_nValue;    /**< ����ֵ */

    BOOL m_bShowPercent; /**< �Ƿ���ʾ�ٷֱ� */
    BOOL m_bVertical;    /**< �Ƿ���ֱ״̬ */

    CDuiSkinBase *m_pSkinBg;   /**< ��ʱ���� */
    CDuiSkinBase *m_pSkinPos;  /**< ��ʱ���� */

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()

    SOUI_ATTRS_BEGIN()
    ATTR_SKIN("bgskin", m_pSkinBg, TRUE)
    ATTR_SKIN("posskin", m_pSkinPos, TRUE)
    ATTR_INT("min", m_nMinValue, FALSE)
    ATTR_INT("max", m_nMaxValue, FALSE)
    ATTR_INT("value", m_nValue, FALSE)
    ATTR_UINT("vertical", m_bVertical, FALSE)
    ATTR_UINT("showpercent", m_bShowPercent, FALSE)
    SOUI_ATTRS_END()
};

/**
 * @class      CDuiLine
 * @brief      �����ؼ�
 * 
 * Describe    �����ؼ�
 * Usage: <hr style=solid size=1 crbg=.../>
 */
class SOUI_EXP CDuiLine : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiLine, "hr")

public:
    /**
     * CDuiLine::CDuiLine
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
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

    SOUI_ATTRS_BEGIN()
    ATTR_INT("size", m_nLineSize, FALSE)
    ATTR_UINT("shadow", m_bLineShadow, FALSE)
    ATTR_COLOR("crshadow", m_crShadow, FALSE)
    ATTR_ENUM_BEGIN("mode", HRMODE, FALSE)
        ATTR_ENUM_VALUE("vertical", HR_VERT)
        ATTR_ENUM_VALUE("horizon", HR_VERT)
        ATTR_ENUM_VALUE("tilt", HR_VERT)
    ATTR_ENUM_END(m_mode)
    ATTR_ENUM_BEGIN("style", int, FALSE)
    ATTR_ENUM_VALUE("solid", PS_SOLID)             // default
    ATTR_ENUM_VALUE("dash", PS_DASH)               /* -------  */
    ATTR_ENUM_VALUE("dot", PS_DOT)                 /* .......  */
    ATTR_ENUM_VALUE("dashdot", PS_DASHDOT)         /* _._._._  */
    ATTR_ENUM_VALUE("dashdotdot", PS_DASHDOTDOT)   /* _.._.._  */
    ATTR_ENUM_END(m_nPenStyle)
    SOUI_ATTRS_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()
};

/**
 * @class      CDuiCheckBox
 * @brief      ��ѡ��ؼ�
 * 
 * Describe    ��ѡ��ؼ�
 * Usage: <check state=4>This is a check-box</check>
 */
class SOUI_EXP CDuiCheckBox : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiCheckBox, "check")

    enum
    {
        CheckBoxSpacing = 4,
    };

public:
    /**
     * CDuiCheckBox::CDuiCheckBox
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiCheckBox();

    void OnPaint(CDCHandle dc);
protected:

    CDuiSkinBase *m_pSkin;   /**< ��ʱ���� */
    CDuiSkinBase *m_pFocusSkin; /**< ��ʱ���� */
    /**
     * CDuiCheckBox::_GetDrawState
     * @brief    ��ø�ѡ��״̬
     * @return   ����״ֵ̬
     *
     * Describe  ��ȡ��ѡ��״̬
     */
    UINT _GetDrawState();
    /**
     * CDuiCheckBox::GetCheckRect
     * @brief    ��ø�ѡ�����
     * @return   ����ֵCRect���ο�
     *
     * Describe  ��ȡ��ѡ�����
     */
    CRect GetCheckRect();
    /**
     * CDuiCheckBox::GetDesiredSize
     * @brief    ��ȡԤ�ڴ�С
     * @param    LPRECT pRcContainer  --  ���ݾ��ο� 
     * @return   ����ֵ CSize���� 
     *
     * Describe  ���ݾ��εĴ�С����ȡԤ�ڴ�С(�����е㲻��)
     */
    virtual CSize GetDesiredSize(LPRECT pRcContainer);
    /**
     * CDuiCheckBox::GetTextRect
     * @brief    ��ȡ�ı���С
     * @param    LPRECT pRect  --  ���ݾ��ο� 
     *
     * Describe  ���þ��εĴ�С
     */
    virtual void GetTextRect(LPRECT pRect);
    /**
     * CDuiCheckBox::NeedRedrawWhenStateChange
     * @brief    �ж�״̬�ı��Ƿ���Ҫ�ػ�
     * @return   ����ֵ BOOL 
     *
     * Describe  ״̬�ı��Ƿ���Ҫ�ػ�
     */
    virtual BOOL NeedRedrawWhenStateChange()
    {
        return TRUE;
    }

    /**
     * CDuiCheckBox::OnGetDuiCode
     * @brief    ���ض�Ӧ��Ϣ��
     * @return   ����ֵ UINT 
     *
     * Describe  ���ض�Ӧ��Ϣ��
     */
    virtual UINT OnGetDuiCode()
    {
        return DUIC_WANTCHARS;
    }
    /**
     * CDuiCheckBox::DuiDrawFocus
     * @brief    ���ƻ�ȡ����
     * @param    HDC dc  --  �豸���
     *
     * Describe  ���ض�Ӧ��Ϣ��
     */
    virtual void DuiDrawFocus(HDC dc);

    void OnLButtonDown(UINT nFlags, CPoint point);

    void OnLButtonUp(UINT nFlags, CPoint point);

    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

    SOUI_ATTRS_BEGIN()
        ATTR_SKIN("skin", m_pSkin, FALSE)
        ATTR_SKIN("focusskin", m_pFocusSkin, FALSE)
    SOUI_ATTRS_END()

    WND_MSG_MAP_BEGIN()
        MSG_WM_PAINT(OnPaint)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_KEYDOWN(OnKeyDown)
    WND_MSG_MAP_END()
};

/**
 * @class      CDuiIconWnd
 * @brief      ͼ��ؼ�
 * 
 * Describe    ͼ��ؼ� Use src attribute specify a resource id
 * Usage: <icon src=xx size="16"/>
 */
class SOUI_EXP CDuiIconWnd : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiIconWnd, "icon")
public:    
    /**
     * CDuiIconWnd::CDuiIconWnd
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiIconWnd();
    /**
     * CDuiIconWnd::Load
     * @brief    ������Դ
     * @param    pugi::xml_node xmlNode  --  ��Դ�����ļ�
     * @return   ����ֵBOOL 
     *
     * Describe  ����ͼ����Դ
     */
    virtual BOOL Load(pugi::xml_node xmlNode);

    void OnPaint(CDCHandle dc);
    /**
     * CDuiIconWnd::AttachIcon
     * @brief    ����ͼ����Դ
     * @param    HICON hIcon -- ͼ����Դ���
     * @return   ����ֵ HICON 
     *
     * Describe  ����ͼ����Դ
     */
    HICON AttachIcon(HICON hIcon);
    /**
     * CDuiIconWnd::LoadIconFile
     * @brief    ������Դ
     * @param    LPCTSTR lpFIleName -- ��Դ�ļ�
     *
     * Describe  ͨ���ļ�����ͼ��
     */
    void LoadIconFile( LPCTSTR lpFIleName );
protected:
    virtual CSize GetDesiredSize(LPRECT pRcContainer);
    /**
     * CDuiIconWnd::_ReloadIcon
     * @brief    ���¼���ͼ����Դ
     *
     * Describe  ���¼���ͼ����Դ
     */
    void _ReloadIcon();

    HICON m_theIcon; /**< ͼ����Դ��� */
    CDuiStringT m_strIconName; /**< ͼ����Դ���� */
    CDuiStringT m_strCurIconName; /**< ��ǰͼ����Դ���� */
    int m_nSize; /**< ��ʱ���� */

    SOUI_ATTRS_BEGIN()
    ATTR_STRINGT("src", m_strIconName, FALSE)
    ATTR_INT("size", m_nSize, FALSE)
    SOUI_ATTRS_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()
};


/**
 * @class      CDuiRadioBox
 * @brief      ��ѡ��ؼ�
 * 
 * Describe    ��ѡ��ؼ�
 * Usage: <radio state=1>This is a check-box</radio>
 */
class SOUI_EXP CDuiRadioBox : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiRadioBox, "radio")

    enum
    {
        RadioBoxSpacing = 4,
    };

public:
    /**
     * CDuiRadioBox::CDuiRadioBox
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiRadioBox();


    void OnPaint(CDCHandle dc);

protected:

    // CDuiRadioBoxTheme m_theme;
    CDuiSkinBase *m_pSkin;  /**< Ƥ����Դ */
    CDuiSkinBase *m_pFocusSkin; /**< ����Ƥ����Դ */
    /**
     * CDuiRadioBox::CDuiRadioBox
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    UINT _GetDrawState(); 
    /**
     * CDuiRadioBox::CDuiRadioBox
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CRect GetRadioRect();
    /**
     * CDuiRadioBox::GetTextRect
     * @brief    ����ı���С
     * @param    LPRECT pRect -- �ı���СRect
     *
     * Describe  ���캯��
     */
    virtual void GetTextRect(LPRECT pRect);
    /**
     * CDuiRadioBox::GetDesiredSize
     * @brief    ��ȡԤ�ڴ�Сֵ
     * @param    LPRECT pRcContainer -- ���ݴ���Rect
     *
     * Describe  ��ȡԤ�ڴ�Сֵ
     */
    virtual CSize GetDesiredSize(LPRECT pRcContainer);
    /**
     * CDuiRadioBox::NeedRedrawWhenStateChange
     * @brief    ��״̬�ı�ʱ���Ƿ���Ҫ�ػ�
     * @return   ����BOOL
     *
     * Describe  ��״̬�ı�ʱ���Ƿ���Ҫ�ػ�
     */
    virtual BOOL NeedRedrawWhenStateChange();
    /**
     * CDuiRadioBox::DuiDrawFocus
     * @brief    ���ƽ�����ʽ
     * @param    HDC dc -- �����豸
     *
     * Describe  ����ý���ʱ����Ҫ����
     */
    virtual void DuiDrawFocus(HDC dc);
    /**
     * CDuiRadioBox::OnGetDuiCode
     * @brief    ��ȡ��Ϣ����
     * @return   ���ر���ֵ
     *
     * Describe  ��ȡ��Ϣ����
     */
    virtual UINT OnGetDuiCode()
    {
        return 0;
    }
    /**
     * CDuiRadioBox::IsSiblingsAutoGroupped
     * @brief    �Ƿ��Զ���ӵ�ͬһ��
     * @return   ����BOOL 
     *
     * Describe  ��ͬ���Ƶĵ�ѡ��ť�Ƿ��Զ���ӵ�ͬһ����
     */
    virtual BOOL IsSiblingsAutoGroupped() {return TRUE;}

    void OnLButtonDown(UINT nFlags, CPoint point);

    void OnSetDuiFocus();


    SOUI_ATTRS_BEGIN()
    ATTR_SKIN("skin", m_pSkin, FALSE)
    ATTR_SKIN("focusskin", m_pFocusSkin, FALSE)
    SOUI_ATTRS_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    MSG_WM_SETFOCUS_EX(OnSetDuiFocus)
    WND_MSG_MAP_END()
};

/**
 * @class      CDuiToggle
 * @brief      Toggle�ؼ�
 * 
 * Describe    Toggle�ؼ�
 */
class SOUI_EXP CDuiToggle : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiToggle, "togglectrl")
public:
    
    /**
     * CDuiToggle::CDuiToggle
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    CDuiToggle();
    /**
     * CDuiToggle::SetToggle
     * @brief    ����Toggle����
     * @param    BOOL bToggle -- �Ƿ�����Toggle��Ч         
     * @param    BOOL bUpdate -- �Ƿ���� Ĭ��ֵTRUE
     *
     * Describe  ����Toggle����
     */
    void SetToggle(BOOL bToggle,BOOL bUpdate=TRUE);
    /**
     * CDuiToggle::GetToggle
     * @brief    ��ȡToggle����
     * @return   ����ֵBOOL        
     *
     * Describe  ��ȡToggle���� ��Ҫ�ǻ�ȡ�Ƿ�Toggle
     */
    BOOL GetToggle();
protected:
    void OnPaint(CDCHandle dc);
    void OnLButtonUp(UINT nFlags,CPoint pt);
    virtual CSize GetDesiredSize(LPRECT pRcContainer);
    virtual BOOL NeedRedrawWhenStateChange(){return TRUE;}

    SOUI_ATTRS_BEGIN()
    ATTR_INT("toggled", m_bToggled, TRUE)
    ATTR_SKIN("skin", m_pSkin, TRUE)
    SOUI_ATTRS_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    MSG_WM_LBUTTONUP(OnLButtonUp)
    WND_MSG_MAP_END()
protected:
    BOOL m_bToggled;
    CDuiSkinBase *m_pSkin;
};

/**
 * @class      CDuiGroup
 * @brief      ��ؼ�
 * 
 * Describe    ��ؼ�
 * Usage       <group crline1="b8d5e2" crline2="999999">group text</>
 */
class SOUI_EXP CDuiGroup : public CDuiWindow
{
    SOUI_CLASS_NAME(CDuiGroup, "group")
public:
    CDuiGroup();

protected:
    void OnPaint(CDCHandle dc);
    COLORREF m_crLine1,m_crLine2; /**< ��ɫ */
    int         m_nRound; /**< ��ʱ���� */
public:
    SOUI_ATTRS_BEGIN()
    ATTR_COLOR("crline1", m_crLine1, FALSE)
    ATTR_COLOR("crline2", m_crLine2, FALSE)
    ATTR_INT("round",m_nRound,FALSE)
    SOUI_ATTRS_END()

    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    WND_MSG_MAP_END()
};

}//namespace SOUI
