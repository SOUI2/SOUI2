/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       SFontPool.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    SOUI�������ģ��
*/

#pragma once

#include "core/ssingletonmap.h"
#include "interface/render-i.h"
#include "unknown/obj-ref-impl.hpp"

/**
* @union      FONTSTYLE
* @brief      FONT�ķ��
* 
* Describe    
*/
union FONTSTYLE{
    DWORD     dwStyle;  //DWORD�汾�ķ��
    struct
    {
        DWORD cSize:16;//�����С��Ϊshort�з�������
        DWORD fItalic:1;//б���־λ
        DWORD fUnderline:1;//�»��߱�־λ
        DWORD fBold:1;//�����־λ
        DWORD fStrike:1;//ɾ���߱�־λ
        DWORD fAbsSize:1;//�����cSize�Ǿ��Դ�С���������Ĭ������Ĵ�С,1����cSizeΪ���Դ�С
    };
    
    FONTSTYLE(DWORD _dwStyle):dwStyle(_dwStyle){}
}; 

#define FF_DEFAULTFONT FONTSTYLE(0)

/**
* @class     FontKey
* @brief      һ��FONT��KEY
* 
* Describe    ����ʵ��һ��font map
*/
class SOUI_EXP FontKey
{
public:
    FontKey(DWORD _dwStyle,LPCTSTR pszFaceName=NULL)
    {
        if(pszFaceName)
        {
            _tcscpy_s(strFaceName,LF_FACESIZE,pszFaceName);
        }
        else
        {
            strFaceName[0]=0;
        }
        dwStyle=_dwStyle;
    }
    
    DWORD    dwStyle;
    TCHAR    strFaceName[LF_FACESIZE+1];
};


/**
* @class     CElementTraits< FontKey >
* @brief      FontKey��Hash���Ƚ�ģ��
* 
* Describe    ����ʵ��һ��font map
*/
template<>
class SOUI::CElementTraits< FontKey > :
    public SOUI::CElementTraitsBase<FontKey >
{
public:
    static ULONG Hash( INARGTYPE fontKey )
    {
        ULONG_PTR uRet=0;
        SStringT strType=fontKey.strFaceName;
        strType.MakeLower();
        for(int i=0; i<strType.GetLength(); i++)
        {
            uRet=uRet*68+strType[i];
        }

        return (ULONG)(uRet*10000+(UINT)fontKey.dwStyle+1);
    }

    static bool CompareElements( INARGTYPE element1, INARGTYPE element2 )
    {
        return _tcsicmp(element1.strFaceName,element2.strFaceName)==0 && element1.dwStyle==element2.dwStyle;
    }

    static int CompareElementsOrdered( INARGTYPE element1, INARGTYPE element2 )
    {
        int nRet=_tcsicmp(element1.strFaceName,element2.strFaceName);
        if(nRet<0) return -1;
        if(nRet>0) return 1;
        return element1.dwStyle-element2.dwStyle;
    }
};

namespace SOUI
{
    typedef IFont * IFontPtr;

    /**
    * @class      SFontPool
    * @brief      font pool
    * 
    * Describe
    */
    class SOUI_EXP SFontPool :public SSingletonMap<SFontPool,IFontPtr,FontKey>
    {
    public:
        SFontPool(IRenderFactory *pRendFactory);

        
        /**
         * GetFont
         * @brief    �����ָ����strFont��Ӧ��IFontPtr
         * @param    const SStringW & strFont --  font�����ַ���
         * @return   IFontPtr -- font����
         *
         * Describe  �����ַ�����ʽ�磺face:����;bold:0;italic:1;underline:1;strike:1;adding:10
         */
        IFontPtr GetFont(const SStringW & strFont);

        /**
         * GetFont
         * @brief    �����ָ����font key��Ӧ��IFontPtr
         * @param    FONTSTYLE style --  ������
         * @param    LPCTSTR strFaceName --  ������
         * @return   IFontPtr -- font����
         * Describe  
         */    
        IFontPtr GetFont(FONTSTYLE style,LPCTSTR strFaceName=_T(""));
        
        /**
         * SetDefaultFont
         * @brief    ����Ĭ������
         * @param    LPCTSTR lpszFaceName --  ������
         * @param    LONG lSize --  �����С
         * @return   void
         * Describe  
         */    
        void SetDefaultFont(LPCTSTR lpszFaceName, LONG lSize);
    protected:
        static void OnKeyRemoved(const IFontPtr & obj)
        {
            obj->Release();
        }

        IFontPtr _CreateFont(const LOGFONT &lf);
        
        IFontPtr _CreateFont(FONTSTYLE style,const SStringT & strFaceName);

        LOGFONT m_lfDefault;
        CAutoRefPtr<IRenderFactory> m_RenderFactory;
    };

}//namespace SOUI

