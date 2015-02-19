/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 * 
 * @file       stabctrl.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-06
 * 
 * Describe    ��չ�б�� 
 */
#pragma once
#include "core/SPanel.h"
#include "core/SItempanel.h"
#include "stree.hpp"

namespace SOUI
{
/** 
 * @class     STreeItem 
 * @brief     tree item
 *
 * Describe   tree item
 */
class SOUI_EXP STreeItem : public SItemPanel
{
public:
    /**
     * STreeItem::STreeItem
     * @brief    ���캯��
     * @param    SWindow *pFrameHost -- ����
     * @param    IItemContainer *pContainer -- ���������
     *
     * Describe  ���캯��  
     */
    STreeItem(SWindow *pFrameHost,IItemContainer *pContainer);

    BOOL m_bCollapsed; /**< �Ƿ��۵� */
    BOOL m_bVisible;   /**< �Ƿ���ʾ */
    int  m_nLevel;     /**< tree��� */
    int  m_nItemHeight;/**< ����߶� */
    int  m_nBranchHeight;/**< ��֦����ʾ�߶� */
};

/** 
 * @class     STreeBox 
 * @brief     STreeBox
 *
 * Describe   STreeBox
 */
class SOUI_EXP STreeBox
    : public SScrollView
    , public IItemContainer
    , protected CSTree<STreeItem *>
{
    SOUI_CLASS_NAME(STreeBox, L"treebox")
public:
    /**
     * STreeBox::STreeBox
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    STreeBox();

    /**
     * STreeBox::~STreeBox
     * @brief    ��������
     *
     * Describe  ��������
     */
    virtual ~STreeBox();

    /**
     * STreeBox::InsertItem
     * @brief    ��������    
     * @param    pugi::xml_node xmlNode -- xml���ݽ��
     * @param    DWORD dwData -- ��������
     * @param    HSTREEITEM hParent -- ���ڵ�
     * @param    HSTREEITEM hInsertAfter -- ĳ��֮�����
     * @param    BOOL bEnsureVisible -- �Ƿ���ʾ
     * @return   ����HSTREEITEM
     * 
     * Describe  ��������
     */
    HSTREEITEM InsertItem(pugi::xml_node xmlNode,DWORD dwData,HSTREEITEM hParent=STVI_ROOT, HSTREEITEM hInsertAfter=STVI_LAST,BOOL bEnsureVisible=FALSE);

    /**
     * STreeBox::InsertItem
     * @brief    ��������    
     * @param    LPCWSTR pszXml -- xml�ַ���(utf16)
     * @param    DWORD dwData -- ��������
     * @param    HSTREEITEM hParent -- ���ڵ�
     * @param    HSTREEITEM hInsertAfter -- ĳ��֮�����
     * @param    BOOL bEnsureVisible -- �Ƿ���ʾ
     * @return   ����STreeItem*
     * 
     * Describe  ��������
     */
    STreeItem* InsertItem(LPCWSTR pszXml,DWORD dwData,HSTREEITEM hParent=STVI_ROOT, HSTREEITEM hInsertAfter=STVI_LAST,BOOL bEnsureVisible=FALSE);

    /**
     * STreeBox::RemoveItem
     * @brief    ɾ��ĳ��    
     * @param    HSTREEITEM hItem -- ��ɾ���ڵ�
     * @return   ����BOOL
     * 
     * Describe  ��������
     */
    BOOL RemoveItem(HSTREEITEM hItem);

    /**
     * STreeBox::RemoveAllItems
     * @brief    ɾ������ĳ��    
     * 
     * Describe  ��������
     */
    void RemoveAllItems();

    /**
     * STreeBox::GetRootItem
     * @brief    ��ȡ���ڵ�   
     * @return   ����HSTREEITEM
     * 
     * Describe  ��ȡ���ڵ�   
     */
    HSTREEITEM GetRootItem();

    /**
     * STreeBox::GetNextSiblingItem
     * @brief    ��ȡ�ֵܽڵ�--��һ��  
     * @param    HSTREEITEM hItem -- �ڵ�
     * @return   ����HSTREEITEM
     * 
     * Describe  ��ȡ�ֵܽڵ�--��һ��  
     */
    HSTREEITEM GetNextSiblingItem(HSTREEITEM hItem);
    /**
     * STreeBox::GetPrevSiblingItem
     * @brief    ��ȡ�ֵܽڵ�--ǰһ�� 
     * @param    HSTREEITEM hItem -- �ڵ�
     * @return   ����HSTREEITEM
     * 
     * Describe  ��ȡ�ֵܽڵ�--ǰһ��
     */
    HSTREEITEM GetPrevSiblingItem(HSTREEITEM hItem);
    /**
     * STreeBox::GetChildItem
     * @brief    ��ȡ�ӽڵ�    
     * @param    HSTREEITEM hItem -- ���ڵ�
     * @param    BOOL bFirst -- �ڼ����ӽڵ�
     * @return   ����HSTREEITEM
     * 
     * Describe  ��ȡ�ӽڵ�  
     */
    HSTREEITEM GetChildItem(HSTREEITEM hItem,BOOL bFirst =TRUE);
    /**
     * STreeBox::GetParentItem
     * @brief    ��ȡ���ڵ�    
     * @param    HSTREEITEM hItem -- �ӽڵ�
     * @return   ����HSTREEITEM
     * 
     * Describe  ��ȡ���ڵ� 
     */
    HSTREEITEM GetParentItem(HSTREEITEM hItem);

    /**
     * STreeBox::OnDestroy
     * @brief    ����    
     * 
     * Describe  ��ȡ���ڵ� 
     */
    void OnDestroy();

    /**
     * STreeBox::Expand
     * @brief    չ��    
     * @param    HSTREEITEM hItem -- �ڵ�
     * @param    UINT nCode -- 
     * @return   ����BOOL
     * 
     * Describe  չ��
     */
    BOOL Expand(HSTREEITEM hItem , UINT nCode);

    /**
     * STreeBox::EnsureVisible
     * @brief    ��ʾĳ�ڵ� 
     * @param    HSTREEITEM hItem -- �ڵ�
     * 
     * Describe  ��ʾĳ�ڵ� 
     */
    BOOL EnsureVisible(HSTREEITEM hItem);

    /**
     * STreeBox::HitTest
     * @brief    ��ȡ�ڵ�
     * @param    HSTREEITEM hItem -- �ڵ�
     * 
     * Describe  ���ĳ�ڵ� ���ؽڵ���Ϣ
     */
    HSTREEITEM HitTest(CPoint &pt);

    /**
     * STreeBox::GetItemPanel
     * @brief    ��ȡ�ڵ��STreeItem����
     * @param    HSTREEITEM hItem -- �ڵ�
     * 
     * Describe  ��ȡ�ڵ�
     */
    STreeItem * GetItemPanel(HSTREEITEM hItem)
    {
        return GetItem(hItem);
    }

    /**
     * STreeBox::GetItemRect
     * @brief    ��ȡ�ڵ��ڴ����е���ʾλ��
     * @param    HSTREEITEM hItem --  Ŀ��ڵ�
     * @return   CRect -- ��ʾλ�ã��������꣩
     * Describe  ����ʾ�򷵻ؿվ���
     */    
    CRect GetItemRect(HSTREEITEM hItem);
protected:
    /**
     * STreeBox::SetChildrenVisible
     * @brief    ���ýڵ���ʾ
     * @param    HSTREEITEM hItem -- �ڵ�
     * @param    BOOL bVisible -- �Ƿ���ʾ
     * 
     * Describe  ���ýڵ���ʾ
     */
    void SetChildrenVisible(HSTREEITEM hItem,BOOL bVisible);
    /**
     * STreeBox::OnNodeFree
     * @brief    �ͷŽڵ�
     * @param    STreeItem * & pItem  -- ���ͷŽڵ�
     * 
     * Describe  �ͷŽڵ�
     */
    virtual void OnNodeFree(STreeItem * & pItem);

    /**
     * STreeBox::CreateChildren
     * @brief    ����tree
     * @param    pugi::xml_node xmlNode -- xml�ļ�
     * 
     * Describe  ����tree
     */
    virtual BOOL CreateChildren(pugi::xml_node xmlNode);
    /**
     * STreeBox::LoadBranch
     * @brief    ���ط�֧�ڵ�
     * @param    HSTREEITEM hParent -- ���ڵ�
     * @param    pugi::xml_node xmlNode -- xml�ļ�
     * 
     * Describe  ���ط�֧�ڵ�
     */
    void LoadBranch(HSTREEITEM hParent,pugi::xml_node xmlNode);

    void OnSize(UINT nType,CSize size);

    /**
     * STreeBox::RedrawItem
     * @brief    ���»���
     * @param    HSTREEITEM hItem -- �ڵ�
     * 
     * Describe  ���»���
     */
    void RedrawItem(HSTREEITEM hItem);

    /**
     * STreeBox::DrawItem
     * @brief    ����
     * @param    IRenderTarget *pRT -- ��ͼ�豸
     * @param    CRect & rc -- λ��
     * @param    HSTREEITEM hItem -- �ڵ�
     * 
     * Describe  ���»���
     */
    virtual void DrawItem(IRenderTarget *pRT, CRect & rc, HSTREEITEM hItem);

    virtual BOOL OnUpdateToolTip(CPoint pt, SwndToolTipInfo & tipInfo);

    /**
     * STreeBox::OnPaint
     * @brief    ����
     * @param    IRenderTarget *pRT -- ��ͼ�豸
     * 
     * Describe  ����
     */
    void OnPaint(IRenderTarget *pRT);

    /**
     * STreeBox::OnLButtonDown
     * @brief    �����������¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
    */
    void OnLButtonDown(UINT nFlags,CPoint pt);
    /**
     * STreeBox::OnLButtonDbClick
     * @brief    ������˫���¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
    */
    void OnLButtonDbClick(UINT nFlags,CPoint pt);
    /**
     * STreeBox::OnLButtonDbClick
     * @brief    ����¼�
     * @param    UINT uMsg  -- ��Ϣ��
     * @param    WPARAM wParam  --
     * @param    LPARAM lParam  -- 
     * @return   ����LRESULT
     *
     * Describe  �˺�������Ϣ��Ӧ����
    */
    LRESULT OnMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

    /**
     * STreeBox::OnMouseMove
     * @brief    ����ƶ��¼�
     * @param    UINT nFlags -- ��־
     * @param    CPoint point -- �������
     *
     * Describe  �˺�������Ϣ��Ӧ����
    */
    void OnMouseMove(UINT nFlags,CPoint pt);

    /**
     * STreeBox::OnMouseLeave
     * @brief    ����뿪�¼�
     *
     * Describe  �˺�������Ϣ��Ӧ����
    */
    void OnMouseLeave();
    /**
     * STreeBox::OnSetFocus
     * @brief    ��ý���
     *
     * Describe  �˺�������Ϣ��Ӧ����
    */
    void OnSetFocus();
    /**
     * STreeBox::OnKillFocus
     * @brief    ʧȥ����
     *
     * Describe  �˺�������Ϣ��Ӧ����
    */
    void OnKillFocus();
    /**
     * STreeBox::OnKeyEvent
     * @brief    �����¼�
     * @param    UINT uMsg  -- ��Ϣ��
     * @param    WPARAM wParam  --
     * @param    LPARAM lParam  -- 
     * @return   ����LRESULT
     *
     * Describe  �˺�������Ϣ��Ӧ����
    */
    LRESULT OnKeyEvent( UINT uMsg,WPARAM wParam,LPARAM lParam );
    /**
     * STreeBox::FireEvent
     * @brief     
     * @param    EventArgs &evt  --  
     *
     * Describe   
    */
    virtual BOOL FireEvent(EventArgs &evt);
    /**
     * STreeBox::OnSetCursor
     * @brief    �������
     * @param    const CPoint &pt  -- λ��
     *
     * Describe  �˺�������Ϣ��Ӧ����
    */
    virtual BOOL OnSetCursor(const CPoint &pt);
    /**
     * STreeBox::OnViewOriginChanged
     * @brief    
     * @param    CPoint ptOld  -- 
     * @param    CPoint ptNew  --
     *
     * Describe  
    */
    virtual void OnViewOriginChanged( CPoint ptOld,CPoint ptNew );

    virtual void OnViewSizeChanged(CSize szOld,CSize szNew);

    /**
     * STreeBox::OnGetDlgCode
     * @brief    ��ȡ������Ϣ��
     * @return   ����UINT
     *
     * Describe  �˺�������Ϣ��Ӧ����
    */
    virtual UINT OnGetDlgCode()
    {
        return SC_WANTALLKEYS;
    }

protected:
    /**
     * STreeBox::IsAncestor
     * @brief    �ж��Ƿ�������
     * @param    HSTREEITEM hItem1  -- �ڵ�1
     * @param    HSTREEITEM hItem2  -- �ڵ�2
     *
     * Describe  �ж��Ƿ�������
    */
    BOOL IsAncestor(HSTREEITEM hItem1,HSTREEITEM hItem2);

    void UpdateSwitchState(HSTREEITEM hItem);

    void UpdateItemWidth(HSTREEITEM hItem,int nWidth);
    
    void SetViewHeight(int nHeight);

    bool OnItemStateChanged(EventArgs *pEvt);
    
    void UpdateAncestorBranchHeight(HSTREEITEM hItem,int nHeightChange);

        /**
     * STreeBox::GetItemShowIndex
     * @brief    ��ȡ����
     * @param    HSTREEITEM hItemObj -- �ڵ�
     * 
     * Describe  ��ȡ����
     */
    int GetItemShowIndex(HSTREEITEM hItemObj);
    
    //����һ��ITEM�ڿؼ�����ʾ��ƫ����
    CPoint GetItemOffsetInView(HSTREEITEM hItem);

    CRect GetItemRectInView(HSTREEITEM hItem);

    void  PaintVisibleItem(IRenderTarget *pRT,IRegion *pRgn,HSTREEITEM hItem,int & yOffset);

    HSTREEITEM _HitTest(HSTREEITEM hItem,int & yOffset,const CPoint & pt );
protected:
    /**
     * STreeBox::OnItemSetCapture
     * @brief    �ж��Ƿ񲶻�
     * @param    SItemPanel *pItem  -- �ڵ�
     * @param    BOOL bCapture  -- �Ƿ񲶻�
     *
     * Describe  �ж��Ƿ񲶻�
    */
    virtual void OnItemSetCapture(SItemPanel *pItem,BOOL bCapture);
    /**
     * STreeBox::OnItemGetRect
     * @brief    
     * @param    SItemPanel *pItem  -- �ڵ�
     * @param    CRect &rcItem  -- λ��
     *
     * Describe  
    */
    virtual BOOL OnItemGetRect(SItemPanel *pItem,CRect &rcItem);

    /**
     * STreeBox::IsItemRedrawDelay
     * @brief    ��ȡ������ʱˢ�±�־
     * @param    ����BOOL
     *
     * Describe 
    */
    virtual BOOL IsItemRedrawDelay(){return m_bItemRedrawDelay;}

    HSTREEITEM    m_hSelItem;  /**< ѡ��item */
    HSTREEITEM    m_hHoverItem; /**< hover״̬item */

    SItemPanel    *m_pCapturedFrame;  /**< ��ǰ������ı��� */

    int  m_nItemHeight;         /**< �߶� */ 
    int  m_nIndent;             /**< ���� */ 
    COLORREF m_crItemBg;        /**< ����ɫ */ 
    COLORREF m_crItemSelBg;     /**< ѡ�б���ɫ */ 
    ISkinObj * m_pItemSkin;     /**< ISkinObj���� */ 
    BOOL m_bItemRedrawDelay;    /**< �����пؼ�ˢ��ʱ��ʱ*/
    pugi::xml_document  m_xmlTemplate;/**< XMLģ��*/

    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"indent", m_nIndent, TRUE)
        ATTR_INT(L"itemHeight", m_nItemHeight, TRUE)
        ATTR_SKIN(L"itemSkin", m_pItemSkin, TRUE)
        ATTR_COLOR(L"colorItemBkgnd",m_crItemBg,FALSE)
        ATTR_COLOR(L"colorItemSelBkgnd",m_crItemSelBg,FALSE)
        ATTR_INT(L"itemRedrawDelay", m_bItemRedrawDelay, TRUE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_PAINT_EX(OnPaint)
        MSG_WM_NCCALCSIZE(OnNcCalcSize)
        MSG_WM_SIZE(OnSize)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_LBUTTONDOWN(OnLButtonDown)
        MSG_WM_LBUTTONDBLCLK(OnLButtonDbClick)
        MSG_WM_MOUSEMOVE(OnMouseMove)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_SETFOCUS_EX(OnSetFocus)
        MSG_WM_KILLFOCUS_EX(OnKillFocus)
        MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST,WM_MOUSELAST,OnMouseEvent)
        MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST,WM_KEYLAST,OnKeyEvent)
        MESSAGE_RANGE_HANDLER_EX(WM_IME_STARTCOMPOSITION,WM_IME_KEYLAST,OnKeyEvent)
        MESSAGE_HANDLER_EX(WM_IME_CHAR,OnKeyEvent)
   SOUI_MSG_MAP_END()
};

}//namespace SOUI