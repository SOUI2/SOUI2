#pragma once

#include "core/Swnd.h"
#include "core/SItemPanel.h"
#include "interface/Adapter-i.h"
#include "interface/TvItemLocator-i.h"

namespace SOUI
{
	class SOUI_EXP STreeView : public SPanel, protected IItemContainer
	{
		SOUI_CLASS_NAME(STreeView, L"treeview")
		
	public:
		STreeView();
		~STreeView();
			
		BOOL SetAdapter(ITvAdapter * adapter);
		ITvAdapter * GetAdapter () { return m_adapter; }
		void SetItemLocator(ITreeViewItemLocator *pItemLocator)
		{
		    m_tvItemLocator = pItemLocator;
		}
		
		ITreeViewItemLocator * GetItemLocator() const
		{
		    return m_tvItemLocator;
		}
		
		void onBranchChanged(HTREEITEM hBranch);
		void onBranchInvalidated(HTREEITEM hBranch);
        void onBranchExpandedChanged(HTREEITEM hBranch,BOOL bExpandedOld,BOOL bExpandedNew);
        
        void SetSel(HTREEITEM hItem,BOOL bNotify=FALSE);
        HTREEITEM  GetSel()const{return m_hSelected;}
        
    protected:
        bool OnItemClick(EventArgs *pEvt);
        
    protected:
		void OnPaint(IRenderTarget * pRT);
		void OnSize(UINT nType, CSize size);
		void OnDestroy();
 		void OnKeyDown(TCHAR nChar, UINT nRepCnt, UINT nFlags);//ʵ�ּ���ѡ��
		LRESULT OnKeyEvent( UINT uMsg,WPARAM wParam,LPARAM lParam );
		
		void OnMouseLeave();
		BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
		LRESULT OnMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

		void OnKillFocus();
		void OnSetFocus();

		SOUI_MSG_MAP_BEGIN()
			MSG_WM_PAINT_EX(OnPaint)
			MSG_WM_SIZE(OnSize)
			MSG_WM_DESTROY(OnDestroy)
			MSG_WM_KEYDOWN(OnKeyDown)
			MSG_WM_KILLFOCUS_EX(OnKillFocus)
			MSG_WM_SETFOCUS_EX(OnSetFocus)
			MSG_WM_MOUSEWHEEL(OnMouseWheel)
			MSG_WM_MOUSELEAVE(OnMouseLeave)
			MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST,WM_MOUSELAST,OnMouseEvent)
 			MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST,WM_KEYLAST,OnKeyEvent)
 			MESSAGE_RANGE_HANDLER_EX(WM_IME_STARTCOMPOSITION,WM_IME_KEYLAST,OnKeyEvent)
		SOUI_MSG_MAP_END()
	protected:
		virtual BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos);
		virtual int  GetScrollLineSize(BOOL bVertical);
		virtual BOOL CreateChildren(pugi::xml_node xmlNode);
	
		virtual void OnItemSetCapture(SItemPanel *pItem,BOOL bCapture); //����or�ͷ���겶��
		virtual BOOL OnItemGetRect(SItemPanel *pItem,CRect &rcItem);    //��ñ������ʾλ��
		virtual BOOL IsItemRedrawDelay();                               //ָʾ����ĸ��·�ʽ
		virtual void OnItemRequestRelayout(SItemPanel *pItem);          //�б����������²���
	protected:

		void UpdateScrollBar();
		void UpdateVisibleItems();


		void RedrawItem(SItemPanel *pItem);
		void _SetSel(int iItem,BOOL bNotify, SWND hHitWnd);
		SItemPanel * GetItemPanel(HTREEITEM hItem);
		SItemPanel * HitTest(CPoint & pt);

		void EnsureVisible(HTREEITEM hItem);

	protected:
		CAutoRefPtr<ITvAdapter>		m_adapter;
		CAutoRefPtr<ITvDataSetObserver>   m_observer;
		CAutoRefPtr<ITreeViewItemLocator> m_tvItemLocator;
        
        struct ItemInfo
        {
            SItemPanel* pItem;
            int         nType;
        };
        SArray<SList<SItemPanel*> *>    m_itemRecycle;//item����վ,ÿһ����ʽ�ڻ���վ�б���һ���б��Ա��ظ�����
		SList<ItemInfo> m_visible_items; //�ɼ�Ԫ��
		
		typedef SMap<HTREEITEM,ItemInfo> VISIBLEITEMSMAP;
		VISIBLEITEMSMAP * m_pVisibleMap;
		
		pugi::xml_document m_xmlTemplate;

		SItemPanel * m_itemCapture;
		SItemPanel * m_pHoverItem;
        
        HTREEITEM    m_hSelected;               /**< ��ǰѡ���� */ 
        
		int				m_nIndent;             /**< ���� */ 

		SOUI_ATTRS_BEGIN()
			ATTR_INT(L"indent", m_nIndent, TRUE)
		SOUI_ATTRS_END()

	};
}