// dllmain.cpp : DllMain ��ʵ�֡�

#include "souistd.h"

#if defined(USING_ATL) && defined(DLL_SOUI)
//ֻ��ʹ��ATL�Ķ�̬��汾����ҪDllMain

class CSOUIModule : public CAtlDllModuleT< CSOUIModule >
{
} _AtlModule;

// DLL ��ڵ�
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    return _AtlModule.DllMain(dwReason, lpReserved); 
}

#endif