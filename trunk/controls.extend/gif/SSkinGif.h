/********************************************************************
created:	2012/12/27
created:	27:12:2012   14:55
filename: 	DuiSkinGif.h
file base:	DuiSkinGif
file ext:	h
author:		huangjianxiong

purpose:	�Զ���Ƥ������
*********************************************************************/
#pragma once
#include <interface/SSkinobj-i.h>
#include <unknown/obj-ref-impl.hpp>

namespace Gdiplus
{
class Bitmap;
}
namespace SOUI
{
    class SGifFrame
    {
    public:
        CAutoRefPtr<IBitmap> pBmp;
        int                  nDelay;
    };

    
    class SSkinGif : public ISkinObj
    {
        SOUI_CLASS_NAME(SSkinGif, L"gif")
    public:
        SSkinGif():m_nFrames(0),m_iFrame(0),m_pFrames(NULL)
        {

        }

        static BOOL Gdiplus_Startup();
        static void Gdiplus_Shutdown();

        virtual ~SSkinGif()
        {
            if(m_pFrames) delete [] m_pFrames;
        }

        virtual void Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha=0xFF);

        virtual int GetStates(){return m_nFrames;}
        virtual SIZE GetSkinSize()
        {
            SIZE sz={0};
            if(m_nFrames>0 && m_pFrames)
            {
                sz=m_pFrames[0].pBmp->Size();
            }
            return sz;
        }

        long GetFrameDelay(int iFrame=-1);
        void ActiveNextFrame();
        void SelectActiveFrame(int iFrame);
        
        int LoadFromFile(LPCTSTR pszFileName);
        int LoadFromMemory(LPVOID pBits,size_t szData);

        SOUI_ATTRS_BEGIN()
            ATTR_CUSTOM(L"src",OnAttrSrc)
        SOUI_ATTRS_END()
    protected:
        LRESULT OnAttrSrc(const SStringW &strValue,BOOL bLoading);
        int LoadFromGdipImage(Gdiplus::Bitmap * pImg);
        int m_nFrames;
        int m_iFrame;

        SGifFrame * m_pFrames;
    };
}//end of name space SOUI
