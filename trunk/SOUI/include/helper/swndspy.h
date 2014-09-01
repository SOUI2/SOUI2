#pragma once

#define SPYMSG_SETSPY    (WM_USER+1000)     //����SPY��Ϣ���մ��ھ��

#define SPYMSG_SWNDENUM  (WM_USER+1001)     //ö�ٴ����б�,wparam:SWND,lparam:SWindow::GetWindow
                                            //���ش��ڵ�SWNDֵ

#define SPYMSG_SWNDINFO  (WM_USER+1002)      //��ȡ�������ԣ�wparam:swnd,lparam:Cookie

#define SWND_MAX_NAME   250
#define SWND_MAX_CLASS  50
#define SWND_MAX_XML    500

#pragma pack(push,1)
struct SWNDINFO
{
    DWORD swnd;
    RECT rcWnd;
    RECT rcClient;
    BOOL bVisible;
    int  nID;
    wchar_t szName[SWND_MAX_NAME+1];
    wchar_t szClassName[SWND_MAX_CLASS+1];
    wchar_t szXmlStr[SWND_MAX_XML+1];
};
#pragma pack(pop)