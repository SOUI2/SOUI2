/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       SCaption.h
 * @brief      �������ؼ�
 * @version    v1.0      
 * @author     soui      
 * @date       2014-05-28
 * 
 * Describe    ������ɱ������ؼ�
 */

#pragma once
#include "core/SWnd.h"

namespace SOUI
{
/**
 * @class      CSCaption
 * @brief      ��ǩ��
 * 
 * Describe    ��ǩ�� ֻ��Ҫ�̳д��༴��
 */
class SCaption :
    public SWindow
{
    SOUI_CLASS_NAME(SCaption, L"caption")
public:
    /**
     * CSCaption::CSCaption
     * @brief    ���캯��
     *
     * Describe  CSCaption��Ĺ��캯��
     */ 
    SCaption(void);
    /**
     * CSCaption::~CSCaption
     * @brief    ��������
     *
     * Describe  ~CSCaption��Ĺ��캯��
     */     
    virtual ~SCaption(void);

protected:
    /**
     * CSCaption::OnLButtonDown
     * @brief    ��������¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void OnLButtonDown(UINT nFlags, CPoint point);
    /**
     * CSCaption::OnLButtonDblClk
     * @brief    ���˫���¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
     */    
    void OnLButtonDblClk(UINT nFlags, CPoint point);

    SOUI_MSG_MAP_BEGIN()
    MSG_WM_LBUTTONDOWN(OnLButtonDown)
    MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
    SOUI_MSG_MAP_END()
};
}
