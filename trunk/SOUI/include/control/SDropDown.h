/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 * 
 * @file       SDropDown.h
 * @brief      һ��ͨ�õ���������ģ��
 * @version    v1.0      
 * @author     soui      
 * @date       2014-05-25
 * 
 * Describe    �������������ڵĸ��� ֻ��Ҫ�������༴��
 */
#pragma once
#include "core/shostwnd.h"

namespace SOUI
{

    class SDropDownWnd;
    /**
     * @class      ISDropDownOwner
     * @brief      ISDropDownOwner�ӿ���
     * 
     * Describe    �������ڽӿ��� ����ֻ����һЩ�麯��
     */
    class SOUI_EXP ISDropDownOwner
    {
    public:
        /**
         * ISDropDownOwner::GetDropDownOwner
         * @brief    �����������������
         *
         * Describe  �˺����Ǵ��麯��  
         */
        virtual SWindow * GetDropDownOwner() =0;
        
        /**
         * ISDropDownOwner::OnDropDown
         * @brief    �������ڷ���DropDown,�����˺���
         *
         * Describe  �˺����Ǵ��麯��
         */        
        virtual void OnDropDown(SDropDownWnd *pDropDown) = 0;
        
        /**
         * ISDropDownOwner::OnCloseUp
         * @brief    �������ڷ���CloseUp,�����˺���
         *
         * Describe  �˺����Ǵ��麯��  
         */
        virtual void OnCloseUp(SDropDownWnd *pDropDown,UINT uCode) = 0;
    };

    /**
     * @class      SDropDownWnd
     * @brief      ����������
     * 
     * Describe    ���������� ֻ��Ҫ�̳д��༴��
     */
    class SOUI_EXP SDropDownWnd : public SHostWnd, public IMessageFilter
    {
    public:
    
        /**
         * SDropDownWnd::SDropDownWnd
         * @brief    ���캯��
         * @param    ISDropDownOwner* pOwner -- ������ָ��
         *
         * Describe  SDropDownWnd��Ĺ��캯��
         */        
        SDropDownWnd(ISDropDownOwner* pOwner);

        /**
         * SDropDownWnd::~SDropDownWnd
         * @brief    ��������
         *
         * Describe  SDropDownWnd�����������
         */        
        virtual ~SDropDownWnd();

        /**
         * SDropDownWnd::Create
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
         * SDropDownWnd::EndDropDown
         * @brief    ������������
         * @param    UINT uCode -- ��Ϣ�� Ĭ����IDCANCEL
         * 
         * Describe  �˺���������������������(ע�Ϳ��ܲ��� ����ָ��)
         */
        void EndDropDown(UINT uCode=IDCANCEL);
    protected:
        /**
         * OnReleaseSwndCapture
         * @brief    ��ֹ���ڵ�ReleaseCapture
         * @return   BOOL 
         *
         * Describe  ����ReleaseCapture�����µ���SetCapture
         */
        virtual BOOL OnReleaseSwndCapture()
        {
            BOOL bRet=SHostWnd::OnReleaseSwndCapture();
            CSimpleWnd::SetCapture();
            return bRet;
        }
    
        /**
         * PreTranslateMessage
         * @brief    
         * @param    MSG * pMsg --  ��ǰ������Ϣ
         * @return   BOOL-- TRUE��Ϣ���������ٷַ���
         *
         * Describe  
         */
        virtual BOOL PreTranslateMessage(MSG* pMsg);

        /**
         * SDropDownWnd::OnLButtonDown
         * @brief    �������������������¼�
         * @param    UINT nFlags -- ��־
         * @param    CPoint point -- �������
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnLButtonDown(UINT nFlags, CPoint point);

        /**
         * SDropDownWnd::OnLButtonDown
         * @brief    ��������������̧���¼�
         * @param    UINT nFlags -- ��־
         * @param    CPoint point -- �������
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnLButtonUp(UINT nFlags, CPoint point);

        /**
         * SDropDownWnd::OnKeyDown
         * @brief    ���̰����¼�
         * @param    UINT nChar -- ������Ӧ����ֵ 
         * @param    UINT nRepCnt -- �ظ�����
         * @param    UINT nFlags -- ��־
         * 
         * Describe  �˺�������Ϣ��Ӧ����
         */        
        void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

        /**
         * SDropDownWnd::OnKillFocus
         * @brief    ��������ʧȥ������Ϣ��Ӧ����
         * @param    HWND wndFocus -- ��ý��㴰�ھ��
         * 
         * Describe  ��������ʧȥ����ʱ����ô˺����������ǻ�ý���Ĵ��ھ��
         */        
        void OnKillFocus(HWND wndFocus);

        /**
         * SDropDownWnd::OnDestroy
         * @brief    ������������
         * 
         * Describe  �˺���������������������
         */        
        void OnDestroy();

        /**
         * SDropDownWnd::OnActivateApp
         * @brief    �������ڼ������ֹͣ
         * @param    BOOL bActive  -- ���ڼ����־
         * @param    DWORD dwThreadID -- �߳�ID
         * 
         * Describe  ���������ڼ���ʱ����ô˺�������ϸ˵������鿴MSDN
         */        
        void OnActivateApp(BOOL bActive, DWORD dwThreadID);

        /**
         * SDropDownWnd::OnMouseActivate
         * @brief    ���������ʹ���ڻ
         * @param    HWND wndTopLevel  -- ��������
         * @param    UINT nHitTest -- ָ�����в�������
         * @param    UINT message -- �����Ϣ��
         * 
         * Describe  ���������Ч����ʱ�������û�������갴ť���ô˺��� 
         *           ��ϸ˵������鿴MSDN
         */        
        int OnMouseActivate(HWND wndTopLevel, UINT nHitTest, UINT message);
        
         /**
         * SDropDownWnd::OnActivate
         * @brief    ������������
         * @param    UINT nState  -- ��������
         * @param    BOOL bMinimized -- ��С����־
         * @param    HWND wndOther -- ԭ�����
         * 
         * Describe  
         *           ��ϸ˵������鿴MSDN
         */        
        void OnActivate(UINT nState, BOOL bMinimized, HWND wndOther){}//�ж���Ϣ������ֹ���ý���

        virtual void OnFinalMessage(HWND);
        
    protected:
        ISDropDownOwner* m_pOwner; /**< ���������� */
        BOOL                m_bClick; /**< ����״̬ */
        UINT                m_uExitCode; /**< �˳���Ϣ�� */

        BEGIN_MSG_MAP_EX(SDropDownWnd)
            MSG_WM_LBUTTONDOWN(OnLButtonDown)
            MSG_WM_LBUTTONUP(OnLButtonUp)
            MSG_WM_KEYDOWN(OnKeyDown);
            MSG_WM_KILLFOCUS(OnKillFocus)
            MSG_WM_DESTROY(OnDestroy)
            MSG_WM_ACTIVATE(OnActivate)
            MSG_WM_ACTIVATEAPP(OnActivateApp)
            MSG_WM_MOUSEACTIVATE(OnMouseActivate)
            CHAIN_MSG_MAP(SHostWnd)
        END_MSG_MAP()
    };

}//end of namespace SOUI
