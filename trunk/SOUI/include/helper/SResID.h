#pragma once


#define MAX_RES_TYPE        30            //��Դ����Ԥ���壬��󳤶Ȳ�����10
#define MAX_RES_NAME        100            //ע�⣺����Դ����ʱ����󳤶Ȳ�Ҫ����MAX_RES_NAME
namespace SOUI
{

class SOUI_EXP SResID
{
public:
    SResID( LPCTSTR pszType,LPCTSTR pszName )
    {
        memset(this,0,sizeof(SResID));
        if(pszType) _tcscpy_s(szType,MAX_RES_TYPE,pszType);
        if(pszName) _tcscpy_s(szName,MAX_RES_NAME,pszName);
        _tcslwr(szType);
        _tcslwr(szName);
    }

    TCHAR szType[MAX_RES_TYPE+1];
    TCHAR szName[MAX_RES_NAME+1];
};

}//end of namespace SOUI

template<>
class SOUI::CElementTraits<SOUI::SResID > :
    public SOUI::CElementTraitsBase<SOUI::SResID >
{
public:
    static ULONG Hash( INARGTYPE resid )
    {
        ULONG_PTR uRet=0;

        for(LPCTSTR p=resid.szType; *p; p++)
        {
            uRet=uRet*68+*p;
        }
        uRet*=10000;
        for(LPCTSTR p=resid.szName; *p; p++)
        {
            uRet=uRet*68+*p;
        }
        return (ULONG)uRet;
    }

    static bool CompareElements( INARGTYPE element1, INARGTYPE element2 )
    {
        return _tcscmp(element1.szType,element2.szType)==0
            && _tcscmp(element1.szName,element2.szName)==0;
    }

    static int CompareElementsOrdered( INARGTYPE element1, INARGTYPE element2 )
    {
        int nRet=_tcscmp(element1.szType,element2.szType);
        if(nRet==0) nRet=_tcscmp(element1.szName,element2.szName);
        return nRet;
    }
};

