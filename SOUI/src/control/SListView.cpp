#include "souistd.h"
#include "control/SListView.h"

namespace SOUI
{
    class SListViewItemLocatorFix : public TObjRefImpl<IListViewItemLocator>
    {
    public:
        SListViewItemLocatorFix(int nItemHei):m_nItemHeight(nItemHei){}
        virtual bool IsFixHeight() const 
        {
            return true;
        }

        virtual int GetItemHeight(IAdapter *adapter,int iItem){
            return m_nItemHeight;
        }
        virtual int GetTotalHeight(IAdapter *adapter)
        {
            if(!adapter) return 0;
            return m_nItemHeight * adapter->getCount();
        }
        virtual int Item2Position(IAdapter *adapter,int iItem)
        {
            return iItem * m_nItemHeight;
        }
        
        virtual int Position2Item(IAdapter *adapter,int position,bool bTop)
        {
            if(!adapter) return -1;
            int nRet = (position+(bTop?0:(m_nItemHeight-1)))/m_nItemHeight;
            
            if(nRet<0) nRet =0;
            if(nRet>adapter->getCount()) nRet = adapter->getCount();
            return nRet;
        }
        
        virtual void SetItemHeight(int iItem,int nHeight){}
    protected:
        int m_nItemHeight;
    };
    
    class SListViewDataSetObserver : public TObjRefImpl<IDataSetObserver>
    {
    public:
        SListViewDataSetObserver(SListView *pView):m_pOwner(pView)
        {
        }
        virtual void onChanged();
        virtual void onInvalidated();

    protected:
        SListView * m_pOwner;
    };
    
    //////////////////////////////////////////////////////////////////////////
    void SListViewDataSetObserver::onChanged()
    {
        m_pOwner->onDataSetChanged();
    }

    void SListViewDataSetObserver::onInvalidated()
    {
        m_pOwner->onDataSetInvalidated();
    }

    //////////////////////////////////////////////////////////////////////////
    SListView::SListView()
    :m_iSelItem(-1)
    ,m_pHoverItem(NULL)
    ,m_itemCapture(NULL)
    {
        m_bFocusable = TRUE;
        m_observer.Attach(new SListViewDataSetObserver(this));
        m_lvItemLocator.Attach(new SListViewItemLocatorFix(50));
    }

    SListView::~SListView()
    {
        m_observer=NULL;
        m_lvItemLocator=NULL;
    }

    void SListView::SetAdapter(IAdapter * adapter)
    {
        if(m_adapter)
        {
            m_adapter->unregisterDataSetObserver(m_observer);
            
            //free all itemPanels in recycle
            for(size_t i=0;i<m_itemRecycle.GetCount();i++)
            {
                SList<SItemPanel*> *lstItemPanels = m_itemRecycle.GetAt(i);
                SPOSITION pos = lstItemPanels->GetHeadPosition();
                while(pos)
                {
                    SItemPanel * pItemPanel = lstItemPanels->GetNext(pos);
                    pItemPanel->DestroyWindow();
                }
                delete lstItemPanels;
            }
            m_itemRecycle.RemoveAll();
            
            //free all visible itemPanels
            SPOSITION pos=m_lstItems.GetHeadPosition();
            while(pos)
            {
                ItemInfo ii = m_lstItems.GetNext(pos);
                ii.pItem->DestroyWindow();
            }
            m_lstItems.RemoveAll();
        }
        
        m_adapter = adapter;
        if(m_adapter) 
        {
            m_adapter->registerDataSetObserver(m_observer);
            for(int i=0;i<m_adapter->getViewTypeCount();i++)
            {
                m_itemRecycle.Add(new SList<SItemPanel*>());
            }
            onDataSetChanged();
        }
    }
    
    void SListView::UpdateScrollBar()
    {
        CRect rcClient=SWindow::GetClientRect();
        CSize size = rcClient.Size();
        CSize szView;
        szView.cx = rcClient.Width();
        szView.cy = m_lvItemLocator->GetTotalHeight(m_adapter);

        //  关闭滚动条
        m_wBarVisible = SSB_NULL;

        if (size.cy<szView.cy )
        {
            //  需要纵向滚动条
            m_wBarVisible |= SSB_VERT;
            m_siVer.nMin  = 0;
            m_siVer.nMax  = szView.cy-1;
            m_siVer.nPage = size.cy;
            m_siVer.nPos = min(m_siVer.nPos,m_siVer.nMax-m_siVer.nPage);
        }
        else
        {
            //  不需要纵向滚动条
            m_siVer.nPage = size.cy;
            m_siVer.nMin  = 0;
            m_siVer.nMax  = size.cy-1;
            m_siVer.nPos  = 0;
        }

        SetScrollPos(TRUE, m_siVer.nPos, FALSE);

        //  重新计算客户区及非客户区
        SSendMessage(WM_NCCALCSIZE);

        InvalidateRect(NULL);
    }

    void SListView::onDataSetChanged()
    {
        UpdateScrollBar();

        int iFirstVisible = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos,true);
        int iLastVisible = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos + m_siVer.nPage,false);
        if(m_iSelItem!=-1 && m_iSelItem>=iFirstVisible && m_iSelItem < iLastVisible)
        {
            SPOSITION pos = m_lstItems.GetHeadPosition();
            while(pos)
            {
                ItemInfo ii = m_lstItems.GetNext(pos);
                if(ii.pItem->GetItemIndex()==m_iSelItem)
                {
                    ii.pItem->ModifyItemState(0,WndState_Check);
                    break;
                }
            }
        }
        if(m_pHoverItem)
        {
            m_pHoverItem->DoFrameEvent(WM_MOUSELEAVE,0,0);
            m_pHoverItem=NULL;
        }
        
        SPOSITION pos = m_lstItems.GetHeadPosition();
        while(pos)
        {
            ItemInfo ii = m_lstItems.GetNext(pos);
            m_itemRecycle[ii.nType]->AddTail(ii.pItem);
        }
        m_lstItems.RemoveAll();
        
        AddVisibleItems(iFirstVisible,iLastVisible,true);
    }

    void SListView::onDataSetInvalidated()
    {
        //todo:
        onDataSetChanged();
    }

    void SListView::OnPaint(IRenderTarget *pRT)
    {
        SPainter duiDC;
        BeforePaint(pRT,duiDC);

        CRect rcClient;
        GetClientRect(&rcClient);
        pRT->PushClipRect(&rcClient,RGN_AND);

        CRect rcClip,rcInter;
        pRT->GetClipBox(&rcClip);

        int iFirst = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos,true);
        int nOffset = m_lvItemLocator->Item2Position(m_adapter,iFirst)-m_siVer.nPos;
        
        CRect rcItem(rcClient);
        rcItem.bottom = rcItem.top + nOffset;
        
        SPOSITION pos= m_lstItems.GetHeadPosition();
        int i=0;
        for(;pos;i++)
        {
            ItemInfo ii = m_lstItems.GetNext(pos);
            rcItem.top=rcItem.bottom;
            rcItem.bottom += ii.pItem->GetWindowRect().Height();
            rcInter.IntersectRect(&rcClip,&rcItem);
            if(!rcInter.IsRectEmpty())
                ii.pItem->Draw(pRT,rcItem);
        }
        pRT->PopClip();
        AfterPaint(pRT,duiDC);
    }

    BOOL SListView::OnScroll(BOOL bVertical,UINT uCode,int nPos)
    {
        CRect rgnOld(0,0,1,0);
        rgnOld.top = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos,true);
        rgnOld.bottom = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos + m_siVer.nPage,false);
        
        __super::OnScroll(bVertical, uCode, nPos);
        CRect rgnNew(0,0,1,0);
        rgnNew.top = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos,true);
        rgnNew.bottom = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos + m_siVer.nPage,false);
        
        UpdateVisibleItems(rgnOld.top,rgnOld.bottom,rgnNew.top,rgnNew.bottom);
        
        //加速滚动时UI的刷新
        static DWORD dwTime1=0;
        DWORD dwTime=GetTickCount();
        if(dwTime-dwTime1>50)
        {
            UpdateWindow();
            dwTime1=dwTime;
        }

        return TRUE;
    }

    void SListView::RemoveVisibleItems(int nItems,bool bHeader)
    {
        SASSERT(nItems<=m_lstItems.GetCount());
        if(bHeader)        
        {//hide head items
            for(int i=0;i<nItems;i++)
            {
                ItemInfo ii=m_lstItems.RemoveHead();
                if(ii.pItem == m_pHoverItem)
                {
                    m_pHoverItem->SSendMessage(WM_MOUSELEAVE);
                    m_pHoverItem=NULL;
                }
                if(ii.pItem->GetItemIndex() == m_iSelItem)
                {
                    ii.pItem->ModifyItemState(0,WndState_Check);
                    ii.pItem->GetFocusManager()->SetFocusedHwnd(0);
                }
                m_itemRecycle[ii.nType]->AddTail(ii.pItem);
            }
        }else
        {//hide tail items;
            for(int i=0;i<nItems;i++)
            {
                ItemInfo ii = m_lstItems.RemoveTail();
                if(ii.pItem == m_pHoverItem)
                {
                    m_pHoverItem->SSendMessage(WM_MOUSELEAVE);
                    m_pHoverItem=NULL;
                }
                if(ii.pItem->GetItemIndex() == m_iSelItem)
                {
                    ii.pItem->ModifyItemState(0,WndState_Check);
                    ii.pItem->GetFocusManager()->SetFocusedHwnd(0);
                }

                m_itemRecycle[ii.nType]->AddTail(ii.pItem);
            }
        }
    }

    void SListView::AddVisibleItems(int iItem1,int iItem2,bool bHeader)
    {
        SASSERT(iItem2 > iItem1);
        //将先增加的可见项保存到临时列表中
        SList<ItemInfo> lstItems;
        for(int i=iItem1;i<iItem2;i++)
        {
            int nItemType = m_adapter->getItemViewType(i);
            SList<SItemPanel *> *lstRecycle = m_itemRecycle.GetAt(nItemType);

            SItemPanel * pItemPanel = NULL;
            if(lstRecycle->IsEmpty())
            {//创建一个新的列表项
                pItemPanel = new SItemPanel(this,pugi::xml_node(),this);
            }else
            {
                pItemPanel = lstRecycle->RemoveHead();
            }
            CRect rcItem = GetClientRect();
            rcItem.MoveToXY(0,0);
            rcItem.bottom=m_lvItemLocator->GetItemHeight(m_adapter,i);
            pItemPanel->Move(rcItem);
            pItemPanel->SetItemIndex(i);

            SWindow *pView = pItemPanel->GetWindow(GSW_FIRSTCHILD);
            pView=m_adapter->getView(i,pView,pItemPanel);
            pItemPanel->UpdateChildrenPosition();
            if(i == m_iSelItem)
            {
                pItemPanel->ModifyItemState(WndState_Check,0);
            }
            /*
            if(!m_lvItemLocator->IsFixHeight())
            {
                int nHei=0;
                m_lvItemLocator->SetItemHeight(i,nHei);//防止死循环
            }
            */
            ItemInfo ii;
            ii.nType = nItemType;
            ii.pItem = pItemPanel;
            lstItems.AddTail(ii);
        }
        
        //从临时列表中获取数据连接到显示列表中
        if(bHeader)
        {
            SPOSITION pos=lstItems.GetTailPosition();
            while(pos)
            {
                ItemInfo ii=lstItems.GetPrev(pos);
                m_lstItems.AddHead(ii);
            }
        }else
        {
            SPOSITION pos=lstItems.GetHeadPosition();
            while(pos)
            {
                ItemInfo ii=lstItems.GetNext(pos);
                m_lstItems.AddTail(ii);
            }
        }
    }

    void SListView::UpdateVisibleItems(int minOld,int maxOld,int minNew,int maxNew)
    {
        CRect rcOld(0,minOld,1,maxOld);
        CRect rcNew(0,minNew,1,maxNew);
        
        CRect rgnHide;
        rgnHide.SubtractRect(rcOld,rcNew);
        if(!rgnHide.IsRectEmpty())
        {
            RemoveVisibleItems(rgnHide.bottom-rgnHide.top,rgnHide.top==minOld);
        }
        
        CRect rgnShow;
        rgnShow.SubtractRect(rcNew,rcOld);
        if(!rgnShow.IsRectEmpty())
        {
            AddVisibleItems(rgnShow.top,rgnShow.bottom,rgnShow.bottom == minOld);
        }

    }

    void SListView::OnSize(UINT nType, CSize size)
    {
        CRect rgnOld(0,0,1,0);
        rgnOld.top = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos,true);
        rgnOld.bottom = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos + m_siVer.nPage,false);

        __super::OnSize(nType,size);
        UpdateScrollBar();
        //update item window
        CRect rcClient=GetClientRect();
        SPOSITION pos = m_lstItems.GetHeadPosition();
        while(pos)
        {
            ItemInfo ii = m_lstItems.GetNext(pos);
            int idx = (int)ii.pItem->GetItemIndex();
            int nHei = m_lvItemLocator->GetItemHeight(m_adapter,idx);
            CRect rcItem(0,0,rcClient.Width(),nHei);
            ii.pItem->Move(rcItem);
        }
        
        CRect rgnNew(0,0,1,0);
        rgnNew.top = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos,true);
        rgnNew.bottom = m_lvItemLocator->Position2Item(m_adapter,m_siVer.nPos + m_siVer.nPage,false);

        UpdateVisibleItems(rgnOld.top,rgnOld.bottom,rgnNew.top,rgnNew.bottom);
    }

    //////////////////////////////////////////////////////////////////////////
    void SListView::OnItemRequestRelayout(SItemPanel *pItem)
    {
        pItem->UpdateChildrenPosition();
    }

    BOOL SListView::IsItemRedrawDelay()
    {
        return TRUE;
    }

    BOOL SListView::OnItemGetRect(SItemPanel *pItem,CRect &rcItem)
    {
        int iPosition = (int)pItem->GetItemIndex();
        int nOffset = m_lvItemLocator->Item2Position(m_adapter,iPosition)-m_siVer.nPos;
        rcItem = GetClientRect();
        rcItem.top += nOffset;
        rcItem.bottom = rcItem.top + m_lvItemLocator->GetItemHeight(m_adapter,iPosition);
        return TRUE;
    }

    void SListView::OnItemSetCapture(SItemPanel *pItem,BOOL bCapture)
    {
        if(bCapture)
        {
            GetContainer()->OnSetSwndCapture(m_swnd);
            m_itemCapture=pItem;
        }else
        {
            GetContainer()->OnReleaseSwndCapture();
            m_itemCapture=NULL;
        }
    }

    void SListView::RedrawItem(SItemPanel *pItem)
    {
        pItem->InvalidateRect(NULL);
    }

    SItemPanel * SListView::HitTest(CPoint & pt)
    {
        SPOSITION pos = m_lstItems.GetHeadPosition();
        while(pos)
        {
            ItemInfo ii = m_lstItems.GetNext(pos);
            CRect rcItem = ii.pItem->GetItemRect();
            if(rcItem.PtInRect(pt)) 
            {
                pt-=rcItem.TopLeft();
                return ii.pItem;
            }
        }
        return NULL;
    }
    
    LRESULT SListView::OnMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
    {
        LRESULT lRet=0;
        CPoint pt(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));

        if(m_itemCapture)
        {
            CRect rcItem=m_itemCapture->GetItemRect();
            pt.Offset(-rcItem.TopLeft());
            lRet = m_itemCapture->DoFrameEvent(uMsg,wParam,MAKELPARAM(pt.x,pt.y));
        }
        else
        {
            if(m_bFocusable && (uMsg==WM_LBUTTONDOWN || uMsg== WM_RBUTTONDOWN || uMsg==WM_LBUTTONDBLCLK))
                SetFocus();

            SItemPanel * pHover=HitTest(pt);
            if(pHover!=m_pHoverItem)
            {
                SItemPanel * nOldHover=m_pHoverItem;
                m_pHoverItem=pHover;
                if(nOldHover)
                {
                    nOldHover->DoFrameEvent(WM_MOUSELEAVE,0,0);
                    RedrawItem(nOldHover);
                }
                if(m_pHoverItem)
                {
                    m_pHoverItem->DoFrameEvent(WM_MOUSEHOVER,wParam,MAKELPARAM(pt.x,pt.y));
                    RedrawItem(m_pHoverItem);
                }
            }
            if(uMsg==WM_LBUTTONDOWN )
            {//选择一个新行的时候原有行失去焦点
                int nSelNew = m_pHoverItem?m_pHoverItem->GetItemIndex():-1;
                if(m_iSelItem!=-1 && m_iSelItem != nSelNew)
                {
                    SPOSITION pos = m_lstItems.GetHeadPosition();
                    while(pos)
                    {
                        ItemInfo ii = m_lstItems.GetNext(pos);
                        if(ii.pItem->GetItemIndex() == m_iSelItem)
                        {
                            ii.pItem->ModifyItemState(0,WndState_Check);
                            ii.pItem->GetFocusManager()->SetFocusedHwnd(0);
                            RedrawItem(ii.pItem);
                            break;
                        }
                    }
                }
                m_iSelItem = nSelNew;
                if(m_iSelItem!=-1)
                {
                    m_pHoverItem->ModifyItemState(WndState_Check,0);
                    RedrawItem(m_pHoverItem);
                }
            }
            if(m_pHoverItem)
            {
                m_pHoverItem->DoFrameEvent(uMsg,wParam,MAKELPARAM(pt.x,pt.y));
            }
        }
        return 0;
    }

    LRESULT SListView::OnKeyEvent(UINT uMsg,WPARAM wParam,LPARAM lParam)
    {
        return 0;
    }

    void SListView::OnMouseLeave()
    {
        if(m_pHoverItem)
        {
            m_pHoverItem->DoFrameEvent(WM_MOUSELEAVE,0,0);
            m_pHoverItem = NULL;
        }

    }

    BOOL SListView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
    {
        return __super::OnMouseWheel(nFlags, zDelta, pt);
        
        //return FALSE;
    }


}