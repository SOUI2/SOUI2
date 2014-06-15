/**
 * Copyright (C) 2014-2050 SOUI团队
 * All rights reserverd.
 * 
 * @file       DuiDropDown.h
 * @brief      一个通用的下拉窗口模块
 * @version    v1.0      
 * @author     soui      
 * @date       2014-05-25
 * 
 * Describe    此类是下拉窗口的父类 只需要派生该类即可
 */
#pragma once
#include "duihostwnd.h"

namespace SOUI
{

    class CDuiDropDownWnd;
    /**
     * @class      IDuiDropDownOwner
     * @brief      IDuiDropDownOwner接口类
     * 
     * Describe    下拉窗口接口类 里面只定义一些虚函数
     */
    class SOUI_EXP IDuiDropDownOwner
    {
    public:
        /**
         * IDuiDropDownOwner::GetDropDownOwner
         * @brief    获得下拉窗口所属者
         *
         * Describe  此函数是纯虚函数  
         */
        virtual CDuiWindow * GetDropDownOwner() =0;
        
        /**
         * IDuiDropDownOwner::OnDropDown
         * @brief    下拉窗口发生DropDown,触发此函数
         *
         * Describe  此函数是纯虚函数
         */        
        virtual void OnDropDown(CDuiDropDownWnd *pDropDown) = 0;
        
        /**
         * IDuiDropDownOwner::OnCloseUp
         * @brief    下拉窗口发生CloseUp,触发此函数
         *
         * Describe  此函数是纯虚函数  
         */
        virtual void OnCloseUp(CDuiDropDownWnd *pDropDown,UINT uCode) = 0;
    };

    /**
     * @class      CDuiDropDownWnd
     * @brief      下拉窗口类
     * 
     * Describe    下拉窗口类 只需要继承此类即可
     */
    class SOUI_EXP CDuiDropDownWnd : public CDuiHostWnd , public CDuiMessageFilter
    {
    public:
    
        /**
         * CDuiDropDownWnd::CDuiDropDownWnd
         * @brief    构造函数
         * @param    IDuiDropDownOwner* pOwner -- 所属者指针
         *
         * Describe  CDuiDropDownWnd类的构造函数
         */        
        CDuiDropDownWnd(IDuiDropDownOwner* pOwner);

        /**
         * CDuiDropDownWnd::~CDuiDropDownWnd
         * @brief    析构函数
         *
         * Describe  CDuiDropDownWnd类的析构函数
         */        
        virtual ~CDuiDropDownWnd();

        /**
         * CDuiDropDownWnd::Create
         * @brief    下拉窗口创建函数
         * @param     LPCRECT lpRect -- 下拉窗口大小
         * @param     LPVOID lParam -- 与下拉窗口关联的数据
         * @param     DWORD dwStyle -- 下拉窗口样式
         * @param     DWORD dwExStyle -- 下拉窗口扩展样式
         * 
         * Describe  此函数是虚函数，用于指定下拉窗口相关属性。比如样式，大小等
         */        
        virtual BOOL Create(LPCRECT lpRect,LPVOID lParam,DWORD dwStyle=WS_POPUP,DWORD dwExStyle=WS_EX_TOOLWINDOW|WS_EX_TOPMOST);

        /**
         * CDuiDropDownWnd::EndDropDown
         * @brief    下拉窗口销毁
         * @param    UINT uCode -- 消息码 默认是IDCANCEL
         * 
         * Describe  此函数是用于销毁下拉窗口(注释可能不对 请大家指点)
         */
        void EndDropDown(UINT uCode=IDCANCEL);
    protected:
        /**
         * CDuiDropDownWnd::OnLButtonDown
         * @brief    下拉窗口鼠标左键按下事件
         * @param    UINT nFlags -- 标志
         * @param    CPoint point -- 鼠标坐标
         *
         * Describe  此函数是消息响应函数
         */
        void OnLButtonDown(UINT nFlags, CPoint point);

        /**
         * CDuiDropDownWnd::OnLButtonDown
         * @brief    下拉窗口鼠标左键抬起事件
         * @param    UINT nFlags -- 标志
         * @param    CPoint point -- 鼠标坐标
         *
         * Describe  此函数是消息响应函数
         */
        void OnLButtonUp(UINT nFlags, CPoint point);

        /**
         * CDuiDropDownWnd::OnKeyDown
         * @brief    键盘按下事件
         * @param    UINT nChar -- 按键对应的码值 
         * @param    UINT nRepCnt -- 重复次数
         * @param    UINT nFlags -- 标志
         * 
         * Describe  此函数是消息响应函数
         */        
        void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

        /**
         * CDuiDropDownWnd::OnKillFocus
         * @brief    下拉窗口失去焦点消息响应函数
         * @param    HWND wndFocus -- 获得焦点窗口句柄
         * 
         * Describe  下拉窗口失去焦点时候调用此函数，参数是获得焦点的窗口句柄
         */        
        void OnKillFocus(HWND wndFocus);

        /**
         * CDuiDropDownWnd::OnDestroy
         * @brief    下拉窗口销毁
         * 
         * Describe  此函数是用于销毁下拉窗口
         */        
        void OnDestroy();

        /**
         * CDuiDropDownWnd::OnActivateApp
         * @brief    下拉窗口激活或者停止
         * @param    BOOL bActive  -- 窗口激活标志
         * @param    DWORD dwThreadID -- 线程ID
         * 
         * Describe  当下拉窗口激活时候调用此函数。详细说明，请查看MSDN
         */        
        void OnActivateApp(BOOL bActive, DWORD dwThreadID);

        /**
         * CDuiDropDownWnd::OnMouseActivate
         * @brief    下拉窗口销毁
         * @param    HWND wndTopLevel  -- 顶级窗口
         * @param    UINT nHitTest -- 指定命中测试区号
         * @param    UINT message -- 鼠标消息码
         * 
         * Describe  当光标在无效窗口时，并且用户按下鼠标按钮调用此函数 
         *           详细说明，请查看MSDN
         */        
        int OnMouseActivate(HWND wndTopLevel, UINT nHitTest, UINT message);

        virtual void OnFinalMessage(HWND);
        
        virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
        IDuiDropDownOwner* m_pOwner; /**< 窗口所属者 */
        BOOL                m_bClick; /**< 单击状态 */
        UINT                m_uExitCode; /**< 退出消息码 */

        BEGIN_MSG_MAP_EX(CDuiDropDownWnd)
            MSG_WM_LBUTTONDOWN(OnLButtonDown)
            MSG_WM_LBUTTONUP(OnLButtonUp)
            MSG_WM_KEYDOWN(OnKeyDown);
            MSG_WM_KILLFOCUS(OnKillFocus)
            MSG_WM_DESTROY(OnDestroy)
            MSG_WM_ACTIVATEAPP(OnActivateApp)
            MSG_WM_MOUSEACTIVATE(OnMouseActivate)
            CHAIN_MSG_MAP(CDuiHostWnd)
        END_MSG_MAP()
    };

}//end of namespace SOUI
