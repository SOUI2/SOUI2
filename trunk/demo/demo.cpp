// dui-demo.cpp : main source file
//

#include "stdafx.h"

#include <com-loader.hpp>
#include <helper/mybuffer.h>
#if defined(_DEBUG) && !defined(_WIN64)
// #include <vld.h>//ʹ��Vitural Leaker Detector������ڴ�й©�����Դ�http://vld.codeplex.com/ ����
#endif

#include "MainDlg.h"

#define RES_TYPE 0   //���ļ��м�����Դ
// #define RES_TYPE 1   //��PE��Դ�м���UI��Դ
// #define RES_TYPE 2   //��zip���м�����Դ

#include "../components/resprovider-zip/zipresprovider-param.h"

#ifdef _DEBUG
#define COM_IMGDECODER  _T("imgdecoder-wicd.dll")
#define COM_RENDER_GDI  _T("render-gdid.dll")
#define COM_RENDER_SKIA _T("render-skiad.dll")
#define COM_SCRIPT_LUA _T("scriptmodule-luad.dll")
#define COM_TRANSLATOR _T("translatord.dll")
#define COM_ZIPRESPROVIDER _T("resprovider-zipd.dll")
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define COM_IMGDECODER  _T("imgdecoder-wic.dll")
#define COM_RENDER_GDI  _T("render-gdi.dll")
#define COM_RENDER_SKIA _T("render-skia.dll")
#define COM_SCRIPT_LUA _T("scriptmodule-lua.dll")
#define COM_TRANSLATOR _T("translator.dll")
#define COM_ZIPRESPROVIDER _T("resprovider-zip.dll")
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
    //����Ҫ����OleInitialize����ʼ�����л���
    HRESULT hRes = OleInitialize(NULL);
    SASSERT(SUCCEEDED(hRes));
    
    int nRet = 0; 

    //����һ��������ظ�������
    //SComLoaderʵ�ִ�DLL��ָ��������������SOUIҪ�����COM�����
    SComLoader imgDecLoader;
    SComLoader renderLoader;
    SComLoader transLoader;
    SComLoader scriptLoader;
    SComLoader zipResLoader;
    
    //�����������·���޸ĵ�demo���ڵ�Ŀ¼
    TCHAR szCurrentDir[MAX_PATH]={0};
    GetModuleFileName( NULL, szCurrentDir, sizeof(szCurrentDir) );
    LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
    _tcscpy(lpInsertPos,_T("\\..\\demo"));
    SetCurrentDirectory(szCurrentDir);
    
    {
        //����һ����SOUIϵͳ��ʹ�õ���COM���
        //CAutoRefPtr��һ��SOUIϵͳ��ʹ�õ�����ָ����
        CAutoRefPtr<IImgDecoderFactory> pImgDecoderFactory; //ͼƬ����������imagedecoder-wid.dllģ���ṩ
        CAutoRefPtr<IRenderFactory> pRenderFactory;         //UI��Ⱦģ�飬��render-gdi.dll����render-skia.dll�ṩ
        CAutoRefPtr<ITranslatorMgr> trans;                  //�����Է���ģ�飬��translator.dll�ṩ
        CAutoRefPtr<IScriptModule> pScriptLua;              //lua�ű�ģ�飬��scriptmodule-lua.dll�ṩ
        
        BOOL bLoaded=FALSE;
        int nType=MessageBox(GetActiveWindow(),_T("ѡ����Ⱦ���ͣ�\n[yes]: Skia\n[no]:GDI\n[cancel]:Quit"),_T("select a render"),MB_ICONQUESTION|MB_YESNOCANCEL);
        if(nType == IDCANCEL) return -1;
        //�Ӹ��������ʾ���������������
        bLoaded=renderLoader.CreateInstance(nType==IDYES?COM_RENDER_SKIA:COM_RENDER_GDI,(IObjRef**)&pRenderFactory);
        SASSERT_FMT(bLoaded,_T("load module [%s] failed!"),nType==IDYES?COM_RENDER_SKIA:COM_RENDER_GDI);
        bLoaded=imgDecLoader.CreateInstance(COM_IMGDECODER,(IObjRef**)&pImgDecoderFactory);
        SASSERT_FMT(bLoaded,_T("load module [%s] failed!"),COM_IMGDECODER);
        bLoaded=transLoader.CreateInstance(COM_TRANSLATOR,(IObjRef**)&trans);
        SASSERT_FMT(bLoaded,_T("load module [%s] failed!"),COM_TRANSLATOR);
        //Ϊ��Ⱦģ����������Ҫ���õ�ͼƬ����ģ��
        pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
        //����һ��Ψһ��SApplication����SApplication��������Ӧ�ó������Դ
        SApplication *theApp=new SApplication(pRenderFactory,hInstance);

        //����һ�˸���Դ�ṩ����,SOUIϵͳ��ʵ����3����Դ���ط�ʽ���ֱ��Ǵ��ļ����أ���EXE����Դ���ؼ���ZIPѹ��������
        CAutoRefPtr<IResProvider>   pResProvider;
#if (RES_TYPE == 0)//���ļ�����
        CreateResProvider(RES_FILE,(IObjRef**)&pResProvider);
        if(!pResProvider->Init((LPARAM)_T("uires"),0))
        {
            SASSERT(0);
            return 1;
        }
#elif (RES_TYPE==1)//��EXE��Դ����
        CreateResProvider(RES_PE,(IObjRef**)&pResProvider);
        pResProvider->Init((WPARAM)hInstance,0);
#elif (RES_TYPE==2)//��ZIP������
        bLoaded=zipResLoader.CreateInstance(COM_ZIPRESPROVIDER,(IObjRef**)&pResProvider);
        SASSERT(bLoaded);
        ZIPRES_PARAM param;
        param.ZipFile(pRenderFactory, _T("uires.zip"),"souizip");
        bLoaded = pResProvider->Init((WPARAM)&param,0);
        SASSERT(bLoaded);
#endif
        //��������IResProvider����SApplication����
        theApp->AddResProvider(pResProvider);

        if(trans)
        {//�������Է����
            theApp->SetTranslator(trans);
            pugi::xml_document xmlLang;
            if(theApp->LoadXmlDocment(xmlLang,_T("lang_cn"),_T("translator")))
            {
                CAutoRefPtr<ITranslator> langCN;
                trans->CreateTranslator(&langCN);
                langCN->Load(&xmlLang.child(L"language"),1);//1=LD_XML
                trans->InstallTranslator(langCN);
            }
        }
#ifdef DLL_SOUI
        //����LUA�ű�ģ�飬ע�⣬�ű�ģ��ֻ����SOUI�ں�����DLL��ʽ����ʱ����ʹ�á�
        bLoaded=scriptLoader.CreateInstance(COM_SCRIPT_LUA,(IObjRef**)&pScriptLua);
        SASSERT_FMT(bLoaded,_T("load module [%s] failed!"),COM_SCRIPT_LUA);
        if(pScriptLua)
        {
            theApp->SetScriptModule(pScriptLua);
            size_t sz=pResProvider->GetRawBufferSize(_T("script"),_T("lua_test"));
            if(sz)
            {
                CMyBuffer<char> lua;
                lua.Allocate(sz);
                pResProvider->GetRawBuffer(_T("script"),_T("lua_test"),lua,sz);
                pScriptLua->executeScriptBuffer(lua,sz);
            }
        }
#endif//DLL_SOUI

        //��SApplicationϵͳ��ע�����ⲿ��չ�Ŀؼ���SkinObj��
        SWkeLoader wkeLoader;
        if(wkeLoader.Init(_T("wke.dll")))        
        {
            theApp->RegisterWndFactory(TplSWindowFactory<SWkeWebkit>());//ע��WKE�����
        }
        theApp->RegisterWndFactory(TplSWindowFactory<SGifPlayer>());//ע��GIFPlayer
        theApp->RegisterSkinFactory(TplSkinFactory<SSkinGif>());//ע��SkinGif
        SSkinGif::Gdiplus_Startup();
        
        //����ϵͳ��Դ
        HMODULE hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
        if(hSysResource)
        {
            CAutoRefPtr<IResProvider> sysSesProvider;
            CreateResProvider(RES_PE,(IObjRef**)&sysSesProvider);
            sysSesProvider->Init((WPARAM)hSysResource,0);
            theApp->LoadSystemNamedResource(sysSesProvider);
        }

        //����ȫ����Դ����XML
        theApp->Init(_T("xml_init")); 

        {
            //��������ʾʹ��SOUI����Ӧ�ó��򴰿�,Ϊ�˱��洰�ڶ�������������������󣬰���������һ�㡣
            CMainDlg dlgMain;  
            dlgMain.Create(GetActiveWindow(),0,0,800,600);
            dlgMain.GetNative()->SendMessage(WM_INITDIALOG);
            dlgMain.CenterWindow();
            dlgMain.ShowWindow(SW_SHOWNORMAL);
            nRet=theApp->Run(dlgMain.m_hWnd);
        }
        
        //Ӧ�ó����˳�
        delete theApp; 
        SSkinGif::Gdiplus_Shutdown();

    }

    OleUninitialize();
    return nRet;
}
