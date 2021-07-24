#include "./F_HMI_STM32F4.h"
#include "all_config.h"
#include "math.h"
#include "string.h"
#include "stdio.h"
/*
 * STM32F4串口屏使用说明：
 * 1 把这句话放到串口初始化下边
 * 		HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
 *
 * 2 初始化串口1
 *
 * 3 修改TJC_Pro()中想要的效果
 *
 * 4 调用TJC_Pro()
 *
 * */

#define FSK_TEST
#define High_ARR 224
#define Low_ARR  336

#ifdef Service_Display_HMI

#ifdef F_STM32_F4
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart3;
#define Service_Display_HMI_Send


#define AD9959_Mode_Sweep 1			//模式--扫频
#define AD9959_Mode_FixedFre 2		//模式--点频
extern u8 AD9959_Mode;				//扫频或者点频
extern u8 AD9959_Wave_Show_Mode;	//跟随扫频--1  不跟随扫频--0

extern u32 AD9959_SweepMaxFre; 		//最大扫频频率--Hz
extern u32 AD9959_SweepMinFre;  	//最小扫频频率--Hz
extern u32 AD9959_SweepStepFre;   	//扫频步进频率--Hz
extern u32 AD9959_SweepTime;    	//扫频间隔时间--ms
extern u8  AD9959_SweepWaveFlag;   	//是否显示波形
extern u32 AD9959_SweepCount;    	//extern到定时器中--ms
extern u32 AD9959_SweepCountTimes; 	//extern到定时器中

extern u32 AD9959_FixedMaxFre; 		//最大固定输出频率--Hz
extern u32 AD9959_FixedMinFre;  	//最小固定输出频率--Hz
extern u32 AD9959_FixedStepFre; 	//步进固定输出频率--Hz
extern u32 AD9959_FixedAmpli; 	    //最大输出频率幅度--Hz
extern u32 AD9959_FixedNowFre; 		//此时输出频率--Hz

extern u32 AD9959_NowSinFre[5];
extern u32 AD9959_NowSinAmp[5];
extern u32 AD9959_NowSinPhr[5];


#define Wave_Size 255
char Send_Buffer[30];


#define RXBUFFERSIZE  255     //最大接收字节数
char RxBuffer[RXBUFFERSIZE];   //接收数据
char HMI_Num = 0;
char HMI_Buffer[RXBUFFERSIZE];
char HMI_Count = 0;
u16 HMI_Get_Num = 0;
uint8_t aRxBuffer;			//接收中断缓冲
uint8_t Uart1_Rx_Cnt = 0;		//接收缓冲计数

int __io_putchar(int ch)
{
  HAL_UART_Transmit(&huart3, (uint8_t*)&ch, 1,HAL_MAX_DELAY);
  return ch;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(huart);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_UART_TxCpltCallback could be implemented in the user file
   */

	if(Uart1_Rx_Cnt >= 255)  //溢出判断
	{
		Uart1_Rx_Cnt = 0;
		memset(RxBuffer,0x00,sizeof(RxBuffer));
		HAL_UART_Transmit(&huart1, (uint8_t *)"数据溢出", 10,0xFFFF);
	}
	//如果没有溢出
	else
	{
		RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //接收数据转存

		if((RxBuffer[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer[Uart1_Rx_Cnt-2] == 0x0D)) //判断结束位
		{
//			HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, Uart1_Rx_Cnt,0xFFFF); //将收到的信息发送出去
//			while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束
			memcpy(HMI_Buffer, RxBuffer, Uart1_Rx_Cnt);					  //将RxBuffer中的数据给FAN
			HMI_Count = Uart1_Rx_Cnt;
			HMI_Num = RxBuffer[Uart1_Rx_Cnt-3];
			Uart1_Rx_Cnt = 0;
			memset(RxBuffer,0x00,sizeof(RxBuffer)); //清空数组
		}
	}

	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //再开启接收中断
}








/*发送单个字节*/
void HMI_SendByte(uint8_t data)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)&data, sizeof(data), HAL_MAX_DELAY);
	while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);
}

/*发送字符串*/
void HMI_Send_String(uint8_t *str)
{
	while(*str != '\0')
	{
		HMI_SendByte(*str++);
	}
}




/*发送结束标志 0xff 0xff 0xff*/
void HMI_Send_End(void)
{
	HMI_SendByte(0xff);
	HMI_SendByte(0xff);
	HMI_SendByte(0xff);
}


/*完整发送单个数据--打点*/
void HMI_Send_Wave_Data(uint8_t ID,uint8_t channel,uint8_t data)
{
	uint8_t temp[50];
	sprintf((char *)temp,"add %d,%d,%d",ID,channel,data);
	HMI_Send_String(temp);
	HMI_Send_End();
}

/*完整发送单个数据--文本框文本*/
void HMI_Send_Textbox_Text(u8 Text_ID, u32 data)
{
	uint8_t temp[100] = {0};
	u8 i = 0;
	for(i = 0; i < 1; i++)
	{
		if(Text_ID == 31)
		{
			sprintf((char *)temp,"t%d.txt=\"send ok\"", Text_ID);//输出格式为:t0.txt="10000Hz"
			HMI_Send_String(temp);
			HMI_Send_End();
		}

		else if(Text_ID == 43)
		{
			sprintf((char *)temp,"t%d.txt=\"%ldms\"", Text_ID, data);//输出格式为:t0.txt="10000Hz"
			HMI_Send_String(temp);
			HMI_Send_End();
		}
		else
		{
			sprintf((char *)temp,"t%d.txt=\"%ldHz\"", Text_ID, data);//输出格式为:t0.txt="10000Hz"
			HMI_Send_String(temp);
			HMI_Send_End();
		}
	}
}

/*完整发送单个数据--按钮文本*/
void HMI_Send_Buttton_Text(u8 Text_ID, u32 data)
{
	uint8_t temp[100] = {0};
	u8 i = 0;
	for(i = 0; i < 1; i++)
	{
		if(Text_ID == 21)
		{
			sprintf((char *)temp,"b%d.txt=\"MinFre:%ldHz\"", Text_ID, data);//输出格式为:t0.txt="10000Hz"
			HMI_Send_String(temp);
			HMI_Send_End();
		}
		else if(Text_ID == 22)
		{
			sprintf((char *)temp,"b%d.txt=\"MaxFre:%ldHz\"", Text_ID, data);//输出格式为:t0.txt="10000Hz"
			HMI_Send_String(temp);
			HMI_Send_End();
		}
		else if(Text_ID == 23)
		{
			sprintf((char *)temp,"b%d.txt=\"MinFre:%ldHz\"", Text_ID, data);//输出格式为:t0.txt="10000Hz"
			HMI_Send_String(temp);
			HMI_Send_End();
		}
		else if(Text_ID == 24)
		{
			sprintf((char *)temp,"b%d.txt=\"NowFre:%ldHz\"", Text_ID, data);//输出格式为:t0.txt="10000Hz"
			HMI_Send_String(temp);
			HMI_Send_End();
		}
		else if(Text_ID == 25)
		{
			sprintf((char *)temp,"b%d.txt=\"StepFre:%ldHz\"", Text_ID, data);//输出格式为:t0.txt="10000Hz"
			HMI_Send_String(temp);
			HMI_Send_End();
		}

		else if(Text_ID == 26)
		{
			sprintf((char *)temp,"b%d.txt=\"StepTime:%ldms\"", Text_ID, data);//输出格式为:t0.txt="10000Hz"
			HMI_Send_String(temp);
			HMI_Send_End();
		}
		else
		{
			sprintf((char *)temp,"b%d.txt=\"%ldHz\"", Text_ID,data);
			HMI_Send_String(temp);
			HMI_Send_End();
		}
	}
}

/*串口发送波形数据*/
void HMI_Send_Wave(char* Temp_Buf, u16 Length)
{
	u8 i= 0;
	u8 temp = 0;
	for (i = 0; i < Length; i++)
	{
		temp = (char)(Temp_Buf[i]);//仅仅转换，非必要
		HMI_Send_Wave_Data(1,0,temp);
		HMI_Send_Wave_Data(7,0,temp);
		HMI_Send_Wave_Data(8,0,temp);
	}
}


/*更新ADC波形数据*/
void HMI_Send_ADC_Wave(u16 ADC_Value_1, u16 ADC_Value_2)
{
	u8 temp_send_1,temp_send_2 = 0;
//	temp_send_1 = (u8)(ADC_Value_1*256/4096);
//	temp_send_2 = (u8)(ADC_Value_2*256/4096);

	temp_send_1 = (u8)(ADC_Value_1*256*3/4096);
	temp_send_2 = (u8)(ADC_Value_2*256*3/4096);

	HMI_Send_Wave_Data(1,0,temp_send_1);
	HMI_Send_Wave_Data(7,0,temp_send_2);
//	HMI_Send_Wave_Data(8,0,temp_send_2);
}

/*清除波形数据*/
void HMI_Clear_ADC_Wave(u8 channel)
{
	uint8_t temp[50];
	sprintf((char *)temp,"cle %d,255", channel);
	HMI_Send_String(temp);
	HMI_Send_End();
}


/*更新9959的各项数据*/
void Refresh_AD9959_Data(void)
{
	/*扫频*/
	if(AD9959_Mode == AD9959_Mode_Sweep)
	{
		HMI_Send_Buttton_Text(22, AD9959_SweepMaxFre);
		HMI_Send_Buttton_Text(23, AD9959_SweepMinFre);
		HMI_Send_Buttton_Text(24, AD9959_FixedNowFre);
		HMI_Send_Buttton_Text(25, AD9959_SweepStepFre);
		HMI_Send_Buttton_Text(26, AD9959_SweepTime);
	}
	/*点频*/
	else if(AD9959_Mode == AD9959_Mode_FixedFre)
	{
		HMI_Send_Buttton_Text(22, AD9959_FixedMaxFre);
		HMI_Send_Buttton_Text(23, AD9959_FixedMinFre);
		HMI_Send_Buttton_Text(24, AD9959_FixedNowFre);
		HMI_Send_Buttton_Text(25, AD9959_FixedStepFre);;
	}
}

/**/
u32 HMI_Receive(u8 Count, char* Temp_Buf_Rceive)
{
	u8 i = 0;

	u32 temp = 0;


	char Temp_Buf[Count];
	for (i = 0; i <= Count; i++)
	{
		Temp_Buf[i] = Temp_Buf_Rceive[i] - 48;
	}

	switch(Count)
	{
		case 4:
			temp = Temp_Buf[0];
			break;
		case 5:
			temp = Temp_Buf[0]*10 + Temp_Buf[1];
			break;
		case 6:
			temp = Temp_Buf[0]*100 + Temp_Buf[1]*10 + Temp_Buf[2];
			break;
		case 7:
			temp = Temp_Buf[0]*1000 + Temp_Buf[1]*100 + Temp_Buf[2]*10 + Temp_Buf[3];
			break;
		case 8:
			temp = Temp_Buf[0]*10000 + Temp_Buf[1]*1000 + Temp_Buf[2]*100 + Temp_Buf[3]*10 + Temp_Buf[4];
			break;
		case 9:
			temp = Temp_Buf[0]*100000 + Temp_Buf[1]*10000 + Temp_Buf[2]*1000 + Temp_Buf[3]*100 + Temp_Buf[4]*10 + Temp_Buf[5];
			break;

		case 10:
			temp = Temp_Buf[0]*1000000 + Temp_Buf[1]*100000 + Temp_Buf[2]*10000 + Temp_Buf[3]*1000 + Temp_Buf[4]*100 + Temp_Buf[5]*10 + Temp_Buf[6];
			break;

		case 11:
			temp = Temp_Buf[0]*10000000 + Temp_Buf[1]*1000000 + Temp_Buf[2]*100000 + Temp_Buf[3]*10000 + Temp_Buf[4]*1000 + Temp_Buf[5]*100 + Temp_Buf[6]*10 + Temp_Buf[7];
			break;

		case 12:
			temp = Temp_Buf[0]*100000000 + Temp_Buf[1]*10000000 + Temp_Buf[2]*1000000 + Temp_Buf[3]*100000 + Temp_Buf[4]*10000 + Temp_Buf[5]*1000 + Temp_Buf[6]*100 + Temp_Buf[7]*10 + Temp_Buf[8];
			break;

		case 13:
			temp = Temp_Buf[0]*1000000000 + Temp_Buf[1]*100000000 + Temp_Buf[2]*10000000 + Temp_Buf[3]*1000000 + Temp_Buf[4]*100000 + Temp_Buf[5]*10000 + Temp_Buf[6]*1000 + Temp_Buf[7]*100 + Temp_Buf[8]*10 + Temp_Buf[9];
			break;
		default:
			break;
	}
	return temp;
}




/*判断接收服务函数*/
void TJC_Pro(void)
{
	u32 temp_receive = 0;
	char temp_buffer[255];
	char temp_char = 0;
	switch (HMI_Num)
	{
		/********************************AD9959********************************/
		/*更新数据*/
		case 0x20:
			Refresh_AD9959_Data();
			HMI_Num = 0;
			break;


		/*修改最大频率*/
		case 0x22:
			temp_receive = HMI_Receive(HMI_Count, HMI_Buffer);
			if (AD9959_Mode == AD9959_Mode_FixedFre)
			{
				if(temp_receive != 0 && temp_receive > AD9959_FixedMinFre)
					AD9959_FixedMaxFre = temp_receive;
				HMI_Send_Buttton_Text(22, AD9959_FixedMaxFre);
			}
			else if (AD9959_Mode == AD9959_Mode_Sweep)
			{
				if(temp_receive != 0 && temp_receive > AD9959_SweepMaxFre)
					AD9959_SweepMaxFre = temp_receive;
				HMI_Send_Buttton_Text(22, AD9959_SweepMaxFre);
			}

			HMI_Num = 0;
			break;

		/*修改最小频率*/
		case 0x23:
			temp_receive = HMI_Receive(HMI_Count, HMI_Buffer);
			if (AD9959_Mode == AD9959_Mode_FixedFre)
			{
				if(temp_receive != 0 && temp_receive < AD9959_FixedMaxFre)
					AD9959_FixedMinFre = temp_receive;
				HMI_Send_Buttton_Text(23, AD9959_FixedMinFre);
			}
			else if (AD9959_Mode == AD9959_Mode_Sweep)
			{
				if(temp_receive != 0 && temp_receive < AD9959_SweepMaxFre)
					AD9959_SweepMinFre = temp_receive;
				HMI_Send_Buttton_Text(23, AD9959_SweepMinFre);
			}

			HMI_Num = 0;
			break;


		/*固定频率输出--瞬间更改*/
		case 0x24:
			temp_receive = HMI_Receive(HMI_Count, HMI_Buffer);
			if (AD9959_Mode == AD9959_Mode_FixedFre)
			{
				if (temp_receive <= AD9959_FixedMaxFre && temp_receive >= AD9959_FixedMinFre)
					{
						AD9959_FixedNowFre = temp_receive;
						HMI_Send_Buttton_Text(24, AD9959_FixedNowFre);
					}
			}
			HMI_Num = 0;
			break;


		/*修改步进频率*/
		case 0x25:
			temp_receive = HMI_Receive(HMI_Count, HMI_Buffer);
			if (AD9959_Mode == AD9959_Mode_Sweep)
			{
				if(temp_receive != 0)
					AD9959_FixedStepFre = temp_receive;
				HMI_Send_Buttton_Text(25, AD9959_FixedStepFre);
			}
			else if (AD9959_Mode == AD9959_Mode_FixedFre)
			{
				if(temp_receive != 0)
					AD9959_FixedStepFre = temp_receive;
				HMI_Send_Buttton_Text(25, AD9959_FixedStepFre);
			}

			HMI_Num = 0;
			break;

		/*修改步进时间*/
		case 0x26:
			temp_receive = HMI_Receive(HMI_Count, HMI_Buffer);
			if (AD9959_Mode == AD9959_Mode_Sweep)
			{
				if(temp_receive != 0)
					AD9959_SweepTime = temp_receive;
				HMI_Send_Buttton_Text(26, AD9959_SweepTime);
			}

			HMI_Num = 0;
			break;

		/*固定频率输出--加*/
		case 0x27:
			if (AD9959_Mode == AD9959_Mode_FixedFre)
			{
				temp_receive = AD9959_FixedNowFre + AD9959_FixedStepFre;
				if(temp_receive <= AD9959_FixedMaxFre)
					AD9959_FixedNowFre = temp_receive;
				Write_frequence(0,AD9959_FixedNowFre);
				HMI_Send_Buttton_Text(24, AD9959_FixedNowFre);
			}
			HMI_Num = 0;
			break;

		/*固定频率输出--减*/
		case 0x28:
			if (AD9959_Mode == AD9959_Mode_FixedFre)
			{
				temp_receive = AD9959_FixedNowFre - AD9959_FixedStepFre;
				if (temp_receive >= AD9959_FixedMinFre && temp_receive > 0)
					AD9959_FixedNowFre = temp_receive;
				Write_frequence(0,AD9959_FixedNowFre);
				HMI_Send_Buttton_Text(24, AD9959_FixedNowFre);
			}
			HMI_Num = 0;

			break;

		/*点频模式*/
		case 0x29:
			AD9959_Mode = AD9959_Mode_FixedFre;
			Refresh_AD9959_Data();
			Write_frequence(0,AD9959_FixedNowFre);
			HMI_Num = 0;
			break;

		/*扫频模式*/
		case 0x30:
			AD9959_Mode = AD9959_Mode_Sweep;
			Refresh_AD9959_Data();
			HMI_Num = 0;
			break;

		/*显示波形*/
		case 0x31:
			AD9959_SweepWaveFlag = 1;	//显示波形
			HMI_Num = 0;
			break;


		/*发送字符串*/
		case 0x32:
//			FSK_Send_Char_2(HMI_Buffer[HMI_Count-4], temp_buffer);

			memcpy(temp_buffer, HMI_Buffer, HMI_Count-3);	//把接收到的字符串放到temp_buffer中
			FSK_Send_String(temp_buffer, HMI_Count-3);		//把temp_buffer中的字符发出去


			HMI_Num = 0;
			memset(temp_buffer,0x00,sizeof(temp_buffer));   //清空数组
			break;

		default:
			break;
	}
}

void FAN_delay_us(u16 time)
{
   u16 i=0;
   while(time--)
   {
      i=10;  //自己定义
      while(i--) ;
   }
}





#endif
#endif

