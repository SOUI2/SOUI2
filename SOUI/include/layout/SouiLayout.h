#pragma once
#include "interface/slayout-i.h"
#include <sobject/sobject-state-impl.hpp>
#include <helper/SplitString.h>

namespace SOUI{

#define POSFLAG_REFCENTER      '|'        //�ο�����������
#define POSFLAG_REFPREV_NEAR   '['        //�ο�ǰһ���ֵܴ������Լ����ı�
#define POSFLAG_REFNEXT_NEAR   ']'        //�ο���һ���ֵܴ������Լ����ı�
#define POSFLAG_REFPREV_FAR    '{'        //�ο�ǰһ���ֵܴ������Լ�Զ�ı�
#define POSFLAG_REFNEXT_FAR    '}'        //�ο���һ���ֵܴ������Լ�Զ�ı�
#define POSFLAG_PERCENT        '%'        //�����ڸ����ڵİٷֱȶ�������
#define POSFLAG_SIZE           '@'        //��pos�����ж��崰�ڵ�size��ֻ���ڶ���x2,y2ʱ��Ч

	enum SWNDPOSMASK//��������
	{
		// Specify by "width" attribute
		SizeX_Mask          = 0x000fUL,
		SizeX_Specify       = 0x0001UL, // width > 0
		SizeX_FitContent    = 0x0002UL, // width <= 0
		SizeX_FitParent     = 0x0004UL, // width = "full" default

		// Specify by "height" attribute
		SizeY_Mask          = 0x00f0UL,
		SizeY_Specify       = 0x0010UL, // height > 0
		SizeY_FitContent    = 0x0020UL, // height <= 0 default
		SizeY_FitParent     = 0x0040UL, // height = "full" default
	};

	//��������
	enum PIT{

		PIT_NULL=0,        //��Ч����
		PIT_NORMAL,        //ê������
		PIT_CENTER,        //�ο����������ĵ�,��"|"��ʼ
		PIT_PERCENT,       //ָ���ڸ�����������еİٷֱ�,��"%"��ʼ
		PIT_PREV_NEAR,     //�ο�ǰһ���ֵܴ������Լ����ı�,��"["��ʼ
		PIT_NEXT_NEAR,     //�ο���һ���ֵܴ������Լ����ı�,��"]"��ʼ
		PIT_PREV_FAR,      //�ο�ǰһ���ֵܴ������Լ�Զ�ı�,��"{"��ʼ
		PIT_NEXT_FAR,      //�ο���һ���ֵܴ������Լ�Զ�ı�,��"}"��ʼ
		PIT_SIZE,          //ָ�����ڵĿ���߸�,��"@"��ʼ
		PIT_SIB_LEFT=10,       //�ֵܽ���left,����X
		PIT_SIB_TOP=10,        //�ֵܽ���top����left��ͬ������Y
		PIT_SIB_RIGHT=11,      //�ֵܽ���right,����X 
		PIT_SIB_BOTTOM=11,      //�ֵܽ���bottom,��right��ͬ,����Y 
	};

	struct POSITION_ITEM
	{
		PIT     pit;        /**<�������� */
		int     nRefID;     /**<����ID�����ֵܴ���ʱʹ�õ�ID,-1�����ο��ض�ID���ֵ�,ʹ��ID���õĸ�ʽΪ"sib.left@200:10"���Ƶĸ�ʽ */
		char    cMinus;     /**<�����ֵ����"-", ����-0����ֱ����nPos��ʾ����Ҫһ�������ı�־λ */
		float   nPos;       /**<����ֵ*/
	};


	enum POSINDEX
	{
		PI_LEFT = 0,
		PI_TOP,
		PI_RIGHT,
		PI_BOTTOM,
	};

	class SouiLayoutParam: public SObjectImpl<TObjRefImpl<ILayoutParam>>
	{
		SOUI_CLASS_NAME(SouiLayoutParam,L"SouiLayoutParam")

		friend class SouiLayout;
	public:
		virtual bool IsMatchParent(ORIENTATION orientation) const;

		virtual bool IsSpecifiedSize(ORIENTATION orientation) const;

		virtual bool IsWrapContent(ORIENTATION orientation) const;

		virtual int GetSpecifiedSize(ORIENTATION orientation) const;

		virtual void Clear();

		virtual void SetMatchParent(ORIENTATION orientation);

		virtual void SetWrapContent(ORIENTATION orientation);

		virtual void SetSpecifiedSize(ORIENTATION orientation, int nSize);

	public:
		bool IsOffsetRequired(ORIENTATION orientation) const;
        int  GetExtraSize(ORIENTATION orientation) const;
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

	class SouiLayout: public SObjectImpl<TObjRefImpl<ILayout>>
	{
		SOUI_CLASS_NAME(SouiLayout,L"SouiLayout")

	public:
		SouiLayout(void);
		~SouiLayout(void);

		static HRESULT CreateLayout(IObjRef ** ppObj);

		static HRESULT CreateLayoutParam(IObjRef ** ppObj);

        virtual bool IsParamAcceptable(ILayoutParam *pLayoutParam) const;

        virtual void LayoutChildren(SWindow * pParent);

        virtual ILayoutParam * CreateLayoutParam() const;

        virtual CSize MeasureChildren(SWindow * pParent,int nWidth,int nHeight) const;
    protected:
        struct WndPos{
            SWindow *pWnd;
            CRect    rc;
			bool     bWaitOffsetX;
			bool	 bWaitOffsetY;
        };

        void CalcPositionEx(SList<WndPos> *pListChildren,int nWidth,int nHeight) const;
        int CalcPostion(SList<WndPos> *pListChildren,int nWidth,int nHeight) const;

		int PositionItem2Value(SList<WndPos> *pLstChilds,SPOSITION position,const POSITION_ITEM &pos , int nMax,BOOL bX) const;
        
        int CalcChildLeft(SWindow *pWindow,SouiLayoutParam *pParam);
        int CalcChildRight(SWindow *pWindow,SouiLayoutParam *pParam);
        int CalcChildTop(SWindow *pWindow,SouiLayoutParam *pParam);
        int CalcChildBottom(SWindow *pWindow,SouiLayoutParam *pParam);


        BOOL IsWaitingPos( int nPos ) const;
		SWindow * GetRefSibling(SWindow *pCurWnd,int uCode);
        CRect GetWindowLayoutRect(SWindow *pWindow);
    };


}
