#include "./F_HMI.h"
#include "all_config.h"
#ifdef Service_Display_HMI
#include "../../../F_Chip/F_AD9959/F_AD9959.h"
#include "math.h"

/*
  * 发送单个字节
 * */
void HMI_SendByte(uint8_t data)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)&data, sizeof(data), HAL_MAX_DELAY);
	while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);
}


/*
  * 发送字符串
 * */
void HMI_Send_String(uint8_t *str)
{
	while(*str != '\0')
	{
		HMI_SendByte(*str++);
	}
}


/*
  * 发送结束标志 0xff 0xff 0xff
 * */
void HMI_Send_End(void)
{
	HMI_SendByte(0xff);
	HMI_SendByte(0xff);
	HMI_SendByte(0xff);
}


/*
  * 完整发送单个数据--打点
 * */
void HMI_Send_Wave_Data(uint8_t ID,uint8_t channel,uint8_t data)
{
	uint8_t temp[50];
	sprintf((char *)temp,"add %d,%d,%d",ID,channel,data);
	HMI_Send_String(temp);
	HMI_Send_End();
}


/*
  * 完整发送单个数据--文本框文本
 * */
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


/*
  * 完整发送单个数据--按钮文本
 * */
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


/*
  * 串口发送波形数据
 * */
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


/*
  * 更新ADC波形数据
 * */
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


/*
  * 清除波形数据
 * */
void HMI_Clear_ADC_Wave(u8 channel)
{
	uint8_t temp[50];
	sprintf((char *)temp,"cle %d,255", channel);
	HMI_Send_String(temp);
	HMI_Send_End();
}


/*
  * 更新9959的各项数据
 * */
void Refresh_AD9959_Data(void)
{
	u8 i = 0;
	for(i = 0; i <= 1; i++)
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
			HMI_Send_Buttton_Text(25, AD9959_FixedStepFre);
		}
	}
}


/*
  * 得到输入的数据
 * */
u32 HMI_Receive(u8 Count, char* Temp_Buf_Rceive)
{
	int i, j = 0;
	u32 temp = 1, sum = 0;
	u8 count_num = 0;
	u8 Temp_Buf[Count - 3];

	count_num = Count - 3;//有效数据个数
//	printf("%d\r\n", count_num);

	//删掉后三位剩下的
	for (i = 0; i < count_num; i++)
	{
		Temp_Buf[i] = Temp_Buf_Rceive[i] - 48;
	}

	if (count_num >= 1)
	{
		for (i = count_num - 1; i >= 0; i--)
		{
			for (j = 1; j <= count_num-1-i; j++)
			{
				temp *= 10;
			}
//			printf("%ld\r\n", temp);
			sum += Temp_Buf[i] * temp;
			temp = 1;
		}
//		printf("SUM:%ld\r\n", sum);
	}
	return sum;
}


//u32 HMI_Receive(u8 Count, char* Temp_Buf_Rceive)
//{
//	u8 i = 0;
//
//	u32 temp = 0;
//
//
//	char Temp_Buf[Count];
//	for (i = 0; i <= Count; i++)
//	{
//		Temp_Buf[i] = Temp_Buf_Rceive[i] - 48;
//	}
//
//	switch(Count)
//	{
//		case 4:
//			temp = Temp_Buf[0];
//			break;
//		case 5:
//			temp = Temp_Buf[0]*10 + Temp_Buf[1];
//			break;
//		case 6:
//			temp = Temp_Buf[0]*100 + Temp_Buf[1]*10 + Temp_Buf[2];
//			break;
//		case 7:
//			temp = Temp_Buf[0]*1000 + Temp_Buf[1]*100 + Temp_Buf[2]*10 + Temp_Buf[3];
//			break;
//		case 8:
//			temp = Temp_Buf[0]*10000 + Temp_Buf[1]*1000 + Temp_Buf[2]*100 + Temp_Buf[3]*10 + Temp_Buf[4];
//			break;
//		case 9:
//			temp = Temp_Buf[0]*100000 + Temp_Buf[1]*10000 + Temp_Buf[2]*1000 + Temp_Buf[3]*100 + Temp_Buf[4]*10 + Temp_Buf[5];
//			break;
//
//		case 10:
//			temp = Temp_Buf[0]*1000000 + Temp_Buf[1]*100000 + Temp_Buf[2]*10000 + Temp_Buf[3]*1000 + Temp_Buf[4]*100 + Temp_Buf[5]*10 + Temp_Buf[6];
//			break;
//
//		case 11:
//			temp = Temp_Buf[0]*10000000 + Temp_Buf[1]*1000000 + Temp_Buf[2]*100000 + Temp_Buf[3]*10000 + Temp_Buf[4]*1000 + Temp_Buf[5]*100 + Temp_Buf[6]*10 + Temp_Buf[7];
//			break;
//
//		case 12:
//			temp = Temp_Buf[0]*100000000 + Temp_Buf[1]*10000000 + Temp_Buf[2]*1000000 + Temp_Buf[3]*100000 + Temp_Buf[4]*10000 + Temp_Buf[5]*1000 + Temp_Buf[6]*100 + Temp_Buf[7]*10 + Temp_Buf[8];
//			break;
//
//		case 13:
//			temp = Temp_Buf[0]*1000000000 + Temp_Buf[1]*100000000 + Temp_Buf[2]*10000000 + Temp_Buf[3]*1000000 + Temp_Buf[4]*100000 + Temp_Buf[5]*10000 + Temp_Buf[6]*1000 + Temp_Buf[7]*100 + Temp_Buf[8]*10 + Temp_Buf[9];
//			break;
//		default:
//			break;
//	}
//	return temp;
//}


/*
  * 判断接收服务函数
 * */
void HMI_Pro(void)
{
	u32 temp_receive = 0;
	char temp_buffer[255];
//	char temp_char = 0;
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
			printf("GetNum:%ld\r\n", temp_receive);
			temp_receive = HMI_Receive(HMI_Count, HMI_Buffer);
			printf("GetNum:%ld\r\n", temp_receive);
			if (AD9959_Mode == AD9959_Mode_FixedFre)
			{
				if(temp_receive != 0 && temp_receive > AD9959_FixedMinFre)
					AD9959_FixedMaxFre = temp_receive;
				Refresh_AD9959_Data();
			}
			else if (AD9959_Mode == AD9959_Mode_Sweep)
			{
				if(temp_receive != 0 && temp_receive > AD9959_SweepMaxFre)
					AD9959_SweepMaxFre = temp_receive;
				Refresh_AD9959_Data();
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
				Refresh_AD9959_Data();
			}
			else if (AD9959_Mode == AD9959_Mode_Sweep)
			{
				if(temp_receive != 0 && temp_receive < AD9959_SweepMaxFre)
					AD9959_SweepMinFre = temp_receive;
				Refresh_AD9959_Data();
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
						Refresh_AD9959_Data();
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
				Refresh_AD9959_Data();
			}
			else if (AD9959_Mode == AD9959_Mode_FixedFre)
			{
				if(temp_receive != 0)
					AD9959_FixedStepFre = temp_receive;
				Refresh_AD9959_Data();
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
				Refresh_AD9959_Data();
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
				Refresh_AD9959_Data();
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
				Refresh_AD9959_Data();
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
//			FSK_Send_String(temp_buffer, HMI_Count-3);		//把temp_buffer中的字符发出去

			HMI_Num = 0;
			memset(temp_buffer,0x00,sizeof(temp_buffer));   //清空数组
			break;

		default:
			break;
	}
}




#endif
