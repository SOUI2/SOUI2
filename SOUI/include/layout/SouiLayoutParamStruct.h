#pragma once

#define POSFLAG_REFCENTER      '|'        //�ο�����������
#define POSFLAG_REFPREV_NEAR   '['        //�ο�ǰһ���ֵܴ������Լ����ı�
#define POSFLAG_REFNEXT_NEAR   ']'        //�ο���һ���ֵܴ������Լ����ı�
#define POSFLAG_REFPREV_FAR    '{'        //�ο�ǰһ���ֵܴ������Լ�Զ�ı�
#define POSFLAG_REFNEXT_FAR    '}'        //�ο���һ���ֵܴ������Լ�Զ�ı�
#define POSFLAG_PERCENT        '%'        //�����ڸ����ڵİٷֱȶ�������
#define POSFLAG_SIZE           '@'        //��pos�����ж��崰�ڵ�size��ֻ���ڶ���x2,y2ʱ��Ч

namespace SOUI{

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

	struct SouiLayoutParamStruct
	{
		int  nCount;                /**< ������������ */
		POSITION_ITEM pos[4];       /**< ��pos���Զ����ֵ, nCount >0 ʱ��Ч*/

		float fOffsetX,fOffsetY;    /**< ��������ƫ����, x += fOffsetX * width, y += fOffsetY * height  */

		int  width;        /**<ʹ��width���Զ���Ŀ� nCount==0 ʱ��Ч*/
		int  height;       /**<ʹ��height���Զ���ĸ� nCount==0 ʱ��Ч*/
	};
}
