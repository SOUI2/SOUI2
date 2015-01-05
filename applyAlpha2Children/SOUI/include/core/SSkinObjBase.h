#pragma once

#include "interface/Sskinobj-i.h"
#include <unknown/obj-ref-impl.hpp>

namespace SOUI
{

    class SOUI_EXP SSkinObjBase : public TObjRefImpl<ISkinObj>
    {
    public:
        SSkinObjBase():m_byAlpha(0xFF){}

        /**
        * GetAlpha
        * @brief    ���skin�������͸����
        * @return   BYTE -- ͸����
        * Describe  [0-255]
        */    
        BYTE GetAlpha() const
        {
            return m_byAlpha;
        }

        /**
        * SetAlpha
        * @brief    �趨skin�������͸����
        * @param    BYTE byAlpha-- ͸����
        * @return   void
        * Describe  
        */    
        virtual void SetAlpha(BYTE byAlpha)
        {
            m_byAlpha = byAlpha;
        }

        virtual void Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha)
        {
            _Draw(pRT,rcDraw,dwState,byAlpha);
        }

        virtual void Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState)
        {
            Draw(pRT,rcDraw,dwState,GetAlpha());
        }

        virtual SIZE GetSkinSize()
        {
            SIZE ret = {0, 0};

            return ret;
        }

        virtual BOOL IgnoreState()
        {
            return TRUE;
        }

        virtual int GetStates()
        {
            return 1;
        }

        SOUI_ATTRS_BEGIN()
            ATTR_INT(L"alpha",m_byAlpha,TRUE)   //Ƥ��͸����
        SOUI_ATTRS_END()

    protected:

        /**
        * _Draw
        * @brief    Draw������ʵ��
        * @param    IRenderTarget * pRT --  ��ȾĿ��
        * @param    LPCRECT rcDraw --  ��Ⱦλ��
        * @param    DWORD dwState --  ��Ⱦ״̬
        * @param    BYTE byAlpha --  ͸����
        * @return   void
        * Describe  ÿһ��skin��Ҫʵ��һ��_Draw����
        */    
        virtual void _Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha)=0;

        BYTE m_byAlpha;
    };

}//namespace SOUI