#ifndef __F_ADC_H
#define __F_ADC_H

#include "all_config.h"
#ifdef F_ADC


#define ADC_Fliter_Times 30		//Fliter_Times为几个数取一次平均值
#define ADC_1_Channel_Num 1		//ADC1开了3个通道
#define ADC_2_Channel_Num 1		//ADC2开了3个通道
#define ADC_All_Channel_Num 2   //总的ADC通道数
extern u16 ADC_1_Value_DMA[ADC_1_Channel_Num];			//3为ADC1开的通道数量
extern u16 ADC_2_Value_DMA[ADC_2_Channel_Num];			//2为ADC2开的通道数量
extern u32 ADC_Value_Sum[ADC_All_Channel_Num];	 		//存放滤波时的总和
extern u16 ADC_Value_Real[ADC_All_Channel_Num]; 		//存放滤波之后的数字量
extern u16 ADC_Value_Last[ADC_All_Channel_Num];			//存放上次的数字量--用于卡尔曼滤波
extern u16 ADC_Value_Real_mV[ADC_All_Channel_Num];
extern u8 ADC_Fliter_Flag;		//extern到滴答定时器或者其他中
extern u8 ADC_Fliter_Count;		//extern到滴答定时器或者其他中


void ADC_Fliter(u16 adc_fliter_times);




#endif
#endif
