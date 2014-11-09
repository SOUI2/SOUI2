#include "stdafx.h"
#include "SGifPlayer.h"
#include "sskingif.h"
#include "SSkinAPNG.h"

namespace SOUI
{

SGifPlayer::SGifPlayer() :m_aniSkin(NULL), m_iCurFrame(0)
{

}

SGifPlayer::~SGifPlayer()
{
}

void SGifPlayer::OnTimer(char cTimerID)
{	
    UNREFERENCED_PARAMETER(cTimerID);
	KillTimer(1);	

	if(m_aniSkin)
	{
		int nStates=m_aniSkin->GetStates();
		m_iCurFrame++;
		m_iCurFrame%=nStates;
		Invalidate();
        
        if(m_aniSkin->GetFrameDelay()==0)
            SetTimer(1,90);
        else
            SetTimer(1, m_aniSkin->GetFrameDelay()*10);	
	}
}

void SGifPlayer::OnPaint( IRenderTarget *pRT )
{	
	__super::OnPaint(pRT);
	if(m_aniSkin)
	{		
		m_aniSkin->Draw(pRT, m_rcWindow,m_iCurFrame);
	}
}

void SGifPlayer::OnShowWindow( BOOL bShow, UINT nStatus )
{
	__super::OnShowWindow(bShow,nStatus);
	if(!bShow)
	{
		KillTimer(1);
	}else if(m_aniSkin)
	{
        if(m_aniSkin->GetFrameDelay()==0)
            SetTimer(1,90);
        else
		    SetTimer(1, m_aniSkin->GetFrameDelay()*10);					
	}
}

HRESULT SGifPlayer::OnAttrSkin( const SStringW & strValue, BOOL bLoading )
{
	ISkinObj *pSkin = SSkinPoolMgr::getSingleton().GetSkin(strValue);
	if(!pSkin) return E_FAIL;
	if(!pSkin->IsClass(SSkinAni::GetClassName())) return S_FALSE;
	m_aniSkin=static_cast<SSkinAni*>(pSkin);
	return bLoading?S_OK:S_FALSE;
}

CSize SGifPlayer::GetDesiredSize( LPRECT /*pRcContainer*/ )
{
	CSize sz;
	if(m_aniSkin) sz=m_aniSkin->GetSkinSize();
	return sz;
}

BOOL SGifPlayer::PlayGifFile( LPCTSTR pszFileName )
{
    return _PlayFile(pszFileName,TRUE);
}

BOOL SGifPlayer::PlayAPNGFile( LPCTSTR pszFileName )
{
    return _PlayFile(pszFileName,FALSE);
}

BOOL SGifPlayer::_PlayFile( LPCTSTR pszFileName, BOOL bGif )
{
    SStringW key=S_CT2W(pszFileName);
    SSkinPool *pBuiltinSkinPool = SSkinPoolMgr::getSingletonPtr()->GetBuiltinSkinPool();
    ISkinObj *pSkin=pBuiltinSkinPool->GetSkin(key);
    if(pSkin)
    {
        if(!pSkin->IsClass(SSkinAni::GetClassName())) return FALSE;
        m_aniSkin=static_cast<SSkinAni*>(pSkin);
    }else
    {
        SSkinAni *pGifSkin = (SSkinAni*)SApplication::getSingleton().CreateSkinByName(bGif?SSkinGif::GetClassName():SSkinAPNG::GetClassName());
        if(!pGifSkin) return FALSE;
        if(0==pGifSkin->LoadFromFile(pszFileName))
        {
            pGifSkin->Release();
            return FALSE;
        }

        pBuiltinSkinPool->AddKeyObject(key,pGifSkin);//��������skin����skinpool����
        m_aniSkin = pGifSkin;
    }
    if(m_layout.IsFitContent())
    {
        GetParent()->UpdateChildrenPosition();
    }
    return TRUE;
}

}
