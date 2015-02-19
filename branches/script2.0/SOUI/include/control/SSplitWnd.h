/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
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
#include <core/swnd.h>
#include <helper/copylist.hpp>

namespace SOUI
{

/** 
 * @class     SSplitPane
 * @brief     �ָ��
 *
 * Describe   �ָ��
 */
class SOUI_EXP SSplitPane : public SWindow
{
    friend class SSplitWnd;
    SOUI_CLASS_NAME(SSplitPane, L"pane")
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
        ATTR_INT(L"idealSize", m_nSizeIdeal, FALSE)
        ATTR_INT(L"minSize", m_nSizeMin, FALSE)
        ATTR_INT(L"maxSize", m_nSizeMax,FALSE)
        ATTR_INT(L"priority", m_nPriority, FALSE)
    SOUI_ATTRS_END()
    
protected:
    int m_nSizeIdeal;  /**< �����С */
    int m_nSizeMin;    /**< ��С��С */
    int m_nSizeMax;    /**< ����С */
    int m_nPriority;   /**< ���ȼ�,ֵԽ�����ȼ�Խ��,���ȼ�Խ�ߣ�����Խ�ȵ���idealSize  */
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
    
    enum SPLIT_ORINTATION
    {
        Horizontal=0,
        Vertical,
    };
    //���ڵ�SIZE��Ϣ
    struct PANESIZE
    {
        int actural;
        int preferred;
        int minimum;
        int maximum;
    };
    typedef SArray<PANESIZE> PANESIZELIST;
    
protected:

    typedef SArray<SSplitPane*> SplitPaneList;
    SplitPaneList     m_lstPane;            /**< ����ʾ˳������ķָ��б� */
    SplitPaneList     m_lstPriority;        /**< �����ȼ�����ķָ��б� */
    int                 m_spliterSize;        /**< �ָ�����size */
    int                 m_orintation;         /**< �ָ�򣬲ο� SPLIT_ORINTATION */

    BOOL                m_bAdjustable;        /**< �Ƿ�֧���϶����ڴ����С */
    ISkinObj *          m_pSkinSep;           /**< ISkinObj���� */

    CPoint              m_ptDragPrev;         /**< �϶�������ǰһ��λ�� */
    int                 m_iDragSep;           /**< �����϶���һ���ָ���,-1����û���϶�״̬ */

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

    SSplitPane * GetPane(UINT iPane);

    /**
     * SSplitWnd::ShowPane
     * @brief    ��ʾpane
     * @param    UINT iPane -- pane index     
     * @return   ����BOOL     
     *
     * Describe  ��ʾpane 
     */
    BOOL ShowPane(UINT iPane);

    /**
     * SSplitWnd::HidePane
     * @brief    ����pane
     * @param    UINT iPane -- panel index
     * @return   ����BOOL
     *
     * Describe  ����pane  
     */
    BOOL HidePane(UINT iPane);

    /**
     * SSplitWnd::PaneIndex
     * @brief    ���һ��Pane������
     * @param    const SStringW & strName --  Pane��name
     * @return   int -- Pane������
     * Describe  
     */    
    int  PaneIndex(const SStringW & strName) const;
    
    /**
     * SSplitWnd::InsertItem
     * @brief    ����һ���µĴ���
     * @param    SSplitPane* pane --  ����ָ��
     * @param    int index --  ����λ�ã�Ĭ�����
     * @return   int -- Pane������
     * Describe  
     */    
    int  InsertItem( SSplitPane* pane, int index = -1  );

    /**
     * SSplitWnd::RemoveItem
     * @brief    ɾ��һ������
     * @param    SSplitPane* pane --  ����ָ��
     * @return   void
     * Describe  
     */    
    void RemoveItem( SSplitPane * pane );

protected:
    
    /**
     * SSplitWnd::UpdateChildrenPosition
     * @brief    �����Ӵ���λ��
     *
     * Describe  �����Ӵ���λ��
     */
    virtual void UpdateChildrenPosition();

    
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
     * SSplitWnd::OnPaint
     * @brief    ����
     * @param    IRenderTarget * pRT -- �����豸
     *
     * Describe  ���� 
     */
    void OnPaint(IRenderTarget * pRT);
    
    
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

protected:
    //qsort�ȽϺ���
    static int FunComp(const void * p1,const void * p2);
    
    //��һ��SplitPaneList�������ȼ��Ӵ�С����
    void SortPriorityList(SplitPaneList & lstPane);
    
    //��SplitPaneList��ȡsize��Ϣ
    void FatchPaneSizeInfo(const SplitPaneList & lstPane, PANESIZELIST & lstPaneSize);
    
    //���ݼ����õĴ���size��Ϣ���ô���λ��
    int ResetPanesPostion(SplitPaneList & lstPane, SplitPaneList & lstPanePriority, PANESIZELIST & lstPaneSize, int offset);

    //�����б��пؼ��ĸ߶ȣ���ȣ�
    int AdjustPanesSize(PANESIZELIST & lstPriority, int remain);

    //���²���
    void Relayout(const CRect &rc,PANESIZELIST lstPaneSize=PANESIZELIST());

public:
    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"sepSize", m_spliterSize, TRUE)
        ATTR_SKIN(L"sepSkin",m_pSkinSep,TRUE)
        ATTR_INT(L"adjustable", m_bAdjustable, TRUE)
        ATTR_INT(L"vertical", m_orintation, TRUE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_PAINT_EX(OnPaint)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_MOUSEMOVE(OnMouseMove)
    SOUI_MSG_MAP_END()

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
        m_pSkinSep= GETBUILTINSKIN(SKIN_SYS_SPLIT_VERT);
        m_orintation=Vertical;
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
        m_pSkinSep=GETBUILTINSKIN(SKIN_SYS_SPLIT_HORZ);
        m_orintation=Horizontal;
    }
};

}//namespace SOUI
