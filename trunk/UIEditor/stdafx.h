// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

#include <duistd.h>
#include <duihostwnd.h>
#include <duictrls.h>
#include <duiwndnotify.h>
#include <DuiCSS.h>

#include "resource.h"	//win32 id

#include "FileHelper.h"

using namespace SOUI;
using namespace pugi;

#include "UIHelper.h"
#include "SkinView.h"
#include "colorpicker/DuiColorPicker.h"

#ifdef _DEBUG
	#ifdef DLL_SOUI
#pragma  message("link to soui_d.lib")
	# pragma comment(lib, "soui_d.lib")
	#else
#pragma  message("link to soui_static_d.lib")
	# pragma comment(lib, "soui_static_d.lib")
	#endif
#else
	#ifdef DLL_SOUI
#pragma  message("link to soui.lib")
	# pragma comment(lib, "soui.lib")
	#else
#pragma  message("link to soui_static.lib")
	# pragma comment(lib, "soui_static.lib")
	#endif

#endif





