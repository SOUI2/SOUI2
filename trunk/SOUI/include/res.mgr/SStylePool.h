/**
* Copyright (C) 2014-2050 SOUI�Ŷ�
* All rights reserved.
* 
* @file       SStylePool.h
* @brief      SkinObj Pool
* @version    v1.0      
* @author     soui      
* @date       2014-05-28
* 
* Describe    ����Style
*/

#pragma once
#include "core/SSingletonMap.h"
#include "core/swndstyle.h"
#include "interface/obj-ref-i.h"
#include <unknown/obj-ref-impl.hpp>

//���StylePoolMgrָ��
#define GETSTYLEPOOLMGR SStylePoolMgr::getSingletonPtr()
//ͨ��NAME��ö�Ӧ��Style
//p1: name of style
//p2: output of style
#define GETSTYLE(p1,p2) SStylePoolMgr::getSingleton().GetStyle(p1,p2)

namespace SOUI
{
    /**
    * @class      SStylePool
    * @brief      name��SwndStyle��ӳ���
    * 
    * Describe    
    */
    class SOUI_EXP SStylePool :public SCmnMap<SwndStyle,SStringW> , public TObjRefImpl2<IObjRef,SStylePool>
    {
    public:
        /**
         * GetStyle
         * @brief    Get style object from pool by class name
         * @param    LPCWSTR lpszName --  name of style
         * @param [out]  SwndStyle & style --  style
         * @return   BOOL -- TRUE: success; FALSE: not exist
         * Describe  
         */    
        BOOL GetStyle(LPCWSTR lpszName,SwndStyle& style);

        /**
         * Init
         * @brief    Load Style table from xml node
         * @param    pugi::xml_node xmlNode --  xml node that describe style list
         * @return   BOOL -- TRUE: loaded; FALSE:failed;
         * Describe  
         */    
        BOOL Init(pugi::xml_node xmlNode);
    };

    /**
    * @class      SStylePoolMgr
    * @brief      SwndStyle��ӳ�����б�
    * 
    * Describe    
    */
    class SOUI_EXP SStylePoolMgr : public SSingleton<SStylePoolMgr>
    {
    public:
        ~SStylePoolMgr();
        
        /**
        * GetStyle
        * @brief    Get style object from pool by class name
        * @param    LPCWSTR lpszName --  name of style
        * @param [out]  SwndStyle & style --  style
        * @return   BOOL -- TRUE: success; FALSE: not exist
        * Describe  
        */    
        BOOL GetStyle(LPCWSTR lpszName,SwndStyle& style);
        
        /**
         * PushStylePool
         * @brief    push a new SStylePool to the tail of style pool list
         * @param    SStylePool * pStylePool --  the target style pool
         * @return   void
         * Describe  
         */    
        void PushStylePool(SStylePool *pStylePool);
        
        /**
         * PopStylePool
         * @brief    remove the target style pool from list
         * @param    SStylePool * pStylePool --  the target style pool
         * @return   SStylePool * -- the removed style pool
         * Describe  if pStylePool is null, it remove the last style pool from the list
         */    
        SStylePool * PopStylePool(SStylePool *pStylePool);
    protected:
        SList<SStylePool *> m_lstStylePools;
    };
}//end of namespace SOUI
