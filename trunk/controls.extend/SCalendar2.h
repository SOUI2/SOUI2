/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 * 
 * @file       SCalendar.h
 * @brief      ����ʱ��ؼ�
 * @version    v1.0      
 * @author     soui      
 * @date       2014-05-25
 * 
 * Describe    ������������ؼ�
 */

#pragma once
#include "core/SWnd.h"

namespace SOUI
{
    /**
     * @class      SCalendar
     * @brief      ������
     * 
     * Describe    �����������ĺ����� �󲿷ֺ������Ǿ�̬����
     */
    class SCalendar2 : public SWindow
    {
    public:
        SOUI_CLASS_NAME(SCalendar2, L"calendar2")
        
        /**
         * CCalendarCore::SCalendar
         * @brief    ���캯��
         * @param    WORD iYear -- ��
         * @param    WORD iMonth -- ��
         * @param    WORD iDay -- ��
         *
         * Describe  ���캯��
         */
        SCalendar2(WORD iYear, WORD iMonth, WORD iDay);

        /**
         * SCalendar::SCalendar
         * @brief    ���캯��
         *
         * Describe  ���캯��
         */
        SCalendar2();

    public:
        /**
         * SCalendar::GetYear
         * @brief    �����
         *
         * Describe  �����
         */
        WORD GetYear(){return m_iYear;}
        
        /**
         * SCalendar::GetMonth
         * @brief    �����
         *
         * Describe  �����
         */
        WORD GetMonth(){return m_iMonth;}

        /**
         * SCalendar::GetDay
         * @brief    �����
         *
         * Describe  �����
         */
        WORD GetDay(){return m_iDay;}
        
        /**
         * SCalendar::GetDate
         * @brief    �������
         * @param    WORD iYear -- ��
         * @param    WORD iMonth -- ��
         * @param    WORD iDay -- ��         
         *
         * Describe  �������
         */
        void GetDate(WORD &iYear, WORD &iMonth, WORD &iDay);

        /**
         * SCalendar::SetDate
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
       * SCalendar::Init
       * @brief    ��ʼ������
       *
       * Describe  ��ʼ������
       */            
        void Init();

        /**
         * SCalendar::OnPaint
         * @brief    �滭��Ϣ
         * @param    IRenderTarget *pRT -- �����豸���
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnPaint(IRenderTarget *pRT);
        
        /**
         * SCalendar::OnLButtonDown
         * @brief    ������̧���¼�
         * @param    UINT nFlags -- ��־
         * @param    CPoint point -- �������
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnLButtonDown(UINT nFlags, CPoint point);
        
        /**
         * SCalendar::OnMouseMove
         * @brief    ����ƶ��¼�
         * @param    UINT nFlags -- ��־
         * @param    CPoint point -- �������
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnMouseMove(UINT nFlags,CPoint pt);
        
        /**
         * SCalendar::OnMouseLeave
         * @brief    ����뿪�¼�
         *
         * Describe  �˺�������Ϣ��Ӧ����
         */
        void OnMouseLeave();

        
        /**
         * SCalendar::Load
         * @brief    ����xml
         * @param    pugi::xml_node xmlNode -- xml�ڵ�    
         *
         * Describe  ͨ������xml�����촰��
         */
        virtual BOOL InitFromXml(pugi::xml_node xmlNode);
    protected:
        /**
         * SCalendar::GetDayRect
         * @brief    ������ڵ�����
         * @param    WORD iDay  -- ����         
         *
         * Describe  �����������ڵ����Լ����ڼ�������������
         */    
        CRect GetDayRect(WORD iDay);
        WORD HitTest(CPoint  pt);
	   bool  ShowSelectMonthYear(EventArgs *pArg); //��ʾ�����棬ѡ���ꡢ��
	   bool  SelectPrevYear(EventArgs *pArg); //�л���ȥ��
	   bool  SelectNextYear(EventArgs *pArg); //�л�������
		void DrawBackGround(IRenderTarget *pRT);
		void	DrawBorder(IRenderTarget *pRT);
		void DrawHeader(IRenderTarget *pRT);
		void DrawFooter(IRenderTarget *pRT);

        /**
         * SCalendar::DrawTitle
         * @brief    ���Ʊ���
         * @param    IRenderTarget *pRT -- �����豸���         
         *
         * Describe  ����ֻ�Ǹ��������ڵ����꣬����CRect��ʾ
         */    
        void DrawTitle(IRenderTarget *pRT);
        
        /**
         * SCalendar::DrawDate
         * @brief    ��������
         * @param    IRenderTarget *pRT -- �����豸���         
         *
         * Describe  ��������
         */            
        void DrawDate(IRenderTarget *pRT);

        /**
         * SCalendar::DrawDay
         * @brief    ��������--��
         * @param    IRenderTarget *pRT -- �����豸���         
         *
         * Describe  ��������--��
         */    
        void DrawDay(IRenderTarget *pRT,CRect & rcDay,WORD iDay );
        
        /**
         * SCalendar::RedrawDay
         * @brief    ���»�������--��
         * @param    CDCHandle dc -- �����豸���         
         *
         * Describe  ���»�������--��
         */    
        void RedrawDay(WORD iDay);

        /**
         * SCalendar::OnTodayClick
         * @brief    ������---��ĵ����¼�
         *
         * Describe  ������---��ĵ����¼�
         */            
        bool OnTodayClick(EventArgs *pArg);

        SOUI_ATTRS_BEGIN()
            ATTR_INT(L"titleHeight", m_nTitleHei, FALSE)			
            ATTR_INT(L"footerHeight", m_nFooterHei, FALSE)
            ATTR_COLOR(L"colorWeekend", m_crWeekend, FALSE)
            ATTR_COLOR(L"colorTitleBack", m_crTitleBack, FALSE)
			ATTR_COLOR(L"colorBorder", m_crBorder, FALSE)
            ATTR_COLOR(L"colorDay", m_crDay, FALSE)
            ATTR_SKIN(L"titleSkin", m_pTitleSkin, FALSE)
			
			//��������
            ATTR_STRINGW(L"daySkin", m_strDaySkin, FALSE)			
			ATTR_STRINGW(L"bkgSkin", m_strBkgSkin, FALSE)
			ATTR_STRINGW(L"headerTxtColor", m_strCRHeader, FALSE)
			ATTR_STRINGW(L"headerSkin", m_strHeaderSkin, FALSE)
			ATTR_INT(L"headerHeight", m_nHeaderHei, FALSE)
			ATTR_STRINGW(L"footerSkin", m_strFooterSkin, FALSE)
			ATTR_STRINGW(L"preMonSkin", m_strPreMonSkin, FALSE)
			ATTR_STRINGW(L"nextMonSkin", m_strNxtMonSkin, FALSE)
			ATTR_STRINGW(L"selectMonYearSkin", m_strSelMYSkin, FALSE)
			ATTR_STRINGW(L"MonYearSkin", m_strMYSkin, FALSE)
			ATTR_STRINGW(L"prevYearSkin", m_strPreYearSkin, FALSE)
			ATTR_STRINGW(L"nextYearSkin", m_strNxtYearSkin, FALSE)
			ATTR_STRINGW(L"sepMonYearSkin", m_strMonSepYearSkin, FALSE)

            ATTR_I18NSTRT(L"title-1", m_strTitle[0], FALSE)
            ATTR_I18NSTRT(L"title-2", m_strTitle[1], FALSE)
            ATTR_I18NSTRT(L"title-3", m_strTitle[2], FALSE)
            ATTR_I18NSTRT(L"title-4", m_strTitle[3], FALSE)
            ATTR_I18NSTRT(L"title-5", m_strTitle[4], FALSE)
            ATTR_I18NSTRT(L"title-6", m_strTitle[5], FALSE)
            ATTR_I18NSTRT(L"title-7", m_strTitle[6], FALSE)
        SOUI_ATTRS_END()

        SOUI_MSG_MAP_BEGIN()
            MSG_WM_PAINT_EX(OnPaint)
            MSG_WM_LBUTTONDOWN(OnLButtonDown)
            MSG_WM_MOUSEMOVE(OnMouseMove)
            MSG_WM_MOUSELEAVE(OnMouseLeave)
        SOUI_MSG_MAP_END()
    protected:
        int             m_nTitleHei;    /**< ��ͷ�߶� */
		int             m_nHeaderHei ;
        int             m_nFooterHei;   /**< ��β�߶� */	
        SStringW     m_strDaySkin;	
        ISkinObj    *m_pDaySkin;    /**< ������Ƥ�� */
		SStringW   m_strCRHeader; /*��ͷ����������ɫ*/
		SStringW   m_strHeaderSkin;  /**< ��ͷƤ�� */
        ISkinObj    *m_pTitleSkin;  /**< ��ͷ �ܱ��� ����Ƥ�� */	 		
		SStringW    m_strBkgSkin; /*������Ƥ��*/
		SStringW    m_strFooterSkin; /*��βƤ��*/
		SStringW    m_strPreMonSkin;  /**< �·�ǰ����ťƤ�� */	 		
		SStringW   m_strNxtMonSkin;  /**< �·ݺ󷭰�ťƤ�� */	 		
		SStringW   m_strSelMYSkin;  /**< ѡ�����°�ť(�¼�ͷ)Ƥ�� */	 		
		SStringW   m_strMYSkin;  /**< ������Ƥ�� */	 		
		SStringW   m_strPreYearSkin;  /**< ���ǰ����ťƤ�� */	 		
		SStringW   m_strNxtYearSkin;  /**< ��ݺ󷭰�ťƤ�� */	 		
		SStringW   m_strMonSepYearSkin;  /**<�·���ݷָ���ͼƬƤ�� */	 		
		
		
		COLORREF		m_crBorder; /*����߿���ɫ*/
        COLORREF        m_crWeekend;    /**< ��ĩ������ɫ */
        COLORREF        m_crTitleBack;  /**< ��ͷ����ɫ */
        COLORREF        m_crDay;        /**< ѡ��������ɫ */
        COLORREF        m_crDayBack;    /**< ѡ�����ڱ�����ɫ */
        SStringT     m_strTitle[7];  /**< ��ͷ�ı� */

        WORD    m_iYear, m_iMonth, m_iDay; /**< ������ */
        int        m_iHoverDay;
		BOOL  m_beInited;
		UINT  m_selMonth,m_selYear;
    };
}//end of namespace

