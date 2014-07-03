/********************************************************************
    created:    2013/02/19
    created:    19:2:2013   10:11
    filename:     DuiMessageBox.h
    author:        Huang Jianxiong
    
    purpose:    ģ��һ��MessageBox
*********************************************************************/
#pragma once

#include "duihostwnd.h"

namespace SOUI
{
    //�����Ǽ�����msgboxģ���б���ָ����ID��
    #define NAME_MSGBOX_BTN1PANEL    L"btn1panel"    //����������ť��panel
    #define NAME_MSGBOX_BTN2PANEL    L"btn2panel"    //����2����ť��panel
    #define NAME_MSGBOX_BTN3PANEL    L"btn3panel"    //����3����ť��panel
    #define NAME_MSGBOX_TEXT            L"msgtext"    //�ı��ؼ���ֻ��Ҫָ����������
    #define NAME_MSGBOX_TITLE        L"msgtitle"    //����ID
    #define NAME_MSGBOX_ICON            L"msgicon"    //ͼ����ʾ�ؼ�
    #define NAME_MSGBOX_BTN1            L"button1st"    //��1����ťID����ťID����ʾʱ���Զ��޸�Ϊ��IDOK,IDCANCEL������ID��
    #define NAME_MSGBOX_BTN2            L"button2nd"    //��2����ťID
    #define NAME_MSGBOX_BTN3            L"button3rd"    //��3����ťID

    //msgbox����Ϣ������������Ҫ���Ӹ��Ի���msgbox�������������ࡣ
    class SOUI_EXP SMessageBoxImpl:public CDuiHostWnd
    {
    public:
        int MessageBox( HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType );

        static BOOL SetMsgTemplate(pugi::xml_node xmlNode);
    protected:
        //�������ظ÷�������ʾ�Զ����ͼ��
        virtual BOOL SetIcon(UINT uType);

        void OnBtnClick(UINT uID)
        {
            EndDialog(uID);
        }

        static pugi::xml_document s_xmlMsgTemplate;

        SOUI_NOTIFY_MAP_BEGIN()
            SOUI_NOTIFY_ID_COMMAND_RANGE(IDOK,IDNO, OnBtnClick)
        SOUI_NOTIFY_MAP_END()    

        BEGIN_MSG_MAP_EX(SMessageBoxImpl)
            MSG_SOUI_NOTIFY()
            CHAIN_MSG_MAP(CDuiHostWnd)
            REFLECT_NOTIFICATIONS_EX()
        END_MSG_MAP()


    };

    int SOUI_EXP SMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);

}//end of namespace 

