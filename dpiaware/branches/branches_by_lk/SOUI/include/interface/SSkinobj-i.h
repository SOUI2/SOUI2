/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       SSkinobj-i.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/01
* 
* Describe    interface of SSkinObj
*/
#pragma once

#include "sobject.h"
#include <unknown/obj-ref-i.h>
#include <unknown/obj-ref-impl.hpp>

namespace SOUI
{
    /**
    * @struct     ISkinObj
    * @brief      Skin ����
    * 
    * Describe
    */
    class SOUI_EXP ISkinObj : public SObject,public TObjRefImpl2<IObjRef,ISkinObj>
    {
    public:
        ISkinObj()
        {
        }
        virtual ~ISkinObj()
        {
        }

        /**
         * Draw
         * @brief    ��this���Ƶ�RenderTarget��ȥ
         * @param    IRenderTarget * pRT --  �����õ�RenderTarget
         * @param    LPCRECT rcDraw --  ����λ��
         * @param    DWORD dwState --  ����״̬
         * @param    BYTE byAlpha --  ͸����
         * @return   void
         * Describe  
         */    
        virtual void Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha=0xFF)=0;

        /**
         * GetSkinSize
         * @brief    ���Skin��Ĭ�ϴ�С
         * @return   SIZE -- Skin��Ĭ�ϴ�С
         * Describe  ������Ӧ�ø���skin���ص�ʵ�ָýӿ�
         */    
        virtual SIZE GetSkinSize()
        {
            SIZE ret = {0, 0};

            return ret;
        }

        /**
         * IgnoreState
         * @brief    ��ѯskin�Ƿ���״̬��Ϣ
         * @return   BOOL -- true��״̬��Ϣ
         * Describe  
         */    
        virtual BOOL IgnoreState()
        {
            return TRUE;
        }

        /**
         * GetStates
         * @brief    ���skin���������״̬����
         * @return   int -- ״̬����
         * Describe  Ĭ��Ϊ1
         */    
        virtual int GetStates()
        {
            return 1;
        }
    };
}//namespace SOUI
