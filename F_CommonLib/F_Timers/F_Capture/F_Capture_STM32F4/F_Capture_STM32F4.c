#include "./F_Capture_STM32F4.h"

#include "all_config.h"
#ifdef F_Capture_STM32F4
#ifdef F_STM32_F4



TIM_HandleTypeDef htim5;
#define Capture_Count_Time 1000000
#define Capture_High_Time  Capture_Buf[1]-Capture_Buf[0] //高电平时间
#define Capture_Cycle_Time Capture_Buf[2]-Capture_Buf[0] //一个周期时间
u8 Capture_Mode = 0;		 //状态标志
u8 Capture_Fliter_Flag = 0;
u32 Capture_Buf[3] = {0};        //存放计数值  上升沿时的计数值 下降沿时的计数值 下一个上升沿时的计数值
u32 Capture_Buf_Real[3] = {0};   //存放计数值  上升沿时的计数值 下降沿时的计数值 下一个上升沿时的计数值
uint_least64_t Capture_Sum[3] = {0};        //存放计数值  上升沿时的计数值 下降沿时的计数值 下一个上升沿时的计数值 分别的总和（滤波用）
u8 Capture_Duty = 0;			  	  //占空比
u32  Capture_Frequency = 0;	 		  //频率
u8 Capture_Duty_Last = 0;			  //占空比
u32  Capture_Frequency_Last = 0;	  //频率


u16 FSK_Period_Level[100] = {0};
u8 FSK_Reveive_Count[100] = {0};
u32 FSK_Level_Last[8] = {0};
u8 FSK_Reveive[8] = {0};

void Capture_Pro(void)
{
	switch (Capture_Mode)
	{
		case 0:
			Capture_Mode++;
			  HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_2);
			  HAL_TIM_IC_Start_IT(&htim5, TIM_CHANNEL_1);
			break;

		case 5:
			Capture_Mode = 0;  //清空标志
			FSK_Receive_Data(FSK_Reveive_Count, FSK_Reveive);
			break;
		default:
			break;
	}
}

uint32_t Highlevel_num;
uint32_t Period_num;
uint32_t Fre_Receive = 0;
u8 temp_i = 0;

static u8 period_level_count = 0;
static u8 FSK_reveive_count = 0;
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	switch(Capture_Mode)
	{
		case 1:
			Highlevel_num = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_1);
			Period_num    = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_2);
			Fre_Receive = (u32)(1000000.0 / (float)Period_num);
//			printf("Fre_Receive:%d\r\n",Fre_Receive);

			if (Fre_Receive <= 15500 && Fre_Receive >= 14000)
			{
				period_level_count++;
				if (period_level_count >= 8)
				{
					period_level_count = 0;
					printf("ReceiveBegin   ");
					Capture_Mode = 2;
				}
			}
//			printf("%d\r\n", period_level_count);
			break;
		case 2:
			Period_num = HAL_TIM_ReadCapturedValue(&htim5, TIM_CHANNEL_2);
			Fre_Receive = (u32)(1000000.0 / (float)Period_num);

			if (Fre_Receive <= 15500 && Fre_Receive >= 14000)
			{
				FSK_Reveive[FSK_reveive_count] = 0;
				FSK_reveive_count++;
				printf("%d", FSK_Reveive[FSK_reveive_count]);
			}
			else
			{
				FSK_Reveive[FSK_reveive_count] = 1;
				FSK_reveive_count++;
				printf("%d", FSK_Reveive[FSK_reveive_count]);
			}
			Capture_Mode = 1;
			printf("\r\nReceiveOver    \r\n");
			break;

		default:
			break;
	}
}


//static temp_count = 0;
//static high_level_count = 0;
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//	if(TIM5 == htim->Instance)
//	{
//		switch(Capture_Mode)
//		{
//			case 1:
//				Capture_Buf[0] = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_4);//获取当前的捕获值
//				__HAL_TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_4,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
//				Capture_Mode++;
//				HAL_Delay_us(2);
//				break;
//			case 2:
//				Capture_Buf[1] = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_4);//获取当前的捕获值
//				__HAL_TIM_SET_CAPTUREPOLARITY(&htim5, TIM_CHANNEL_4, TIM_INPUTCHANNELPOLARITY_RISING); //设置为上升沿捕获
//				printf("%d\r\n", Capture_Buf[1] - Capture_Buf[0]);
//				Capture_Mode = 1;
//				HAL_Delay_us(2);
////				if (FSK_Judge_Begin(FSK_High_Level, high_level_count) > 1000)
////				{
////					Capture_Mode++;
////					__HAL_TIM_SET_COUNTER(&htim5,0);   //设置计数寄存器的值变为0
////				}
////				else
////				{
////					Capture_Mode = 1;
////				}
//
//				break;
//
//			case 3:
//				FSK_Reveive_Count[temp_count] = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_4);//获取当前的捕获值
//				__HAL_TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_4,TIM_INPUTCHANNELPOLARITY_RISING);  //设置为下降沿捕获
//				temp_count++;
//				Capture_Mode++;
//				break;
//
//			case 4:
//				FSK_Reveive_Count[temp_count] = HAL_TIM_ReadCapturedValue(&htim5,TIM_CHANNEL_4);//获取当前的捕获值
//				__HAL_TIM_SET_CAPTUREPOLARITY(&htim5,TIM_CHANNEL_4,TIM_INPUTCHANNELPOLARITY_RISING);  //设置为下降沿捕获
//				temp_count++;
//				Capture_Mode = 3;
//				if (temp_count == 15)
//				{
//					temp_count = 0;
//					Capture_Mode = 5;
//					HAL_TIM_IC_Stop_IT(&htim5,TIM_CHANNEL_4); //停止捕获
//					__HAL_TIM_SET_COUNTER(&htim5,0);   //设置计数寄存器的值变为0
//				}
//				break;
//
//			default:
//				break;
//		}
//	}
//}




void FSK_Receive_Data(u8* array_count, u8* array_data)
{
	u8 i = 0;
	for (i = 0; i < 8; i++)
	{
		if (array_count[2 * i + 1] - array_count[2 * i] > 90)
		{
			array_data[i] = 0;
			printf("%d", array_data[i]);
		}

		else
		{
			array_data[i] = 1;
			printf("%d", array_data[i]);
		}
	}
	printf("\r\n");
}



#endif
#endif
