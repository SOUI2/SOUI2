//////////////////////////////////////////////////////////////////////////
//  Class Name: SFontPool
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "core/ssingletonmap.h"
#include "interface/render-i.h"
#include "unknown/obj-ref-impl.hpp"

#define FF_STRIKE      0x0008U
#define FF_BOLD        0x0004U
#define FF_UNDERLINE   0x0002U
#define FF_ITALIC      0x0001U

#define FF_MAKEKEY(bold, underline, italic,strike, adding) \
    (WORD)((adding << 8) \
    | (bold ? FF_BOLD : 0) \
    | (underline ? FF_UNDERLINE : 0) \
    | (italic ? FF_ITALIC : 0) \
    | (strike ? FF_STRIKE : 0))

#define FF_ISSTRIKE(key)       ((key & FF_STRIKE) == FF_STRIKE)
#define FF_ISBOLD(key)         ((key & FF_BOLD) == FF_BOLD)
#define FF_ISUNDERLINE(key)    ((key & FF_UNDERLINE) == FF_UNDERLINE)
#define FF_ISITALIC(key)       ((key & FF_ITALIC) == FF_ITALIC)
#define FF_GETADDING(key)      (key >> 8)

#define FF_DEFAULTFONT         (FF_MAKEKEY(FALSE, FALSE, FALSE,FALSE, 0))
#define FF_BOLDFONT            (FF_MAKEKEY(TRUE, FALSE, FALSE,FALSE, 0))

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
    TCHAR    strFaceName[LF_FACESIZE+1];
    DWORD     dwStyle;
};


/**
* @class     CElementTraits< FontKey >
* @brief      FontKey��Hash���Ƚ�ģ��
* 
* Describe    ����ʵ��һ��font map
*/
template<>
class _COLL_NS::CElementTraits< FontKey > :
    public _COLL_NS::CElementTraitsBase<FontKey >
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
         * @brief    �����ָ����font key��Ӧ��IFontPtr
         * @param    WORD uKey --  font ��־λ
         * @param    LPCTSTR strFaceName --  font name
         * @return   IFontPtr -- font����
         * Describe  
         */    
        IFontPtr GetFont(WORD uKey,LPCTSTR strFaceName=_T(""));

        /**
         * GetFont
         * @brief    �����ָ����font key��Ӧ��IFontPtr
         * @param    BOOL bBold --  ����
         * @param    BOOL bUnderline --  �»���
         * @param    BOOL bItalic --  б��
         * @param    BOOL bStrike --  ɾ����
         * @param    char chAdding --  �����С�仯��
         * @param    LPCTSTR strFaceName --  ������
         * @return   IFontPtr -- font����
         * Describe  
         */    
        IFontPtr GetFont(BOOL bBold, BOOL bUnderline, BOOL bItalic, BOOL bStrike,char chAdding = 0,LPCTSTR strFaceName=_T(""));
        
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

        IFontPtr _CreateDefaultFont();

        IFontPtr _CreateFont(BOOL bBold, BOOL bUnderline, BOOL bItalic, BOOL bStrike,char chAdding,SStringT strFaceName=_T(""));

        LONG _GetFontAbsHeight(LONG lSize);

        LOGFONT m_lfDefault;
        TCHAR m_szDefFontFace[LF_FACESIZE];
        LONG m_lFontSize;

        CAutoRefPtr<IRenderFactory> m_RenderFactory;
    };

}//namespace SOUI

