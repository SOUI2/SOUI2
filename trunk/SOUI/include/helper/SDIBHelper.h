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
		
		static bool GrayImage(IBitmap * pBmp); 

	public:// ����
		static void RGBtoHSL(BYTE &R, BYTE &G, BYTE &B, float &H, float &S, float &L);
		static void HSLtoRGB(float &H, float &S, float &L, BYTE &R, BYTE &G, BYTE &B);
    };

}//namespace SOUI