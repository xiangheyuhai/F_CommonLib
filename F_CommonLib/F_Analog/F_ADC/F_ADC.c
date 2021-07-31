#include "./F_ADC.h"

#include "all_config.h"
#ifdef F_ADC
u16 ADC_1_Value_DMA[ADC_1_Channel_Num] = {0};//3为ADC1开的通道数量
u16 ADC_2_Value_DMA[ADC_2_Channel_Num] = {0};//2为ADC2开的通道数量
u32 ADC_Value_Sum[ADC_All_Channel_Num] = {0};	 //存放滤波时的总和
u16 ADC_Value_Real[ADC_All_Channel_Num] = {0}; //存放滤波之后的数字量
u16 ADC_Value_Last[ADC_All_Channel_Num] = {0}; //存放上次的数字量--用于卡尔曼滤波
u16 ADC_Value_Real_mV[ADC_All_Channel_Num] = {0};
u8 ADC_Fliter_Flag = 1;		//extern到滴答定时器或者其他中
u8 ADC_Fliter_Count = 0;	//extern到滴答定时器或者其他中
u8 ADC_Value_For_Wave[ADC_All_Channel_Num] = {0};



/*简单滤波*/
static u8 adc_fliter_count_temp = 0;	//滤波时计数用
void ADC_Fliter(u16 adc_fliter_times)
{
	if(ADC_Fliter_Flag)//根据自己的需求更新每次取出来的时间
	{
		ADC_Fliter_Flag = 0;
		adc_fliter_count_temp++;
		if (adc_fliter_count_temp <= adc_fliter_times)//没有达到滤波次数，不停地累加
		{
			ADC_Value_Sum[0] += ADC_1_Value_DMA[0];
			ADC_Value_Sum[1] += ADC_2_Value_DMA[0];
		}
		else//达到滤波次数，sum归零，得到平均值
		{
			adc_fliter_count_temp = 0;

			ADC_Value_Real[0] = (u16)(ADC_Value_Sum[0]/(adc_fliter_times));
			ADC_Value_Real[1] = (u16)(ADC_Value_Sum[1]/(adc_fliter_times));

			ADC_Value_Real_mV[0] = (u16)((float)ADC_Value_Real[0]/4096*3300);
			ADC_Value_Real_mV[1] = (u16)((float)ADC_Value_Real[1]/4096*3300);

			ADC_Value_Sum[0] = 0;
			ADC_Value_Sum[1] = 0;

			printf("%d,%d\r\n", ADC_Value_Real_mV[0], ADC_Value_Real_mV[1]);

//		  if (ADC_Value_Real_mV[1] >= 100 && ADC_Value_Real_mV[1] < 140)	//150
//		  {
//			  sprintf((char *)OLED_IIC_SHOW_BUF, "L:%3d  R:%3d", 100, 200);
//			  OLED_ShowString(0,3, OLED_IIC_SHOW_BUF,16);
//		  }
//
//		  if (ADC_Value_Real_mV[1] >= 140 && ADC_Value_Real_mV[1] < 175)	//150
//		  {
//			  sprintf((char *)OLED_IIC_SHOW_BUF, "L:%3d  R:%3d", 150, 150);
//			  OLED_ShowString(0,3, OLED_IIC_SHOW_BUF,16);
//		  }
//
//		  if (ADC_Value_Real_mV[1] >= 175 && ADC_Value_Real_mV[1] < 190)	//200
//		  {
//			  sprintf((char *)OLED_IIC_SHOW_BUF, "L:%3d  R:%3d",200 , 100);
//			  OLED_ShowString(0,3, OLED_IIC_SHOW_BUF,16);
//		  }
//
//		  if (ADC_Value_Real_mV[1] >= 175 && ADC_Value_Real_mV[1] < 190)	//200
//		  {
//			  sprintf((char *)OLED_IIC_SHOW_BUF, "L:%3d  R:%3d",200 , 100);
//			  OLED_ShowString(0,3, OLED_IIC_SHOW_BUF,16);
//		  }

		}
	}
}
///*简单滤波*/
//static u8 adc_fliter_count_temp_0 = 0;	//滤波时计数用
//static u8 adc_fliter_count_temp_1 = 0;	//滤波时计数用
//static u8 adc_fliter_count_temp   = 0;	//滤波时计数用
//void ADC_Fliter(u16 adc_fliter_times)
//{
//	u16 temp_mv_0 = 0;
//	u16 temp_mv_1 = 0;
//	if(ADC_Fliter_Flag)//根据自己的需求更新每次取出来的时间
//	{
//		ADC_Fliter_Flag = 0;
//		if (adc_fliter_count_temp <= adc_fliter_times)//没有达到滤波次数，不停地累加
//		{
//			adc_fliter_count_temp++;
//
//			temp_mv_0 = (u16)((float)ADC_1_Value_DMA[0]/4096*3300);
//			temp_mv_1 = (u16)((float)ADC_1_Value_DMA[1]/4096*3300);
//			if ( abs(temp_mv_0 - ADC_Value_For_Wave[0]) >= 20 || abs(temp_mv_0 - ADC_Value_For_Wave[0]) <= 6)
//			{
//				ADC_Value_Sum[0] += temp_mv_0;
//				adc_fliter_count_temp_0++;
//			}
//
//			if ( abs(temp_mv_1 - ADC_Value_For_Wave[1]) >= 20 || abs(temp_mv_1 - ADC_Value_For_Wave[1]) <= 6)
//			{
//				ADC_Value_Sum[1] += temp_mv_1;
//				adc_fliter_count_temp_1++;
//			}
//		}
//		else	//达到滤波次数，sum归零，得到平均值
//		{
//			adc_fliter_count_temp = 0;
//
//			ADC_Value_Real_mV[0] = (u16)(ADC_Value_Sum[0]/(adc_fliter_count_temp_0));
//			ADC_Value_Real_mV[1] = (u16)(ADC_Value_Sum[1]/(adc_fliter_count_temp_1));
//
//			adc_fliter_count_temp_0 = 0;
//			adc_fliter_count_temp_1 = 0;
//
//			ADC_Value_For_Wave[0] = (u16)KalmanFilter_Elect((float)ADC_Value_Real_mV[0], (float)ADC_Value_Last[0]);
//			ADC_Value_For_Wave[1] = (u16)KalmanFilter_Elect((float)ADC_Value_Real_mV[1], (float)ADC_Value_Last[1]);
//
//			ADC_Value_Last[0] = ADC_Value_For_Wave[0];
//			ADC_Value_Last[1] = ADC_Value_For_Wave[1];
//
//			ADC_Value_Sum[0] = 0;
//			ADC_Value_Sum[1] = 0;
//		}
//	}
//}











#endif

