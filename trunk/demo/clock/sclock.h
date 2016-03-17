#pragma once

using namespace SOUI;

#include "helper/SMatrix.h"

namespace SOUI{

class SClock : public SWindow
{
	SOUI_CLASS_NAME(SClock, L"clock")

public:
	SClock();

	enum {TIMER_REFRESH = 1};

protected:
    SMatrix InitMatrix(double angle, CPoint &center);

    double GetMinuteSecondAngle(int nValue);
    double GetHourAngle(int nHour,int nMinute);

protected:
	int  OnCreate(void*);
	void OnPaint(SOUI::IRenderTarget * pRT);
	void OnTimer(char cTimerID);

	SOUI_MSG_MAP_BEGIN()
		MSG_WM_PAINT_EX(OnPaint)
		MSG_WM_TIMER_EX(OnTimer)
		MSG_WM_CREATE(OnCreate)
	SOUI_MSG_MAP_END()

protected:
	SOUI_ATTRS_BEGIN()
		ATTR_IMAGE(L"pointer_hour",   pointer_hour, TRUE)
		ATTR_IMAGE(L"pointer_minute", pointer_minute, TRUE)
		ATTR_IMAGE(L"pointer_second", pointer_second, TRUE)
	SOUI_ATTRS_END()

	SOUI::IBitmap* pointer_hour;
	SOUI::IBitmap* pointer_minute;
	SOUI::IBitmap* pointer_second;
};

}