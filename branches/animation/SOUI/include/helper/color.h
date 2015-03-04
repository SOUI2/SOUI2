#pragma once

#define GetAValue(rgb)      (LOBYTE((rgb)>>24))
#define RGBA(r,g,b,a)       (RGB(r,g,b)|(a<<24))
#define CR_INVALID          0x00FFFFFF

//��ARGB��ʽ�洢��ɫֵ
class SColor
{
public:
	SColor(BYTE r,BYTE g,BYTE b,BYTE a=0xFF):a(a),b(b),g(g),r(r)
	{

	}

	SColor(COLORREF cr,BYTE a)
	{
	    r=GetRValue(cr);
	    g=GetGValue(cr);
	    b=GetBValue(cr);
        this->a = a;
	}

    SColor(COLORREF cr)
    {
        r=GetRValue(cr);
        g=GetGValue(cr);
        b=GetBValue(cr);
        a=GetAValue(cr);
    }
  
    const COLORREF toCOLORREF() const
    {
        return RGB(r,g,b)|(a<<24);
    }

    const DWORD toARGB() const
    {
        DWORD crRet;
        memcpy(&crRet,this,4);
        return crRet;
    }
        
    void setRGB(COLORREF cr)
    {
        r=GetRValue(cr);
        g=GetGValue(cr);
        b=GetBValue(cr);
        a=GetAValue(cr);
    }
    
    void setRGB(COLORREF cr,BYTE a)
    {
        r=GetRValue(cr);
        g=GetGValue(cr);
        b=GetBValue(cr);
        this->a=a;
    }
    
    DWORD b:8;
    DWORD g:8;
    DWORD r:8;
    DWORD a:8;
};