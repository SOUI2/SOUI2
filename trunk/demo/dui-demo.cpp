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

//��ʾ���ʹ�������ⲿʵ�ֵ�DUI�ؼ�
class  CDuiListBox2 :public CDuiListBoxEx
{
public:
	SOUI_CLASS_NAME(CDuiListBox2, "listboxex")

};
//����һ��ֻ�����������Ƥ��
class CDuiVScrollBarSkin : public SOUI::CDuiScrollbarSkin
{
	SOUI_CLASS_NAME(CDuiVScrollBarSkin, "vscrollbar")

public:

	CDuiVScrollBarSkin():m_nStates(3)
	{

	}

	virtual void Draw(HDC dc, CRect rcDraw, DWORD dwState,BYTE byAlpha=0xff)
	{
		if(!m_pDuiImg) return;
		int nSbCode=LOWORD(dwState);
		int nState=LOBYTE(HIWORD(dwState));
		BOOL bVertical=HIBYTE(HIWORD(dwState));
		if(bVertical)
		{
			CRect rcMargin(0,0,0,0);
			rcMargin.top=m_nMargin,rcMargin.bottom=m_nMargin;
			CRect rcSour=GetPartRect(nSbCode,nState,bVertical);
			FrameDraw(dc, m_pDuiImg , rcSour,rcDraw,rcMargin, CLR_INVALID, m_uDrawPart,m_bTile,byAlpha);
		}
	}

	//ָʾ������Ƥ���Ƿ�֧����ʾ���¼�ͷ
	virtual BOOL HasArrow(){return FALSE;}
	virtual int GetIdealSize(){
		if(!m_pDuiImg) return 0;
		return m_pDuiImg->GetWidth()/(1+m_nStates);//ͼƬ�ֳ�4 or 5 ���ֺ������У���һ���ǹ����2,3,4,5�ֱ��Ӧ�������������������ѹ, Disable״̬
	}
	SOUO_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("states",m_nStates,FALSE)
		SOUI_ATTRIBUTES_END()
protected:
	//����Դָ��������ԭλͼ�ϵ�λ�á�
	CRect GetPartRect(int nSbCode, int nState,BOOL bVertical)
	{
		CRect rc;
		if(!bVertical || nSbCode==SB_LINEDOWN || nSbCode==SB_LINEUP) return rc;

		rc.right=GetImage()->GetWidth()/(1+m_nStates);
		rc.bottom=GetImage()->GetHeight();

		if(nSbCode == SB_PAGEUP || nSbCode == SB_PAGEDOWN)
		{
			return rc;
		}
		rc.OffsetRect(rc.Width()*(1+nState),0);
		return rc;
	}

	int m_nStates;
};

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
	HRESULT hRes = OleInitialize(NULL);
	DUIASSERT(SUCCEEDED(hRes));

	pugi::xml_node node;
	node.set_name("abc");
#if !defined(_WIN64)
//#if 0
	//<--��Դ����ѡ�� 
	DuiSystem * pDuiModeSel = new DuiSystem(hInstance);
	DuiSystem::getSingletonPtr();

	DuiResProviderZip *pResModeSel= new DuiResProviderZip;
	pResModeSel->Init(hInstance,MAKEINTRESOURCE(IDR_ZIP_MODESEL),_T("ZIP"));
	pDuiModeSel->SetDefResProvider(pResModeSel);

	pDuiModeSel->Init(_T("xml_init"));

	int nMode=-1;
 	{
 		CResModeSelDlg dlgModeSel;  
 		if(IDOK==dlgModeSel.DoModal())
 		{
 			nMode=dlgModeSel.m_nMode;
 		}
 	}
//	delete pResModeSel;
	delete pDuiModeSel->GetDefResProvider();
	delete pDuiModeSel;

	if(nMode==-1) return -1;
#else
	int nMode=0;	//64λʱֱ�Ӵ��ļ�������Դ
#endif
	//��Դ����ѡ����� -->
	
	DuiSystem *pDuiSystem=new DuiSystem(hInstance);

	//���ɿؼ��೧��ע�ᵽϵͳ
	pDuiSystem->RegisterWndFactory(TplDuiWindowFactory<CDuiListBox2>(),true);

	//����Ƥ���೧��ע�ᵽϵͳ
	pDuiSystem->RegisterSkinFactory(TplSkinFactory<CDuiVScrollBarSkin>());
	pDuiSystem->RegisterSkinFactory(TplSkinFactory<CDuiSkinGif>());


	TCHAR szCurrentDir[MAX_PATH]; memset( szCurrentDir, 0, sizeof(szCurrentDir) );
	GetModuleFileName( NULL, szCurrentDir, sizeof(szCurrentDir) );
	LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
	*lpInsertPos = _T('\0');   

	DefaultLogger loger;
	loger.setLogFilename(CDuiStringT(szCurrentDir)+_T("\\dui-demo.log")); 
	pDuiSystem->SetLogger(&loger);

	//����ѡ�����Դ����ģʽ����resprovider 
	switch(nMode)
	{
	case 0://load from files
		{
			_tcscat( szCurrentDir, _T("\\..\\demo") );
			DuiResProviderFiles *pResFiles=new DuiResProviderFiles;
			if(!pResFiles->Init(szCurrentDir))
			{
				DUIASSERT(0);
				return 1;
			}
			pDuiSystem->SetDefResProvider(pResFiles);
			pDuiSystem->logEvent(_T("load resource from files"));
		}
		break;
	case 1://load from PE
		{
			pDuiSystem->SetDefResProvider(new DuiResProviderPE(hInstance));
			pDuiSystem->logEvent(_T("load resource from exe"));
		}
		break;
	default://load form ZIP
		{
#if !defined(_WIN64)
			//��ZIP�ļ�����Ƥ��
			DuiResProviderZip *zipSkin=new DuiResProviderZip;
			CDuiStringT strZip=CDuiStringT(szCurrentDir)+_T("\\def_skin.zip");
			if(!zipSkin->Init(strZip))
			{ 
				DUIASSERT(0);
				return 1;
			}
			pDuiSystem->SetDefResProvider(zipSkin); 
			pDuiSystem->logEvent(_T("load resource from zip"));
#else
			return -1;
#endif;
		}
		break;
	}

	BOOL bOK=pDuiSystem->Init(_T("IDR_DUI_INIT")); //��ʼ��DUIϵͳ,ԭ����ϵͳ��ʼ����ʽ��Ȼ����ʹ�á�
	pDuiSystem->SetMsgBoxTemplate(_T("IDR_DUI_MSGBOX"));

#ifdef LUA_TEST
	CLuaScriptModule scriptLua;
	scriptLua.executeScriptFile("..\\dui_demo\\lua\\test.lua");
	pDuiSystem->SetScriptModule(&scriptLua);
#endif

	CMenuWndHook::InstallHook(hInstance,"skin_menuborder");
	int nRet = 0; 
	// BLOCK: Run application
	{
		pDuiSystem->logEvent(_T("demo started"));
		CMainDlg dlgMain;  
		nRet = dlgMain.DoModal();  
		pDuiSystem->logEvent(_T("demo end"));
	}


	delete pDuiSystem->GetDefResProvider();
	//�ͷ���Դ 
	CMenuWndHook::UnInstallHook();

	delete pDuiSystem;

	OleUninitialize();
	return nRet;
}
