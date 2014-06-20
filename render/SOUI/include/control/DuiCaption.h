/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       DuiCaption.h
 * @brief      �������ؼ�
 * @version    v1.0      
 * @author     soui      
 * @date       2014-05-28
 * 
 * Describe    ������ɱ������ؼ�
 */

#pragma once
#include "duiwnd.h"

namespace SOUI
{
/**
 * @class      CDuiCaption
 * @brief      ��ǩ��
 * 
 * Describe    ��ǩ�� ֻ��Ҫ�̳д��༴��
 */
class SCaption :
    public SWindow
{
    SOUI_CLASS_NAME(SCaption, "caption")
public:
    /**
     * CDuiCaption::CDuiCaption
     * @brief    ���캯��
     *
     * Describe  CDuiCaption��Ĺ��캯��
     */ 
    SCaption(void);
    /**
     * CDuiCaption::~CDuiCaption
     * @brief    ��������
     *
     * Describe  ~CDuiCaption��Ĺ��캯��
     */     
    virtual ~SCaption(void);

protected:
    /**
     * CDuiCaption::OnLButtonDown
     * @brief    ��������¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnLButtonDown(UINT nFlags, CPoint point);
    /**
     * CDuiCaption::OnLButtonDblClk
     * @brief    ���˫���¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
     */    
    void OnLButtonDblClk(UINT nFlags, CPoint point);

    WND_MSG_MAP_BEGIN()
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
    WND_MSG_MAP_END()
};
}
