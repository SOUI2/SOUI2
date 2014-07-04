/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
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
{
}

SCaption::~SCaption(void)
{
}

void SCaption::OnLButtonDown( UINT nFlags, CPoint point )
{
    HWND hHost=GetContainer()->GetHostHwnd();
    if (WS_MAXIMIZE == (GetWindowLong(hHost,GWL_STYLE) & WS_MAXIMIZE)) return;
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


}//namespace SOUI

