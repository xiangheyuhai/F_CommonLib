#include "./F_ADC.h"


#ifdef F_ADC
u16 ADC_1_Value_DMA[ADC_1_Channel_Num] = {0};//3为ADC1开的通道数量
u16 ADC_2_Value_DMA[ADC_2_Channel_Num] = {0};//2为ADC2开的通道数量
u32 ADC_Value_Sum[ADC_All_Channel_Num] = {0};	 //存放滤波时的总和
u16 ADC_Value_Real[ADC_All_Channel_Num] = {0}; //存放滤波之后的数字量
u16 ADC_Value_Last[ADC_All_Channel_Num] = {0}; //存放上次的数字量--用于卡尔曼滤波
u8 ADC_Fliter_Flag = 1;		//extern到滴答定时器或者其他中
u8 ADC_Fliter_Count = 0;	//extern到滴答定时器或者其他中



/*简单滤波*/
static u8 adc_fliter_count_temp = 0;	//滤波时计数用

void ADC_Fliter(u8 adc_fliter_times)
{
	if(ADC_Fliter_Flag)//根据自己的需求更新每次取出来的时间
	{
		ADC_Fliter_Flag = 0;
		adc_fliter_count_temp++;
		if (adc_fliter_count_temp <= adc_fliter_times)//没有达到滤波次数，不停地累加
		{
			ADC_Value_Sum[0] += ADC_1_Value_DMA[0];
			ADC_Value_Sum[1] += ADC_1_Value_DMA[1];
//			ADC_Value_Sum[2] += ADC_1_Value_DMA[1];
		}
		else//达到滤波次数，sum归零，得到平均值
		{
			adc_fliter_count_temp = 0;

			ADC_Value_Real[0] = (u16)(ADC_Value_Sum[0]/(adc_fliter_times));
			ADC_Value_Real[1] = (u16)(ADC_Value_Sum[1]/(adc_fliter_times));
//			ADC_Value_Real[2] = (u16)(ADC_Value_Sum[2]/(ADC_Fliter_Times));

			ADC_Value_Sum[0] = 0;
			ADC_Value_Sum[1] = 0;
//			ADC_Value_Sum[2] = 0;
		}
	}
}







#endif

