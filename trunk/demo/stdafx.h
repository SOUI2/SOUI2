// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#if DLL_SOUI
#define SUPPORT_LUA     //��SUPPORT_LUA����ʾ�����SOUI�к�LUA����,LUA��������DLL�����SOUI��ֻ�ж�����DLL_SOUI���ܴ��������
#endif
//#define SUPPORT_WKE      //��Ҫ��third-part/wke/wke.7z��ѹ��binĿ¼���ܴ򿪸ÿ��ز���wkeWebkit

#include <souistd.h>
#include <core/SHostDialog.h>
#include <control/SMessageBox.h>
#include <control/souictrls.h>
#include <res.mgr/sobjdefattr.h>

#include "resource.h"	//APP��Դ

#ifdef SUPPORT_WKE
#include "../controls.extend/SWkeWebkit.h"
#endif

#include "../controls.extend/gif/SGifPlayer.h"


using namespace SOUI;

#ifdef _DEBUG
	# pragma comment(lib, "souid.lib")
#else
	# pragma comment(lib, "soui.lib")
#endif


