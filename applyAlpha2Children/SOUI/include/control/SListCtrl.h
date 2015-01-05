/**
* Copyright (C) 2014-2050 SOUI�Ŷ�
* All rights reserved.
* 
* @file       SListCtrl.h
* @brief      
* @version    v1.0      
* @author     soui      
* @date       2014-07-06
* 
* Describe    ListCtrl�ؼ� 
*/
#pragma once
#include "core/SPanel.h"
#include "SHeaderCtrl.h"

namespace SOUI
{
    /** 
    * @enum      
    * @brief     ����
    *
    * Describe   ����
    */
    enum{
        S_LVIF_TEXT=0x01,
        S_LVIF_IMAGE=0x02,
        S_LVIF_INDENT=0x04,
    };

    /** 
    * qsort_s    
    * @brief     �ȽϺ���--����ָ��
    *
    * Describe   ����ָ��
    */
    typedef int (__cdecl  *PFNLVCOMPAREEX)(void *, const void *, const void *);//ʹ�ÿ��������㷨�еıȽϺ���,�ο�qsort_s

    /** 
    * @struct    _DXLVSUBITEM
    * @brief     ����ṹ
    *
    * @Describe  ����ṹ
    */
    typedef struct _DXLVSUBITEM
    {
        /** 
        * _DXLVSUBITEM   
        * @brief     ���캯��
        *
        * Describe   ���캯��
        */
        _DXLVSUBITEM()
        {
            mask=0;
            nImage = 0;
            strText=NULL;
            cchTextMax=0;
            nIndent=0;
        }

        UINT    mask;         /**<  */
        LPTSTR  strText;      /**< �ı� */
        int     cchTextMax;   /**< �ı������ */
        UINT    nImage;       /**< ͼ�� */
        int     nIndent;      /**< ���� */
    } DXLVSUBITEM;

    typedef SArray<DXLVSUBITEM>   ArrSubItem; /**< ������������	 */

    /** 
    * @struct    _DXLVITEM
    * @brief     ��Ŀ�ṹ
    *
    * @Describe  ��Ŀ�ṹ
    */
    typedef struct _DXLVITEM
    {
        /** 
        * _DXLVITEM   
        * @brief     ���캯��
        *
        * Describe   ���캯��
        */
        _DXLVITEM()
        {
            dwData = 0;
            arSubItems=NULL;
            checked = FALSE;
        }

        ArrSubItem  *arSubItems;
        DWORD       dwData;
        BOOL    checked;
    } DXLVITEM;

    //////////////////////////////////////////////////////////////////////////
    //  SListCtrl
    class SOUI_EXP SListCtrl : public SPanel
    {
        SOUI_CLASS_NAME(SListCtrl, L"listctrl")

    public:
        /**
        * SListCtrl::SListCtrl
        * @brief    ���캯��
        *
        * Describe  ���캯��  
        */
        SListCtrl();

        /**
        * SListCtrl::~SListCtrl
        * @brief    ��������
        *
        * Describe  ��������  
        */
        virtual ~SListCtrl();
        /**
        * SListCtrl::InsertColumn
        * @brief    ����һ��
        * @param    int nIndex -- ����
        * @param    LPCTSTR pszText -- ����
        * @param    int nWidth -- ���
        * @param    LPARAM lParam -- ���Ӳ���
        *
        * Describe  ����һ��
        */
        int             InsertColumn(int nIndex, LPCTSTR pszText, int nWidth, LPARAM lParam=0);
        /**
        * SListCtrl::InsertItem
        * @brief    ������Ŀ
        * @param    int nIndex -- ����
        * @param    LPCTSTR pszText -- ����
        * @param    int nImage -- ͼ��
        *
        * Describe  ������Ŀ
        */
        int             InsertItem(int nItem, LPCTSTR pszText, int nImage=-1);
        /**
        * SListCtrl::SetItemData
        * @brief    ���ø�������
        * @param    int nItem -- ����
        * @param    DWORD dwData-- ��������
        *
        * Describe  ���ø�������
        */
        BOOL            SetItemData(int nItem, DWORD dwData);
        /**
        * SListCtrl::GetItemData
        * @brief    ��ȡ��������
        * @param    int nItem -- ����
        * @return   ����DWORD
        *
        * Describe  ��ȡ��������
        */
        DWORD           GetItemData(int nItem);
        /**
        * SListCtrl::SetSubItem
        * @brief    ��������
        * @param    int nItem -- ����
        * @param    int nSubItem -- ��������
        * @param    const DXLVSUBITEM* plv -- 
        * @return   ����BOOL
        *
        * Describe  ��������
        */
        BOOL            SetSubItem(int nItem, int nSubItem,const DXLVSUBITEM* plv);
        /**
        * SListCtrl::GetSubItem
        * @brief    ��ȡ����
        * @param    int nItem -- ����
        * @param    int nSubItem -- ��������
        * @param    DXLVSUBITEM* plv -- 
        * @return   ����BOOL
        *
        * Describe  ��ȡ��������
        */
        BOOL            GetSubItem(int nItem, int nSubItem, DXLVSUBITEM* plv) const;
        /**
        * SListCtrl::SetSubItemText
        * @brief    ���������ı�
        * @param    int nItem -- ����
        * @param    int nSubItem -- ��������
        * @param    LPCTSTR pszText -- �ı�
        * @return   ����BOOL
        *
        * Describe  ���������ı�
        */
        BOOL            SetSubItemText(int nItem, int nSubItem, LPCTSTR pszText);

        /**
        * GetSubItemText
        * @brief    ��ȡ�����ı�
        * @param    int nItem -- ����
        * @param    int nSubItem -- ��������
        * @return   SOUI::SStringT -- ����ַ���
        * Describe  
        */    
        SStringT        GetSubItemText(int nItem, int nSubItem) const;

        /**
        * SListCtrl::GetSelectedItem
        * @brief    ��ȡѡ����
        * @return   ����int
        *
        * Describe  ����ѡ����
        */
        int             GetSelectedItem();
        /**
        * SListCtrl::SetSelectedItem
        * @brief    ����ѡ����
        * @param    int nItem -- ����
        *
        * Describe  ����ѡ����
        */
        void            SetSelectedItem(int nItem);
        /**
        * SListCtrl::GetItemCount
        * @brief    ��ȡ��Ŀ����
        * @return   ����int
        *
        * Describe  ��ȡ��Ŀ����
        */
        int             GetItemCount() const;
        /**
        * SListCtrl::SetItemCount
        * @brief    ������Ŀ��
        * @param    int nItems -- ����
        * @param    int nGrowBy -- 
        * @return   ����BOOL
        *
        * Describe  ������Ŀ��
        */
        BOOL            SetItemCount( int nItems ,int nGrowBy);
        /**
        * SListCtrl::GetColumnCount
        * @brief    ��ȡ������
        * @return   ����int
        *
        * Describe  ��ȡ������
        */
        int             GetColumnCount() const;
        /**
        * SListCtrl::GetCountPerPage
        * @brief    ��ȡÿҳ��Ŀ����
        * @return   ����int
        *
        * Describe  ��ȡÿҳ��Ŀ����
        */
        int             GetCountPerPage(BOOL bPartial);
        /**
        * SListCtrl::DeleteItem
        * @brief    ɾ��ָ����
        * @param    int nItem -- ����
        *
        * Describe  ɾ��ָ����
        */
        void            DeleteItem(int nItem);
        /**
        * SListCtrl::DeleteColumn
        * @brief    ɾ��ָ����
        * @param    int iCol -- ����
        *
        * Describe  ɾ��ָ����
        */
        void            DeleteColumn(int iCol);
        /**
        * SListCtrl::DeleteAllItems
        * @brief    ɾ��������
        *
        * Describe  ɾ��������
        */
        void            DeleteAllItems();

        /**
        * SListCtrl::CreateChildren
        * @brief    ��������
        * @param    pugi::xml_node xmlNode -- xml�ļ�
        *
        * Describe  ͨ������xml�ļ�����
        */
        virtual BOOL    CreateChildren(pugi::xml_node xmlNode);

        /**
        * SListCtrl::HitTest
        * @brief    ��ȡ��������Ϣ
        * @param    CPoint &pt -- ����
        *
        * Describe  �Զ��޸�pt��λ��Ϊ��Ե�ǰ���ƫ����
        */
        int             HitTest(const CPoint& pt);
        /**
        * SListCtrl::SortItems
        * @brief    ����
        * @param    PFNLVCOMPAREEX pfnCompare -- �ȽϺ���
        * @param    void * pContext -- �Ƚ�����
        * @return   ����BOOL
        * 
        * Describe  ����
        */
        BOOL            SortItems( PFNLVCOMPAREEX pfnCompare, void * pContext );

        /**
        * SListCtrl::GetCheckState
        * @brief    ��ȡĳһ���Ƿ�ѡ��
        * @param    int nItem -- ָ����һ��
        * @return   ����ѡ��״̬
        *
        * Describe  ��ȡĳһ���Ƿ�ѡ��
        */
        BOOL            GetCheckState(int nItem);  

        /**
        * SListCtrl::SetCheckState
        * @brief   ����ĳһ�е�ѡ��״̬
        * @param   int nItem -- ָ����
        * @param   BOOL bCheck -- ״̬
        * @return  ���غ���ִ���Ƿ�ɹ�
        *
        * Describe ����ĳһ�е�ѡ��״̬
        */
        BOOL            SetCheckState(int nItem, BOOL bCheck);  

        /**
        * SListCtrl::GetCheckedItemCount
        * @brief   ��ȡѡ���еļ���
        * @return  ���ؼ���
        *
        * Describe ��ȡѡ���еļ���
        */
        int             GetCheckedItemCount();


        int             GetFirstCheckedItem();
        int             GetLastCheckedItem();
        VOID            EnableMultiSelection(BOOL enable) { m_bMultiSelection = enable; }
        VOID            EnableCheckBox(BOOL enable) { m_bCheckBox = enable; }
        VOID            EnableHotTrack(BOOL enable) { m_bHotTrack = enable; }
    protected:
        /**
        * SListCtrl::GetTopIndex
        * @brief    ��ȡ�ö���ѡ������
        * @return   ����int
        *
        * Describe  ����ѡ����
        */
        int             GetTopIndex() const;
        /**
        * SListCtrl::GetItemRect
        * @brief    ��ȡitemλ��
        * @param    int nItem -- ����
        * @param    int nSubItem -- ��������
        * @return   ����int
        *
        * Describe  ����ѡ����
        */
        CRect           GetItemRect(int nItem, int nSubItem=0);

        /**
        * SListCtrl::DrawItem
        * @brief    ����
        * @param    IRenderTarget *pRT -- �����豸
        * @param    CRect &rc -- Ŀ������
        * @param    int iItem -- ѡ��
        *
        * Describe  ����
        */
        virtual void    DrawItem(IRenderTarget *pRT, CRect rcItem, int nItem);
        /**
        * SListCtrl::RedrawItem
        * @brief    �ػ�ѡ��
        * @param    int iItem  -- ����
        *
        * Describe  �ػ�ѡ��
        */
        void            RedrawItem(int nItem);

        /**
        * SListCtrl::NotifySelChange
        * @brief    �޸�ѡ����
        * @param    int nOldSel -- ��ѡ����
        * @param    int nNewSel -- ��ѡ����
        *
        * Describe  �޸�ѡ����
        */
        void            NotifySelChange(int nOldSel, int nNewSel, BOOL checkBox = FALSE);
        /**
        * SListCtrl::OnPaint
        * @brief    ����
        * @param    IRenderTarget *pRT -- �����豸
        *
        * Describe  ��Ϣ��Ӧ���� 
        */
        void            OnPaint(IRenderTarget *pRT);
        /**
        * SListCtrl::OnDestroy
        * @brief    ����
        *
        * Describe  ����
        */
        void            OnDestroy();
        /**
        * SListCtrl::OnHeaderClick
        * @brief    �б�ͷ�����¼� -- 
        * @param    EventArgs *pEvt
        *
        * Describe  �б�ͷ�����¼�
        */
        bool            OnHeaderClick(EventArgs *pEvt);
        /**
        * SListCtrl::OnHeaderSizeChanging
        * @brief    �б�ͷ��С�ı�
        * @param    EventArgs *pEvt -- 
        *
        * Describe  �б�ͷ��С�ı�
        */
        bool            OnHeaderSizeChanging(EventArgs *pEvt);
        /**
        * SListCtrl::OnHeaderSwap
        * @brief    �б�ͷ����
        * @param    EventArgs *pEvt -- 
        *
        * Describe  �б�ͷ����
        */
        bool            OnHeaderSwap(EventArgs *pEvt);
        /**
        * SListCtrl::OnScroll
        * @brief    �����¼�
        * @param    BOOL bVertical -- �Ƿ��Ǵ�ֱ
        * @param    UINT uCode -- 
        * @param    int nPos -- 
        *
        * Describe  �б�ͷ����
        */
        virtual BOOL    OnScroll(BOOL bVertical,UINT uCode,int nPos);
        /**
        * SListCtrl::OnLButtonDown
        * @brief    �������
        * @param    UINT nFlags -- ��־
        * @param    CPoint pt -- ����
        *
        * Describe  ��Ϣ��Ӧ���� 
        */
        void    OnLButtonDown(UINT nFlags, CPoint pt);

        /**
        * SListCtrl::OnLButtonUp
        * @brief    ���̧��
        * @param    UINT nFlags -- ��־
        * @param    CPoint pt -- ����
        *
        * Describe  ��Ϣ��Ӧ���� 
        */
        void    OnLButtonUp(UINT nFlags, CPoint pt);

        /**
        * OnMouseMove
        * @brief    ��������ƶ�
        * @param    UINT nFlags --  ��־
        * @param    CPoint pt --  ����
        * @return   void 
        * Describe  
        */    
        void    OnMouseMove(UINT nFlags, CPoint pt);

        /**
        * OnMouseLeave
        * @brief    ��������뿪��Ϣ
        * @return   void
        * Describe  
        */    
        void   OnMouseLeave();

        /**
        * SListCtrl::OnSize
        * @brief    ��Ϣ��Ӧ����
        * @param    UINT nType --
        * @param    CSize size -- 
        *
        * Describe  ��ȡĳ�������  
        */
        void    OnSize(UINT nType, CSize size);
        /**
        * SListCtrl::UpdateChildrenPosition
        * @brief    ��������λ��
        *
        * Describe  ��������λ��
        */
        virtual void    UpdateChildrenPosition();
        /**
        * SListCtrl::GetListRect
        * @brief    ��ȡlistλ��
        * @return   ����CRect 
        *
        * Describe  ��ȡlistλ��
        */
        CRect           GetListRect();
        /**
        * SListCtrl::UpdateScrollBar
        * @brief    ���¹�����
        *
        * Describe  ���¹�����
        */
        void            UpdateScrollBar();
        /**
        * SListCtrl::UpdateHeaderCtrl
        * @brief    �����б�ͷ�ؼ�
        *
        * Describe  �����б�ͷ�ؼ�
        */
        void            UpdateHeaderCtrl();

        BOOL            HitCheckBox(const CPoint& pt);

    protected:
        int             m_nHeaderHeight;  /**< �б�ͷ�߶� */
        int             m_nItemHeight;  /**< ��Ŀ�߶� */

        int             m_nSelectItem;  /**< ѡ���� */
        int             m_nHoverItem;  /**< Hover״̬�� */
        BOOL            m_bHotTrack;  /**<  */

        CPoint          m_ptIcon;  /**< ͼ��λ�� */
        CPoint          m_ptText;  /**< �ı�λ�� */

        COLORREF        m_crItemBg;  /**< ����ɫ */
        COLORREF        m_crItemBg2;  /**< ����ɫ */
        COLORREF        m_crItemSelBg;  /**< ѡ�б���ɫ */
        COLORREF        m_crText;  /**< �ı���ɫ */
        COLORREF        m_crSelText;  /**< ѡ���ı���ɫ */

        ISkinObj*    m_pItemSkin;  /**< */
        ISkinObj*    m_pIconSkin;  /**< */
        ISkinObj*    m_pCheckSkin; /**< */
        BOOL        m_bCheckBox;
        BOOL        m_bMultiSelection;

    protected:
        typedef SArray<DXLVITEM> ArrLvItem;  /**< ����item���� */

        SHeaderCtrl*  m_pHeader;  /**< �б�ͷ�ؼ� */
        ArrLvItem       m_arrItems;  /**< */
        CPoint          m_ptOrigin;  /**< */

    protected:
        SOUI_ATTRS_BEGIN()
            ATTR_INT(L"headerHeight", m_nHeaderHeight, FALSE)
            ATTR_INT(L"itemHeight", m_nItemHeight, FALSE)
            ATTR_INT(L"checkBox", m_bCheckBox, TRUE)
            ATTR_INT(L"multiSelection", m_bMultiSelection, TRUE)
            ATTR_SKIN(L"itemSkin", m_pItemSkin, TRUE)
            ATTR_SKIN(L"iconSkin", m_pIconSkin, TRUE)
            ATTR_SKIN(L"checkSkin", m_pCheckSkin, TRUE)
            ATTR_COLOR(L"colorItemBkgnd", m_crItemBg, FALSE)
            ATTR_COLOR(L"colorItemBkgnd2", m_crItemBg2, FALSE)
            ATTR_COLOR(L"colorItemSelBkgnd", m_crItemSelBg, FALSE)
            ATTR_COLOR(L"colorText", m_crText, FALSE)
            ATTR_COLOR(L"colorSelText", m_crSelText, FALSE)
            ATTR_INT(L"icon-x", m_ptIcon.x, FALSE)
            ATTR_INT(L"icon-y", m_ptIcon.y, FALSE)
            ATTR_INT(L"text-x", m_ptText.x, FALSE)
            ATTR_INT(L"text-y", m_ptText.y, FALSE)
            ATTR_INT(L"hotTrack", m_bHotTrack, FALSE)
        SOUI_ATTRS_END()

        SOUI_MSG_MAP_BEGIN()
            MSG_WM_PAINT_EX(OnPaint)
            MSG_WM_DESTROY(OnDestroy)
            MSG_WM_SIZE(OnSize)
            MSG_WM_LBUTTONDOWN(OnLButtonDown)
            MSG_WM_LBUTTONUP(OnLButtonUp)
            MSG_WM_MOUSEMOVE(OnMouseMove)
            MSG_WM_MOUSELEAVE(OnMouseLeave)
        SOUI_MSG_MAP_END()
    };

}//end of namespace
