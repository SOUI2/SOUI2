// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "DuiSystem.h" 

#ifdef _DEBUG
#include <vld.h>//ʹ��Vitural Leaker Detector������ڴ�й©�����Դ�http://vld.codeplex.com/ ����
#endif

#include "MainDlg.h"


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = OleInitialize(NULL);
	DUIASSERT(SUCCEEDED(hRes));

#ifdef _DEBUG
    HMODULE hRenderSkia = LoadLibrary(_T("render-skia_d.dll"));
#else
    HMODULE hRenderSkia = LoadLibrary(_T("render-skia.dll"));
#endif
    typedef BOOL (*fnCreateRenderFactory)(SOUI::IRenderFactory **);
    fnCreateRenderFactory fun = (fnCreateRenderFactory)GetProcAddress(hRenderSkia,"CreateRenderFactory");

    CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
    fun(&pRenderFactory);

	DuiSystem *pDuiSystem=new DuiSystem(pRenderFactory,hInstance);

#if 1
    TCHAR szCurrentDir[MAX_PATH]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
    GetModuleFileName( NULL, szCurrentDir, sizeof(szCurrentDir) );
    LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
    *lpInsertPos = _T('\0');   
    _tcscat( szCurrentDir, _T("\\..\\demo\\skin") );

    DuiResProviderFiles *pResProvider=new DuiResProviderFiles;
    if(!pResProvider->Init(szCurrentDir))
    {
        DUIASSERT(0);
        return 1;
    }
#else
    DuiResProviderPE *pResProvider = new DuiResProviderPE(hInstance);
#endif
    
    pDuiSystem->AddResProvider(pResProvider);

	BOOL bOK=pDuiSystem->Init(_T("IDR_DUI_INIT")); //��ʼ��DUIϵͳ,ԭ����ϵͳ��ʼ����ʽ��Ȼ����ʹ�á�
	pDuiSystem->SetMsgBoxTemplate(_T("IDR_DUI_MSGBOX"));

	int nRet = 0; 
	// BLOCK: Run application
	{
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
	}



	delete pDuiSystem;
    
    delete pResProvider;
    
    pRenderFactory=NULL;
    
	OleUninitialize();
	return nRet;
}
