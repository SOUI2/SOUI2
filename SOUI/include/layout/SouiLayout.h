#pragma once
#include "interface/slayout-i.h"
#include <sobject/sobject-state-impl.hpp>
#include <helper/SplitString.h>

namespace SOUI{

	class SouiLayoutParam: public SObjectImpl<ILayoutParam>
	{
		SOUI_CLASS_NAME(SouiLayoutParam,L"SouiLayoutParam")

	public:
		virtual bool IsMatchParent(ORIENTATION orientation) const;

		virtual bool IsSpecifiedSize(ORIENTATION orientation) const;

		virtual bool IsWrapContent(ORIENTATION orientation) const;

		virtual int GetSpecifiedSize(ORIENTATION orientation) const;

	public:
		bool IsOffsetRequired(ORIENTATION orientation) const;

	protected:
		HRESULT OnAttrWidth(const SStringW & strValue,BOOL bLoading);

		HRESULT OnAttrHeight(const SStringW & strValue,BOOL bLoading);

		HRESULT OnAttrSize(const SStringW & strValue,BOOL bLoading);

		HRESULT OnAttrPos(const SStringW & strValue,BOOL bLoading);

		HRESULT OnAttrOffset(const SStringW & strValue,BOOL bLoading);

		SOUI_ATTRS_BEGIN()
            ATTR_CUSTOM(L"width",OnAttrWidth)
            ATTR_CUSTOM(L"height",OnAttrHeight)
			ATTR_CUSTOM(L"pos",OnAttrPos)
			ATTR_CUSTOM(L"size",OnAttrSize)
			ATTR_CUSTOM(L"offset",OnAttrOffset)
        SOUI_ATTRS_BREAK()

    protected:
        //���ַ�������������ת����POSITION_ITEM
        BOOL StrPos2ItemPos(const SStringW &strPos,POSITION_ITEM & posItem);

        //������pos�ж����ǰ����λ��
        BOOL ParsePosition12(const SStringW & pos1, const SStringW &pos2);

        //������pos�ж���ĺ�����λ��
        BOOL ParsePosition34(const SStringW & pos3, const SStringW &pos4);

	protected:
        int  nCount;                /**< ������������ */
        POSITION_ITEM pos[4];       /**< ��pos���Զ����ֵ, nCount >0 ʱ��Ч*/

		float fOffsetX,fOffsetY;    /**< ��������ƫ����, x += fOffsetX * width, y += fOffsetY * height  */

		int  m_width;        /**<ʹ��width���Զ���Ŀ� nCount==0 ʱ��Ч*/
		int  m_height;       /**<ʹ��height���Զ���ĸ� nCount==0 ʱ��Ч*/
	};

	class SouiLayout: public SObjectImpl<ILayout>
	{
		SOUI_CLASS_NAME(SouiLayout,L"SouiLayout")

	public:
		SouiLayout(void);
		~SouiLayout(void);

        virtual bool IsParamAcceptable(ILayoutParam *pLayoutParam) const;

        virtual void CalcPostionOfChildren(SWindow * pParent);

        virtual ILayoutParam * CreateLayoutParam() const;

        virtual CSize MeasureChildren(SWindow * pParent,int nWidth,int nHeight) const;
    protected:
        struct WndPos{
            SWindow *pWnd;
            CRect    rc;
			bool     bWaitOffsetX;
			bool	 bWaitOffsetY;
        };

        void _MeasureChildren(SList<WndPos> *pListChildren,int nWidth,int nHeight);
        int _MeasureChildrenStep1(SList<WndPos> *pListChildren,int nWidth,int nHeight);

		int PositionItem2Value(SList<WndPos> *pLstChilds,SPOSITION position,const POSITION_ITEM &pos , int nMax,BOOL bX);
        
        int CalcChildLeft(SWindow *pWindow,SouiLayoutParam *pParam);
        int CalcChildRight(SWindow *pWindow,SouiLayoutParam *pParam);
        int CalcChildTop(SWindow *pWindow,SouiLayoutParam *pParam);
        int CalcChildBottom(SWindow *pWindow,SouiLayoutParam *pParam);


        BOOL CalcChildrenPosition(SList<SWindowRepos*> *pListChildren,int nWidth,int nHeight);
        int CalcPosition(SWindow *pWnd,const CRect & rcContainer,CRect & rcWindow, const SwndLayout * pSwndLayout=NULL);
        BOOL IsWaitingPos( int nPos );
        int PositionItem2Value(SWindow *pWindow,const POSITION_ITEM &pos ,int nMin, int nMax,BOOL bX);
		SWindow * GetRefSibling(SWindow *pCurWnd,int uCode);
        CRect GetWindowLayoutRect(SWindow *pWindow);
    };


}
