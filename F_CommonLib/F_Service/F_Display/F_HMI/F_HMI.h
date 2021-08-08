#ifndef __F_HMI_H
#define __F_HMI_H
#include "all_config.h"
#ifdef Service_Display_HMI


void HMI_SendByte(uint8_t data);								//发送单个字节
void HMI_Send_String(uint8_t *str);								//发送字符串
void HMI_Send_End(void);										//发送结束标志 0xff 0xff 0xff
void HMI_Send_Wave_Data(uint8_t ID,uint8_t channel,uint8_t data);//完整发送单个数据--打点
void HMI_Send_Textbox_Text(u8 Text_ID, u32 data);				//完整发送单个数据--文本框文本
void HMI_Send_Buttton_Text(u8 Text_ID, u32 data);				//完整发送单个数据--按钮文本
void HMI_Send_Wave(char* Temp_Buf, u16 Length);					//串口发送波形数据
void HMI_Send_ADC_Wave(u16 ADC_Value_1, u16 ADC_Value_2);		//更新ADC波形数据
void HMI_Clear_ADC_Wave(u8 channel);							//清除波形数据
void Refresh_AD9959_Data(void);									//更新9959的各项数据
u32 HMI_Receive(u8 Count, char* Temp_Buf_Rceive);
void HMI_Pro(void);										//判断接收服务函数


#endif
#endif
