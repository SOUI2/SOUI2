#pragma once

#include "interface/render-i.h"

namespace SOUI
{
	/// <summary>
	///		���汾�����ȥ���˶�8��16��24λ��֧��,
	/// </summary>
	class SOUI_EXP SDIBHelper
	{
    public:
		/// <summary>
		///     H:-180~180���ȣ�,=0��������, S/L:0~200(���飬���ֵ��>200),=100��������
		/// </summary>
		/// <remarks>
		///     HSL�任,HSL�����������ڷ�Ԥ�����������½��У���Ϊ�˸����Ч�ʣ�Ŀǰ����Ԥ����������
		///     HSL�任Ӧ���������������в��ٱ仯ʱ��ʼ������.��Ȼԭʼ�������оͲ���׼ȷ
		/// </remarks>
		static bool AdjustHSL32(IBitmap * pBmp, int H, int S, int L);
		
		static bool AdjustHue(IBitmap *pBmp,COLORREF crRef);
		
        static bool AdjustHue(COLORREF & crTarget,COLORREF crRef);

		static bool GrayImage(IBitmap * pBmp); 
        
        //����ͼƬ��ƽ��ɫ
        //IBitmap *pBmp:ͼƬԴ
        //int nPercent:��Чֵ�ٷֱȣ�90������ߺ����5%��ֵ�ᶪ����������ƽ����
        //int int nBlockSize:�ֿ��С, ÿ�μ���һ�������ɫƽ��ֵ��
        static COLORREF CalcAvarageColor(IBitmap *pBmp,int nPercent=90,int nBlockSize=5);
	public:// ����
		static void RGBtoHSL(const BYTE &R, const BYTE &G, const BYTE &B, float &H, float &S, float &L);
		static void HSLtoRGB(const float &H, const float &S, const float &L, BYTE &R, BYTE &G, BYTE &B);
    };

}//namespace SOUI