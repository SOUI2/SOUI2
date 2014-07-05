//////////////////////////////////////////////////////////////////////////
//  Class Name: SListBoxEx
//////////////////////////////////////////////////////////////////////////

#pragma  once

#include "core/SPanel.h"
#include "core/Sitempanel.h"

namespace SOUI
{

class SOUI_EXP SListBoxEx :public SScrollView
    ,public IItemContainer
{
public:

    SOUI_CLASS_NAME(SListBoxEx, L"listboxex")

    SListBoxEx();

    virtual ~SListBoxEx();


    void DeleteAllItems(BOOL bUpdate=TRUE);

    void DeleteItem(int iItem);

    int InsertItem(int iItem,pugi::xml_node xmlNode,DWORD dwData=0);

    int InsertItem(int iItem,LPCWSTR pszXml,DWORD dwData=0);

    BOOL SetCurSel(int iItem);

    void EnsureVisible(int iItem);

    int GetCurSel();

    int GetItemObjIndex(SWindow *pItemObj);

    SWindow * GetItemPanel(int iItem);

    LPARAM GetItemData(int iItem);

    void SetItemData(int iItem,LPARAM lParam);

    //************************************
    // Method:    SetItemCount
    // FullName:  SOUI::SListBoxEx::SetItemCount
    // Access:    public 
    // Returns:   BOOL
    // Qualifier:
    // Parameter: int nItems ��Ŀ����
    // Parameter: LPCTSTR pszXmlTemplate ��ʾʱʹ�õ�XMLģ�壬Ϊ��ʱʹ��XML�ű���ָ����template�ӽڵ�����
    //************************************
    BOOL SetItemCount(int nItems,LPCTSTR pszXmlTemplate=NULL);

    int GetItemCount() ;

    int GetItemHeight()
    {
        return m_nItemHei;
    }

    void RedrawItem(int iItem);

    //�Զ��޸�pt��λ��Ϊ��Ե�ǰ���ƫ����
    int HitTest(CPoint &pt);

protected:
    virtual void OnItemSetCapture(SItemPanel *pItem,BOOL bCapture);
    virtual BOOL OnItemGetRect(SItemPanel *pItem,CRect &rcItem);
    virtual BOOL IsItemRedrawDelay(){return m_bItemRedrawDelay;}
protected:
    void UpdatePanelsIndex(UINT nFirst=0,UINT nLast=-1);

    CRect    GetItemRect(int iItem);


    virtual int GetScrollLineSize(BOOL bVertical);

    void OnPaint(IRenderTarget * pRT);

    void OnSize(UINT nType, CSize size);

    virtual void OnDrawItem(IRenderTarget *pRT, CRect & rc, int iItem);

    virtual BOOL CreateChildren(pugi::xml_node xmlNode);
    // Get tooltip Info
    virtual BOOL OnUpdateToolTip(SWND hCurTipHost,SWND &hNewTipHost,CRect &rcTip,SStringT &strTip);

    void NotifySelChange(int nOldSel,int nNewSel);

    LRESULT OnMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

    LRESULT OnKeyEvent( UINT uMsg,WPARAM wParam,LPARAM lParam );

    void OnMouseLeave();

    BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

    void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );

    void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    UINT OnGetDlgCode();

    virtual BOOL OnSetCursor(const CPoint &pt);

    virtual void OnViewOriginChanged(CPoint ptOld,CPoint ptNew);

    void OnDestroy();

    void OnSetFocus();

    void OnKillFocus();

    LRESULT OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam);

    void Relayout();
protected:
    SArray<SItemPanel *> m_arrItems;

    int        m_iSelItem;
    int        m_iHoverItem;
    int        m_iScrollSpeed;

    pugi::xml_document m_xmlTempl;        ////�б�ģ��XML
    SItemPanel    *    m_pCapturedFrame;
    ISkinObj * m_pItemSkin;
    COLORREF m_crItemBg,m_crItemSelBg;
    int        m_nItemHei;
    BOOL    m_bVirtual;
    BOOL    m_bItemRedrawDelay;            //�����ػ�ʱ����
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