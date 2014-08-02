/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       SSingleton.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    SOUIϵͳ��ʹ�õĵ���ģ��
*/

#pragma once

#include <assert.h>

namespace SOUI
{

    /**
    * @class      SSingleton
    * @brief      ����ģ��
    * 
    * Describe    
    */
    template <typename T> 
    class SOUI_EXP SSingleton
    {
    protected:
        static    T* ms_Singleton;

    public:
        SSingleton( void )
        {
            assert( !ms_Singleton );
            ms_Singleton = static_cast<T*>(this);
        }
        virtual ~SSingleton( void )
        {
            assert( ms_Singleton );
            ms_Singleton = 0;
        }
        static T& getSingleton( void )
        {
            assert( ms_Singleton );
            return ( *ms_Singleton );
        }
        static T* getSingletonPtr( void )
        {
            return ( ms_Singleton );
        }

    private:
        SSingleton& operator=(const SSingleton&)
        {
            return *this;
        }
        SSingleton(const SSingleton&) {}
    };

}//namespace SOUI