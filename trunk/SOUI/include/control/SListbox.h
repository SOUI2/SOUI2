/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 * 
 * @file       SListbox.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-06
 * 
 * Describe     
 */
#pragma  once
#include "core/SPanel.h"

namespace SOUI
{
/** 
 * @struct    tagLBITEM
 * @brief     LBitem
 *
 * @Describe  LBitem�ṹ��
 */
typedef struct tagLBITEM
{
    SStringT    strText;  /**< �ı� */
    int         nImage;   /**< ͼ�� */
    LPARAM      lParam;   /**< ���Ӳ��� */

    tagLBITEM()
    {
        nImage = -1;
        lParam = NULL;
    }

} LBITEM, *LPLBITEM;

/** 
 * @class     SListBox
 * @brief     �б��
 *
 * Describe   �б��
 */
class SOUI_EXP SListBox :public SScrollView
{
public:

    SOUI_CLASS_NAME(SListBox, L"listbox")
    /**
     * SListBox::SListBox
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    SListBox();

    /**
     * SListBox::~SListBox
     * @brief    ��������
     *
     * Describe  ��������  
     */
    virtual ~SListBox();

    /**
     * SListBox::GetCount
     * @brief    ��ȡ�����
     * @return   ����int
     *
     * Describe  ��ȡ�����
     */
    int GetCount() const;

    /**
     * SListBox::GetCurSel
     * @brief    ��ȡ��ǰѡ��������
     * @return   ����int
     *
     * Describe  ��ȡ��ǰѡ��������
     */
    int GetCurSel() const;

    /**
     * SListBox::SetCurSel
     * @brief    ����ѡ����
     * @param    int nIndex -- ��ѡ������
     *
     * Describe  ����ѡ����
     */
    BOOL SetCurSel(int nIndex);

    /**
     * SListBox::GetTopIndex
     * @brief    ��ȡ�ö���ѡ������
     * @return   ����int
     *
     * Describe  ����ѡ����
     */
    inline int GetTopIndex() const;

    /**
     * SListBox::SetTopIndex
     * @brief    �����ö���
     * @param    int nIndex -- ���ö�������
     *
     * Describe  �����ö���
     */
    BOOL SetTopIndex(int nIndex);

    /**
     * SListBox::GetItemHeight
     * @brief    ��ȡ�߶�
     * @return   ����int 
     *
     * Describe  ��ȡ�߶�
     */
    int GetItemHeight() const
    {
        return m_nItemHei;
    }

    /**
     * SListBox::GetItemData
     * @brief    ��ȡ��������
     * @param    int nIndex -- ѡ������
     * @return   ����LPARAM
     *
     * Describe  ��ȡ��������
     */
    LPARAM GetItemData(int nIndex) const;

    /**
     * SListBox::SetItemData
     * @brief    ����ѡ�������
     * @param    int nIndex -- ѡ������
     * @param    LPARAM lParam  -- ��������
     * @return   ����BOOL
     *
     * Describe  ����ѡ�������
     */
    BOOL SetItemData(int nIndex, LPARAM lParam);

    /**
     * SListBox::GetText
     * @brief    ��ȡָ�����ı�
     * @param    int nIndex -- ѡ������
     * @param    LPTSTR lpszBuffer -- ������
     * @return   ����int 
     *
     * Describe  ��ȡָ�����ı�
     */
    int GetText(int nIndex, LPTSTR lpszBuffer) const;

    /**
     * SListBox::GetText
     * @brief    ��ȡָ�����ı�
     * @param    int nIndex -- ѡ������
     * @param    SStringT& strText -- ������
     * @return   ����int 
     *
     * Describe  ��ȡָ�����ı�
     */
    int GetText(int nIndex, SStringT& strText) const;

    /**
     * SListBox::GetTextLen
     * @brief    ��ȡָ�����ı�����
     * @param    int nIndex -- ѡ������
     * @return   ����int 
     *
     * Describe  ��ȡ�ı�����
     */
    int GetTextLen(int nIndex) const;

    /**
     * SListBox::GetItemHeight
     * @brief    ��ȡָ����߶�
     * @param    int nIndex -- ѡ������
     * @return   ����int 
     *
     * Describe  ��ȡָ����߶�
     */
    int GetItemHeight(int nIndex) const;

    /**
     * SListBox::SetItemHeight
     * @brief    ����ָ����߶�
     * @param    int nIndex -- ѡ������
     * @param    int cyItemHeight -- �߶�
     * @return   ����int 
     *
     * Describe  ����ָ����߶�
     */
    BOOL SetItemHeight(int nIndex, int cyItemHeight);

    /**
     * SListBox::DeleteAll
     * @brief    ɾ������
     *
     * Describe  ɾ������
     */
    void DeleteAll();

    /**
     * SListBox::DeleteString
     * @brief    ����ָ�����ı�
     * @param    int nIndex -- ѡ������
     * @return   ����BOOL
     *
     * Describe  ����ָ�����ı�
     */
    BOOL DeleteString(int nIndex);

    /**
     * SListBox::AddString
     * @brief    ����ı�
     * @param    LPCTSTR lpszItem -- �ı�
     * @param    int nImage -- ͼ��
     * @param    LPARAM lParam -- ��������
     * @return   ����int ����
     *
     * Describe  ����ı�
     */
    int AddString(LPCTSTR lpszItem, int nImage = -1, LPARAM lParam = 0);

    /**
     * SListBox::InsertString
     * @brief    �����ı�
     * @param    int nIndex  -- ����
     * @param    LPCTSTR lpszItem -- �ı�
     * @param    int nImage -- ͼ��
     * @param    LPARAM lParam -- ��������
     * @return   ����int ����
     *
     * Describe  ��ĳ������ı�
     */
    int InsertString(int nIndex, LPCTSTR lpszItem, int nImage = -1, LPARAM lParam = 0);

    /**
     * SListBox::EnsureVisible
     * @brief    ����ĳ����ʾ
     * @param    int nIndex  -- ����
     *
     * Describe  ����ĳ����ʾ
     */
    void EnsureVisible(int nIndex);

    /**
     * SListBox::RedrawItem
     * @brief    �ػ�ѡ��
     * @param    int iItem  -- ����
     *
     * Describe  �ػ�ѡ��
     */
    void RedrawItem(int iItem);

    /**
     * SListBox::HitTest
     * @brief    ��ȡ��������Ϣ
     * @param    CPoint &pt -- ����
     *
     * Describe  �Զ��޸�pt��λ��Ϊ��Ե�ǰ���ƫ����
     */
    int HitTest(CPoint &pt);

protected:
    /**
     * SListBox::CreateChildren
     * @brief    ��������
     * @param    pugi::xml_node xmlNode -- xml�ļ�
     *
     * Describe  ͨ������xml�ļ�����
     */
    virtual BOOL CreateChildren(pugi::xml_node xmlNode);

    /**
     * SListBox::LoadItemAttribute
     * @brief    ��������
     * @param    pugi::xml_node xmlNode -- xml�ļ�
     * @param    LPLBITEM pItem  -- ����
     *
     * Describe  �Զ��޸�pt��λ��Ϊ��Ե�ǰ���ƫ����
     */
    void LoadItemAttribute(pugi::xml_node xmlNode, LPLBITEM pItem);

    /**
     * SListBox::InsertItem
     * @brief    ��������
     * @param    int nIndex -- ����
     * @param    LPLBITEM pItem -- ����������
     *
     * Describe  ��ĳ��֮�����
     */
    int InsertItem(int nIndex, LPLBITEM pItem);

    /**
     * SListBox::GetScrollLineSize
     * @brief    ��ȡ������С
     * @param    BOOL bVertical -- �Ƿ��Ǵ�ֱ
     *
     * Describe  ��ȡ������С
     */
    virtual int GetScrollLineSize(BOOL bVertical);

    /**
     * SListBox::DrawItem
     * @brief    ����
     * @param    IRenderTarget *pRT -- �����豸
     * @param    CRect &rc -- Ŀ������
     * @param    int iItem -- ѡ��
     *
     * Describe  ����
     */
    void DrawItem(IRenderTarget *pRT, CRect &rc, int iItem);

    /**
     * SListBox::NotifySelChange
     * @brief    �޸�ѡ����
     * @param    int nOldSel -- ��ѡ����
     * @param    int nNewSel -- ��ѡ����
     *
     * Describe  �޸�ѡ����
     */
    void NotifySelChange(int nOldSel,int nNewSel);

    /**
     * SListBox::OnGetDlgCode
     * @brief    ��ȡ������Ϣ��
     * @param    ����UINT
     *
     * Describe  ��ȡ������Ϣ��
     */
    UINT OnGetDlgCode();

protected:
    /**
     * SListBox::OnSize
     * @brief    ��Ϣ��Ӧ����
     * @param    UINT nType --
     * @param    CSize size -- 
     *
     * Describe  ��ȡĳ�������  
     */
    void OnSize(UINT nType,CSize size);

    /**
     * SListBox::OnPaint
     * @brief    ����
     * @param    IRenderTarget *pRT -- �����豸
     *
     * Describe  ��Ϣ��Ӧ����  
     */
    void OnPaint(IRenderTarget *pRT);

    /**
     * SListBox::OnLButtonDown
     * @brief    �������
     * @param    UINT nFlags -- ��־
     * @param    CPoint pt -- ����
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnLButtonDown(UINT nFlags,CPoint pt);

    /**
     * SListBox::OnLButtonDbClick
     * @brief    ���˫��
     * @param    UINT nFlags -- ��־
     * @param    CPoint pt -- ����
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnLButtonDbClick(UINT nFlags,CPoint pt);

    /**
     * SListBox::OnLButtonUp
     * @brief    ���̧��
     * @param    UINT nFlags -- ��־
     * @param    CPoint pt -- ����
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnLButtonUp(UINT nFlags,CPoint pt);
    
    /**
     * SListBox::OnMouseMove
     * @brief    ����ƶ�
     * @param    UINT nFlags -- ��־
     * @param    CPoint pt -- ����
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnMouseMove(UINT nFlags,CPoint pt);
    
    /**
     * SListBox::OnKeyDown
     * @brief    ��������
     * @param    TCHAR nChar -- ����ֵ
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );

    /**
     * SListBox::OnChar
     * @brief    ��������
     * @param    TCHAR nChar -- ����ֵ
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    /**
     * SListBox::OnDestroy
     * @brief    ����
     *
     * Describe  ����
     */
    void OnDestroy();

    /**
     * SListBox::OnChar
     * @brief    ��������
     * @param    TCHAR nChar -- ����ֵ
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnShowWindow(BOOL bShow, UINT nStatus);

protected:

    SArray<LPLBITEM>    m_arrItems;  /**< ����item */

    int     m_nItemHei;     /**< item�߶� */
    int     m_iSelItem;     /**< ѡ��item */
    int     m_iHoverItem;   /**< Hover״̬��item */
    int     m_iScrollSpeed; /**< �����ٶ� */
    BOOL    m_bHotTrack;    /**<  */

    CPoint m_ptIcon;  /**< ͼ������ */
    CPoint m_ptText;  /**< �ı����� */

    COLORREF m_crItemBg;    /**< ����ɫ */
    COLORREF m_crItemBg2;   /**< ����ɫ */
    COLORREF m_crItemSelBg; /**< ѡ�б���ɫ */
    COLORREF m_crText;      /**< ����ɫ */
    COLORREF m_crSelText;   /**< ѡ�б���ɫ */
    ISkinObj *m_pItemSkin, *m_pIconSkin;

public:

    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"scrollSpeed", m_iScrollSpeed, FALSE)
        ATTR_INT(L"itemHeight", m_nItemHei, FALSE)
        ATTR_SKIN(L"itemSkin", m_pItemSkin, TRUE)
        ATTR_SKIN(L"iconSkin", m_pIconSkin, TRUE)
        ATTR_COLOR(L"colorItemBkgnd",m_crItemBg,FALSE)
        ATTR_COLOR(L"colorItemBkgnd2", m_crItemBg2, FALSE)
        ATTR_COLOR(L"colorItemSelBkgnd",m_crItemSelBg,FALSE)
        ATTR_COLOR(L"colorText",m_crText,FALSE)
        ATTR_COLOR(L"colorSelText",m_crSelText,FALSE)
        ATTR_INT(L"icon-x", m_ptIcon.x, FALSE)
        ATTR_INT(L"icon-y", m_ptIcon.y, FALSE)
        ATTR_INT(L"text-x", m_ptText.x, FALSE)
        ATTR_INT(L"text-y", m_ptText.y, FALSE)
        ATTR_INT(L"hotTrack",m_bHotTrack,FALSE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_SIZE(OnSize)
        MSG_WM_PAINT_EX(OnPaint)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONDBLCLK(OnLButtonDbClick)
        MSG_WM_LBUTTONUP(OnLButtonUp)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_KEYDOWN(OnKeyDown)
        MSG_WM_CHAR(OnChar)
        MSG_WM_SHOWWINDOW(OnShowWindow)
    SOUI_MSG_MAP_END()
};

}//namespace SOUI