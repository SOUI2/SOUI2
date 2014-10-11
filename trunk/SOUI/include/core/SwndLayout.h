/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       SwndLayout.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    SOUI�Ĵ��ڲ���ģ��
*/

#pragma once

namespace SOUI
{

#define POSFLAG_REFCENTER      '|'        //�ο�����������
#define POSFLAG_REFPREV_NEAR   '['        //�ο�ǰһ���ֵܴ������Լ����ı�
#define POSFLAG_REFNEXT_NEAR   ']'        //�ο���һ���ֵܴ������Լ����ı�
#define POSFLAG_REFPREV_FAR    '{'        //�ο�ǰһ���ֵܴ������Լ�Զ�ı�
#define POSFLAG_REFNEXT_FAR    '}'        //�ο���һ���ֵܴ������Լ�Զ�ı�
#define POSFLAG_PERCENT        '%'        //�����ڸ����ڵİٷֱȶ�������
#define POSFLAG_DEFSIZE        '@'        //��pos�����ж��崰�ڵ�size��ֻ���ڶ���x2,y2ʱ��Ч

    enum
    {
        POS_INIT=0x11000000,    //����ĳ�ʼ��ֵ
        POS_WAIT=0x12000000,    //����ļ����������������ڵĲ���
    };

    enum //��������
    {
        // Specify by "width" attribute
        SizeX_Mask          = 0x0007UL,
        SizeX_Specify       = 0x0001UL, // width > 0
        SizeX_FitContent    = 0x0002UL, // width <= 0
        SizeX_FitParent     = 0x0004UL, // width = "full" default

        // Specify by "height" attribute
        SizeY_Mask          = 0x0070UL,
        SizeY_Specify       = 0x0010UL, // height > 0
        SizeY_FitContent    = 0x0020UL, // height <= 0 default
        SizeY_FitParent     = 0x0040UL, // height = "full" default

        Position_Mask       = 0x0300UL, // ָ���Ǹ������ڻ�����ê�㴰��
        Pos_Float            = 0x0100UL,    // 1:�������ڣ�0:ê�㴰��
    };

    //��������
    enum PIT{
        PIT_NORMAL=0,      //һ������
        PIT_CENTER,        //�ο����������ĵ�,��"|"��ʼ
        PIT_PERCENT,       //ָ���ڸ�����������еİٷֱ�,��"%"��ͷ
        PIT_PREV_NEAR,     //�ο�ǰһ���ֵܴ������Լ����ı�
        PIT_NEXT_NEAR,     //�ο���һ���ֵܴ������Լ����ı�
        PIT_PREV_FAR,      //�ο�ǰһ���ֵܴ������Լ�Զ�ı�
        PIT_NEXT_FAR,      //�ο���һ���ֵܴ������Լ�Զ�ı�
        PIT_OFFSET,        //�����ǰ��x1,y1��ƫ��,ֻ����x2,y2��ʹ�ã���@��ͷ
    };

    struct POSITION_ITEM
    {
        PIT pit;
        BOOL bMinus;
        float  nPos;
    };

    typedef enum tagPOS2TYPE{
        POS2_LEFTTOP=0,    //���Ͻ�
        POS2_MIDTOP,
        POS2_RIGHTTOP,    //������
        POS2_LEFTMID,
        POS2_CENTER,    //����
        POS2_RIGHTMID,
        POS2_LEFTBOTTOM,//���½�
        POS2_MIDBOTTOM,
        POS2_RIGHTBOTTOM,//���½�
    }POS2TYPE;

    class SWindow;
    class SOUI_EXP SwndLayout
    {
    public:
        SwndLayout(SWindow *pOwner);
        
        /**
         * ParseStrPostion
         * @brief    ����һ��pos�ַ���
         * @param    LPCWSTR pszPos --  pos�ַ���
         * @return   void 
         *
         * Describe  
         */
        void ParseStrPostion(LPCWSTR pszPos);


        /**
         * CalcPosition
         * @brief    ���㴰������
         * @param    LPRECT prcContainer --  ����λ��
         * @param  [out]  CRect & rcWindow --  ���ھ���
         * @return   int ����õ����������
         *
         * Describe  ÿ�����ڰ���4�����꣬����һ��������������������ֵܴ��ڵĲ��֣�һ�μ�����ܲ���ȫ���õ�4������
         */
        int CalcPosition(LPRECT prcContainer,CRect &rcWindow);


        /**
         * CalcChildrenPosition
         * @brief    �����б����Ӵ��ڵ�����
         * @param    SList<SWindow * > * pListChildren --  �Ӵ����б�
         * @return   BOOL TRUE-�ɹ���FALSE-ʧ�ܣ��������ڲ��������γ�����
         *
         * Describe  
         */
        BOOL CalcChildrenPosition(SList<SWindow*> *pListChildren);
        
        /**
         * IsFitContent
         * @brief    ��ò����Ƿ����������ݱ�־
         * @return   BOOL 
         *
         * Describe  
         */
        BOOL IsFitContent();
        
        /**
         * IsFloat
         * @brief    ��ѯ�����Ƿ�ΪPos_float���͵Ĵ���
         * @return   BOOL TRUE-float
         *
         * Describe  
         */
        BOOL IsFloat();
    protected:
    
        /**
         * PositionItem2Value
         * @brief    ��һ��position_item����Ϊ��������
         * @param    const POSITION_ITEM & pos --  һ��λ�ö��������
         * @param    int nMin --  �����ڵķ�Χ
         * @param    int nMax --  �����ڵķ�Χ
         * @param    BOOL bX --  ����X����
         * @return   int ����õ�������
         *
         * Describe  
         */
        int PositionItem2Value(const POSITION_ITEM &pos,int nMin, int nMax,BOOL bX);

        /**
         * ParsePosition
         * @brief    ����һ���ַ������������
         * @param    LPCWSTR pszPos --  "pos"�����ַ���
         * @param    BOOL bFirst2Pos --  Ϊǰ�����������־
         * @param  [out]  SWND_POSITION_ITEM & pos --  �������궨��
         * @return   LPCWSTR ������һ��λ�ÿ�ʼ
         *
         * Describe  ǰ���������겻��ָ����С������������������ָ����С
         */
        LPCWSTR ParsePosition(LPCWSTR pszPos,BOOL bFirst2Pos,POSITION_ITEM &pos);


        /**
         * CalcSize
         * @brief    ���㴰�ڴ�С
         * @param    LPRECT pRcContainer --  ����λ��
         * @return   CSize 
         *
         * Describe  
         */
        CSize CalcSize(LPRECT pRcContainer);

        SWindow *m_pOwner;  //**< layout������ */
        
    public:
        int nCount;         //**< ������������ */
        union
        {
            struct
            {
                POSITION_ITEM Left;
                POSITION_ITEM Top;
                POSITION_ITEM Right;
                POSITION_ITEM Bottom;
            };
            POSITION_ITEM Item[4];
        };
        UINT uPositionType;       /**< �������� */
        POS2TYPE pos2Type;        /**< ָ��2������ʱ���������� */
        UINT uSpecifyWidth;       /**< ָ���Ŀ�� */
        UINT uSpecifyHeight;      /**< ָ���ĸ߶� */
        int  nSepSpace;           /**< ����ˮƽ�Զ��Ű��ˮƽ�������֧�ִ�ֱ������Զ��Ű� */
    };
}
