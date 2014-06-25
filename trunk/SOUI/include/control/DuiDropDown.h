/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       DuiDropDown.h
 * @brief      һ��ͨ�õ���������ģ��
 * @version    v1.0      
 * @author     soui      
 * @date       2014-05-25
 * 
 * Describe    �������������ڵĸ��� ֻ��Ҫ�������༴��
 */
#pragma once
#include "duihostwnd.h"

namespace SOUI
{

    class CDuiDropDownWnd;
    /**
     * @class      IDuiDropDownOwner
     * @brief      IDuiDropDownOwner�ӿ���
     * 
     * Describe    �������ڽӿ��� ����ֻ����һЩ�麯��
     */
    class SOUI_EXP IDuiDropDownOwner
    {
    public:
        /**
         * IDuiDropDownOwner::GetDropDownOwner
         * @brief    �����������������
         *
         * Describe  �˺����Ǵ��麯��  
         */
        virtual SWindow * GetDropDownOwner() =0;
        
        /**
         * IDuiDropDownOwner::OnDropDown
         * @brief    �������ڷ���DropDown,�����˺���
         *
         * Describe  �˺����Ǵ��麯��
         */        
        virtual void OnDropDown(CDuiDropDownWnd *pDropDown) = 0;
        
        /**
         * IDuiDropDownOwner::OnCloseUp
         * @brief    �������ڷ���CloseUp,�����˺���
         *
         * Describe  �˺����Ǵ��麯��  
         */
        virtual void OnCloseUp(CDuiDropDownWnd *pDropDown,UINT uCode) = 0;
    };

    /**
     * @class      CDuiDropDownWnd
     * @brief      ����������
     * 
     * Describe    ���������� ֻ��Ҫ�̳д��༴��
     */
    class SOUI_EXP CDuiDropDownWnd : public CDuiHostWnd , public CDuiMessageFilter
    {
    public:
    
        /**
         * CDuiDropDownWnd::CDuiDropDownWnd
         * @brief    ���캯��
         * @param    IDuiDropDownOwner* pOwner -- ������ָ��
         *
         * Describe  CDuiDropDownWnd��Ĺ��캯��
         */        
        CDuiDropDownWnd(IDuiDropDownOwner* pOwner);

        /**
         * CDuiDropDownWnd::~CDuiDropDownWnd
         * @brief    ��������
         *
         * Describe  CDuiDropDownWnd�����������
         */        
        virtual ~CDuiDropDownWnd();

        /**
         * CDuiDropDownWnd::Create
         * @brief    �������ڴ�������
         * @param     LPCRECT lpRect -- �������ڴ�С
         * @param     LPVOID lParam -- ���������ڹ���������
         * @param     DWORD dwStyle -- ����������ʽ
         * @param     DWORD dwExStyle -- ����������չ��ʽ
         * 
         * Describe  �˺������麯��������ָ����������������ԡ�������ʽ����С��
         */        
        virtual BOOL Create(LPCRECT lpRect,LPVOID lParam,DWORD dwStyle=WS_POPUP,DWORD dwExStyle=WS_EX_TOOLWINDOW|WS_EX_TOPMOST);

        /**
         * CDuiDropDownWnd::EndDropDown
         * @brief    ������������
         * @param    UINT uCode -- ��Ϣ�� Ĭ����IDCANCEL
         * 
         * Describe  �˺���������������������(ע�Ϳ��ܲ��� ����ָ��)
         */
        void EndDropDown(UINT uCode=IDCANCEL);
    protected:
        /**
         * CDuiDropDownWnd::OnLButtonDown
         * @brief    �������������������¼�
         * @param    UINT nFlags -- ��־
         * @param    CPoint point -- �������
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnLButtonDown(UINT nFlags, CPoint point);

        /**
         * CDuiDropDownWnd::OnLButtonDown
         * @brief    ��������������̧���¼�
         * @param    UINT nFlags -- ��־
         * @param    CPoint point -- �������
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnLButtonUp(UINT nFlags, CPoint point);

        /**
         * CDuiDropDownWnd::OnKeyDown
         * @brief    ���̰����¼�
         * @param    UINT nChar -- ������Ӧ����ֵ 
         * @param    UINT nRepCnt -- �ظ�����
         * @param    UINT nFlags -- ��־
         * 
         * Describe  �˺�������Ϣ��Ӧ����
         */        
        void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

        /**
         * CDuiDropDownWnd::OnKillFocus
         * @brief    ��������ʧȥ������Ϣ��Ӧ����
         * @param    HWND wndFocus -- ��ý��㴰�ھ��
         * 
         * Describe  ��������ʧȥ����ʱ����ô˺����������ǻ�ý���Ĵ��ھ��
         */        
        void OnKillFocus(HWND wndFocus);

        /**
         * CDuiDropDownWnd::OnDestroy
         * @brief    ������������
         * 
         * Describe  �˺���������������������
         */        
        void OnDestroy();

        /**
         * CDuiDropDownWnd::OnActivateApp
         * @brief    �������ڼ������ֹͣ
         * @param    BOOL bActive  -- ���ڼ����־
         * @param    DWORD dwThreadID -- �߳�ID
         * 
         * Describe  ���������ڼ���ʱ����ô˺�������ϸ˵������鿴MSDN
         */        
        void OnActivateApp(BOOL bActive, DWORD dwThreadID);

        /**
         * CDuiDropDownWnd::OnMouseActivate
         * @brief    ������������
         * @param    HWND wndTopLevel  -- ��������
         * @param    UINT nHitTest -- ָ�����в�������
         * @param    UINT message -- �����Ϣ��
         * 
         * Describe  ���������Ч����ʱ�������û�������갴ť���ô˺��� 
         *           ��ϸ˵������鿴MSDN
         */        
        int OnMouseActivate(HWND wndTopLevel, UINT nHitTest, UINT message);

        virtual void OnFinalMessage(HWND);
        
        virtual BOOL PreTranslateMessage(MSG* pMsg);
    protected:
        IDuiDropDownOwner* m_pOwner; /**< ���������� */
        BOOL                m_bClick; /**< ����״̬ */
        UINT                m_uExitCode; /**< �˳���Ϣ�� */

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
