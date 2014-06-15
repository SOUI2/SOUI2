/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserverd.
 * 
 * @file       DuiCalendar.h
 * @brief      ����ʱ��ؼ�
 * @version    v1.0      
 * @author     soui      
 * @date       2014-05-25
 * 
 * Describe    ������������ؼ�
 */

#pragma once
#include "duiwnd.h"

namespace SOUI
{
#define START_YEAR    1901
#define END_YEAR    2050
    /**
     * @class      CCalendarCore
     * @brief      ����������
     * 
     * Describe    �����������ĺ����� �󲿷ֺ������Ǿ�̬����
     */
    class CCalendarCore
    {
    public:
        /**
         * CCalendarCore::IsLeapYear
         * @brief    �ж�iYear�ǲ�������
         * @param    WORD iYear -- ���жϵ����
         * @return   TRUE -- ����  FALSE -- ������
         *
         * Describe  �ж��Ƿ�������  
         */        
        static BOOL IsLeapYear(WORD iYear)
        {
            return !(iYear%4)&&(iYear%100) || !(iYear%400);
        }

        /**
         * CCalendarCore::WeekDay
         * @brief    �������ڼ�
         * @param    WORD iYear -- ��
         * @param    WORD iMonth -- ��
         * @param    WORD iDay -- ��
         * @return   ����:0,1,2,3,4,5,6�ֱ��Ӧ�ա�һ�����������ġ��塢��
         *
         * Describe  ���������շ������ڼ� 
         *           ע��:��Ч��Χ��(1��1��1�� --- 65535��12��31��)
         */
        static WORD WeekDay(WORD iYear, WORD iMonth, WORD iDay);

        /**
         * CCalendarCore::MonthWeeks
         * @brief    ����ָ���·ݵ�����
         * @param    WORD iYear -- ��
         * @param    WORD iMonth -- ��
         * @return   ����
         *
         * Describe  �������·��ر����м���
         *           ע��:��Ч��Χ��(1��1��1�� --- 65535��12��31��)
         */
        static WORD MonthWeeks(WORD iYear, WORD iMonth);
        
        /**
         * CCalendarCore::DayWeek
         * @brief    ����ĳ���ڵ��µĵڼ���
         * @param    WORD iYear -- ��
         * @param    WORD iMonth -- ��
         * @param    WORD iDay -- ��         
         * @return   ����
         *
         * Describe  ���������գ����������ڵ��µĵڼ���
         *           ע��:��Ч��Χ��(1��1��1�� --- 65535��12��31��)
         */
        static WORD DayWeek(WORD iYear, WORD iMonth, WORD iDay);

        /**
         * CCalendarCore::MonthDays
         * @brief    ����ָ���·ݵ�����
         * @param    WORD iYear -- ��
         * @param    WORD iMonth -- ��
         * @return   ���ظ��µ�����
         *
         * Describe  �������·��ر��µ����� 
         *           ע��:��Ч��Χ��(1��1�� --- 65535��12��)
         */
        static WORD MonthDays(WORD iYear, WORD iMonth);

        /**
         * CCalendarCore::LunarMonthDays
         * @brief    ָ���������·ַ��ظ��µ�����
         * @param    WORD iLunarYear -- ��
         * @param    WORD iLunarMonth -- ��
         * @return   ���ظ��µ�����
         *
         * Describe  ���iLunarMonthΪ���£�����Ϊ�ڶ���iLunarMonth�µ�������
         *           �������Ϊ0  ע��:��Ч��Χ��(1901��1��---2050��12��)
         */
        static LONG LunarMonthDays(WORD iLunarYear, WORD iLunarMonth);

        /**
         * CCalendarCore::LunarYearDays
         * @brief    ָ�������귵�ظ����������
         * @param    WORD iLunarYear -- ��
         * @return   ���ظ��������������
         *
         * Describe  ������ݣ����ظ���������������
         *           ע��:��Ч��Χ��(1901��1��---2050��12��)
         */
        static WORD LunarYearDays(WORD iLunarYear);

        /**
         * CCalendarCore::LunarYearDays
         * @brief    ָ�������귵�ظ���������·�
         * @param    WORD iLunarYear -- ��
         * @return   ����0��ʾ����û������ �������·�
         *
         * Describe  ָ�������귵�ظ���������·�
         *           ע��:��Ч��Χ��(1901��1��---2050��12��)
         */
        static WORD GetLeapMonth(WORD iLunarYear);

        /**
         * CCalendarCore::FormatLunarYear
         * @brief    ��ʽ�������ʾ��ʽ
         * @param    WORD iLunarYear -- ��
         * @param    TCHAR *pBuffer -- ��������������ʽ�����ַ���
         *
         * Describe  ָ�������귵�ز��ø�֧���귨
         */        
        static void FormatLunarYear(WORD  iYear, TCHAR *pBuffer);

        /**
         * CCalendarCore::FormatMonth
         * @brief    ��ʽ���·���ʾ��ʽ
         * @param    WORD iMonth -- ��
         * @param    TCHAR *pBuffer -- ��������������ʽ�����ַ���
         * @param    BOOL bLunar -- �Ƿ������� Ĭ����TRUE
         *
         * Describe  �������������һ�·��ص���"����",�������"һ��"
         */        
        static void FormatMonth(WORD iMonth, TCHAR *pBuffer, BOOL bLunar = TRUE);
        
        /**
         * CCalendarCore::FormatLunarDay
         * @brief    ��ʽ��������ʾ��ʽ
         * @param    WORD iDay -- ��
         * @param    TCHAR *pBuffer -- ��������������ʽ�����ַ���
         *
         * Describe  Ĭ���ǰ����������أ�����˵"����"
         */
        static void FormatLunarDay(WORD  iDay, TCHAR *pBuffer);

        /**
         * CCalendarCore::CalcDateDiff
         * @brief    ���ع���ĳ����������������
         * @param    WORD iEndYear  -- ������
         * @param    WORD iEndMonth  -- ������
         * @param    WORD iEndDay  -- ������
         * @param    WORD iStartYear  -- ��ʼ�� Ĭ��ֵ1901
         * @param    WORD iStartMonth  -- ��ʼ�� Ĭ��ֵ1
         * @param    WORD iStartDay  -- ��ʼ�� Ĭ��ֵ1
         * @return   ��������
         *
         * Describe  ������������֮���������
         */
        static LONG CalcDateDiff(WORD iEndYear, WORD iEndMonth, WORD iEndDay,
            WORD iStartYear = START_YEAR, 
            WORD iStartMonth =1, WORD iStartDay =1);

        /**
         * CCalendarCore::GetLunarDate
         * @brief    �������������Լ���������
         * @param    WORD iYear  -- ������
         * @param    WORD iMonth  -- ������
         * @param    WORD iDay  -- ������
         * @param    WORD &iLunarYear  -- ������� ������ 
         * @param    WORD &iLunarMonth  -- ������� ������ 
         * @param    WORD &iLunarDay  -- ������� ������ 
         * @return   ���ؽ������ 0 - 24 0���ǽ���
         *
         * Describe  ���빫�����ڣ����ض�Ӧ���������ںͽ��� 
         *           ע��:��Ч��Χ��(1901��1��1��---2050��12��31��)
         */
        static WORD GetLunarDate(WORD iYear, WORD iMonth, WORD iDay,
            WORD &iLunarYear, WORD &iLunarMonth, WORD &iLunarDay);

    protected:
        /**
         * CCalendarCore::l_CalcLunarDate
         * @brief    ������������
         * @param    WORD iYear  -- ������� ������ 
         * @param    WORD iMonth  -- ������� ������ 
         * @param    WORD iDay  -- ������� ������ 
         * @param    LONG iSpanDays  -- �������ھ���1901��1��1������
         *
         * Describe  ���빫�����ڣ����ض�Ӧ����������
         *           ע��:��Ч��Χ��(1901��1��1��---2050��12��31��)
         */
        static void   l_CalcLunarDate(WORD &iYear, WORD &iMonth ,WORD &iDay, LONG iSpanDays);
        
        /**
         * CCalendarCore::l_GetLunarHolDay
         * @brief    ��������
         * @param    WORD iYear  -- ������ 
         * @param    WORD iMonth  -- ������ 
         * @param    WORD iDay  -- ������ 
         * @return   0-24  0���ǽ���
         *
         * Describe  �жϵ����Ƿ���24������һ�� ������Ƿ���0���򷵻ض�Ӧ����
         */
        static WORD   l_GetLunarHolDay(WORD iYear, WORD iMonth, WORD iDay);
    };

    /**
     * @class      CDuiCalendar
     * @brief      ������
     * 
     * Describe    �����������ĺ����� �󲿷ֺ������Ǿ�̬����
     */
    class CDuiCalendar : public CDuiWindow
    {
    public:
        SOUI_CLASS_NAME(CDuiCalendar, "calendar")
        
        /**
         * CCalendarCore::CDuiCalendar
         * @brief    ���캯��
         * @param    WORD iYear -- ��
         * @param    WORD iMonth -- ��
         * @param    WORD iDay -- ��
         *
         * Describe  ���캯��
         */
        CDuiCalendar(WORD iYear, WORD iMonth, WORD iDay);

        /**
         * CDuiCalendar::CDuiCalendar
         * @brief    ���캯��
         *
         * Describe  ���캯��
         */
        CDuiCalendar();

    public:
        /**
         * CDuiCalendar::GetYear
         * @brief    �����
         *
         * Describe  �����
         */
        WORD GetYear(){return m_iYear;}
        
        /**
         * CDuiCalendar::GetMonth
         * @brief    �����
         *
         * Describe  �����
         */
        WORD GetMonth(){return m_iMonth;}

        /**
         * CDuiCalendar::GetDay
         * @brief    �����
         *
         * Describe  �����
         */
        WORD GetDay(){return m_iDay;}
        
        /**
         * CDuiCalendar::GetDate
         * @brief    �������
         * @param    WORD iYear -- ��
         * @param    WORD iMonth -- ��
         * @param    WORD iDay -- ��         
         *
         * Describe  �������
         */
        void GetDate(WORD &iYear, WORD &iMonth, WORD &iDay);

        /**
         * CDuiCalendar::SetDate
         * @brief    ��������
         * @param    WORD iYear -- ��
         * @param    WORD iMonth -- ��
         * @param    WORD iDay -- ��         
         *
         * Describe  ��������
         */        
        BOOL SetDate(WORD iYear, WORD iMonth, WORD iDay);

    protected:
      /**
       * CDuiCalendar::Init
       * @brief    ��ʼ������
       *
       * Describe  ��ʼ������
       */            
        void Init();

        /**
         * CDuiCalendar::OnPaint
         * @brief    �滭��Ϣ
         * @param    CDCHandle dc -- �����豸���
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnPaint(CDCHandle dc);
        
        /**
         * CDuiCalendar::OnLButtonDown
         * @brief    ������̧���¼�
         * @param    UINT nFlags -- ��־
         * @param    CPoint point -- �������
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnLButtonDown(UINT nFlags, CPoint point);
        
        /**
         * CDuiCalendar::OnMouseMove
         * @brief    ����ƶ��¼�
         * @param    UINT nFlags -- ��־
         * @param    CPoint point -- �������
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnMouseMove(UINT nFlags,CPoint pt);
        
        /**
         * CDuiCalendar::OnMouseLeave
         * @brief    ����뿪�¼�
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnMouseLeave();

        
        /**
         * CDuiCalendar::Load
         * @brief    ����xml
         * @param    pugi::xml_node xmlNode -- xml�ڵ�    
         *
         * Describe  ͨ������xml�����촰��
         */
        virtual BOOL Load(pugi::xml_node xmlNode);
    protected:
        /**
         * CDuiCalendar::GetDayRect
         * @brief    ������ڵ�����
         * @param    WORD iDay  -- ����         
         *
         * Describe  �����������ڵ����Լ����ڼ�������������
         */    
        CRect GetDayRect(WORD iDay);
        WORD HitTest(CPoint  pt);

        /**
         * CDuiCalendar::DrawTitle
         * @brief    ���Ʊ���
         * @param    CDCHandle dc -- �����豸���         
         *
         * Describe  ����ֻ�Ǹ��������ڵ����꣬����CRect��ʾ
         */    
        void DrawTitle(CDCHandle &dc);
        
        /**
         * CDuiCalendar::DrawDate
         * @brief    ��������
         * @param    CDCHandle dc -- �����豸���         
         *
         * Describe  ��������
         */            
        void DrawDate(CDCHandle &dc);

        /**
         * CDuiCalendar::DrawDay
         * @brief    ��������--��
         * @param    CDCHandle dc -- �����豸���         
         *
         * Describe  ��������--��
         */    
        void DrawDay(CDCHandle &dc,CRect & rcDay,WORD iDay );
        
        /**
         * CDuiCalendar::RedrawDay
         * @brief    ���»�������--��
         * @param    CDCHandle dc -- �����豸���         
         *
         * Describe  ���»�������--��
         */    
        void RedrawDay(WORD iDay);

        /**
         * CDuiCalendar::OnTodayClick
         * @brief    ������---��ĵ����¼�
         *
         * Describe  ������---��ĵ����¼�
         */            
        bool OnTodayClick(CDuiWindow * pSender, LPDUINMHDR pNmhdr);

        SOUI_ATTRS_BEGIN()
            ATTR_INT("titleHeight", m_nTitleHei, FALSE)
            ATTR_INT("footerHeight", m_nFooterHei, FALSE)
            ATTR_COLOR("crWeekend", m_crWeekend, FALSE)
            ATTR_COLOR("crTitleBack", m_crTitleBack, FALSE)
            ATTR_COLOR("crDay", m_crDay, FALSE)
            ATTR_SKIN("daySkin", m_pDaySkin, FALSE)
            ATTR_SKIN("titleSkin", m_pTitleSkin, FALSE)
            ATTR_STRINGT("title-1", m_strTitle[0], FALSE)
            ATTR_STRINGT("title-2", m_strTitle[1], FALSE)
            ATTR_STRINGT("title-3", m_strTitle[2], FALSE)
            ATTR_STRINGT("title-4", m_strTitle[3], FALSE)
            ATTR_STRINGT("title-5", m_strTitle[4], FALSE)
            ATTR_STRINGT("title-6", m_strTitle[5], FALSE)
            ATTR_STRINGT("title-7", m_strTitle[6], FALSE)
        SOUI_ATTRS_END()

        WND_MSG_MAP_BEGIN()
            MSG_WM_PAINT(OnPaint)
            MSG_WM_LBUTTONDOWN(OnLButtonDown)
            MSG_WM_MOUSEMOVE(OnMouseMove)
            MSG_WM_MOUSELEAVE(OnMouseLeave)
        WND_MSG_MAP_END()
    protected:
        int             m_nTitleHei;    /**< ��ͷ�߶� */
        int             m_nFooterHei;   /**< ��β�߶� */
        CDuiSkinBase    *m_pDaySkin;    /**< ������Ƥ�� */
        CDuiSkinBase    *m_pTitleSkin;  /**< ��ͷƤ�� */

        COLORREF        m_crWeekend;    /**< ��ĩ������ɫ */
        COLORREF        m_crTitleBack;  /**< ��ͷ����ɫ */
        COLORREF        m_crDay;        /**< ѡ��������ɫ */
        COLORREF        m_crDayBack;    /**< ѡ�����ڱ�����ɫ */
        CDuiStringT     m_strTitle[7];  /**< ��ͷ�ı� */

        WORD    m_iYear, m_iMonth, m_iDay; /**< ������ */
        int        m_iHoverDay;

    };
}//end of namespace

