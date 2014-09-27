#include "StdAfx.h"
#include "ImageOle.h"
#include "../../controls.extend/gif/SSkinGif.h"
#include <tom.h>
#include "../soui/include/sapp.h"

#define DEFINE_GUIDXXX(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
	EXTERN_C const GUID CDECL name \
	= { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

DEFINE_GUIDXXX(IID_ITextDocument,0x8CC497C0,0xA1DF,0x11CE,0x80,0x98,
			   0x00,0xAA,0x00,0x47,0xBE,0x5D);

using namespace SOUI;

CImageOle::CImageOle(SRichEdit *pRichedit)
:m_ulRef(0)
,m_pOleClientSite(NULL)
,m_pAdvSink(NULL)
,m_pSkin(NULL)
,m_iFrame(0)
,m_pRichedit(pRichedit)
,m_nTimePass(0)
{
}

CImageOle::~CImageOle(void)
{
}

HRESULT WINAPI CImageOle::QueryInterface(REFIID iid, void ** ppvObject)
{
	if (iid == IID_IUnknown || iid == IID_IOleObject)
	{
		*ppvObject = (IOleObject *)this;
		((IOleObject *)(*ppvObject))->AddRef();
		return S_OK;
	}
	else if (iid == IID_IViewObject || iid == IID_IViewObject2)
	{
		*ppvObject = (IViewObject2 *)this;
		((IViewObject2 *)(*ppvObject))->AddRef();
		return S_OK;
	}

	return E_NOINTERFACE;
}

ULONG WINAPI CImageOle::AddRef(void)
{
	m_ulRef++;
	return m_ulRef;
}

ULONG WINAPI CImageOle::Release(void)
{
	if (--m_ulRef == 0)
	{
		delete this;
		return 0;
	}

	return m_ulRef;
}

HRESULT WINAPI CImageOle::SetClientSite(IOleClientSite *pClientSite)
{
	m_pOleClientSite = pClientSite;
	if(m_pOleClientSite) m_pOleClientSite->AddRef();
	return S_OK;
}

HRESULT WINAPI CImageOle::GetClientSite(IOleClientSite **ppClientSite)
{
	*ppClientSite = m_pOleClientSite;
	return S_OK;
}

HRESULT WINAPI CImageOle::SetHostNames(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj)
{
	return S_OK;
}

HRESULT WINAPI CImageOle::Close(DWORD dwSaveOption)
{
	if(m_pOleClientSite)
	{
		m_pOleClientSite->Release();
		m_pOleClientSite = NULL;
	}
	if (m_pAdvSink != NULL)
	{
		m_pAdvSink->Release();
		m_pAdvSink = NULL;
	}
	if(m_pSkin)
	{
		m_pSkin->Release();
		m_pSkin=NULL;
	}

	m_pRichedit->GetContainer()->UnregisterTimelineHandler(this);

	return S_OK;
}

HRESULT WINAPI CImageOle::SetMoniker(DWORD dwWhichMoniker, IMoniker *pmk)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::GetMoniker(DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::InitFromData(IDataObject *pDataObject, BOOL fCreation, DWORD dwReserved)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::GetClipboardData(DWORD dwReserved, IDataObject **ppDataObject)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::DoVerb(LONG iVerb, LPMSG lpmsg, IOleClientSite *pActiveSite, LONG lindex, HWND hwndParent, LPCRECT lprcPosRect)
{
	return S_OK;
}

HRESULT WINAPI CImageOle::EnumVerbs(IEnumOLEVERB **ppEnumOleVerb)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::Update(void)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::IsUpToDate(void)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::GetUserClassID(CLSID *pClsid)
{
	*pClsid = IID_NULL;
	return S_OK;
}

HRESULT WINAPI CImageOle::GetUserType(DWORD dwFormOfType, LPOLESTR *pszUserType)
{
	return E_NOTIMPL;
}

// ���ÿؼ���ʹ�õĿռ䣨�ؼ�����Ļ��ʹ�õ�����Χ��
HRESULT WINAPI CImageOle::SetExtent(DWORD dwDrawAspect, SIZEL *psizel)
{
	return E_NOTIMPL;
}

// ��ȡ�ؼ���ʹ�õĿռ�
HRESULT WINAPI CImageOle::GetExtent(DWORD dwDrawAspect, SIZEL *psizel)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::Advise(IAdviseSink *pAdvSink, DWORD *pdwConnection)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::Unadvise(DWORD dwConnection)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::EnumAdvise(IEnumSTATDATA **ppenumAdvise)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::GetMiscStatus(DWORD dwAspect, DWORD *pdwStatus)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::SetColorScheme(LOGPALETTE *pLogpal)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::Draw(DWORD dwDrawAspect, LONG lindex, void *pvAspect, 
							   DVTARGETDEVICE *ptd, HDC hdcTargetDev, HDC hdcDraw, 
							   LPCRECTL lprcBounds, LPCRECTL lprcWBounds,
							   BOOL ( WINAPI *pfnContinue )(ULONG_PTR dwContinue), 
							   ULONG_PTR dwContinue)
{
	if (lindex != -1)
		return S_FALSE;

	RECT rcItem;
	rcItem.left   = lprcBounds->left;
	rcItem.top    = lprcBounds->top;
	rcItem.right  = lprcBounds->right;
	rcItem.bottom = lprcBounds->bottom;

	if(m_pSkin)
	{
	    SOUI::IRenderTarget * pRT =NULL;
        RECT rc2={0,0,rcItem.right-rcItem.left,rcItem.bottom-rcItem.top};
	    GETRENDERFACTORY->CreateRenderTarget(&pRT,rc2.right,rc2.bottom);
	    if(pRT)
        {
            HDC hdcSrc=pRT->GetDC();
            ::BitBlt(hdcSrc,0,0,rc2.right,rc2.bottom,hdcDraw,rcItem.left,rcItem.top,SRCCOPY);
            if(m_pSkin->IsClass(SSkinGif::GetClassName()))
            {
                SSkinGif *pSkinGif=static_cast<SSkinGif*>(m_pSkin);
                pSkinGif->Draw(pRT,&rc2,m_iFrame);
            }else
            {
                m_pSkin->Draw(pRT,&rc2,0);
            }
            ::BitBlt(hdcDraw,rcItem.left,rcItem.top,rc2.right,rc2.bottom,hdcSrc,0,0,SRCCOPY);
            pRT->ReleaseDC(hdcSrc);
            pRT->Release();
        }
		
	}
	return S_OK;
}

HRESULT WINAPI CImageOle::GetColorSet(DWORD dwDrawAspect, LONG lindex, void *pvAspect, 
									  DVTARGETDEVICE *ptd, HDC hicTargetDev, LOGPALETTE **ppColorSet)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::Freeze(DWORD dwDrawAspect, LONG lindex, void *pvAspect, DWORD *pdwFreeze)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::Unfreeze(DWORD dwFreeze)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::SetAdvise(DWORD aspects, DWORD advf, IAdviseSink *pAdvSink)
{
	if (pAdvSink != NULL)
	{
		m_pAdvSink = pAdvSink;
		m_pAdvSink->AddRef();
	}

	if (m_pSkin != NULL && m_pSkin->IsClass(SSkinGif::GetClassName()))
	{
		SSkinGif *pGif=static_cast<SSkinGif*>(m_pSkin);
		m_iFrame=0;
		m_nTimeDelay=pGif->GetFrameDelay(0);
		m_nTimePass=0;
		m_pRichedit->GetContainer()->RegisterTimelineHandler(this);
	}

	return S_OK;
}

HRESULT WINAPI CImageOle::GetAdvise(DWORD *pAspects, DWORD *pAdvf, IAdviseSink **ppAdvSink)
{
	return E_NOTIMPL;
}

HRESULT WINAPI CImageOle::GetExtent(DWORD dwDrawAspect, LONG lindex, DVTARGETDEVICE *ptd, LPSIZEL lpsizel)
{
	if (m_pSkin != NULL)
	{
		SIZE sz=m_pSkin->GetSkinSize();

		HDC hDC = ::GetDC(NULL);
		lpsizel->cx = ::MulDiv(sz.cx, 2540, GetDeviceCaps(hDC, LOGPIXELSX));
		lpsizel->cy = ::MulDiv(sz.cy, 2540, GetDeviceCaps(hDC, LOGPIXELSY));
		::ReleaseDC(NULL, hDC);
	}

	return S_OK;
}


void CImageOle::SetDuiSkinObj( ISkinObj *pSkin )
{
	if(m_pSkin)
	{
		m_pSkin->Release();
	}
	m_pSkin=pSkin;
	if(m_pSkin)
	{
		m_pSkin->AddRef();
	}
}

//��Ҫ��ö�ٵİ취�����ָ��OLE����ʾλ�ã���֪����û���������õİ취��
BOOL CImageOle::GetOleRect( LPRECT lpRect )
{
	IRichEditOle *pRichEditOle=NULL;
	LRESULT lRes=m_pRichedit->SSendMessage(EM_GETOLEINTERFACE,0,(LPARAM)&pRichEditOle);
	if(!pRichEditOle) return FALSE;

	BOOL bRet=FALSE;

	int nObjCount = pRichEditOle->GetObjectCount();
	int i = 0;
	for (i = 0;i < nObjCount;i++)
	{	
		REOBJECT reo;
		ZeroMemory(&reo, sizeof(REOBJECT));
		reo.cbStruct = sizeof(REOBJECT);

		HRESULT hr = pRichEditOle->GetObject(i, &reo, REO_GETOBJ_POLEOBJ);
		if (hr != S_OK)
			continue;

		reo.poleobj->Release();

		if (reo.poleobj == (IOleObject *)this)
		{

			ITextDocument *pTextDocument = NULL;
			ITextRange *pTextRange = NULL;

			pRichEditOle->QueryInterface(IID_ITextDocument, (void **)&pTextDocument);
			if (!pTextDocument)
				break;

			long nLeft = 0;
			long nBottom = 0;
			pTextDocument->Range(reo.cp, reo.cp, &pTextRange);
			if (reo.dwFlags & REO_BELOWBASELINE)
				hr = pTextRange->GetPoint(TA_BOTTOM|TA_LEFT, &nLeft, &nBottom);
			else
				hr = pTextRange->GetPoint(TA_BASELINE|TA_LEFT, &nLeft, &nBottom);

            if(hr!=S_OK)
            {
                DWORD dwErr=GetLastError();
            }
			pTextDocument->Release();
			pTextRange->Release();

			CRect rcRichedit;
			GetWindowRect(m_pRichedit->GetContainer()->GetHostHwnd(),&rcRichedit);
			CSize szOle=m_pSkin->GetSkinSize();

			lpRect->left   = nLeft - rcRichedit.left;
			lpRect->bottom = nBottom - rcRichedit.top;
			lpRect->right  = lpRect->left + szOle.cx ;
			lpRect->top    = lpRect->bottom - szOle.cy;

			bRet=TRUE;
			break;
		}
	}

	pRichEditOle->Release();
	return bRet;
}

void CImageOle::OnNextFrame()
{
	m_nTimePass+=10;
	if(m_nTimePass>=m_nTimeDelay)
	{
		CRect rcOle;
		if(GetOleRect(&rcOle))
		{
			m_pRichedit->InvalidateRect(rcOle);
		}

		SSkinGif *pSkinGif=static_cast<SSkinGif*>(m_pSkin);
		SASSERT(pSkinGif);
		m_iFrame++;
		if(m_iFrame==pSkinGif->GetStates())
			m_iFrame=0;

		m_nTimeDelay=pSkinGif->GetFrameDelay(m_iFrame)*10;
		m_nTimePass=0;
	}
}

BOOL RichEdit_InsertSkin(SRichEdit *pRicheditCtrl, ISkinObj *pSkin)
{
	IRichEditOle *pRichEditOle=NULL;
	LRESULT lRes=pRicheditCtrl->SSendMessage(EM_GETOLEINTERFACE,0,(LPARAM)&pRichEditOle);
	if(!pRichEditOle) return FALSE;

	SCODE sc;
	IOleClientSite *pOleClientSite = NULL;
	pRichEditOle->GetClientSite(&pOleClientSite);
	if (NULL == pOleClientSite)
		return FALSE;

	IStorage *pStorage = NULL;

	LPLOCKBYTES lpLockBytes = NULL;
	sc = ::CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
	if (sc != S_OK)
		return FALSE;

	sc = ::StgCreateDocfileOnILockBytes(lpLockBytes,
		STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE, 0, &pStorage);
	if (sc != S_OK)
	{
		lpLockBytes->Release();
		lpLockBytes = NULL;
		return FALSE;
	}


	CImageOle *pImageOle = new CImageOle(pRicheditCtrl);
	if (NULL == pImageOle)
		return FALSE;

	pImageOle->SetDuiSkinObj(pSkin);

	IOleObject *pOleObject = NULL;
	pImageOle->QueryInterface(IID_IOleObject, (void **)&pOleObject);
	if (NULL == pOleObject)
	{
		delete pImageOle;
		return FALSE;
	}

	pImageOle->SetClientSite(pOleClientSite);

	HRESULT hr = ::OleSetContainedObject(pOleObject, TRUE);

	REOBJECT reobject = {0};
	reobject.cbStruct = sizeof(REOBJECT);
	reobject.clsid    = CLSID_NULL;
	reobject.cp       = REO_CP_SELECTION;
	reobject.dvaspect = DVASPECT_CONTENT;
	reobject.poleobj  = pOleObject;
	reobject.polesite = pOleClientSite;
	reobject.pstg     = pStorage;
	reobject.dwUser   = 0;

	pRichEditOle->InsertObject(&reobject);

	pOleObject->Release();
	pOleClientSite->Release();
	pStorage->Release();
	pRichEditOle->Release();

	return TRUE;
}

BOOL RichEdit_InsertImage(SRichEdit *pRicheditCtrl, LPCTSTR lpszFileName)
{
    SStringW key=S_CT2W(lpszFileName);
    SSkinPool *pBuiltinSkinPool = SSkinPoolMgr::getSingletonPtr()->GetBuiltinSkinPool();
    ISkinObj *pSkin=pBuiltinSkinPool->GetSkin(key);
    if(!pSkin)
    {
        SSkinGif *pGifSkin = (SSkinGif*)SApplication::getSingleton().CreateSkinByName(SSkinGif::GetClassName());
        if(!pGifSkin) return FALSE;
        if(0==pGifSkin->LoadFromFile(lpszFileName))
        {
            pGifSkin->Release();
            return FALSE;
        }

        pBuiltinSkinPool->AddKeyObject(key,pGifSkin);//��������skin����skinpool����
        pSkin = pGifSkin;
    }
    return RichEdit_InsertSkin(pRicheditCtrl,pSkin);
}