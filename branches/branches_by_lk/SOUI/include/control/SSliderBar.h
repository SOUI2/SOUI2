/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 * 
 * @file       SSliderBar.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-08
 * 
 * Describe     
 */
#pragma once
#include "SCmnCtrl.h"

namespace SOUI
{
/** 
 * @class     SSliderBar
 * @brief     ���鹤����
 *
 * Describe   ���鹤����
 */
class SOUI_EXP SSliderBar : public SProgress
{
    SOUI_CLASS_NAME(SSliderBar, L"sliderbar")

public:
    
    /**
     * SSliderBar::SSliderBar
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    SSliderBar();
    
    /**
     * SSliderBar::~SSliderBar
     * @brief    ��������
     *
     * Describe  ��������  
     */
    ~SSliderBar();

    enum
    {
        SC_RAIL,
        SC_SELECT,
        SC_THUMB,
    };

public:    
    /**
     * SSliderBar::HitTest
     * @brief    ���Ե�
     * @param    CPoint pt  --  ����
     *
     * Describe  ����ĳ�����Ƿ��ڹ�������
     */
    int    HitTest(CPoint pt);

protected:
    BOOL      m_bDrag;  /**< �Ƿ������϶� */
    CPoint    m_ptDrag; /**< �϶�λ��     */
    int       m_nDragValue; /**< �϶����� */
    int       m_uHtPrev; /**<  */

    ISkinObj  *m_pSkinThumb; /**< Ƥ������ */

protected:
    
    /**
     * SSliderBar::NotifyPos
     * @brief    ֪ͨ 
     * @param    UINT uCode  -- ��Ϣ��
     * @param    int nPos  -- ����
     *
     * Describe  �Զ�����Ϣ��Ӧ���� 
     */
    LRESULT    NotifyPos(UINT uCode, int nPos);

    /**
     * SSliderBar::GetDesiredSize
     * @brief    ��ȡ��С 
     * @param    LPRECT pRcContainer  -- ���ݴ�С
     * @return   ����CSize 
     *
     * Describe  ��ȡ��С 
     */
    virtual CSize    GetDesiredSize(LPRECT pRcContainer);

    /**
     * SSliderBar::GetPartRect
     * @brief    
     * @param    UINT uSBCode
     *
     * Describe   
     */
    CRect   GetPartRect(UINT uSBCode);
    
    /**
     * SSliderBar::OnPaint
     * @brief    ����
     * @param    IRenderTarget * pRT  -- �滭�豸
     *
     * Describe  ����
     */
    void    OnPaint(IRenderTarget * pRT);
    
    /**
     * SSliderBar::OnLButtonUp
     * @brief    ���̧��
     * @param    UINT nFlags --  �������־
     * @param    CPoint point -- ����
     *
     * Describe  ��Ϣ��Ӧ����
     */
    void    OnLButtonUp(UINT nFlags, CPoint point);
    
    /**
     * SSliderBar::OnLButtonDown
     * @brief    ������� 
     * @param    UINT nFlags --  �������־
     * @param    CPoint point -- ����
     *
     * Describe  ��Ϣ��Ӧ����
     */
    void    OnLButtonDown(UINT nFlags, CPoint point);
    
    /**
     * SSliderBar::OnMouseMove
     * @brief    ����ƶ�
     * @param    UINT nFlags --  �������־
     * @param    CPoint point -- ����
     *
     * Describe  ��Ϣ��Ӧ����
     */
    void    OnMouseMove(UINT nFlags, CPoint point);
    
    /**
     * SSliderBar::OnMouseLeave
     * @brief    ����ƶ��¼� 
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void    OnMouseLeave();


    SOUI_MSG_MAP_BEGIN()
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_PAINT_EX(OnPaint)
    SOUI_MSG_MAP_END()

    SOUI_ATTRS_BEGIN()
        ATTR_SKIN(L"thumbSkin", m_pSkinThumb, FALSE)
    SOUI_ATTRS_END()
};

template<typename T>
/**
 * _TSWAP
 * @brief    ���� 
 *
 * Describe  ģ�庯�� 
 */
void _TSWAP(T &a,T &b)
{
    T t=a;
    a=b;
    b=t;
}

}
