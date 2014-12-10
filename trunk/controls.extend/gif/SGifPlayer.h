#pragma once
#include <core/swnd.h>

#include "sskingif.h"
#include "SSkinAPNG.h"

namespace SOUI
{

    /**
    * @class     SGifPlayer
    * @brief     GIFͼƬ��ʾ�ؼ�
    * 
    * Describe
    */
    class SGifPlayer : public SWindow
    {
        SOUI_CLASS_NAME(SGifPlayer, L"gifplayer")   //����GIF�ؼ���XM�ӵı�ǩ
    public:
        SGifPlayer();
        ~SGifPlayer();

        /**
         * PlayGifFile
         * @brief    �ڿؼ��в���һ��GIFͼƬ�ļ�
         * @param    LPCTSTR pszFileName --  �ļ���
         * @return   BOOL -- true:�ɹ�
         * Describe  
         */    
        BOOL PlayGifFile(LPCTSTR pszFileName);

        /**
        * PlayAPNGFile
        * @brief    �ڿؼ��в���һ��APNGͼƬ�ļ�
        * @param    LPCTSTR pszFileName --  �ļ���
        * @return   BOOL -- true:�ɹ�
        * Describe  
        */    
        BOOL PlayAPNGFile(LPCTSTR pszFileName);

    protected://SWindow���麯��
        virtual CSize GetDesiredSize(LPCRECT pRcContainer);

    public://���Դ���
        SOUI_ATTRS_BEGIN()		
            ATTR_CUSTOM(L"skin", OnAttrSkin) //Ϊ�ؼ��ṩһ��skin���ԣ���������SSkinObj�����name
        SOUI_ATTRS_END()
    protected:
        HRESULT OnAttrSkin(const SStringW & strValue, BOOL bLoading);
        
    protected:
        BOOL _PlayFile(LPCTSTR pszFileName, BOOL bGif);
    protected://��Ϣ����SOUI�ؼ�����Ϣ�����WTL��MFC�����ƣ��������Ƶ�ӳ�����ͬ�������Ƶ���Ϣӳ���
        
        /**
         * OnPaint
         * @brief    ���ڻ�����Ϣ��Ӧ����
         * @param    IRenderTarget * pRT --  ����Ŀ��
         * @return   void
         * Describe  ע������Ĳ�����IRenderTarget *,������WTL��ʹ�õ�HDC��ͬʱ��Ϣӳ���Ҳ��ΪMSG_WM_PAINT_EX
         */    
        void OnPaint(IRenderTarget *pRT);

        /**
         * OnTimer
         * @brief    SOUI���ڵĶ�ʱ��������
         * @param    char cTimerID --  ��ʱ��ID����Χ��0-127��
         * @return   void
         * Describe  SOUI�ؼ��Ķ�ʱ����Host���ڶ�ʱ��ID�ķֽ⣬�Է������еĿؼ���ͨ��Host��ö�ʱ���ķַ���
         *           ע��ʹ��MSG_WM_TIMER_EX��ӳ�����Ϣ����ʱ��ʹ��SWindow::SetTimer��SWindow::KillTimer���������ͷš�
         *           ����ö�ʱ��ID��Χ��������Ҫ�󣬿���ʹ��SWindow::SetTimer2��������
         */    
        void OnTimer(char cTimerID);

        /**
         * OnShowWindow
         * @brief    ��������ʾ��Ϣ
         * @param    BOOL bShow --  true:��ʾ
         * @param    UINT nStatus --  ��ʾԭ��
         * @return   void 
         * Describe  �ο�MSDN��WM_SHOWWINDOW��Ϣ
         */    
        void OnShowWindow(BOOL bShow, UINT nStatus);

        //SOUI�ؼ���Ϣӳ���
        SOUI_MSG_MAP_BEGIN()	
            MSG_WM_TIMER_EX(OnTimer)    //��ʱ����Ϣ
            MSG_WM_PAINT_EX(OnPaint)    //���ڻ�����Ϣ
            MSG_WM_SHOWWINDOW(OnShowWindow)//������ʾ״̬��Ϣ
        SOUI_MSG_MAP_END()	

    private:
        SSkinAni *m_aniSkin;
        int	m_iCurFrame;
    };

}