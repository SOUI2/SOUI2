/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       Accelerator.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    SOUI���ټ�����ģ��
*/

#pragma once

namespace SOUI
{
    /**
    * @class      CAccelerator
    * @brief      ���ټ�ӳ��
    * 
    * Describe
    */
    class SOUI_EXP CAccelerator
    {
    public:

        /**
         * CAccelerator
         * @brief    ���캯��
         * @param    DWORD dwAccel --  ���ټ�ֵ
         * Describe  
         */    
        CAccelerator(DWORD dwAccel);

        /**
         * CAccelerator
         * @brief    ���캯��
         * @param    UINT vKey --  ��ֵ
         * @param    bool bCtrl --  ��Ctrl���
         * @param    bool bAlt --  ��Alt���
         * @param    bool bShift --  ��Shilft���
         * Describe  
         */    
        CAccelerator(UINT vKey=0,bool bCtrl=false,bool bAlt=false,bool bShift=false);

        /**
         * ~CAccelerator
         * @brief    ��������
         * Describe  
         */    
        ~CAccelerator(void);

        /**
         * GetKeyName
         * @brief    ������ֵת��Ϊ��Ӧ���ַ���
         * @param    WORD vk --  ����ֵ
         * @return   SOUI::SStringT -- ����
         * Describe  
         */    
        SStringT GetKeyName(WORD vk);

        /**
         * FormatHotkey
         * @brief    ��õ�ǰ���ټ����ַ�����ʽ
         * @return   SOUI::SStringT -- ���ټ����ַ�����ʽ
         * Describe  
         */    
        SStringT FormatHotkey();

        /**
         * GetModifier
         * @brief    ��ü��ټ�������λ
         * @return   WORD -- ���ټ������μ�
         * Describe  
         */    
        WORD GetModifier() const {return m_wModifier;}

        /**
         * GetKey
         * @brief    ��ü��ټ�������
         * @return   WORD -- ���ټ�������
         * Describe  
         */    
        WORD GetKey() const {return m_wVK;}

        /**
         * TranslateAccelKey
         * @brief    �������ַ�����Ӧ�ļ��ټ�ֵ
         * @param    LPCTSTR pszKeyName --  ������ټ����ַ���
         * @return   DWORD -- ���ټ�ֵ
         * Describe  
         */    
        static DWORD TranslateAccelKey(LPCTSTR pszKeyName);
    protected:
        WORD     m_wModifier;
        WORD    m_wVK;
    };

    template<>
    class  _COLL_NS::CElementTraits< SOUI::CAccelerator > : public _COLL_NS::CElementTraitsBase< SOUI::CAccelerator >
    {
    public:
        static ULONG Hash(INARGTYPE element ) throw()
        {
            return MAKELONG(element.GetModifier(),element.GetKey());
        }

        static bool CompareElements( INARGTYPE element1, INARGTYPE element2 )
        {
            return Hash(element1)==Hash(element2);
        }

        static int CompareElementsOrdered( INARGTYPE element1, INARGTYPE element2 )
        {
            return Hash(element1)-Hash(element2);
        }
    };

    /**
    * @struct     IAcceleratorTarget
    * @brief      ���ټ����µĴ���ӿ�
    * 
    * Describe ��Ҫע����̼��ټ�������Ҫʵ�ֱ��ӿ�
    */
    struct IAcceleratorTarget
    {
        /**
         * OnAcceleratorPressed
         * @brief    
         * @param    const CAccelerator & accelerator --  ���µļ��ټ�
         * @return   bool -- ���ټ���������true
         * Describe  
         */    
        virtual bool OnAcceleratorPressed(const CAccelerator& accelerator) = 0;
    };

    /**
    * @struct     IAcceleratorMgr
    * @brief      ���ټ�����ӿ�
    * 
    * Describe
    */
    struct IAcceleratorMgr
    {
        // Register a keyboard accelerator for the specified target. If multiple
        // targets are registered for an accelerator, a target registered later has
        // higher priority.
        // Note that we are currently limited to accelerators that are either:
        // - a key combination including Ctrl or Alt
        // - the escape key
        // - the enter key
        // - any F key (F1, F2, F3 ...)
        // - any browser specific keys (as available on special keyboards)
        virtual void RegisterAccelerator(const CAccelerator& accelerator,
            IAcceleratorTarget* target)=NULL;

        // Unregister the specified keyboard accelerator for the specified target.
        virtual void UnregisterAccelerator(const CAccelerator& accelerator,
            IAcceleratorTarget* target)=NULL;

        // Unregister all keyboard accelerator for the specified target.
        virtual void UnregisterAccelerators(IAcceleratorTarget* target)=NULL;
    };
}//end of namespace SOUI
