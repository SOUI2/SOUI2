/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       SHeaderCtrl.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-02
 * 
 * Describe     
 */
#pragma once

#include "core/SWnd.h"
namespace SOUI
{
  #define SHDI_WIDTH               0x0001
  #define SHDI_TEXT                0x0002
  #define SHDI_SORTFLAG            0x0004
  #define SHDI_LPARAM              0x0008
  #define SHDI_ORDER               0x0010

  /**
   * @enum      _SHDSORTFLAG
   * @brief     �����־ 
   * 
   * Describe   �����־
   */
  typedef enum _SHDSORTFLAG{
    ST_NULL=0,
    ST_UP,
    ST_DOWN,
  }SHDSORTFLAG;

  /**
   * @struct    _SHDITEM
   * @brief     �б�ͷ�� 
   * 
   * Describe   �б�ͷ��
   */
  typedef struct _SHDITEM {
    UINT    mask; 
    int     cx; 
    LPTSTR  pszText; 
    int     cchTextMax; 
    SHDSORTFLAG stFlag;
    LPARAM  lParam; 
    UINT   state;
    int        iOrder;
  } SHDITEM,  *LPSHDITEM;


  /**
   * @class     SHeaderCtrl
   * @brief     ��ͷ�ؼ� 
   * 
   * Describe   ��ͷ�ؼ�
   */
  class SOUI_EXP SHeaderCtrl: public SWindow
  {
      SOUI_CLASS_NAME(SHeaderCtrl, L"header")
  public:
      /**
       * SHeaderCtrl::SHeaderCtrl
       * @brief    ���캯��
       *
       * Describe  ���캯��  
       */
      SHeaderCtrl(void);
      /**
       * SHeaderCtrl::~SHeaderCtrl
       * @brief    ��������
       *
       * Describe  ��������  
       */      
      ~SHeaderCtrl(void);

      /**
       * SHeaderCtrl::InsertItem
       * @brief    ��������
       * @param    int iItem --  ��������
       * @param    LPCTSTR pszText  --  �������
       * @param    int nWidth  -- ���
       * @param    SHDSORTFLAG stFlag -- �����־
       * @param    LPARAM lParam -- ���Ӳ���
       * @return   ����int 
       *
       * Describe  ��������  
       */      
      int InsertItem(int iItem,LPCTSTR pszText,int nWidth, SHDSORTFLAG stFlag,LPARAM lParam );
      /**
       * SHeaderCtrl::GetItem
       * @brief    �������
       * @param    int iItem  --  ����
       * @param    SHDITEM *pItem  -- �����б���ṹ
       * @return   ����BOOL 
       *
       * Describe  �������  
       */      
      BOOL GetItem(int iItem,SHDITEM *pItem);

      /**
       * SHeaderCtrl::GetItemCount
       * @brief    ��ȡ�б������
       * @return   ����int 
       *
       * Describe  ��ȡ�б������  
       */      
      int GetItemCount(){return m_arrItems.GetCount();}

      /**
       * SHeaderCtrl::GetTotalWidth
       * @brief    ������п��
       * @return   ����int 
       *
       * Describe  ������п��  
       */      
      int GetTotalWidth();

      /**
       * SHeaderCtrl::GetItemWidth
       * @brief    ���ָ������
       * @param    int iItem  --  ����
       * @return   ����int 
       *
       * Describe  �������  
       */            
      int GetItemWidth(int iItem);
      /**
       * SHeaderCtrl::DeleteItem
       * @brief    ɾ��ָ����
       * @param    int iItem  --  ����
       * @return   ����BOOL 
       *
       * Describe  ɾ��ָ����  
       */            
      BOOL DeleteItem(int iItem);

      /**
       * SHeaderCtrl::DeleteAllItems
       * @brief    ɾ��������
       *
       * Describe  �������  
       */            
      void DeleteAllItems();

      SOUI_ATTRS_BEGIN()
          ATTR_SKIN(L"itemSkin",m_pSkinItem,FALSE)
          ATTR_SKIN(L"sortSkin",m_pSkinSort,FALSE)
          ATTR_INT(L"fixWidth",m_bFixWidth,FALSE)
          ATTR_INT(L"itemSwapEnable",m_bItemSwapEnable,FALSE)
          ATTR_INT(L"sortHeader",m_bSortHeader,FALSE)
      SOUI_ATTRS_END()
  protected:
      /**
       * SHeaderCtrl::CreateChildren
       * @brief    ��������
       * @param    pugi::xml_node xmlNode  -- xml�����ļ�
       *
       * Describe  ��������  
       */              
      virtual BOOL CreateChildren(pugi::xml_node xmlNode);

      /**
       * SHeaderCtrl::OnSetCursor
       * @brief    ����ѡ��
       * @param    const CPoint &pt  --  �����
       *
       * Describe  �������  
       */            
      virtual BOOL OnSetCursor(const CPoint &pt);
      /**
       * SHeaderCtrl::OnPaint
       * @brief    ����ѡ��
       * @param    IRenderTarget * pRT  --  ��ȾĿ��
       *
       * Describe  ��Ϣ��Ӧ����  
       */            
      void OnPaint(IRenderTarget * pRT);

      /**
       * SHeaderCtrl::DrawItem
       * @brief    �滭
       * @param    IRenderTarget * pRT  --  ��ȾĿ��
       * @param    CRect rcItem  --  Ŀ������
       * @param    const LPSHDITEM pItem  --  �б�ͷ
       *
       * Describe  �滭  
       */            
      virtual void DrawItem(IRenderTarget * pRT,CRect rcItem,const LPSHDITEM pItem);

      /**
       * SHeaderCtrl::GetItemRect
       * @brief    ��ȡ��ͷ���λ��
       * @param    UINT iItem  --  ����
       *
       * Describe  ��ȡ��ͷ���λ��  
       */            
      CRect GetItemRect(UINT iItem);

      /**
       * SHeaderCtrl::HitTest
       * @brief    
       * @param    CPoint pt  --  ����
       *
       * Describe  ���λ�÷���������һ��DWORD��LOWORDΪǰ����
       *           HIWORDΪ������ ��ͬʱ������һ������м�
       */
      DWORD  HitTest(CPoint pt);

      /**
       * SHeaderCtrl::RedrawItem
       * @brief    �ػ�
       * @param    CPoint pt  --  ����
       *
       * Describe  �ػ�
       */
      void RedrawItem(int iItem);

      /**
       * SHeaderCtrl::DrawDraggingState
       * @brief    ������ק״̬
       * @param    DWORD dwDragTo  --  
       *
       * Describe  ������ק״̬
       */
      void DrawDraggingState(DWORD dwDragTo);

      /**
       * SHeaderCtrl::IsItemHover
       * @brief    �ж��Ƿ�Hover״̬
       * @param    DWORD dwHitTest 
       * @return   ����BOOL
       *
       * Describe  �ж��Ƿ�Hover״̬
       */
      BOOL IsItemHover(DWORD dwHitTest)
      {
          return dwHitTest!=-1 && LOWORD(dwHitTest)==HIWORD(dwHitTest);
      }

      /**
       * SHeaderCtrl::CreateDragImage
       * @brief    ������קͼƬ
       * @param    UINT iItem -- �б���
       * @return   ����HBITMAP
       *
       * Describe  �ж��Ƿ�Hover״̬
       */
      HBITMAP CreateDragImage(UINT iItem);
      /**
       * SHeaderCtrl::OnLButtonDown
       * @brief    ��������¼�
       * @param    UINT nFlags -- ��־
       * @param    CPoint point -- �������
       *
       * Describe  �˺�������Ϣ��Ӧ����
       */
      void OnLButtonDown(UINT nFlags,CPoint pt);
      /**
       * SHeaderCtrl::OnLButtonUp
       * @brief    ���̧���¼�
       * @param    UINT nFlags -- ��־
       * @param    CPoint point -- �������
       *
       * Describe  �˺�������Ϣ��Ӧ����
       */      
      void OnLButtonUp(UINT nFlags,CPoint pt);
      /**
       * SHeaderCtrl::OnMouseMove
       * @brief    ����ƶ��¼�
       * @param    UINT nFlags -- ��־
       * @param    CPoint point -- �������
       *
       * Describe  �˺�������Ϣ��Ӧ����
       */      
      void OnMouseMove(UINT nFlags,CPoint pt);

      /**
       * SHeaderCtrl::OnMouseLeave
       * @brief    ����뿪�¼�
       *
       * Describe  �˺�������Ϣ��Ӧ����
       */      
      void OnMouseLeave();

      /**
       * SHeaderCtrl::OnDestroy
       * @brief    �����¼�
       *
       * Describe  �˺�������Ϣ��Ӧ����
       */            
      void OnDestroy();
      
      SOUI_MSG_MAP_BEGIN()
          MSG_WM_PAINT_EX(OnPaint)
          MSG_WM_LBUTTONDOWN(OnLButtonDown)
          MSG_WM_LBUTTONUP(OnLButtonUp)
          MSG_WM_MOUSEMOVE(OnMouseMove)
          MSG_WM_MOUSELEAVE(OnMouseLeave)
          MSG_WM_DESTROY(OnDestroy)
      SOUI_MSG_MAP_END()

      ISkinObj *    m_pSkinItem;  /**< ��ͷ����Skin */
      ISkinObj *    m_pSkinSort;  /**< �����־Skin */
      BOOL          m_bSortHeader;      /**< ��ͷ���Ե������ */
      BOOL          m_bFixWidth;        /**< �����ȹ̶����� */
      BOOL          m_bItemSwapEnable;  /**< �����϶�����λ�ÿ��� */

      BOOL            m_bDragging; /**< �����϶���־ */
      HBITMAP         m_hDragImg;  /**< ��ʾ�϶����ڵ���ʱλͼ */
      CPoint          m_ptClick;   /**< ��ǰ������� */
      DWORD           m_dwHitTest; /**< ���λ�� */
      DWORD           m_dwDragTo;  /**< �Ϸ�Ŀ�� */    
      int             m_nAdjItemOldWidth;  /**< ���汻�϶����ԭʼ��� */
      SArray<SHDITEM> m_arrItems; /**< �б���� */
  };
}//end of namespace SOUI
