/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       SSplitWnd.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-08
 * 
 * Describe     
 */
#pragma once
#include "core/SPanel.h"

namespace SOUI
{

enum SPLITMODE {SM_COL=0,SM_ROW};


/** 
 * @class     SSplitPane
 * @brief     �ָ��
 *
 * Describe   �ָ��
 */
class SOUI_EXP SSplitPane : public SWindow
{
    friend class SSplitWnd;
    SOUI_CLASS_NAME(SSplitPane, L"splitpane")
public:
    
    /**
     * SSplitPane::SSplitPane
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    SSplitPane();

    /**
     * SSplitPane::~SSplitPane
     * @brief    ��������
     *
     * Describe  ��������  
     */

    virtual ~SSplitPane() {}

    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"idealsize", m_nSizeIdeal, TRUE)
        ATTR_INT(L"minsize", m_nSizeMin, TRUE)
        ATTR_INT(L"priority", m_nPriority, TRUE)
    SOUI_ATTRS_END()
protected:
    int m_nSizeIdeal;  /**< �����С */
    int m_nSizeMin;    /**< ��С��С */
    int m_nPriority;   /**< ���ȼ�   */
};

/** 
 * @class     SSplitWnd
 * @brief     �ָ��
 *
 * Describe   �ָ��
 */
class SOUI_EXP SSplitWnd :
    public SWindow
{
    SOUI_CLASS_NAME(SSplitWnd, L"splitwnd")

    enum {
        layout_vert=1,        //���򲼾ָı�
        layout_horz=2,        //���򲼾ָı�
        layout_pos=4,        //����λ�÷����ı�
    };
    struct PANEORDER
    {
        int idx;
        SSplitPane *pPane;
    };
public:
    
    /**
     * SSplitWnd::SSplitWnd
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    SSplitWnd(void);

    /**
     * SSplitWnd::~SSplitWnd
     * @brief    ��������
     *
     * Describe  ��������  
     */
    virtual ~SSplitWnd(void);

    /**
     * SSplitWnd::SetPaneInfo
     * @brief    ����panel��Ϣ
     * @param    UINT iPane  --  panel id
     * @param    int nIdealSize  -- �����С
     * @param    int nMinSize    -- ��С��С
     * @param    int nPriority   -- ���ȼ�
     * @return   ����BOOL     
     *
     * Describe  ����panel��Ϣ  
     */
    BOOL SetPaneInfo(UINT iPane,int nIdealSize,int nMinSize,int nPriority);

    /**
     * SSplitWnd::GetPaneInfo
     * @brief    ��ȡpanel��Ϣ
     * @param    UINT iPane  --  panel id
     * @param    int *pnIdealSize  -- �����С
     * @param    int *pnMinSize    -- ��С��С
     * @param    int *pnPriority   -- ���ȼ�
     * @return   ����BOOL     
     *
     * Describe  ��ȡpanel��Ϣ 
     */
    BOOL GetPaneInfo(UINT iPane,int *pnIdealSize,int *pnMinSize,int *pnPriority);

    /**
     * SSplitWnd::ShowPanel
     * @brief    ��ʾpanel
     * @param    UINT iPane -- panel id     
     * @return   ����BOOL     
     *
     * Describe  ��ʾpanel  
     */
    BOOL ShowPanel(UINT iPane);

    /**
     * SSplitWnd::HidePanel
     * @brief    ����panel
     * @param    UINT iPane -- panel id
     * @return   ����BOOL
     *
     * Describe  ����panel  
     */
    BOOL HidePanel(UINT iPane);

protected:
    
    /**
     * SSplitWnd::UpdateChildrenPosition
     * @brief    �����Ӵ���λ��
     *
     * Describe  �����Ӵ���λ��
     */
    virtual void UpdateChildrenPosition(){}//empty
    
    /**
     * SSplitWnd::GetVisiblePanelCount
     * @brief    ��ȡ��ʾ�ɼ�panel����
     * @return   ���� int
     *
     * Describe  ��ȡ��ʾ�ɼ�panel����
     */
    int GetVisiblePanelCount();
    
    /**
     * SSplitWnd::GetNextVisiblePanel
     * @brief    ��ȡ��һ�� panel-id
     * @param    UINT iPanel -- panel id
     * @return   ����int
     *
     * Describe  ��ȡ��һ�� panel-id 
     */
    int GetNextVisiblePanel(UINT iPanel);
    
    /**
     * SSplitWnd::CreateChildren
     * @brief    ����panel
     * @param    pugi::xml_node xmlNode -- xml�ļ�
     * @return   ����BOOL
     *
     * Describe  ����panel 
     */
    virtual BOOL CreateChildren(pugi::xml_node xmlNode);
    
    /**
     * SSplitWnd::OnSetCursor
     * @brief    ��������
     * @param    const CPoint &pt -- ����
     * @return   ����BOOL
     *
     * Describe  ��������
     */
    virtual BOOL OnSetCursor(const CPoint &pt);
    
    /**
     * SSplitWnd::OnDestroy
     * @brief    ����
     *
     * Describe  ����  
     */
    void OnDestroy();
    
    /**
     * SSplitWnd::OnPaint
     * @brief    ����
     * @param    IRenderTarget * pRT -- �����豸
     *
     * Describe  ���� 
     */
    void OnPaint(IRenderTarget * pRT);
    
    /**
     * SSplitWnd::OnWindowPosChanged
     * @brief    �޸Ĵ���λ��
     * @param    LPRECT lpWndPos -- ����λ��
     *
     * Describe  �޸Ĵ���λ��  ��Ϣ��Ӧ����
     */
    LRESULT OnWindowPosChanged(LPRECT lpWndPos);
    
    /**
     * SSplitWnd::OnLButtonDown
     * @brief    ��������¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnLButtonDown(UINT nFlags,CPoint pt);

    /**
     * SSplitWnd::OnLButtonUp
     * @brief    ���̧���¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnLButtonUp(UINT nFlags,CPoint pt);

    /**
     * SSplitWnd::OnMouseMove
     * @brief    ����ƶ��¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnMouseMove(UINT nFlags,CPoint pt);

    /**
     * SSplitWnd::FunComp
     * @brief    �ȽϺ���
     * @param    const void * p1 -- ����1
     * @param    const void * p2 -- ����2
     *
     * Describe  �˺�������Ϣ��Ӧ����
     */
    static int FunComp(const void * p1,const void * p2);

    /**
     * SSplitWnd::Relayout
     * @brief    ���²���
     * @param    UINT uMode -- 
     *
     * Describe  ���²���
     */
    void Relayout(UINT uMode);

    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"sepsize", m_nSepSize, TRUE)
        ATTR_INT(L"adjustable", m_bAdjustable, TRUE)
        ATTR_INT(L"colmode", m_bColMode, TRUE)
        ATTR_SKIN(L"skinsep",m_pSkinSep,TRUE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_PAINT_EX(OnPaint)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_WINPOSCHANGED_EX(OnWindowPosChanged)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_MOUSEMOVE(OnMouseMove)
    SOUI_MSG_MAP_END()

protected:
    SArray<SSplitPane *> m_arrPane; /**< ����panel */
    ISkinObj *m_pSkinSep;   /**< ISkinObj���� */
    int m_nSepSize;         /**<  */
    BOOL m_bAdjustable;     /**<  */
    BOOL m_bColMode;        /**<  */

    int m_iDragBeam;        /**<  */
    CPoint m_ptClick;       /**<  */
};

/** 
 * @class     SSplitWnd_Col
 * @brief     ��ֱ�ָ��
 *
 * Describe   ��ֱ�ָ��
 */
class SOUI_EXP SSplitWnd_Col : public SSplitWnd
{
    SOUI_CLASS_NAME(SSplitWnd_Col, L"splitcol")
public:
    SSplitWnd_Col()
    {
        m_bColMode=TRUE;
    }
};

/** 
 * @class     SSplitWnd_Row
 * @brief     ����ָ��
 *
 * Describe   ����ָ��
 */
class SOUI_EXP SSplitWnd_Row : public SSplitWnd
{
    SOUI_CLASS_NAME(SSplitWnd_Row, L"splitrow")
public:
    SSplitWnd_Row()
    {
        m_bColMode=FALSE;
    }
};

}//namespace SOUI
