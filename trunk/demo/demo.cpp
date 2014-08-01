// dui-demo.cpp : main source file
//

#include "stdafx.h"

#include <unknown/com-loader.hpp>

#if defined(_DEBUG) && !defined(_WIN64)
// #include <vld.h>//ʹ��Vitural Leaker Detector������ڴ�й©�����Դ�http://vld.codeplex.com/ ����
#endif

#include "MainDlg.h"

#define RENDER_GDI      //��RENDER_GDIʱʹ��render-gdiģ������Ⱦ���������render-skia��Ⱦ

#define SUPPORT_LANG    //��SUPPORT_LANGʱ����ʾ������֧��

#define RES_TYPE 0   //���ļ��м�����Դ
// #define RES_TYPE 1   //��PE��Դ�м���UI��Դ
// #define RES_TYPE 2   //��zip���м�����Դ

#if RES_TYPE==2
    #include "../components/resprovider-zip/SResProviderZip.h"
#ifdef _DEBUG
	#pragma comment(lib,"resprovider-zipd.lib")
#else
    #pragma comment(lib,"resprovider-zip.lib")
#endif
#endif


#ifdef _DEBUG
#define COM_IMGDECODER  _T("imgdecoder-wicd.dll")
#define COM_RENDER_GDI  _T("render-gdid.dll")
#define COM_RENDER_SKIA _T("render-skiad.dll")
#define COM_SCRIPT_LUA _T("scriptmodule-luad.dll")
#define COM_TRANSLATOR _T("translatord.dll")
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define COM_IMGDECODER  _T("imgdecoder-wic.dll")
#define COM_RENDER_GDI  _T("render-gdi.dll")
#define COM_RENDER_SKIA _T("render-skia.dll")
#define COM_SCRIPT_LUA _T("scriptmodule-lua.dll")
#define COM_TRANSLATOR _T("translator.dll")
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
    HRESULT hRes = OleInitialize(NULL);
    ASSERT(SUCCEEDED(hRes));
    
    int nRet = 0; 

    SComLoader imgDecLoader;
    SComLoader renderLoader;
    SComLoader transLoader;
    SComLoader scriptLoader;
        
    //�����������·���޸ĵ�demo���ڵ�Ŀ¼
    TCHAR szCurrentDir[MAX_PATH]={0};
    GetModuleFileName( NULL, szCurrentDir, sizeof(szCurrentDir) );
    LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
    _tcscpy(lpInsertPos,_T("\\..\\demo"));
    SetCurrentDirectory(szCurrentDir);
    
    {

        CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
        CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
        imgDecLoader.CreateInstance(COM_IMGDECODER,(IObjRef**)&pImgDecoderFactory);
#ifdef RENDER_GDI
        renderLoader.CreateInstance(COM_RENDER_GDI,(IObjRef**)&pRenderFactory);
#else
        renderLoader.CreateInstance(COM_RENDER_SKIA,(IObjRef**)&pRenderFactory);
#endif

        pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

        SApplication *theApp=new SApplication(pRenderFactory,hInstance);

#ifdef SUPPORT_LANG
        CAutoRefPtr<ITranslatorMgr> trans;
        transLoader.CreateInstance(COM_TRANSLATOR,(IObjRef**)&trans);
        if(trans)
        {
            theApp->SetTranslator(trans);
            pugi::xml_document xmlLang;
            if(xmlLang.load_file(L"translation files/lang_cn.xml"))
            {
                CAutoRefPtr<ITranslator> langCN;
                trans->CreateTranslator(&langCN);
                langCN->Load(&xmlLang.child(L"language"),1);//1=LD_XML
                trans->InstallTranslator(langCN);
            }
        }
#endif//SUPPORT_LANG

#ifdef SUPPORT_LUA
        CAutoRefPtr<IScriptModule> pScriptLua;
        scriptLoader.CreateInstance(COM_SCRIPT_LUA,(IObjRef**)&pScriptLua);
        if(pScriptLua)
        {
            pScriptLua->executeScriptFile("lua/test.lua");
            theApp->SetScriptModule(pScriptLua);
        }
#endif//SUPPORT_LUA

#if (RES_TYPE == 0)
        SResProviderFiles *pResProvider=new SResProviderFiles;
        if(!pResProvider->Init(_T("skin")))
        {
            ASSERT(0);
            return 1;
        }
#elif (RES_TYPE==1)
        SResProviderPE *pResProvider = new SResProviderPE(hInstance);
#elif (RES_TYPE==2)
        SResProviderZip *pResProvider = new SResProviderZip(pRenderFactory);
        pResProvider->Init(_T("skin.zip"));
#endif

#ifdef SUPPORT_WKE
        SWkeWebkit::WkeWebkit_Init();
        theApp->RegisterWndFactory(TplSWindowFactory<SWkeWebkit>());//ע��WKE�����
#endif//SUPPORT_WKE
        theApp->RegisterWndFactory(TplSWindowFactory<SGifPlayer>());//ע��GIFPlayer
        theApp->RegisterSkinFactory(TplSkinFactory<SSkinGif>());//ע��SkinGif
        SSkinGif::Gdiplus_Startup();
        
        theApp->AddResProvider(pResProvider);
        
        HMODULE hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
        if(hSysResource)
        {
            SResProviderPE resPE(hSysResource);
            theApp->LoadSystemNamedResource(&resPE);
        }

        theApp->Init(_T("IDR_DUI_INIT")); 

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
        SSkinGif::Gdiplus_Shutdown();
#ifdef SUPPORT_WKE
        SWkeWebkit::WkeWebkit_Shutdown();
#endif//SUPPORT_WKE

    }

    OleUninitialize();
    return nRet;
}
