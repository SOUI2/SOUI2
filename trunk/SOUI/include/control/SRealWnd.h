/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 * 
 * @file       SRealWnd.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2014-07-06
 * 
 * Describe     
 */
#pragma  once
#include "core/Swnd.h"

//////////////////////////////////////////////////////////////////////////
// Real Window Control
// Binding a real window
//
// Usage: <realwnd id=xx wndclass="edit" wndname="name" style="00000001" exstyle="00000000"/>
//

namespace SOUI
{

/** 
 * @class     SRealWndParam
 * @brief     RealWnd���ڲ���
 *
 * Describe   RealWnd���ڲ���
 */
class SOUI_EXP SRealWndParam
{
public:
    /**
     * SRealWndParam::SRealWndParam
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    SRealWndParam();
    /**
     * SRealWndParam::~SRealWndParam
     * @brief    ��������
     *
     * Describe  ��������
     */
    ~SRealWndParam();

    SStringT m_strClassName;  /**< ���� */
    SStringT m_strWindowName; /**< ������ */
    DWORD     m_dwStyle;   /**< ������ʽ */
    DWORD     m_dwExStyle; /**< ������չ��ʽ */
    pugi::xml_document m_xmlParams;  /**< �ĵ� */
};

/** 
 * @class     SRealWnd
 * @brief     
 *
 * Describe   
 */
class SOUI_EXP SRealWnd : public SWindow
{
    SOUI_CLASS_NAME(SRealWnd, L"realwnd")
public:
    /**
     * SRealWnd::SRealWnd
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    SRealWnd();
    /**
     * SRealWnd::~SRealWnd
     * @brief    ��������
     *
     * Describe  ��������  
     */
    virtual ~SRealWnd();

    /**
     * SRealWnd::GetRealHwnd
     * @brief    ��ȡ���ھ��
     * @param    BOOL bAutoCreate -- �Զ�����
     * @return   ����HWND
     * 
     * Describe  ��ȡ���ھ��
     */
    const HWND GetRealHwnd(BOOL bAutoCreate=TRUE);

    /**
     * SRealWnd::GetRealWndParam
     * @brief    ��ȡ���ڲ���
     * @return   ����SRealWndParam
     *
     * Describe  ��ȡ���ڲ���
     */
    const SRealWndParam & GetRealWndParam()
    {
        return m_realwndParam;
    }

    /**
     * SRealWnd::SetData
     * @brief    ��ȡ��������
     * @param    LPVOID lpData -- ��������
     *
     * Describe  ��ȡ��������
     */
    void SetData(LPVOID lpData)
    {
        m_lpData=lpData;
    }

    /**
     * SRealWnd::GetData
     * @brief    ��ȡ��������
     * @return   ����LPVOID
     *
     * Describe  ��ȡ��������
     */
    const LPVOID GetData()
    {
        return m_lpData;
    }

    SOUI_ATTRS_BEGIN()
    ATTR_STRINGT(L"wndclass", m_realwndParam.m_strClassName, FALSE)
    ATTR_STRINGT(L"wndname", m_realwndParam.m_strWindowName, FALSE)
    ATTR_HEX(L"style", m_realwndParam.m_dwStyle, FALSE)
    ATTR_HEX(L"exstyle", m_realwndParam.m_dwExStyle, FALSE)
    ATTR_INT(L"init",m_bInit,FALSE)
    SOUI_ATTRS_END()
protected:
    /**
     * SRealWnd::NeedRedrawWhenStateChange
     * @brief    ״̬�޸ĺ��ػ�
     * @return   ����BOOL
     *
     * Describe  ״̬�޸ĺ��ػ�
     */
    virtual BOOL NeedRedrawWhenStateChange();
    /**
     * SRealWnd::InitFromXml
     * @brief    ��ʼ��
     * @return   ����BOOL
     *
     * Describe  ��ʼ��
     */

    virtual BOOL InitFromXml(pugi::xml_node xmlNode);

    /**
     * SRealWnd::OnWindowPosChanged
     * @brief    �޸Ĵ���λ��
     * @param    LPRECT lpWndPos -- λ��
     * @return   ����LRESULT
     *
     * Describe  �޸Ĵ���λ��
     */
    LRESULT OnWindowPosChanged(LPRECT lpWndPos);

    /**
     * SRealWnd::OnShowWindow
     * @brief    ������ʾ
     * @param    BOOL bShow -- �Ƿ���ʾ
     * @param    UINT nStatus -- ״̬
     *
     * Describe  ������ʾ
     */
    void OnShowWindow(BOOL bShow, UINT nStatus);

    /**
     * SRealWnd::OnDestroy
     * @brief    ����
     *
     * Describe  ����
     */
    void OnDestroy();

    /**
     * SRealWnd::OnPaint
     * @brief    ����
     * @param    CDCHandle dc -- �����豸
     *
     * Describe  ��Ϣ��Ӧ����  
     */
    void OnPaint(IRenderTarget *pRT) {}

    /**
     * SRealWnd::ShowRealWindow
     * @brief    ��ʾ����
     *
     * Describe  ��ʾ����
     */
    void ShowRealWindow();

    /**
     * SRealWnd::InitRealWnd
     * @brief    ��ʼ������
     *
     * Describe  ��ʼ������
     */
    BOOL InitRealWnd();

    SOUI_MSG_MAP_BEGIN()
    MSG_WM_PAINT_EX(OnPaint)
    MSG_WM_DESTROY(OnDestroy)
    MSG_WM_WINPOSCHANGED_EX(OnWindowPosChanged)
    MSG_WM_SHOWWINDOW(OnShowWindow)
    SOUI_MSG_MAP_END()

    SRealWndParam    m_realwndParam;  /**< ���ڲ��� */
    BOOL    m_bInit;  /**< �Ƿ��ʼ�� */

    HWND     m_hRealWnd;  /**< ���ھ�� */
    LPVOID    m_lpData;   /**< ���Ӳ��� */
};

/** 
 * @interface     IRealWndHandler
 * @brief     
 *
 * Describe   
 */
interface SOUI_EXP IRealWndHandler
{
    /**
     * SRealWnd::OnRealWndCreate
     * @brief    ���ڴ���
     * @param    SRealWnd *pRealWnd -- ����ָ��
     *
     * Describe  ���ڴ���
     */    
    virtual HWND OnRealWndCreate(SRealWnd *pRealWnd)=NULL;

    /**
     * SRealWnd::OnRealWndInit
     * @brief    ��ʼ������
     * @param    SRealWnd *pRealWnd -- ����ָ��
     *
     * Describe  ��ʼ������
     */
    virtual BOOL OnRealWndInit(SRealWnd *pRealWnd)=NULL;

    /**
     * SRealWnd::OnRealWndDestroy
     * @brief    ���ٴ���
     * @param    SRealWnd *pRealWnd -- ����ָ��
     *
     * Describe  ���ٴ���
     */
    virtual void OnRealWndDestroy(SRealWnd *pRealWnd)=NULL;

    /**
     * SRealWnd::OnRealWndSize
     * @brief    �������ڴ�С
     * @param    SRealWnd *pRealWnd -- ����ָ��
     *
     * Describe  �������ڴ�С
     */
    virtual void OnRealWndSize(SRealWnd *pRealWnd)=NULL;
};

}//namespace SOUI