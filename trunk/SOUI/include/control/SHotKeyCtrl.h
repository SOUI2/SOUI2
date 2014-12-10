/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 * 
 * @file       SHotKeyCtrl.h
 * @brief      �ȼ��ؼ�
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-02
 * 
 * Describe    �ȼ��ؼ�
 */
#pragma once
#include "core/SWnd.h"
#include "core/Accelerator.h"

namespace SOUI
{
  /**
   * @class      SHotKeyCtrl
   * @brief      �ȼ��ؼ�
   * 
   * Describe    �ȼ��ؼ�
   */
  class SOUI_EXP SHotKeyCtrl 
      : public SWindow
      , public CAccelerator
  {
      SOUI_CLASS_NAME(SHotKeyCtrl, L"hotkey")
  public:
      /**
       * SHotKeyCtrl::SHotKeyCtrl
       * @brief    ���캯��
       *
       * Describe  ���캯��  
       */
      SHotKeyCtrl(void);
      /**
       * SHotKeyCtrl::~SHotKeyCtrl
       * @brief    ��������
       *
       * Describe  ��������  
       */
      virtual ~SHotKeyCtrl(void);

      /**
       * SHotKeyCtrl::SetRule
       * @brief    ���ù���
       * @param    WORD wInvalidComp --
       * @param    WORD wModifier  --  
       *
       * Describe  ���ù���  
       */
      void SetRule(WORD wInvalidComp,WORD wModifier);
      
      /**
       * SHotKeyCtrl::SetHotKey
       * @brief    �����ȼ�
       * @param    WORD vKey --
       * @param    WORD wModifiers  --  
       *
       * Describe  �����ȼ�  
       */
      void SetHotKey(WORD vKey,WORD wModifiers);
      
      /**
       * SHotKeyCtrl::GetHotKey
       * @brief    ��ȡ�ȼ�
       * @param    WORD &vKey --
       * @param    WORD wModifiers  --  
       *
       * Describe  ��ȡ�ȼ�  
       */
      void GetHotKey(WORD & vKey,WORD &wModifers);


  protected:
      /**
       * SHotKeyCtrl::OnGetDlgCode
       * @brief    ��ȡ������Ϣ��
       *
       * Describe  ��Ϣ��Ӧ����  
       */  
      virtual UINT OnGetDlgCode()
      {
          return (SC_WANTALLKEYS|SC_WANTSYSKEY) & (~SC_WANTTAB);
      }
      /**
       * SHotKeyCtrl::OnCreate
       * @brief    ����
       *
       * Describe  ��Ϣ��Ӧ����  
       */  
      int OnCreate(LPVOID);
      /**
       * SHotKeyCtrl::OnLButtonDown
       * @brief    ��������¼�
       * @param    UINT nFlags -- ��־
       * @param    CPoint point -- �������
       *
       * Describe  �˺�������Ϣ��Ӧ����
       */
      void OnLButtonDown(UINT nFlags,CPoint pt);

      /**
       * SHotKeyCtrl::OnPaint
       * @brief    ������Ϣ
       * @param    IRenderTarget *pRT -- ��ȾĿ��
       * 
       * Describe  �˺�������Ϣ��Ӧ����
       */
      void OnPaint(IRenderTarget *pRT);

      /**
       * SHotKeyCtrl::OnSetFocus
       * @brief    ���ý���
       * 
       * Describe  �˺�������Ϣ��Ӧ����
       */
      void OnSetFocus();

      /**
       * SHotKeyCtrl::OnKillFocus
       * @brief    ʧȥ����
       * 
       * Describe  �˺�������Ϣ��Ӧ����
       */
      void OnKillFocus();

      /**
       * SHotKeyCtrl::OnKeyDown
       * @brief    ���̰����¼�
       * @param    UINT nChar -- ������Ӧ����ֵ 
       * @param    UINT nRepCnt -- �ظ�����
       * @param    UINT nFlags -- ��־
       * 
       * Describe  �˺�������Ϣ��Ӧ����
       */ 
      void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
      /**
       * SHotKeyCtrl::OnKeyUp
       * @brief    ����̧���¼�
       * @param    UINT nChar -- ������Ӧ����ֵ 
       * @param    UINT nRepCnt -- �ظ�����
       * @param    UINT nFlags -- ��־
       * 
       * Describe  �˺�������Ϣ��Ӧ����
       */ 
      void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

      /**
       * SHotKeyCtrl::OnSysKeyDown
       * @brief    ϵͳ���������¼�
       * @param    UINT nChar -- ������Ӧ����ֵ 
       * @param    UINT nRepCnt -- �ظ�����
       * @param    UINT nFlags -- ��־
       * 
       * Describe  �˺�������Ϣ��Ӧ����
       */ 
      void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

      /**
       * SHotKeyCtrl::OnSysKeyUp
       * @brief    ϵͳ����̧���¼�
       * @param    UINT nChar -- ������Ӧ����ֵ 
       * @param    UINT nRepCnt -- �ظ�����
       * @param    UINT nFlags -- ��־
       * 
       * Describe  �˺�������Ϣ��Ӧ����
       */ 
      void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

      void UpdateModifier();

      void UpdateCaret();

      SOUI_ATTRS_BEGIN()
          ATTR_WORD(L"invalidComb",m_wInvalidComb,FALSE)
          ATTR_WORD(L"defCombKey",m_wInvalidModifier,FALSE)
          ATTR_WORD(L"combKey",m_wModifier,FALSE)
          ATTR_WORD(L"hotKey",m_wVK,FALSE)
      SOUI_ATTRS_END()

      SOUI_MSG_MAP_BEGIN()
          MSG_WM_CREATE(OnCreate)
          MSG_WM_PAINT_EX(OnPaint)
          MSG_WM_LBUTTONDOWN(OnLButtonDown)
          MSG_WM_SETFOCUS_EX(OnSetFocus)
          MSG_WM_KILLFOCUS_EX(OnKillFocus)
          MSG_WM_KEYDOWN(OnKeyDown)
          MSG_WM_KEYUP(OnKeyUp)
          MSG_WM_SYSKEYDOWN(OnSysKeyDown)
          MSG_WM_SYSKEYUP(OnSysKeyUp)
      SOUI_MSG_MAP_END()
      WORD     m_wInvalidComb;     /**< ��Ч����ϼ� */
      WORD     m_wInvalidModifier; /**< ����Ч��ϼ����滻����,Ĭ�Ϸ��� */

      BOOL    m_bInSetting;        /**< ���������� */
      CAutoRefPtr<IFont> m_curFont;/**< ��ǰ���壬���ڼ������ִ�С */
  };
}
//namespace SOUI
