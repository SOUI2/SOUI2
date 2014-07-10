// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once

// #include "UIHander.h"
#include "wtlhelper/whwindow.h"

class CMainDlg : public SHostWnd
// 	,public CWHRoundRectFrameHelper<CMainDlg>	//��ҪԲ�Ǵ���ʱ����
{
public:
	CMainDlg();
	~CMainDlg();

	void OnClose()
	{
		AnimateHostWindow(200,AW_CENTER|AW_HIDE);
        PostMessage(WM_QUIT);
	}
	void OnMaximize()
	{
		GetNative()->SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
	}
	void OnRestore()
	{
		GetNative()->SendMessage(WM_SYSCOMMAND,SC_RESTORE);
	}
	void OnMinimize()
	{
		GetNative()->SendMessage(WM_SYSCOMMAND,SC_MINIMIZE);
	}

	void OnSize(UINT nType, CSize size)
	{
		SetMsgHandled(FALSE);
		if(!m_bLayoutInited) return;
		if(nType==SIZE_MAXIMIZED)
		{
			FindChildByID(3)->SetVisible(TRUE);
			FindChildByID(2)->SetVisible(FALSE);
		}else if(nType==SIZE_RESTORED)
		{
			FindChildByID(3)->SetVisible(FALSE);
			FindChildByID(2)->SetVisible(TRUE);
		}
	}
    void OnBtnMsgBox()
    {
        SMessageBox(NULL,L"this is a message box",L"haha",MB_OK|MB_ICONEXCLAMATION);
    }
    
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnShowWindow(BOOL bShow, UINT nStatus);


protected:
    void InitListCtrl();
    bool OnListHeaderClick(EventArgs *pEvt);
    
    LRESULT OnInitDialog(HWND hWnd, LPARAM lParam);
    void OnDestory();

	BOOL OnEditMenu(CPoint pt)
	{
		//��ʾ����edit_1140���Ҽ��˵�
		return TRUE;
	}
	

	EVENT_MAP_BEGIN()
		EVENT_ID_COMMAND(1, OnClose)
		EVENT_ID_COMMAND(2, OnMaximize)
		EVENT_ID_COMMAND(3, OnRestore)
		EVENT_ID_COMMAND(5, OnMinimize)
		EVENT_NAME_CONTEXTMENU(L"edit_1140",OnEditMenu)
		EVENT_NAME_COMMAND(L"btn_msgbox",OnBtnMsgBox)
	EVENT_MAP_END()	

	BEGIN_MSG_MAP_EX(CMainDlg)
// 		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CMainDlg>) //��ҪԲ�Ǵ���ʱ����
		MSG_WM_CREATE(OnCreate)
        MSG_WM_INITDIALOG(OnInitDialog)
        MSG_WM_DESTROY(OnDestory)
		MSG_WM_CLOSE(OnClose)
		MSG_WM_SIZE(OnSize)
		MSG_WM_SHOWWINDOW(OnShowWindow)
// 		CHAIN_MSG_MAP_MEMBER((*m_pUiHandler))
		CHAIN_MSG_MAP(SHostWnd)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
private:
	BOOL			m_bLayoutInited;
	int				m_iStep;
//	CUIHander *    m_pUiHandler; 
};
