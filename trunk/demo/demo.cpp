// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "SApp.h" 

#ifdef _DEBUG
#include <vld.h>//ʹ��Vitural Leaker Detector������ڴ�й©�����Դ�http://vld.codeplex.com/ ����
#endif

#include "MainDlg.h"

#define RENDER_GDI      //��RENDER_GDIʱʹ��render-gdiģ������Ⱦ���������render-skia��Ⱦ

#define SUPPORT_LANG    //��SUPPORT_LANGʱ����ʾ������֧��

#define RES_USINGFILE   //��RES_USINGFILE���ļ��м�����Դ�������PE��Դ�м���UI��Դ


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
    HRESULT hRes = OleInitialize(NULL);
    ASSERT(SUCCEEDED(hRes));
    
    int nRet = 0; 

    SComLoader imgDecLoader;
    SComLoader renderLoader;
    SComLoader transLoader;
    SComLoader scriptLoader;
    
    {

        CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
        CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
#ifdef _DEBUG
        imgDecLoader.CreateInstance(_T("imgdecoder-wic_d.dll"),(IObjRef**)&pImgDecoderFactory);
#ifdef RENDER_GDI
        renderLoader.CreateInstance(_T("render-gdi_d.dll"),(IObjRef**)&pRenderFactory);
#else
        renderLoader.CreateInstance(_T("render-skia_d.dll"),(IObjRef**)&pRenderFactory);
#endif
#else
        imgDecLoader.CreateInstance(_T("imgdecoder-wic.dll"),(IObjRef**)&pImgDecoderFactory);
#ifdef RENDER_GDI
        renderLoader.CreateInstance(_T("render-gdi.dll"),(IObjRef**)&pRenderFactory);
#else
        renderLoader.CreateInstance(_T("render-skia.dll"),(IObjRef**)&pRenderFactory);
#endif
#endif

        pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

        SApplication *theApp=new SApplication(pRenderFactory,hInstance);

#ifdef SUPPORT_LANG
        CAutoRefPtr<ITranslator> trans;
#ifdef _DEBUG
        transLoader.CreateInstance(_T("translator_d.dll"),(IObjRef**)&trans);
#else
        transLoader.CreateInstance(_T("translator.dll"),(IObjRef**)&trans);
#endif//_DEBUG
        if(trans)
        {
            theApp->SetTranslator(trans);
            pugi::xml_document xmlLang;
            if(xmlLang.load_file(L"../demo/translation files/lang_cn.xml"))
            {
                CAutoRefPtr<ILang> langCN;
                trans->CreateLang(&langCN);
                langCN->Load(&xmlLang.child(L"language"),1);//1=LD_XML
                trans->InstallLang(langCN);
            }
        }
#endif//SUPPORT_LANG

#ifdef SUPPORT_LUA
        CAutoRefPtr<IScriptModule> pScriptLua;
#ifdef _DEBUG
        scriptLoader.CreateInstance(_T("scriptmodule-lua_d.dll"),(IObjRef**)&pScriptLua);
#else
        scriptLoader.CreateInstance(_T("scriptmodule-lua.dll"),(IObjRef**)&pScriptLua);
#endif//_DEBUG
        if(pScriptLua)
        {
            pScriptLua->executeScriptFile("../demo/lua/test.lua");
            theApp->SetScriptModule(pScriptLua);
        }
#endif//SUPPORT_LUA

#ifdef RES_USINGFILE
        TCHAR szCurrentDir[MAX_PATH]={0};
        GetModuleFileName( NULL, szCurrentDir, sizeof(szCurrentDir) );
        LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
        *lpInsertPos = _T('\0');   
        _tcscat( szCurrentDir, _T("\\..\\demo\\skin") );

        SResProviderFiles *pResProvider=new SResProviderFiles;
        if(!pResProvider->Init(szCurrentDir))
        {
            ASSERT(0);
            return 1;
        }
#else
        SResProviderPE *pResProvider = new SResProviderPE(hInstance);
#endif

        theApp->AddResProvider(pResProvider);

        BOOL bOK=theApp->Init(_T("IDR_DUI_INIT")); //��ʼ��DUIϵͳ,ԭ����ϵͳ��ʼ����ʽ��Ȼ����ʹ�á�
        theApp->SetMsgBoxTemplate(_T("IDR_DUI_MSGBOX"));

        // BLOCK: Run application
        {
            CMainDlg dlgMain;  
            dlgMain.Create(GetActiveWindow(),0,0,800,600);
            dlgMain.GetNative()->SendMessage(WM_INITDIALOG);
            dlgMain.ShowWindow(SW_SHOWNORMAL);
            nRet=theApp->Run(dlgMain.m_hWnd);
            //  		nRet = dlgMain.DoModal();  
        }

        delete theApp;
        delete pResProvider;

    }

    OleUninitialize();
    return nRet;
}
