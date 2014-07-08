/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       SScrollBar.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-08
 * 
 * Describe     
 */
#pragma once
#include "core/SWnd.h"

namespace SOUI
{
/** 
 * @class     SScrollBar
 * @brief     ������
 *
 * Describe   ������
 */
class SOUI_EXP SScrollBar: public SWindow
{
// Construction
public:
    SOUI_CLASS_NAME(SScrollBar, L"scrollbar")
    /**
     * SScrollBar::SScrollBar
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    SScrollBar();
    /**
     * SScrollBar::SScrollBar
     * @brief    ��������
     *
     * Describe  ��������  
     */
    virtual ~SScrollBar();

public:
    
    /**
     * SScrollBar::IsVertical
     * @brief    �Ƿ�����ֱ
     * @return   ����BOOL 
     *
     * Describe  �Ƿ�����ֱ
     */
    BOOL IsVertical();

    /**
     * SScrollBar::HitTest
     * @brief    ���Ե�
     *
     * Describe  ����ĳ�����Ƿ��ڹ�������
     */
    UINT HitTest(CPoint pt);
    
    /**
     * SScrollBar::SetPos
     * @brief    ����λ��
     *
     * Describe  ����λ��
     */
    int SetPos(int nPos);
    
    /**
     * SScrollBar::GetPos
     * @brief    ��ȡλ��
     *
     * Describe  ��ȡλ��
     */
    int GetPos();
    
protected:    
    /**
     * SScrollBar::GetPartRect
     * @brief    
     * @param   UINT uSBCode -- 
     *
     * Describe  
     */
    CRect GetPartRect(UINT uSBCode);

    /**
     * SScrollBar::OnInitFinished
     * @brief    ��ʼ��
     * @param    pugi::xml_node xmlNode  -- ��ʼ��
     *
     * Describe  ��ʼ��
     */
    virtual void OnInitFinished(pugi::xml_node xmlNode);

    /**
     * SScrollBar::OnPaint
     * @brief    ����
     * @param    IRenderTarget * pRT  -- �滭�豸
     *
     * Describe  ����
     */
    void OnPaint(IRenderTarget * pRT);

    /**
     * SScrollBar::OnLButtonUp
     * @brief    ���̧��
     * @param    UINT nFlags --  �������־
     * @param    CPoint point -- ����
     *
     * Describe  ��Ϣ��Ӧ����
     */
    void OnLButtonUp(UINT nFlags, CPoint point) ;

    /**
     * SScrollBar::OnLButtonDown
     * @brief    ������� 
     * @param    UINT nFlags --  �������־
     * @param    CPoint point -- ����
     *
     * Describe  ��Ϣ��Ӧ����
     */
    void OnLButtonDown(UINT nFlags, CPoint point) ;

    /**
     * SScrollBar::OnMouseMove
     * @brief    ����ƶ�
     * @param    UINT nFlags --  �������־
     * @param    CPoint point -- ����
     *
     * Describe  ��Ϣ��Ӧ����
     */
    void OnMouseMove(UINT nFlags, CPoint point) ;

    /**
     * SScrollBar::OnTimer
     * @brief    ��ʱ�� 
     * @param    char nIDEvent  -- ��ʱ��ID
     *
     * Describe  ��ʱ��ID
     */
    void OnTimer(char nIDEvent) ;

    /**
     * SScrollBar::OnMouseLeave
     * @brief    ����ƶ��¼� 
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnMouseLeave();

    /**
     * SScrollBar::OnSetScrollInfo
     * @brief    ���ù�������Ϣ
     * @param    UINT uMsg  -- ��Ϣ��
     * @param    WPARAM wParam  
     * @param    LPARAM lParam  
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    LRESULT OnSetScrollInfo(UINT uMsg, WPARAM wParam, LPARAM lParam);

    /**
     * SScrollBar::OnGetScrollInfo
     * @brief    ��ȡ��������Ϣ 
     * @param    UINT uMsg  -- ��Ϣ��
     * @param    WPARAM wParam  
     * @param    LPARAM lParam  
     *
     * Describe  �Զ�����Ϣ��Ӧ���� 
     */
    LRESULT OnGetScrollInfo(UINT uMsg, WPARAM wParam, LPARAM lParam);

    /**
     * SScrollBar::NotifySbCode
     * @brief    ֪ͨ 
     * @param    UINT uCode  -- ��Ϣ��
     * @param    int nPos  -- ����
     *
     * Describe  �Զ�����Ϣ��Ӧ���� 
     */
    LRESULT NotifySbCode(UINT uCode,int nPos);

protected:
    SOUI_ATTRS_BEGIN()
        ATTR_SKIN(L"skin", m_pSkin, FALSE)
        ATTR_UINT(L"arrowsize", m_uAllowSize, FALSE)
        ATTR_INT(L"min", m_si.nMin, FALSE)
        ATTR_INT(L"max", m_si.nMax, FALSE)
        ATTR_INT(L"value", m_si.nPos, FALSE)
        ATTR_INT(L"page", m_si.nPage, FALSE)
        ATTR_INT(L"vertical", m_bVertical, FALSE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_TIMER_EX(OnTimer)
        MSG_WM_PAINT_EX(OnPaint)
        MESSAGE_HANDLER_EX(SBM_SETSCROLLINFO,OnSetScrollInfo)
        MESSAGE_HANDLER_EX(SBM_GETSCROLLINFO,OnGetScrollInfo)
    SOUI_MSG_MAP_END()

protected:
    ISkinObj    *m_pSkin;        /**< Ƥ������ */
    UINT        m_uAllowSize;    /**< ��С */

    SCROLLINFO  m_si;         /**< �ṹ�� */
    BOOL        m_bDrag;      /**< �Ƿ������϶� */
    CPoint      m_ptDrag;     /**< �϶����� */
    int         m_nDragPos;   /**< �϶�λ�� */
    UINT        m_uClicked;   /**<  */
    BOOL        m_bNotify;    /**<  */
    UINT        m_uHtPrev;    /**<  */
    BOOL        m_bVertical;  /**< �Ƿ��Ǵ�ֱ������ */
    
};

}//namespace SOUI
