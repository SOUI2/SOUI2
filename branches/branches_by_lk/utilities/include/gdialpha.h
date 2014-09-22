#pragma once

#include "utilities-def.h"

namespace SOUI
{

#define  MAX_ALPHABUF    1<<16

typedef struct tagALPHAINFO
{
    BITMAP bm;
    LPBYTE lpBuf;
    RECT    rc;
    tagALPHAINFO()
    {
        lpBuf=NULL;
        rc.left=rc.top=rc.right=rc.bottom=0;
    }
} ALPHAINFO,* LPALPHAINFO;

class UTILITIES_API CGdiAlpha
{
private:
    static BYTE s_byAlphaBack[MAX_ALPHABUF];

    static LPBYTE ALPHABACKUP(BITMAP *pBitmap,int x,int y,int cx,int cy);
    //�ָ�λͼ��Alphaͨ��
    static void ALPHARESTORE(BITMAP *pBitmap,int x,int y,int cx,int cy,LPBYTE lpAlpha);
public:

    static BOOL AlphaBackup(HDC hdc,LPCRECT pRect,ALPHAINFO &alphaInfo);

    static void AlphaRestore(ALPHAINFO &alphaInfo);
};

}//namespace SOUI