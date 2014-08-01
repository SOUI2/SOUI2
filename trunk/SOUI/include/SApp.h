/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       stabctrl.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-06
 * 
 * Describe    SOUIӦ�ó������ 
 */

#pragma once
#include "core/ssingleton.h"
#include "unknown/obj-ref-impl.hpp"
#include "interface/render-i.h"
#include "interface/SScriptModule-i.h"
#include "interface/STranslator-i.h"

#include "res.mgr/SResProviderMgr.h"

#include "core/smsgloop.h"
#include "core/SWndFactoryMgr.h"
#include "core/SSkinFactoryMgr.h"


#define SOUI_VERSION    _T("0.9.0.1")

#define LOADXML(p1,p2,p3) SApplication::getSingleton().LoadXmlDocment(p1,p2,p3)
#define LOADIMAGE(p1,p2) SApplication::getSingleton().LoadImage(p1,p2)
#define GETRESPROVIDER    SApplication::getSingletonPtr()
#define GETRENDERFACTORY SApplication::getSingleton().GetRenderFactory()
#define TR(p1,p2)       SApplication::getSingleton().GetTranslator()->tr(p1,p2)
               
#define RT_UIDEF _T("UIDEF")
#define RT_LAYOUT _T("LAYOUT")

namespace SOUI
{

/** 
 * @class     SApplication
 * @brief     SOUI Application
 *
 * Describe   SOUI Application
 */
class SOUI_EXP SApplication :public SSingleton<SApplication>
                        ,public SWindowFactoryMgr
                        ,public SSkinFactoryMgr
                        ,public SResProviderMgr
                        ,public SMessageLoop
{
public:
    /**
     * SApplication
     * @brief    ���캯��
     * @param    IRenderFactory * pRendFactory --  ��Ⱦģ��
     * @param    HINSTANCE hInst --  Ӧ�ó�����
     * @param    LPCTSTR pszHostClassName --  ʹ��SOUI��������ʱĬ�ϵĴ�������
     *
     * Describe  
     */
    SApplication(IRenderFactory *pRendFactory,HINSTANCE hInst,LPCTSTR pszHostClassName=_T("SOUIHOST"));
    ~SApplication(void);


    /**
     * GetInstance
     * @brief    ���Ӧ�ó�����
     * @return   HINSTANCE 
     *
     * Describe  
     */
    HINSTANCE GetInstance();

    /**
     * GetVersion
     * @brief    ���SOUI�İ汾��
     * @return   LPCTSTR 
     *
     * Describe  
     */
    LPCTSTR GetVersion();

    /**
     * Init
     * @brief    ��ʼ��SOUIϵͳ
     * @param    LPCTSTR pszName --  ��ʼ��SOUI��XML�ļ�����Դ�е�name
     * @param    LPCTSTR pszType --  ��ʼ��SOUI��XML�ļ�����Դ�е�type
     * @return   BOOL true-��ʼ���ɹ�, false-��ʼ��ʧ��
     *
     * Describe  ��ʼ����XML��������SOUI�ĸ�ʽ��
     */
    BOOL Init(LPCTSTR pszName ,LPCTSTR pszType=RT_UIDEF);

    /**
     * LoadSystemNamedResource
     * @brief    ����SOUIϵͳĬ�ϵ�������Դ
     * @param    IResProvider * pResProvider --  
     * @return   UINT 
     *
     * Describe  
     */
    UINT LoadSystemNamedResource(IResProvider *pResProvider);
    
    /**
     * LoadXmlDocment
     * @brief    ����Դ�м���һ��XML Document��
     * @param [out] pugi::xml_document & xmlDoc --  �����xml_document����
     * @param    LPCTSTR pszXmlName --  XML�ļ�����Դ�е�name
     * @param    LPCTSTR pszType --  XML�ļ�����Դ�е�type
     * @return   BOOL true-���سɹ�, false-����ʧ��
     *
     * Describe  
     */
    BOOL LoadXmlDocment(pugi::xml_document & xmlDoc,LPCTSTR pszXmlName ,LPCTSTR pszType);

    /**
     * GetRenderFactory
     * @brief    ��õ�ǰ����Ⱦģ��
     * @return   IRenderFactory * ��Ⱦģ��ָ��
     *
     * Describe  
     */
    IRenderFactory * GetRenderFactory();

    /**
     * GetScriptModule
     * @brief    ��ȡSOUI�����õĽű�ģ��
     * @return   IScriptModule * �ű�ģ��ָ��
     *
     * Describe  
     */
    IScriptModule * GetScriptModule();

    /**
     * SetScriptModule
     * @brief    ����SOUI��ʹ�õĽű�ģ��
     * @param    IScriptModule * pScriptModule --  �ű�ģ��ָ��
     * @return   void 
     *
     * Describe  
     */
    void SetScriptModule(IScriptModule *pScriptModule);
    
    /**
     * GetTranslator
     * @brief    ��ȡ���Է���ģ��
     * @return   ITranslator * ���Է���ģ��ָ��
     *
     * Describe  
     */
    ITranslatorMgr * GetTranslator();
    
    /**
     * SetTranslator
     * @brief    �������Է���ģ��
     * @param    ITranslator * pTrans --  ���Է���ģ��ָ��
     * @return   void 
     *
     * Describe  
     */
    void SetTranslator(ITranslatorMgr * pTrans);
    
    /**
     * Run
     * @brief    ����SOUI������Ϣѭ��
     * @param    HWND hMainWnd --  Ӧ�ó��������ھ��
     * @return   int ��Ϣѭ������ʱ�ķ���ֵ
     *
     * Describe  
     */
    int Run(HWND hMainWnd);
protected:
    void _CreateSingletons();
    void _DestroySingletons();
    BOOL _LoadXmlDocment(IResProvider* pResProvider, LPCTSTR pszXmlName ,LPCTSTR pszType ,pugi::xml_document & xmlDoc);

    HINSTANCE m_hInst;
    CAutoRefPtr<IScriptModule>  m_pScriptModule;
    CAutoRefPtr<IRenderFactory> m_RenderFactory;
    CAutoRefPtr<ITranslatorMgr>    m_Translator;
};

}//namespace SOUI