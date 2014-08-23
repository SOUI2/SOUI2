/********************************************************************
created:	2012/12/27
created:	27:12:2012   14:55
filename: 	DuiSkinGif.h
file base:	DuiSkinGif
file ext:	h
author:		huangjianxiong

purpose:	�Զ���Ƥ������
*********************************************************************/
#pragma once
#include <interface/SSkinobj-i.h>
#include <unknown/obj-ref-impl.hpp>

namespace Gdiplus
{
class Bitmap;
}
namespace SOUI
{
    class SGifFrame
    {
    public:
        CAutoRefPtr<IBitmap> pBmp;
        int                  nDelay;
    };

    /**
    * @class     SSkinGif
    * @brief     GIFͼƬ���ؼ���ʾ����
    * 
    * Describe
    */
    class SSkinGif : public ISkinObj
    {
        SOUI_CLASS_NAME(SSkinGif, L"gif")
    public:
        SSkinGif():m_nFrames(0),m_iFrame(0),m_pFrames(NULL)
        {

        }
        
        //��ʼ��GDI+����������������Ҫʹ��GDI+������GIF�ļ���ʽ
        static BOOL Gdiplus_Startup();
        //�˳�GDI+����
        static void Gdiplus_Shutdown();

        virtual ~SSkinGif()
        {
            if(m_pFrames) delete [] m_pFrames;
        }

        /**
         * Draw
         * @brief    ����ָ��֡��GIFͼ
         * @param    IRenderTarget * pRT --  ����Ŀ��
         * @param    LPCRECT rcDraw --  ���Ʒ�Χ
         * @param    DWORD dwState --  ����״̬�����ﱻ����Ϊ֡��
         * @param    BYTE byAlpha --  ͸����
         * @return   void
         * Describe  
         */    
        virtual void Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha=0xFF);

        /**
         * GetStates
         * @brief    ���GIF֡��
         * @return   int -- ֡��
         * Describe  
         */    
        virtual int GetStates(){return m_nFrames;}

        /**
         * GetSkinSize
         * @brief    ���ͼƬ��С
         * @return   SIZE -- ͼƬ��С
         * Describe  
         */    
        virtual SIZE GetSkinSize()
        {
            SIZE sz={0};
            if(m_nFrames>0 && m_pFrames)
            {
                sz=m_pFrames[0].pBmp->Size();
            }
            return sz;
        }

        /**
         * GetFrameDelay
         * @brief    ���ָ��֡����ʾʱ��
         * @param    int iFrame --  ֡��,Ϊ-1ʱ�����õ�ǰ֡����ʱ
         * @return   long -- ��ʱʱ��(*10ms)
         * Describe  
         */    
        long GetFrameDelay(int iFrame=-1);

        /**
         * ActiveNextFrame
         * @brief    ������һ֡
         * @return   void 
         * Describe  
         */    
        void ActiveNextFrame();

        /**
         * SelectActiveFrame
         * @brief    ����ָ��֡
         * @param    int iFrame --  ֡��
         * @return   void
         * Describe  
         */    
        void SelectActiveFrame(int iFrame);
        
        /**
         * LoadFromFile
         * @brief    ���ļ�����GIF
         * @param    LPCTSTR pszFileName --  �ļ���
         * @return   int -- GIF֡����0-ʧ��
         * Describe  
         */    
        int LoadFromFile(LPCTSTR pszFileName);

        /**
         * LoadFromMemory
         * @brief    ���ڴ����GIF
         * @param    LPVOID pBits --  �ڴ��ַ
         * @param    size_t szData --  �ڴ����ݳ���
         * @return   int -- GIF֡����0-ʧ��
         * Describe  
         */    
        int LoadFromMemory(LPVOID pBits,size_t szData);

        SOUI_ATTRS_BEGIN()
            ATTR_CUSTOM(L"src",OnAttrSrc)   //XML�ļ���ָ����ͼƬ��Դ��,(type:name)
        SOUI_ATTRS_END()
    protected:
        LRESULT OnAttrSrc(const SStringW &strValue,BOOL bLoading);
        int LoadFromGdipImage(Gdiplus::Bitmap * pImg);
        int m_nFrames;
        int m_iFrame;

        SGifFrame * m_pFrames;
    };
}//end of name space SOUI
