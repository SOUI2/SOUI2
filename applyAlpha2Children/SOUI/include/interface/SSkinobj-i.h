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

namespace SOUI
{
    /**
    * @struct     ISkinObj
    * @brief      Skin ����
    * 
    * Describe
    */
    class SOUI_EXP ISkinObj : public SObject
                            , public IObjRef
    {
    public:
        virtual ~ISkinObj()
        {
        }

        /**
        * DrawEx
        * @brief    ��this���Ƶ�RenderTarget��ȥ
        * @param    IRenderTarget * pRT --  �����õ�RenderTarget
        * @param    LPCRECT rcDraw --  ����λ��
        * @param    DWORD dwState --  ����״̬
        * @param    BYTE byAlpha --  ����͸����
        * @return   void
        * Describe  
        */    
        virtual void Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha)=0;

        /**
        * Draw
        * @brief    ��this���Ƶ�RenderTarget��ȥ
        * @param    IRenderTarget * pRT --  �����õ�RenderTarget
        * @param    LPCRECT rcDraw --  ����λ��
        * @param    DWORD dwState --  ����״̬
        * @return   void
        * Describe  ʹ��SkinObj��GetAlpha���Ի���
        */    
        virtual void Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState)=0;

        /**
        * GetSkinSize
        * @brief    ���Skin��Ĭ�ϴ�С
        * @return   SIZE -- Skin��Ĭ�ϴ�С
        * Describe  ������Ӧ�ø���skin���ص�ʵ�ָýӿ�
        */    
        virtual SIZE GetSkinSize()=0;
        /**
        * IgnoreState
        * @brief    ��ѯskin�Ƿ���״̬��Ϣ
        * @return   BOOL -- true��״̬��Ϣ
        * Describe  
        */    
        virtual BOOL IgnoreState()=0;

        /**
        * GetStates
        * @brief    ���skin���������״̬����
        * @return   int -- ״̬����
        * Describe  Ĭ��Ϊ1
        */    
        virtual int GetStates()=0;

        /**
        * GetAlpha
        * @brief    ���skin�������͸����
        * @return   BYTE -- ͸����
        * Describe  [0-255]
        */    
        virtual BYTE GetAlpha() const=0;

        /**
        * SetAlpha
        * @brief    �趨skin�������͸����
        * @param    BYTE byAlpha-- ͸����
        * @return   void
        * Describe  
        */    
        virtual void SetAlpha(BYTE byAlpha) =0;
    };
}//namespace SOUI
