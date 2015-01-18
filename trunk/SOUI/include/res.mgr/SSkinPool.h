/**
* Copyright (C) 2014-2050 SOUI�Ŷ�
* All rights reserved.
* 
* @file       SSkinPool.h
* @brief      SkinObj Pool
* @version    v1.0      
* @author     soui      
* @date       2014-05-28
* 
* Describe    ����Skin Object
*/

#pragma once
#include "core/SSingletonMap.h"
#include "interface/Sskinobj-i.h"
#include <unknown/obj-ref-impl.hpp>

#define GETSKIN(p1) SSkinPoolMgr::getSingleton().GetSkin(p1)
#define GETBUILTINSKIN(p1) SSkinPoolMgr::getSingleton().GetBuiltinSkin(p1)
#define GETSKINPOOLMGR SSkinPoolMgr::getSingletonPtr()
namespace SOUI
{
    //ϵͳ����Ƥ������
    enum SYS_SKIN
    {
        SKIN_SYS_CHECKBOX=0,            //L"_skin.sys.checkbox",
        SKIN_SYS_RADIO,                 //L"_skin.sys.radio",
        SKIN_SYS_FOCUSCHECKBOX,         //L"_skin.sys.focuscheckbox",
        SKIN_SYS_FOCUSRADIO,            //L"_skin.sys.focusradio",
        SKIN_SYS_BTN_NORMAL,            //L"_skin.sys.btn.normal",
        SKIN_SYS_SCROLLBAR,             //L"_skin.sys.scrollbar",
        SKIN_SYS_BORDER,                //L"_skin.sys.border",
        SKIN_SYS_DROPBTN,               //L"_skin.sys.dropbtn",
        SKIN_SYS_TREE_TOGGLE,           //L"_skin.sys.tree.toggle",
        SKIN_SYS_TREE_CHECKBOX,         //L"_skin.sys.tree.checkbox"
        SKIN_SYS_TAB_PAGE,              //L"_skin.sys.tab.page",
        SKIN_SYS_HEADER,                //L"_skin.sys.header"
        SKIN_SYS_SPLIT_VERT,            //L"_skin.sys.split.vert",
        SKIN_SYS_SPLIT_HORZ,            //L"_skin.sys.split.horz",
        SKIN_SYS_PROG_BKGND,            //L"_skin.sys.prog.bkgnd",
        SKIN_SYS_PROG_BAR,              //L"_skin.sys.prog.bar",
        SKIN_SYS_VERT_PROG_BKGND,       //L"_skin.sys.vert.prog.bkgnd",
        SKIN_SYS_VERT_PROG_BAR,         //L"_skin.sys.vert.prog.bar",
        SKIN_SYS_SLIDER_THUMB,          //L"_skin.sys.slider.thumb",

        SKIN_SYS_BTN_CLOSE,             //L"_skin.sys.btn.close",
        SKIN_SYS_BTN_MINIMIZE,          //L"_skin.sys.btn.minimize",
        SKIN_SYS_BTN_MAXMIZE,           //L"_skin.sys.btn.maxmize",
        SKIN_SYS_BTN_RESTORE,           //L"_skin.sys.btn.restore",

        SKIN_SYS_MENU_CHECK,            //L"_skin.sys.menu.check",
        SKIN_SYS_MENU_SEP,              //L"_skin.sys.menu.sep",
        SKIN_SYS_MENU_BORDER,           //L"_skin.sys.menu.border",
        SKIN_SYS_MENU_SKIN,             //L"_skin.sys.menu.skin",
        SKIN_SYS_ICONS,                 //L"_skin.sys.icons",
        SKIN_SYS_WND_BKGND,             //L"_skin.sys.wnd.bkgnd",
        
        SKIN_SYS_COUNT,
    };

typedef ISkinObj * SSkinPtr;

/**
* @class      SSkinPool
* @brief      name��ISkinObj��ӳ���
* 
* Describe    
*/
class SOUI_EXP SSkinPool :public SCmnMap<SSkinPtr,SStringW>, public TObjRefImpl2<IObjRef,SSkinPool>
{
public:
    SSkinPool();

    virtual ~SSkinPool();

    /**
     * GetSkin
     * @brief    �����ָ��nameƥ���SkinObj
     * @param    LPCWSTR strSkinName --    Name of Skin Object     
     * @return   ISkinObj*  -- �ҵ���Skin Object
     * Describe  
     */    
    ISkinObj* GetSkin(LPCWSTR strSkinName);

    /**
     * LoadSkins
     * @brief    ��XML�м���Skin�б�
     * @param    pugi::xml_node xmlNode --  ����SkinObj��XML��     
     * @return   int -- �ɹ����ص�SkinObj����
     * Describe  
     */    
    int LoadSkins(pugi::xml_node xmlNode);
protected:
    static void OnKeyRemoved(const SSkinPtr & obj);
};

/**
* @class      SSkinPoolMgr
* @brief      ����һ��name��ISkinObj��ӳ�����б�
* 
* Describe    
*/
class SOUI_EXP SSkinPoolMgr : public SSingleton<SSkinPoolMgr> 
{
public:
    SSkinPoolMgr();
    ~SSkinPoolMgr();

    /**
    * GetSkin
    * @brief    �����ָ��nameƥ���SkinObj
    * @param    LPCWSTR strSkinName --    Name of Skin Object     
    * @return   ISkinObj*  -- �ҵ���Skin Object
    * Describe  
    */    
    ISkinObj* GetSkin(LPCWSTR strSkinName);
    
    /**
     * PushSkinPool
     * @brief    ���б�������һ���µ�SSkinPool����
     * @param    SSkinPool * pSkinPool --    SSkinPool����   
     * @return   void
     * Describe  
     */    
    void PushSkinPool(SSkinPool *pSkinPool);

    /**
     * PopSkinPool
     * @brief    ����һ��SSkinPool����
     * @param    SSkinPool * pSkinPool --   ׼��������SSkinPool����
     * @return   SSkinPool *    ���б����ҵ��󵯳���SSkinPool����
     * Describe  �ڽ�SkinPool���õ���PopSkinPool
     */    
    SSkinPool * PopSkinPool(SSkinPool *pSkinPool);

    /**
     * GetBuiltinSkin
     * @brief    ���SOUIϵͳ�ڽ�������SkinObj
     * @param    SYS_SKIN uID --  �ڽ�SKIN��ID
     * @return   ISkinObj * ��SKINID��Ӧ��ISkinObj
     * Describe  ���ܷ���ʧ��
     */    
    ISkinObj * GetBuiltinSkin(SYS_SKIN uID);
    
    /**
     * GetBuiltinSkinPool
     * @brief    ��ù����ڽ�SkinPool����
     * @return   SSkinPool * -- �ڽ�SkinPoolָ��
     * Describe  �û��ڴ����д�����SkinObj���Խ����ڽ�SkinPool����
     */    
    SSkinPool * GetBuiltinSkinPool(){return m_bulitinSkinPool;}
protected:
    SList<SSkinPool *> m_lstSkinPools;
    CAutoRefPtr<SSkinPool> m_bulitinSkinPool;

};


}//namespace SOUI