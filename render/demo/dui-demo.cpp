// dui-demo.cpp : main source file
//

#include "stdafx.h"
#include "menuwndhook.h"
#include "DuiSystem.h" 
#include "DuiDefaultLogger.h"

#include "DuiSkinGif.h"	//Ӧ�ò㶨���Ƥ������

//��ZIP�ļ�����Ƥ��ģ��
#if !defined(_WIN64)
#include "zipskin/DuiResProviderZip.h"
#endif

#ifdef _DEBUG
#include <vld.h>//ʹ��Vitural Leaker Detector������ڴ�й©�����Դ�http://vld.codeplex.com/ ����
#endif

#include "MainDlg.h"
#include "ResModeSelDlg.h"


int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = OleInitialize(NULL);
	DUIASSERT(SUCCEEDED(hRes));


	
	DuiSystem *pDuiSystem=new DuiSystem(hInstance);


	TCHAR szCurrentDir[MAX_PATH]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileName( NULL, szCurrentDir, sizeof(szCurrentDir) );
	LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
	*lpInsertPos = _T('\0');   

    _tcscat( szCurrentDir, _T("\\..\\demo") );
    DuiResProviderFiles *pResFiles=new DuiResProviderFiles;
    if(!pResFiles->Init(szCurrentDir))
    {
        DUIASSERT(0);
        return 1;
    }

	BOOL bOK=pDuiSystem->Init(_T("IDR_DUI_INIT")); //��ʼ��DUIϵͳ,ԭ����ϵͳ��ʼ����ʽ��Ȼ����ʹ�á�
	pDuiSystem->SetMsgBoxTemplate(_T("IDR_DUI_MSGBOX"));

	int nRet = 0; 
	// BLOCK: Run application
	{
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
	}


	delete pDuiSystem->GetDefResProvider();

	delete pDuiSystem;

	OleUninitialize();
	return nRet;
}
