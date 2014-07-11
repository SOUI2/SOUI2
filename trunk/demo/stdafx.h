// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#define SUPPORT_LUA     //��SUPPORT_LUA����ʾ�����SOUI�к�LUA������

#include <souistd.h>
#include <core/SHostDialog.h>
#include <control/SMessageBox.h>
#include <control/souictrls.h>
#include <res.mgr/sobjdefattr.h>

#include "resource.h"	//APP��Դ

using namespace SOUI;

#ifdef _DEBUG
	#ifdef USING_ATL
	# pragma comment(lib, "soui_static_atl_d.lib")
	#elif DLL_SOUI
	# pragma comment(lib, "soui_d.lib")
	#else
	# pragma comment(lib, "soui_static_d.lib")
	#endif
#else
	#ifdef DLL_SOUI
	# pragma comment(lib, "soui.lib")
	#else
	# pragma comment(lib, "soui_static.lib")
	#endif

#endif


