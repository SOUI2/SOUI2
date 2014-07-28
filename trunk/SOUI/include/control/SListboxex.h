/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       SListboxex.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-06
 * 
 * Describe    ��չ�б�� 
 */
#pragma  once
#include "core/SPanel.h"
#include "core/Sitempanel.h"

namespace SOUI
{
/** 
 * @class     SListBox
 * @brief     ��չ�б��
 *
 * Describe   ��չ�б��
 */
class SOUI_EXP SListBoxEx :public SScrollView
    ,public IItemContainer
{
public:

    SOUI_CLASS_NAME(SListBoxEx, L"listboxex")
    
    /**
     * SListBoxEx::SListBox
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    SListBoxEx();

    /**
     * SListBox::~SListBox
     * @brief    ��������
     *
     * Describe  ��������  
     */
    virtual ~SListBoxEx();

    /**
     * SListBoxEx::DeleteAllItems
     * @brief    ɾ������
     * @param    BOOL bUpdate -- �Ƿ����
     *
     * Describe  ɾ������
     */
    void DeleteAllItems(BOOL bUpdate=TRUE);

    /**
     * SListBoxEx::DeleteItem
     * @brief    ɾ��ָ����
     * @param    int iItem -- ����
     *
     * Describe  ɾ��ָ����
     */
    void DeleteItem(int iItem);

    /**
     * SListBoxEx::InsertItem
     * @brief    ��������
     * @param    int iItem -- ����
     * @param    pugi::xml_node xmlNode -- xml�ļ�
     * @param    DWORD dwData  --  ��������
     *
     * Describe  ��ĳ��֮�����
     */
    int InsertItem(int iItem,pugi::xml_node xmlNode,LPARAM dwData=0);

    /**
     * SListBoxEx::InsertItem
     * @brief    ��������
     * @param    int iItem -- ����
     * @param    LPCWSTR pszXml -- xml�ļ�
     * @param    DWORD dwData  --  ��������
     *
     * Describe  ��ĳ��֮�����
     */
    int InsertItem(int iItem,LPCWSTR pszXml,LPARAM dwData=0);
    
    /**
     * SListBoxEx::SetCurSel
     * @brief    ����ѡ����
     * @param    int nIndex -- ��ѡ������
     *
     * Describe  ����ѡ����
     */
    BOOL SetCurSel(int iItem);

    /**
     * SListBoxEx::EnsureVisible
     * @brief    ����ĳ����ʾ
     * @param    int nIndex  -- ����
     *
     * Describe  ����ĳ����ʾ
     */
    void EnsureVisible(int iItem);

    /**
     * SListBoxEx::GetCurSel
     * @brief    ��ȡ��ǰѡ��������
     * @return   ����int
     *
     * Describe  ��ȡ��ǰѡ��������
     */
    int GetCurSel();


    /**
     * SListBoxEx::GetItemPanel
     * @brief    ��ȡָ����ṹ
     * @param    int iItem -- ����
     * @return   ����SWindow
     *
     * Describe  ��ȡָ��������
     */
    SWindow * GetItemPanel(int iItem);

    /**
     * SListBoxEx::GetItemData
     * @brief    ��ȡ��������
     * @param    int nIndex -- ѡ������
     * @return   ����LPARAM
     *
     * Describe  ��ȡ��������
     */
    LPARAM GetItemData(int iItem);

    /**
     * SListBoxEx::SetItemData
     * @brief    ����ѡ�������
     * @param    int nIndex -- ѡ������
     * @param    LPARAM lParam  -- ��������
     * @return   ����BOOL
     *
     * Describe  ����ѡ�������
     */
    void SetItemData(int iItem,LPARAM lParam);

    /**
     * SListBoxEx::SetItemCount
     * @brief    ������Ŀ����
     * @param    int nItems ��Ŀ����
     * @param    LPCTSTR pszXmlTemplate ��ʾʱʹ�õ�XMLģ�壬
     *           Ϊ��ʱʹ��XML�ű���ָ����template�ӽڵ�����
     * @return   ������Ŀ����
     *
     * Describe  ����ѡ�������
     */
    BOOL SetItemCount(int nItems,LPCTSTR pszXmlTemplate=NULL);

    /**
     * SListBoxEx::GetItemCount
     * @brief    ��ȡ��Ŀ����
     * @return   ���� int 
     *
     * Describe  ��ȡ��Ŀ����
     */
    int GetItemCount() ;

    /**
     * SListBoxEx::GetItemHeight
     * @brief    ��ȡ�߶�
     * @return   ����int 
     *
     * Describe  ��ȡ�߶�
     */
    int GetItemHeight()
    {
        return m_nItemHei;
    }

    /**
     * SListBoxEx::RedrawItem
     * @brief    �ػ�ѡ��
     * @param    int iItem  -- ����
     *
     * Describe  �ػ�ѡ��
     */
    void RedrawItem(int iItem);

    /**
     * SListBoxEx::HitTest
     * @brief    ��ȡ��������Ϣ
     * @param    CPoint &pt -- ����
     *
     * Describe  �Զ��޸�pt��λ��Ϊ��Ե�ǰ���ƫ����
     */
    int HitTest(CPoint &pt);

protected:
    /**
     * SListBoxEx::OnItemSetCapture
     * @brief     
     * @param     SItemPanel *pItem
     * @param     BOOL bCapture
     *
     * Describe  
     */    
    virtual void OnItemSetCapture(SItemPanel *pItem,BOOL bCapture);

    /**
     * SListBoxEx::OnItemGetRect
     * @brief     
     * @param     SItemPanel *pItem
     * @param     CRect &rcItem
     *
     * Describe   
     */
    virtual BOOL OnItemGetRect(SItemPanel *pItem,CRect &rcItem);

    /**
     * SListBoxEx::IsItemRedrawDelay
     * @brief    
     *
     * Describe  
     */
    virtual BOOL IsItemRedrawDelay(){return m_bItemRedrawDelay;}

protected:

    /**
     * SListBoxEx::UpdatePanelsIndex
     * @brief    ��������
     * @param    UINT nFirst
     * @param    UINT nLast
     *
     * Describe  ��������
     */   
    void UpdatePanelsIndex(UINT nFirst=0,UINT nLast=-1);

    /**
     * SListBoxEx::GetItemRect
     * @brief    ��ȡָ��λ��
     * @param    int iItem -- ����
     * @return   ����CRect 
     *
     * Describe  ��������
     */
    CRect    GetItemRect(int iItem);

    /**
     * SListBoxEx::GetScrollLineSize
     * @brief    ��ȡ������С
     * @param    BOOL bVertical -- �Ƿ��Ǵ�ֱ
     *
     * Describe  ��ȡ������С
     */
    virtual int GetScrollLineSize(BOOL bVertical);

    /**
     * SListBoxEx::OnPaint
     * @brief    ����
     * @param    IRenderTarget *pRT -- �����豸
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnPaint(IRenderTarget * pRT);

    /**
     * SListBoxEx::OnSize
     * @brief    ��Ϣ��Ӧ����
     * @param    UINT nType --
     * @param    CSize size -- 
     *
     * Describe  ��ȡĳ�������  
     */
    void OnSize(UINT nType, CSize size);

    /**
     * SListBoxEx::OnDrawItem
     * @brief    ����
     * @param    IRenderTarget *pRT  -- �����豸
     * @param    CRect & rc -- λ��
     * @param    int iItem -- ����
     *
     * Describe  ����
     */
    virtual void OnDrawItem(IRenderTarget *pRT, CRect & rc, int iItem);

    /**
     * SListBoxEx::CreateChildren
     * @brief    ��������
     * @param    pugi::xml_node xmlNode -- xml�ļ�
     *
     * Describe  ͨ������xml�ļ�����
     */
    virtual BOOL CreateChildren(pugi::xml_node xmlNode);

    /**
     * SListBoxEx::OnUpdateToolTip
     * @brief    ������ʾ��
     * @param    SWND hCurTipHost -- 
     * @param    SWND &hNewTipHost -- 
     * @param    CRect &rcTip --
     * @param    SStringT &strTip -- 
     *
     * Describe  ������ʾ��
     */
    virtual BOOL OnUpdateToolTip(SWND hCurTipHost,SWND &hNewTipHost,CRect &rcTip,SStringT &strTip);

    /**
     * SListBoxEx::NotifySelChange
     * @brief    �޸�ѡ����
     * @param    int nOldSel -- ��ѡ����
     * @param    int nNewSel -- ��ѡ����
     *
     * Describe  �޸�ѡ����
     */
    void NotifySelChange(int nOldSel,int nNewSel);

    /**
     * SListBoxEx::OnMouseEvent
     * @brief    �Զ�����Ϣ��Ӧ����
     * @param    UINT uMsg --
     * @param    WPARAM wParam -- 
     * @param    LPARAM lParam --
     * @return   ����LRESULT
     *
     * Describe  �Զ�����Ϣ��Ӧ����
     */
    LRESULT OnMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

    /**
     * SListBoxEx::OnKeyEvent
     * @brief    �Զ�����Ϣ��Ӧ����
     * @param    UINT uMsg --
     * @param    WPARAM wParam -- 
     * @param    LPARAM lParam --
     * @return   ����LRESULT
     * 
     * Describe  �Զ�����Ϣ��Ӧ����
     */
    LRESULT OnKeyEvent( UINT uMsg,WPARAM wParam,LPARAM lParam );

    /**
     * SListBoxEx::OnMouseLeave
     * @brief    �Զ�����Ϣ��Ӧ����
     * 
     * Describe  �Զ�����Ϣ��Ӧ����
     */
    void OnMouseLeave();

    /**
     * SListBoxEx::OnMouseWheel
     * @brief    �������¼�
     * @param    UINT nFlags -- ��־
     * @param    short zDelta -- ���ֹ����ľ���
     * @param    CPoint pt -- ����
     * @return   ����BOOL
     * 
     * Describe  �������¼�
     */
    BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

    /**
     * SListBoxEx::OnKeyDown
     * @brief    ��������
     * @param    TCHAR nChar -- ����ֵ
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );

    /**
     * SListBoxEx::OnChar
     * @brief    ��������
     * @param    TCHAR nChar -- ����ֵ
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    /**
     * SListBoxEx::OnGetDlgCode
     * @brief    ��ȡ������Ϣ��
     * @param    ����UINT
     *
     * Describe  ��ȡ������Ϣ��
     */
    UINT OnGetDlgCode();

    /**
     * SListBoxEx::OnSetCursor
     * @brief    �������λ��
     * @param    ����BOOL
     *
     * Describe  �������λ��
     */
    virtual BOOL OnSetCursor(const CPoint &pt);

    /**
     * SListBoxEx::OnViewOriginChanged
     * @brief    
     * @param    CPoint ptOld  --
     * @param    CPoint ptNew  -- 
     *
     * Describe  
     */
    virtual void OnViewOriginChanged(CPoint ptOld,CPoint ptNew);

    /**
     * SListBoxEx::OnDestroy
     * @brief    ����
     *
     * Describe  ����
     */
    void OnDestroy();

    /**
     * SListBoxEx::OnSetFocus
     * @brief    ��ý���
     *
     * Describe  ��ý���
     */
    void OnSetFocus();

    /**
     * SListBoxEx::OnKillFocus
     * @brief    ʧȥ����
     *
     * Describe  ʧȥ����
     */
    void OnKillFocus();

    /**
     * SListBoxEx::OnNcCalcSize
     * @brief    ����ǿͻ�����С
     * @param    BOOL bCalcValidRects -- ��С
     * @param    LPARAM lParam -- ���Ӳ���
     * Describe  ����ǿͻ�����С
     */
    LRESULT OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam);

    /**
     * SListBoxEx::Relayout
     * @brief    ���²���
     *
     * Describe  ���²���
     */
    void Relayout();
protected:
    SArray<SItemPanel *> m_arrItems;  /**< ������Ŀ������ */
    int        m_nItemHei;     /**< �߶�          */
    int        m_iSelItem;     /**< ѡ����Ŀ      */
    int        m_iHoverItem;   /**< Hover״̬��Ŀ */
    int        m_iScrollSpeed; /**< �����ٶ�      */

    pugi::xml_document m_xmlTempl;     /**< �б�ģ��XML */
    SItemPanel   *m_pCapturedFrame;    /**<  */
    ISkinObj     *m_pItemSkin;         /**<  */
    COLORREF     m_crItemBg;           /**< ����ɫ */
    COLORREF     m_crItemSelBg;        /**< ѡ�б���ɫ */
    BOOL       m_bVirtual;             /**< �Ƿ�ֱ */
    BOOL       m_bItemRedrawDelay;     /**< �����ػ�ʱ���� */       
public:
    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"scrollspeed", m_iScrollSpeed, FALSE)
        ATTR_INT(L"itemheight", m_nItemHei, FALSE)
        ATTR_INT(L"virtual", m_bVirtual, TRUE)
        ATTR_SKIN(L"itemskin", m_pItemSkin, TRUE)
        ATTR_COLOR(L"critembg",m_crItemBg,FALSE)
        ATTR_COLOR(L"critemselbg",m_crItemSelBg,FALSE)
        ATTR_INT(L"itemredrawdelay", m_bItemRedrawDelay, TRUE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_MOUSEWHEEL(OnMouseWheel)
        MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST,WM_MOUSELAST,OnMouseEvent)
        MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST,WM_KEYLAST,OnKeyEvent)
        MESSAGE_RANGE_HANDLER_EX(WM_IME_STARTCOMPOSITION,WM_IME_KEYLAST,OnKeyEvent)
        MESSAGE_HANDLER_EX(WM_IME_CHAR,OnKeyEvent)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_PAINT_EX(OnPaint)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_KEYDOWN(OnKeyDown)
        MSG_WM_CHAR(OnChar)
        MSG_WM_SIZE(OnSize)
        MSG_WM_SETFOCUS_EX(OnSetFocus)
        MSG_WM_KILLFOCUS_EX(OnKillFocus)
        MSG_WM_NCCALCSIZE(OnNcCalcSize)
    SOUI_MSG_MAP_END()
};

}//namespace SOUI