#pragma once

namespace SOUI
{

#define POSFLAG_REFCENTER    '|'        //�ο�����������
#define POSFLAG_REFPREV        '['        //�ο�ǰһ���ֵܴ���
#define POSFLAG_REFNEXT        ']'        //�ο���һ���ֵܴ���
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
        PIT_NORMAL=0,    //һ������
        PIT_CENTER,        //�ο����������ĵ�,��"|"��ʼ
        PIT_PERCENT,    //ָ���ڸ�����������еİٷֱ�,��"%"��ͷ
        PIT_PREVSIBLING,    //ָ������Ϊ���ǰһ���ֵܴ��ڵ�ƫ�ƣ�û���ֵܴ���ʱΪ������,��"["��ͷ
        PIT_NEXTSIBLING,    //ָ������Ϊ���ǰһ���ֵܴ��ڵ�ƫ�ƣ�û���ֵܴ���ʱΪ������,��"]"��ͷ
        PIT_OFFSET,        //�����ǰ��x1,y1��ƫ��,ֻ����x2,y2��ʹ�ã���@��ͷ
    };

    struct SWND_POSITION_ITEM
    {
        PIT pit;
        BOOL bMinus;
        float  nPos;
    };

    typedef enum tagPOS2TYPE{
        POS2_LEFTTOP=0,    //���Ͻ�
        POS2_RIGHTTOP,    //������
        POS2_CENTER,    //����
        POS2_LEFTBOTTOM,//
        POS2_RIGHTBOTTOM,//
    }POS2TYPE;

    struct SWND_POSITION
    {
        int nCount;
        union
        {
            struct
            {
                SWND_POSITION_ITEM Left;
                SWND_POSITION_ITEM Top;
                SWND_POSITION_ITEM Right;
                SWND_POSITION_ITEM Bottom;
            };
            SWND_POSITION_ITEM Item[4];
        };
        UINT uPositionType;        //��������
        POS2TYPE pos2Type;        //ָ��2������ʱ����������
        UINT uSpecifyWidth;
        UINT uSpecifyHeight;

        SWND_POSITION():nCount(0)
            ,uPositionType(0)
            ,pos2Type(POS2_LEFTTOP)
            ,uSpecifyWidth(0)
            ,uSpecifyHeight(0)
        {

        }
    };

    class SWindow;
    class SwndLayout
    {
    public:
        static void StrPos2SwndPos(LPCWSTR pszPos,SWND_POSITION &dlgpos);

        //************************************
        // Method:    PositionItem2Point ����һ��position_item����Ϊ��������
        // FullName:  SOUI::SWindow::PositionItem2Point
        // Access:    protected 
        // Returns:   CPoint
        // Qualifier:
        // Parameter: const SWND_POSITION_ITEM & pos
        // Parameter: int nMin �����ڵķ�Χ
        // Parameter: int nMax �����ڵķ�Χ
        // Parameter: BOOL bX ����X����
        //************************************
        static int PositionItem2Value(SWindow *pWnd,const SWND_POSITION_ITEM &pos,int nMin, int nMax,BOOL bX);

        //************************************
        // Method:    ParsePosition :����һ�����궨�嵽position_item,���Ӷ԰ٷֱȵ�֧��
        // FullName:  SOUI::SWindow::ParsePosition
        // Access:    protected 
        // Returns:   LPCSTR
        // Qualifier:
        // Parameter: LPCWSTR pszPos
        // Parameter: BOOL bFirst2Pos:TRUE-����pos��ǰ������ֵ
        // Parameter: SWND_POSITION_ITEM & pos
        //************************************
        static LPCWSTR ParsePosition(LPCWSTR pszPos,BOOL bFirst2Pos,SWND_POSITION_ITEM &pos);

        //************************************
        // Method:    CalcPosition:���㴰������
        // FullName:  SOUI::SWindow::CalcPosition
        // Access:    protected 
        // Returns:   int
        // Qualifier:
        // Parameter: LPRECT prcContainer
        //************************************
        static int CalcPosition(SWindow *pWnd,LPRECT prcContainer,const SWND_POSITION & dlgpos,CRect &rcWindow);


        static BOOL CalcChildrenPosition(SWindow *pWnd,SList<SWindow*> *pListChildren);
    };
}
