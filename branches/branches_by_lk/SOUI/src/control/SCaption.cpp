/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 * 
 * @file       DuiCaption.cpp
 * @brief      ��ǩ�ؼ�
 * @version    v1.0      
 * @author     soui      
 * @date       2014-05-28
 * 
 * Describe    ������ɱ������ؼ�
 */
#include "souistd.h"
#include "control/SCaption.h"

namespace SOUI
{

SCaption::SCaption(void)
:m_bIsMaxDown(FALSE)
{
}

SCaption::~SCaption(void)
{
}

void SCaption::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bIsMaxDown = FALSE;
}

void SCaption::OnMouseMove(UINT nFlags, CPoint point)
{
	HWND hHost=GetContainer()->GetHostHwnd();
    if (WS_MAXIMIZE == (GetWindowLong(hHost,GWL_STYLE) & WS_MAXIMIZE) && m_bIsMaxDown && IsSuppotMaxMove())
	{
		::SendMessage(hHost,WM_SYSCOMMAND, SC_MOVE | HTCAPTION,0);

		m_bIsMaxDown = FALSE;

		return;
	}
}
void SCaption::OnLButtonDown( UINT nFlags, CPoint point )
{
    HWND hHost=GetContainer()->GetHostHwnd();
    if (WS_MAXIMIZE == (GetWindowLong(hHost,GWL_STYLE) & WS_MAXIMIZE))
	{
		m_bIsMaxDown = TRUE;
		return;
	}
    ::SendMessage(hHost,WM_SYSCOMMAND, SC_MOVE | HTCAPTION,0);
}

void SCaption::OnLButtonDblClk( UINT nFlags, CPoint point )
{
    HWND hHost=GetContainer()->GetHostHwnd();

    if (GetWindowLong(hHost,GWL_STYLE) & WS_THICKFRAME)
    {
        if (WS_MAXIMIZE == (GetWindowLong(hHost,GWL_STYLE) & WS_MAXIMIZE))
            ::SendMessage(hHost,WM_SYSCOMMAND, SC_RESTORE | HTCAPTION,0);
        else
            ::SendMessage(hHost,WM_SYSCOMMAND, SC_MAXIMIZE | HTCAPTION,0);
    }
}

BOOL SCaption::IsSuppotMaxMove()
{
	OSVERSIONINFOEX OSVerInfo;
	BOOL bOsVersionInfoEx;

	::ZeroMemory(&OSVerInfo,sizeof(OSVERSIONINFOEX));

	// Get the OS Version Information
	OSVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	if(!(bOsVersionInfoEx = ::GetVersionEx((OSVERSIONINFO *)&OSVerInfo)))
	{
		OSVerInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		if (!::GetVersionEx((OSVERSIONINFO *)&OSVerInfo)) 
		{
			return FALSE;
		}
	}
	
	/**
	 * Does it support Windows 8.1,Windows 8,Windows 7,Windows Vista ?
	 * I just ignore the Windows Server System
	 * if you wanna get more information, you can click the following link:
	 *			http://msdn.microsoft.com/en-us/library/ms724833.aspx
	 */
	if (OSVerInfo.wProductType == VER_NT_WORKSTATION
		&& OSVerInfo.dwMajorVersion == 6)
	{
		return TRUE;
	}
	return FALSE;
}

}//namespace SOUI

