#pragma once

#include <richole.h>
#include <core/simplewnd.h>
#include <control/SRichEdit.h>

class CImageOle : public IOleObject, public IViewObject2, public SOUI::ITimelineHandler
{
private:
	CImageOle(SOUI::SRichEdit *pRichedit);
	~CImageOle(void);

public:
	// IUnknown�ӿ�
	virtual HRESULT WINAPI QueryInterface(REFIID iid, void ** ppvObject);
	virtual ULONG   WINAPI AddRef(void);
	virtual ULONG   WINAPI Release(void);

	// IOleObject�ӿ�
	virtual HRESULT WINAPI SetClientSite(IOleClientSite *pClientSite);
	virtual HRESULT WINAPI GetClientSite(IOleClientSite **ppClientSite);
	virtual HRESULT WINAPI SetHostNames(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj);
	virtual HRESULT WINAPI Close(DWORD dwSaveOption);
	virtual HRESULT WINAPI SetMoniker(DWORD dwWhichMoniker, IMoniker *pmk);
	virtual HRESULT WINAPI GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk);
	virtual HRESULT WINAPI InitFromData(IDataObject *pDataObject, BOOL fCreation, DWORD dwReserved);
	virtual HRESULT WINAPI GetClipboardData(DWORD dwReserved, IDataObject **ppDataObject);
	virtual HRESULT WINAPI DoVerb(LONG iVerb, LPMSG lpmsg, IOleClientSite *pActiveSite, LONG lindex, HWND hwndParent, LPCRECT lprcPosRect);
	virtual HRESULT WINAPI EnumVerbs(IEnumOLEVERB **ppEnumOleVerb);
	virtual HRESULT WINAPI Update(void);
	virtual HRESULT WINAPI IsUpToDate(void);
	virtual HRESULT WINAPI GetUserClassID(CLSID *pClsid);
	virtual HRESULT WINAPI GetUserType(DWORD dwFormOfType, LPOLESTR *pszUserType);
	virtual HRESULT WINAPI SetExtent(DWORD dwDrawAspect, SIZEL *psizel);
	virtual HRESULT WINAPI GetExtent(DWORD dwDrawAspect, SIZEL *psizel);
	virtual HRESULT WINAPI Advise(IAdviseSink *pAdvSink, DWORD *pdwConnection);
	virtual HRESULT WINAPI Unadvise(DWORD dwConnection);
	virtual HRESULT WINAPI EnumAdvise(IEnumSTATDATA **ppenumAdvise);
	virtual HRESULT WINAPI GetMiscStatus(DWORD dwAspect, DWORD *pdwStatus);
	virtual HRESULT WINAPI SetColorScheme(LOGPALETTE *pLogpal);

	// IViewObject�ӿ�
	virtual HRESULT WINAPI Draw(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DVTARGETDEVICE *ptd,
		HDC hdcTargetDev, HDC hdcDraw, LPCRECTL lprcBounds, LPCRECTL lprcWBounds,
		BOOL ( WINAPI *pfnContinue )(ULONG_PTR dwContinue), ULONG_PTR dwContinue);
	virtual HRESULT WINAPI GetColorSet(DWORD dwDrawAspect, LONG lindex, void *pvAspect, 
		DVTARGETDEVICE *ptd, HDC hicTargetDev, LOGPALETTE **ppColorSet);
	virtual HRESULT WINAPI Freeze(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DWORD *pdwFreeze);
	virtual HRESULT WINAPI Unfreeze(DWORD dwFreeze);
	virtual HRESULT WINAPI SetAdvise(DWORD aspects, DWORD advf, IAdviseSink *pAdvSink);
	virtual HRESULT WINAPI GetAdvise(DWORD *pAspects, DWORD *pAdvf, IAdviseSink **ppAdvSink);

	// IViewObject2�ӿ�
	virtual HRESULT WINAPI GetExtent(DWORD dwDrawAspect, LONG lindex, DVTARGETDEVICE *ptd, LPSIZEL lpsizel);

	virtual void OnNextFrame();

	void SetSkinObj(ISkinObj *pSkin);
    
    static CImageOle * CreateObject(SOUI::SRichEdit *pRichedit);
protected:

	volatile LONG m_ulRef;
	
	SOUI::CAutoRefPtr<IOleClientSite> m_pOleClientSite;
	SOUI::CAutoRefPtr<IAdviseSink> m_pAdvSink;
    SOUI::CAutoRefPtr<SOUI::ISkinObj> m_pSkin;

	SOUI::SRichEdit *m_pRichedit;
	
	int		m_iFrame;
	int		m_nTimePass;	//��ȥ��ʱ��
	int		m_nTimeDelay;	//һ������֡��Ҫ��ʱ��
};

BOOL RichEdit_InsertSkin(SOUI::SRichEdit *pRicheditCtrl, SOUI::ISkinObj *pSkin);
BOOL RichEdit_InsertImage(SOUI::SRichEdit *pRicheditCtrl, LPCTSTR lpszFileName);
