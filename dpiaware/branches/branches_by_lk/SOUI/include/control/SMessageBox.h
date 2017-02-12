/**
* Copyright (C) 2014-2050 SOUI�Ŷ�
* All rights reserved.
* 
* @file       SMessageBox.h
* @brief      
* @version    v1.0      
* @author     soui      
* @date       2014-07-06
* 
* Describe     
*/
#pragma once
#include "core/shostdialog.h"

namespace SOUI
{
    //�����Ǽ�����msgboxģ���б���ָ����ID��
    #define NAME_MSGBOX_BTNSWITCH       L"btnSwitch"    //һ������3��ҳ���tabctrl
    #define NAME_MSGBOX_TEXT            L"msgtext"      //�ı��ؼ���ֻ��Ҫָ����������
    #define NAME_MSGBOX_TITLE           L"msgtitle"     //����ID
    #define NAME_MSGBOX_ICON            L"msgicon"      //ͼ����ʾ�ؼ�
    #define NAME_MSGBOX_BTN1            L"button1st"    //��1����ťID����ťID����ʾʱ���Զ��޸�Ϊ��IDOK,IDCANCEL������ID��
    #define NAME_MSGBOX_BTN2            L"button2nd"    //��2����ťID
    #define NAME_MSGBOX_BTN3            L"button3rd"    //��3����ťID
    
    /** 
    * @class     SMessageBoxImpl
    * @brief     ��Ϣ����ģ��
    *
    * Describe   msgbox����Ϣ������������Ҫ���Ӹ��Ի���msgbox�������������ࡣ
    */    
    class SOUI_EXP SMessageBoxImpl:public SHostDialog
    {
    public:
        /**
        * SMessageBoxImpl::SMessageBoxImpl
        * @brief    ���캯��
        *
        * Describe  ���캯��  
        */
        SMessageBoxImpl();
        /**
        * SMessageBoxImpl::MessageBox
        * @brief    ��ʾ��
        * @param    HWND hWnd -- ���ھ��
        * @param    LPCTSTR lpText -- ��Ϣ����
        * @param    LPCTSTR lpCaption -- ���ڱ���
        * @param    UINT uType -- ��������
        *
        * Describe  ��ʾ��
        */        
        INT_PTR MessageBox( HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType );
        /**
        * SMessageBoxImpl::SetMsgTemplate
        * @brief    ������Ϣģ��
        * @param    pugi::xml_node xmlNode -- xml�ļ�
        *
        * Describe  ������Ϣģ��
        */
        static BOOL SetMsgTemplate(pugi::xml_node xmlNode);
    protected:
        /**
         * OnInitDialog
         * @brief    MsgBox��ʼ��
         * @param    HWND wnd -- host���ھ�� 
         * @param    LPARAM lInitParam --  ��ʹ��
         * @return   BOOL ��ʹ��
         *
         * Describe  
         */
        BOOL OnInitDialog(HWND wnd, LPARAM lInitParam);
        
        /**
        * SMessageBoxImpl::OnSetIcon
        * @brief    ����ͼ��
        * @param    UINT uType -- ����
        * @return   ����BOOL
        *
        * Describe  ����ͼ�� �������ظ÷�������ʾ�Զ����ͼ��
        */ 
        virtual BOOL OnSetIcon(UINT uType);

        /**
        * SMessageBoxImpl::OnBtnClick
        * @brief    ��ť��Ӧ����
        * @param    int uID -- �ؼ�ID
        *
        * Describe  ��Ϣ��Ӧ����
        */ 
        void OnBtnClick(int uID)
        {
            EndDialog(uID);
        }

        static pugi::xml_document s_xmlMsgTemplate; /**< ģ�� */

        EVENT_MAP_BEGIN()
            EVENT_ID_COMMAND_RANGE(IDOK,IDNO, OnBtnClick)
        EVENT_MAP_END()

        BEGIN_MSG_MAP_EX(SMessageBoxImpl)
            MSG_WM_INITDIALOG(OnInitDialog)
            CHAIN_MSG_MAP(SHostDialog)
            REFLECT_NOTIFICATIONS_EX()
        END_MSG_MAP()
    };

    int SOUI_EXP SMessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);

}//end of namespace 

