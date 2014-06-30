#pragma once

#include "duiwnd.h"

//////////////////////////////////////////////////////////////////////////
// Real Window Control
// Binding a real window
//
// Usage: <realwnd id=xx wndclass="edit" wndname="name" style="00000001" exstyle="00000000"/>
//

namespace SOUI
{

class SOUI_EXP CDuiRealWndParam
{
public:
    CDuiRealWndParam();
    ~CDuiRealWndParam();

    SStringT m_strClassName,m_strWindowName;
    DWORD     m_dwStyle,m_dwExStyle;
    pugi::xml_document m_xmlParams;
};


class SOUI_EXP SRealWnd : public SWindow
{
    SOUI_CLASS_NAME(SRealWnd, L"realwnd")
public:
    SRealWnd();

    virtual ~SRealWnd();


    const HWND GetRealHwnd(BOOL bAutoCreate=TRUE);

    const CDuiRealWndParam & GetRealWndParam()
    {
        return m_realwndParam;
    }

    void SetData(LPVOID lpData)
    {
        m_lpData=lpData;
    }
    const LPVOID GetData()
    {
        return m_lpData;
    }

    SOUI_ATTRS_BEGIN()
    ATTR_STRINGT(L"wndclass", m_realwndParam.m_strClassName, FALSE)
    ATTR_STRINGT(L"wndname", m_realwndParam.m_strWindowName, FALSE)
    ATTR_HEX(L"style", m_realwndParam.m_dwStyle, FALSE)
    ATTR_HEX(L"exstyle", m_realwndParam.m_dwExStyle, FALSE)
    ATTR_INT(L"init",m_bInit,FALSE)
    SOUI_ATTRS_END()
protected:
    virtual BOOL NeedRedrawWhenStateChange();
    virtual BOOL InitFromXml(pugi::xml_node xmlNode);


    LRESULT OnWindowPosChanged(LPRECT lpWndPos);

    void OnShowWindow(BOOL bShow, UINT nStatus);
    void OnDestroy();

    // Do nothing
    void OnPaint(CDCHandle dc) {}

    void ShowRealWindow();

    BOOL InitRealWnd();


    WND_MSG_MAP_BEGIN()
    MSG_WM_PAINT(OnPaint)
    MSG_WM_DESTROY(OnDestroy)
    MSG_WM_WINPOSCHANGED_EX(OnWindowPosChanged)
    MSG_WM_SHOWWINDOW(OnShowWindow)
    WND_MSG_MAP_END()

    CDuiRealWndParam    m_realwndParam;
    BOOL    m_bInit;

    HWND     m_hRealWnd;
    LPVOID    m_lpData;
};

interface SOUI_EXP IDuiRealWndHandler
{
    virtual HWND OnRealWndCreate(SRealWnd *pRealWnd)=NULL;
    virtual BOOL OnRealWndInit(SRealWnd *pRealWnd)=NULL;
    virtual void OnRealWndDestroy(SRealWnd *pRealWnd)=NULL;
    virtual void OnRealWndSize(SRealWnd *pRealWnd)=NULL;
};

}//namespace SOUI