#pragma once

#include <unknown/obj-ref-impl.hpp>

namespace SOUI
{
    class CSouiRealWndHandler :public TObjRefImpl2<IRealWndHandler,CSouiRealWndHandler>
    {
    public:
        CSouiRealWndHandler(void);
        ~CSouiRealWndHandler(void);

        virtual HWND OnRealWndCreate(SRealWnd *pRealWnd);

        /**
        * SRealWnd::OnRealWndInit
        * @brief    ��ʼ������
        * @param    SRealWnd *pRealWnd -- ����ָ��
        *
        * Describe  ��ʼ������
        */
        virtual BOOL OnRealWndInit(SRealWnd *pRealWnd){return FALSE;}

        /**
        * SRealWnd::OnRealWndDestroy
        * @brief    ���ٴ���
        * @param    SRealWnd *pRealWnd -- ����ָ��
        *
        * Describe  ���ٴ���
        */
        virtual void OnRealWndDestroy(SRealWnd *pRealWnd);

        /**
        * SRealWnd::OnRealWndSize
        * @brief    �������ڴ�С
        * @param    SRealWnd *pRealWnd -- ����ָ��
        *
        * Describe  �������ڴ�С
        */
        virtual void OnRealWndSize(SRealWnd *pRealWnd);
    };

}
