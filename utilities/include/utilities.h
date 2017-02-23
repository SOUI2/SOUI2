#pragma once

#include "utilities-def.h"
#include "string/tstring.h"

namespace SOUI
{
    void UTILITIES_API SHiMetricToPixel(const SIZEL * lpSizeInHiMetric, LPSIZEL lpSizeInPix);
    void UTILITIES_API SPixelToHiMetric(const SIZEL * lpSizeInPix, LPSIZEL lpSizeInHiMetric);

	float UTILITIES_API SPx2Dp(int nPx, bool bVert,HWND hwnd = NULL);
	int  UTILITIES_API SDp2Px(float fDp,bool bVert,HWND hwnd = NULL);

}//end of namespace SOUI
