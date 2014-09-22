#pragma once

#include <unknown/obj-ref-i.h>
#include "../core/smsgloop.h"

namespace SOUI
{
    /** 
     * @struct    TIPID
     * @brief     ��ʶһ��tooltip��ID
     *
     * Describe
     */
    struct TIPID
    {
        DWORD dwHi; //ID1, ��������һ��SWND��
        DWORD dwLow;//ID2, �������渽������
    };

    /** 
     * @struct    IToolTip
     * @brief     tooltip����ӿ�
     *
     * Describe
     */
    struct IToolTip : public IMessageFilter
    {
        /**
         * UpdateTip
         * @brief    ���µ�ǰ��tooltip
         * @param    const TIPID & id --  tooltip��ID
         * @param    CRect rc --  tooltip�ĸ�Ӧ��
         * @param    LPCTSTR pszTip --  tooltip�ַ���
         * @return   void 
         *
         * Describe  
         */
        virtual void UpdateTip(const TIPID &id, CRect rc,LPCTSTR pszTip) = 0;

        /**
         * ClearTip
         * @brief    �����ǰ��tooltip
         * @return   void 
         *
         * Describe  
         */
        virtual void ClearTip() = 0;

        /**
         * RelayEvent
         * @brief    �����Ϣ���м�
         * @param    const MSG * pMsg --  �����Ϣ
         * @return   void 
         *
         * Describe  
         */
        virtual void RelayEvent(const MSG *pMsg) = 0;
    };

    /** 
     * @struct    IToolTipFactory
     * @brief     tooltip�೧
     *
     * Describe
     */
    struct IToolTipFactory : IObjRef
    {
        /**
         * CreateToolTip
         * @brief    ����tooltip����
         * @param    HWND hHost --  soui host
         * @return   IToolTip * ������tooltip����
         *
         * Describe  ��Ҫ��hHost��Ϊtooltip��Owner��������ܵ��³��������쳣��
         */
        virtual IToolTip * CreateToolTip(HWND hHost) = 0;

        /**
         * DestroyToolTip
         * @brief    ����tooltip����
         * @param    IToolTip * pToolTip --  ������tooltip
         * @return   void 
         *
         * Describe  
         */
        virtual void DestroyToolTip(IToolTip *pToolTip) = 0;
    };
}