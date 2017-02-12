/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       STranslator-i.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    
*/

#pragma once

#include <unknown/obj-ref-i.h>
#include <string/tstring.h>

namespace SOUI
{
    /** 
     * @struct     ITranslator
     * @brief      ���Է���ӿ�
     *
     * Describe
     */
    struct ITranslator : public IObjRef
    {
        /**
         * Load
         * @brief    ����Դ�м������Է�������
         * @param    LPVOID pData --  ��Դָ�룬���庬���ɽӿڵ�ʵ��������
         * @param    UINT uType --  ��Դ���ͣ����庬���ɽӿڵ�ʵ��������
         * @return   BOOL true-���سɹ�, false-����ʧ��
         *
         * Describe  
         */
        virtual BOOL Load(LPVOID pData,UINT uType)=0;
        /**
         * name
         * @brief    ��ȡ������Դ��name
         * @return   SOUI::SStringW ������Դ��name
         *
         * Describe  
         */
        virtual SStringW name()=0;
        /**
         * guid
         * @brief    ��ȡ������Դ��ID
         * @return   GUID ������Դ��ID
         *
         * Describe  
         */
        virtual GUID     guid()=0;
        /**
         * tr
         * @brief    ִ�з���Ľӿ�
         * @param    const SStringW & strSrc --  ԭ�ַ���
         * @param    const SStringW & strCtx --  ����������
         * @param    SStringW & strRet --  �������ַ���
         * @return   BOOL true-����ɹ���false-����ʧ��
         *
         * Describe  
         */
        virtual BOOL tr(const SStringW & strSrc,const SStringW & strCtx,SStringW & strRet)=0;
    };

    /** 
     * @struct     ITranslatorMgr
     * @brief      ���Է���ӿڹ�����
     *
     * Describe
     */
    struct ITranslatorMgr : public IObjRef
    {
        /**
         * CreateTranslator
         * @brief    ����һ�����Է������
         * @param [out] ITranslator * * ppTranslator --  �������Է�������ָ��
         * @return   BOOL true-�ɹ���false-ʧ��
         *
         * Describe  
         */
        virtual BOOL CreateTranslator(ITranslator ** ppTranslator)=0;
        /**
         * InstallTranslator
         * @brief    ��������а�װһ�����Է������
         * @param    ITranslator * ppTranslator -- ���Է������
         * @return   BOOL true-�ɹ���false-ʧ��
         *
         * Describe  
         */

        virtual BOOL InstallTranslator(ITranslator * ppTranslator) =0;
        /**
         * UninstallTranslator
         * @brief    �ӹ�������ж��һ�����Է������
         * @param    REFGUID id --  ���Է�������ID
         * @return   BOOL true-�ɹ���false-ʧ��
         *
         * Describe  
         */
        virtual BOOL UninstallTranslator(REFGUID id) =0;
        
        /**
         * tr
         * @brief    �����ַ���
         * @param    const SStringW & strSrc --  ԭ�ַ���
         * @param    const SStringW & strCtx --  ����������
         * @return   SOUI::SStringW �������ַ���
         *
         * Describe  ����ITranslator��tr�ӿ�ִ�о��巭�����
         */
        virtual SStringW tr(const SStringW & strSrc,const SStringW & strCtx)=0;
    };

}