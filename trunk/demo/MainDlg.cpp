// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "helper/SMenu.h"
#include "../controls.extend/FileHelper.h"

#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")

CMainDlg::CMainDlg() : SHostWnd(_T("maindlg"))
{
	m_bLayoutInited=FALSE;
} 

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	// 		MARGINS mar = {5,5,30,5};
	// 		DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	SetMsgHandled(FALSE);
	return 0;
}

void CMainDlg::OnShowWindow( BOOL bShow, UINT nStatus )
{
	if(bShow)
	{
 		AnimateHostWindow(200,AW_CENTER);
	}
}

struct student{
    TCHAR szName[100];
    TCHAR szSex[10];
    int age;
    int score;
};

//init listctrl
void CMainDlg::InitListCtrl()
{
    SListCtrl *pList=FindChildByName2<SListCtrl>(L"lc_test");
    if(pList)
    {
        SWindow *pHeader=pList->GetWindow(GSW_FIRSTCHILD);
        pHeader->GetEventSet()->subscribeEvent(EVT_HEADER_CLICK,Subscriber(&CMainDlg::OnListHeaderClick,this));

        TCHAR szSex[][5]={_T("��"),_T("Ů"),_T("����")};
        for(int i=0;i<100;i++)
        {
            student *pst=new student;
            _stprintf(pst->szName,_T("ѧ��_%d"),i+1);
            _tcscpy(pst->szSex,szSex[rand()%3]);
            pst->age=rand()%30;
            pst->score=rand()%60+40;

            int iItem=pList->InsertItem(i,pst->szName);
            pList->SetItemData(iItem,(DWORD)pst);
            pList->SetSubItemText(iItem,1,pst->szSex);
            TCHAR szBuf[10];
            _stprintf(szBuf,_T("%d"),pst->age);
            pList->SetSubItemText(iItem,2,szBuf);
            _stprintf(szBuf,_T("%d"),pst->score);
            pList->SetSubItemText(iItem,3,szBuf);
        }
    }
}

int funCmpare(void* pCtx,const void *p1,const void *p2)
{
    int iCol=*(int*)pCtx;

    const DXLVITEM *plv1=(const DXLVITEM*)p1;
    const DXLVITEM *plv2=(const DXLVITEM*)p2;

    const student *pst1=(const student *)plv1->dwData;
    const student *pst2=(const student *)plv2->dwData;

    switch(iCol)
    {
    case 0://name
        return _tcscmp(pst1->szName,pst2->szName);
    case 1://sex
        return _tcscmp(pst1->szSex,pst2->szSex);
    case 2://age
        return pst1->age-pst2->age;
    case 3://score
        return pst1->score-pst2->score;
    default:
        return 0;
    }
}

bool CMainDlg::OnListHeaderClick(EventArgs *pEvtBase)
{
    EventHeaderClick *pEvt =(EventHeaderClick*)pEvtBase;
    SHeaderCtrl *pHeader=(SHeaderCtrl*)pEvt->sender;
    SListCtrl *pList=FindChildByName2<SListCtrl>(L"lc_test");

    SHDITEM hditem;
    hditem.mask=SHDI_ORDER;
    pHeader->GetItem(pEvt->iItem,&hditem);
    pList->SortItems(funCmpare,&hditem.iOrder);
    return true;
}

void CMainDlg::OnDestory()
{
    SListCtrl *pList=FindChildByName2<SListCtrl>(L"lc_test");
    if(pList)
    {
        for(int i=0;i<pList->GetItemCount();i++)
        {
            student *pst=(student*) pList->GetItemData(i);
            delete pst;
        }
    }
    SetMsgHandled(FALSE); 
}


LRESULT CMainDlg::OnInitDialog( HWND hWnd, LPARAM lParam )
{
    m_bLayoutInited=TRUE;
    InitListCtrl();
    
    SWindow *pTst=FindChildByName(L"btn_tstevt");
    if(pTst) SApplication::getSingleton().GetScriptModule()->subscribeEvent(pTst,EVT_CMD,"onEvtTstClick");

    return 0;
}

#ifdef SUPPORT_WKE
void CMainDlg::OnBtnWebkitGo()
{
    SWkeWebkit *pWebkit= FindChildByName2<SWkeWebkit>(L"wke_test");
    if(pWebkit)
    {
        SEdit *pEdit=FindChildByName2<SEdit>(L"edit_url");
        SStringW strUrl=pEdit->GetWindowText();
        pWebkit->SetAttribute(L"url",strUrl,FALSE);
    }
}

void CMainDlg::OnBtnWebkitBackward()
{
    SWkeWebkit *pWebkit= FindChildByName2<SWkeWebkit>(L"wke_test");
    if(pWebkit)
    {
        wkeGoBack(pWebkit->GetWebView());
    }
}

void CMainDlg::OnBtnWebkitForeward()
{
    SWkeWebkit *pWebkit= FindChildByName2<SWkeWebkit>(L"wke_test");
    if(pWebkit)
    {
        wkeGoForward(pWebkit->GetWebView());
    }
}

void CMainDlg::OnBtnWebkitRefresh()
{
    SWkeWebkit *pWebkit= FindChildByName2<SWkeWebkit>(L"wke_test");
    if(pWebkit)
    {
    }
}


#endif//SUPPORT_WKE

void CMainDlg::OnBtnSelectGIF()
{
    SGifPlayer *pGifPlayer = FindChildByName2<SGifPlayer>(L"giftest");
    if(pGifPlayer)
    {
        CFileDialogEx openDlg(TRUE,_T("gif"),0,6,_T("gif files(*.gif)\0*.gif\0All files (*.*)\0*.*\0\0"));
        if(openDlg.DoModal()==IDOK)
            pGifPlayer->PlayGifFile(openDlg.m_szFileName);
    }
}

void CMainDlg::OnBtnMenu()
{
    SMenu menu;
    menu.LoadMenu(_T("menu_test"),_T("LAYOUT"));
    POINT pt;
    GetCursorPos(&pt);
    menu.TrackPopupMenu(0,pt.x,pt.y,m_hWnd);
}

//��ʾ�����Ӧ�˵��¼�
void CMainDlg::OnCommand( UINT uNotifyCode, int nID, HWND wndCtl )
{
    if(uNotifyCode==0 && nID==6)
    {//nID==6��Ӧmenu_test����Ĳ˵���exit�
        PostMessage(WM_CLOSE);
    }
}
