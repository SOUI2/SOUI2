#pragma once
#include "duiwnd.h"
#include "activex/flash10t.tlh"
#include "activex/wmp.tlh"
#include <mshtmhst.h>

namespace SOUI
{

    class SOUI_EXP SActiveX : public SWindow
    {
        friend class CDuiAxContainerImpl;
    public:
        SOUI_CLASS_NAME(SActiveX, "activex")
        explicit SActiveX();
        virtual ~SActiveX();

        IUnknown * GetIUnknow();
    protected:
        virtual void OnAxActivate(IUnknown *pUnknwn){}

        int OnCreate(LPVOID);
        void OnSize(UINT nType, CSize size);
        void OnPaint(IRenderTarget *pRT);
        LRESULT OnMouseEvent(UINT uMsg,WPARAM wp,LPARAM lp);
        LRESULT OnKeyEvent(UINT uMsg,WPARAM wp,LPARAM lp);
        void OnShowWindow(BOOL bShow, UINT nStatus);

        virtual UINT OnGetDuiCode(){return DUIC_WANTALLKEYS;}

        virtual BOOL IsTabStop(){return TRUE;}

        HRESULT OnAttrClsid(const CDuiStringA & strValue,BOOL bLoading);
        WND_MSG_MAP_BEGIN()
            MSG_WM_PAINT_EX(OnPaint)
            MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST,WM_MOUSELAST,OnMouseEvent)
            MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST,WM_KEYLAST,OnKeyEvent)
            MSG_WM_CREATE(OnCreate)
            MSG_WM_SIZE(OnSize)
            MSG_WM_SHOWWINDOW(OnShowWindow)
        WND_MSG_MAP_END()

        SOUI_ATTRS_BEGIN()
            ATTR_CUSTOM("clsid",OnAttrClsid)
            ATTR_DWORD("clsctx",m_clsCtx,FALSE)
            ATTR_UINT("delayinit",m_bDelayInit,FALSE)
        SOUI_ATTRS_END()

        virtual void OnInitActiveXFinished(){}

        BOOL InitActiveX();
        void SetActiveXVisible(BOOL bVisible);
        void SetExternalUIHandler(IDocHostUIHandler *pUiHandler);
    protected:
        CDuiAxContainerImpl * m_axContainer;
        CLSID    m_clsid;
        DWORD    m_clsCtx;
        BOOL        m_bDelayInit;
    };

    class SOUI_EXP SFlashCtrl : public SActiveX
    {
    public:
        SOUI_CLASS_NAME(SFlashCtrl, "flash")
        SFlashCtrl();

        ShockwaveFlashObjects::IShockwaveFlash* GetFlashInterface()  const
        {
            return flash_;
        }

    protected:
        virtual void OnAxActivate(IUnknown *pUnknwn)
        {
            flash_=pUnknwn;
            if(flash_)
            {
                flash_->put_WMode(bstr_t(_T("transparent")));
                flash_->put_Movie(bstr_t(m_strUrl));
            }

        }

        SOUI_ATTRS_BEGIN()
            ATTR_STRINGW("url",m_strUrl,FALSE)
        SOUI_ATTRS_END()

        CDuiStringW m_strUrl;

        CDuiComQIPtr<ShockwaveFlashObjects::IShockwaveFlash> flash_;
    };


    class SOUI_EXP SMediaPlayer :public SActiveX
    {
    public:
        SOUI_CLASS_NAME(SMediaPlayer, "mediaplayer")
        SMediaPlayer();

        WMPLib::IWMPPlayer4* GetMediaPlayerInterface()  const
        {
            return wmp_;
        }
        bool Play(LPCWSTR pszUrl);

    protected:
        virtual void OnInitActiveXFinished(){
            if(!m_strUrl.IsEmpty() && wmp_)
            {
                Play(m_strUrl);
            }
        }

        virtual void OnAxActivate(IUnknown *pUnknwn);

        SOUI_ATTRS_BEGIN()
            ATTR_STRINGW("url",m_strUrl,FALSE)
        SOUI_ATTRS_END()

        CDuiStringW m_strUrl;
        CDuiComQIPtr<WMPLib::IWMPPlayer4> wmp_;
    };

}

