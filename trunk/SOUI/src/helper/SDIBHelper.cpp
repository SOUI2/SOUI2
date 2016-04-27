#include "souistd.h"
#include "helper/SDIBHelper.h"

namespace SOUI
{
    enum{Red,Green,Blue};

    struct DIBINFO{
        LPBYTE  pBits;
        int     nWid;
        int     nHei;
    };

	// ------------------------------------------------------------
	// ��̫����㷨��Ҫ��ĳ�ַ�ʽ(map)�任λͼ��ÿ�����ص���ɫ������
	// ��ɫת��Ϊ�Ҷ�ͼ��gammaУ������ɫ�ռ�ת��,hsl����.����дһ��ģ����Ϊ�������õ�ͨ���㷨
	// ------------------------------------------------------------
	template <class Mode, class Param>
	bool ColorTransform(DIBINFO* pDib, Mode mode, const Param &param)
	{
		if (NULL == pDib||NULL == pDib->pBits)
		{
			return false;
		}
        
        int nPixels = pDib->nWid * pDib->nHei;
        LPBYTE pBit = pDib->pBits;
        for(int i=0;i<nPixels;i++, pBit+=4)
        {
            mode(pBit[2], pBit[1], pBit[0], param);
        }

		return true;
	}

	// �Ҷ� = 0.299 * red + 0.587 * green + 0.114 * blue 
	inline void MaptoGray(BYTE & red, BYTE & green, BYTE & blue, const int &)
	{
		red   = (red * 77 + green * 150 + blue * 29 + 128) / 256;
		green = red;
		blue  = red;
	}

    struct HSL32PARAM
    {
        int degHue;
        int perSaturation;
        int perLuminosity;
    };
    
    inline void AdjustPixelHSL(BYTE & red, BYTE & green, BYTE & blue,const HSL32PARAM & param)
    {
        float H = 0.0f;
        float S = 0.0f;
        float L = 0.0f;	

        SDIBHelper::RGBtoHSL(red,green,blue,
            H, S, L);

        H += param.degHue;
        S = (S*(float)param.perSaturation/100.0f);
        L = (L*(float)param.perLuminosity/100.0f);

        SDIBHelper::HSLtoRGB(H, S, L, red,green,blue);
    }
    
	bool SDIBHelper::AdjustHSL32(IBitmap * pBmp,int degHue,int perSaturation,int perLuminosity)
	{
        DIBINFO di={(LPBYTE)pBmp->LockPixelBits(),pBmp->Width(),pBmp->Height()};

		bool bRet = false;
		do 
		{
			if (perSaturation < 0||perLuminosity < 0)
			{
				break;
			}

			if (degHue == 0 && perSaturation == 100 && perLuminosity == 100)
			{
				bRet = true;// δ��������ֱ�ӷ���
				break;
			}
            
            HSL32PARAM param={degHue,perSaturation,perLuminosity};
            bRet =ColorTransform(&di, AdjustPixelHSL,param);
            
		} while (false);
		
		pBmp->UnlockPixelBits(di.pBits);
		return bRet;
	}

    bool SDIBHelper::AdjustHue(IBitmap *pBmp,COLORREF crRef)
    {
        float h,s,l;
        BYTE r=GetRValue(crRef),g=GetGValue(crRef),b=GetBValue(crRef);
        RGBtoHSL(r,g,b,h,s,l);
        return AdjustHSL32(pBmp,(int)h,100,100);
    }

    bool SDIBHelper::AdjustHue(COLORREF & crTarget,COLORREF crRef)
    {
        float h,s,l;
        BYTE r=GetRValue(crRef),g=GetGValue(crRef),b=GetBValue(crRef);
        RGBtoHSL(r,g,b,h,s,l);
        if(h == 0) return true;// δ��������ֱ�ӷ���

        HSL32PARAM param={(int)h,100,100};

        r=GetRValue(crTarget),g=GetGValue(crTarget),b=GetBValue(crTarget);

        AdjustPixelHSL(r,g,b,param);
        crTarget = RGBA(r,g,b,GetAValue(crTarget));

        return true;
    }   

	bool SDIBHelper::GrayImage(IBitmap * pBmp)
	{
	    DIBINFO di={(LPBYTE)pBmp->LockPixelBits(),pBmp->Width(),pBmp->Height()};
		bool bRet =ColorTransform(&di, MaptoGray,0);
		pBmp->UnlockPixelBits(di.pBits);
		return bRet;
	}
	

	void SDIBHelper::RGBtoHSL(const BYTE &red, const BYTE &green, const BYTE &blue,
		                      float &hue, float &saturation, float &lightness)
	{
		float mn  = 0.0f;
		float mx  = 0.0f; 
		int	major = Red;

		if (red < green)
		{
			mn = red; 
			mx = green;
			major = Green;
		}
		else
		{
			mn = green;
			mx = red; 
			major = Red;
		}

		if (blue < mn)
		{
			mn = blue;
		}
		else if (blue > mx)
		{
			mx = blue;
			major = Blue;
		}

		if (mn == mx) 
		{
			lightness    = mn/255.0f;
			saturation   = 0;
			hue          = 0; 
		}   
		else 
		{ 
			lightness = (mn+mx) / 510.0f;

			if (lightness <= 0.5f)
			{
				saturation = (mx-mn) / (mn+mx); 
			}
			else
			{
				saturation = (mx-mn) / (510.0f-mn-mx);
			}

			switch (major)
			{
			case Red:
				hue = (green-blue) * 60 / (mx-mn) + 360; 
				break;

			case Green: 
				hue = (blue-red) * 60  / (mx-mn) + 120;  
				break;

			case Blue : hue = (red-green) * 60 / (mx-mn) + 240;
				break;
			}

			if (hue >= 360.0f)
			{
				hue = hue - 360.0f;
			}
		}
	}

	unsigned char Value(float m1, float m2, float h)
	{
		while (h >= 360.0f) 
		{
			h -= 360.0f;
		}
		while (h < 0) 
		{
			h += 360.0f;
		}

		if (h < 60.0f) 
		{
			m1 = m1 + (m2 - m1) * h / 60;   
		}
		else if (h < 180.0f) 
		{
			m1 = m2;
		}
		else if (h < 240.0f) 
		{
			m1 = m1 + (m2 - m1) * (240 - h) / 60;  
		}

		return (unsigned char)(m1 * 255);
	}


	void SDIBHelper::HSLtoRGB(const float &hue, const float &_saturation, const float &_lightness,
		                      BYTE &red, BYTE &green, BYTE &blue)
	{
		float lightness = min(1.0f, _lightness);
		float saturation = min(1.0f, _saturation);

		if (saturation == 0)
		{
			red = green = blue = (unsigned char) (lightness*255);
		}
		else
		{
			float m1, m2;

			if (lightness <= 0.5f)
			{
				m2 = lightness + lightness * saturation;  
			}
			else       
			{
				m2 = lightness + saturation - lightness * saturation;
			}

			m1 = 2 * lightness - m2;   

			red   = Value(m1, m2, hue + 120);   
			green = Value(m1, m2, hue);
			blue  = Value(m1, m2, hue - 120);
		}
	}

    COLORREF CalcAvarageRectColor(const DIBINFO &di, RECT rc)
    {
        LPBYTE pLine= di.pBits + di.nWid * rc.top *4;
        if(rc.right > di.nWid) rc.right=di.nWid;
        if(rc.bottom > di.nHei) rc.bottom = di.nHei;
        int nWid = rc.right-rc.left;
        int nHei = rc.bottom -rc.top;
        
        int r=0,g=0,b=0;
        for(int y=0;y<nHei;y++)
        {
            LPBYTE p = pLine + rc.left * 4;
            for(int x=0;x<nWid;x++)
            {
                r += *p++;
                g += *p++;
                b += *p++;
                p++;//skip alpha
            }
            pLine += di.nWid*4;
        }
        int nPixels = (nWid*nHei);
        r /= nPixels;
        g /= nPixels;
        b /= nPixels;
        return RGB(r,g,b);
    }
    
    int __cdecl RgbCmp(const void *p1,const void *p2)
    {
        const BYTE * cr1 = (const BYTE*)p1;
        const BYTE * cr2 = (const BYTE*)p2;
        int deltaR = ((int)cr2[0] - (int)cr1[0]);
        int deltaG = ((int)cr2[1] - (int)cr1[1]);
        int deltaB = ((int)cr2[2] - (int)cr1[2]);
        return deltaR + deltaG + deltaB;
    }
    
    COLORREF SDIBHelper::CalcAvarageColor(IBitmap *pBmp,int nPercent,int nBlockSize/*=5*/)
    {
        DIBINFO di={(LPBYTE)pBmp->LockPixelBits(),pBmp->Width(),pBmp->Height()};
        
        int xBlocks = (di.nWid + nBlockSize -1)/nBlockSize;
        int yBlocks = (di.nHei + nBlockSize -1)/nBlockSize;
        
        int nBlocks = xBlocks*yBlocks;
        COLORREF *pAvgColors = new COLORREF[nBlocks];
        
        CRect rcBlock(0,0,nBlockSize,nBlockSize);
        int iBlock = 0;
        for(int y=0;y<yBlocks;y++)
        {
            for(int x=0;x<xBlocks;x++)
            {
                pAvgColors[iBlock++] = CalcAvarageRectColor(di,rcBlock);
                rcBlock.OffsetRect(nBlockSize,0);
            }
            rcBlock.MoveToX(0);
            rcBlock.OffsetRect(0,nBlockSize);
        }
        //RGB����
        qsort(pAvgColors,nBlocks,sizeof(COLORREF),RgbCmp);
        
        int nThrows = nBlocks * (100-nPercent)/200;//һ�˶�������
        int iBegin = nThrows;
        int iEnd = nBlocks - nThrows;
        
        int r = 0, g= 0, b=0;
        for(int i= iBegin;i<iEnd;i++)
        {
            BYTE *p = (BYTE*)(pAvgColors+i);
            r += p[0];
            g += p[1];
            b += p[2];
        }
        
        r /= (iEnd - iBegin);
        g /= (iEnd - iBegin);
        b /= (iEnd - iBegin);
                        
        delete []pAvgColors;
        pBmp->UnlockPixelBits(di.pBits);
        
        return RGB(r,g,b);
    }

}//namespace SOUI