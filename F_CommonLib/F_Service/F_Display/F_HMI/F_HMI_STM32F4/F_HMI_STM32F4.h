#ifndef __F_HMI_STM32F4_H
#define __F_HMI_STM32F4_H
#include "all_config.h"




#ifdef Service_Display_HMI
#ifdef F_STM32_F4

extern u8 Wave_Flag;



int __io_putchar(int ch);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


void HMI_SendByte(uint8_t data);								//发送单个字节
void HMI_Send_String(uint8_t *str);								//发送字符串
void HMI_Send_End(void);										//发送结束标志 0xff 0xff 0xff

void HMI_Send_Wave(char* Temp_Buf, u16 Length);					//串口发送波形数据
void TJC_Pro(void);												//判断接收服务函数

void HMI_Send_Buttton_Text(u8 Text_ID, u32 data);				//完整发送单个数据--按钮文本
void HMI_Send_Textbox_Text(u8 Text_ID, u32 data);						//完整发送单个数据--文本框文本

/*更新9959的各项数据*/
void Refresh_AD9959_Data(void);

void HMI_Send_Wave_Data(uint8_t ID,uint8_t channel,uint8_t data);/*完整发送单个数据--打点*/
/*更新ADC波形数据*/
void HMI_Send_ADC_Wave(u16 ADC_Value_1, u16 ADC_Value_2);
/*清除波形数据*/
void HMI_Clear_ADC_Wave(u8 channel);

/*发送单个字节--USART3*/
void HMI_SendByte_USART3(uint8_t data);
/*发送字符串--USART3*/
void HMI_Send_String_USART3(uint8_t *str);

float KalmanFilter_Elect(float curr_elect_val,float last_elect_val);

void FSK_Send_Char(unsigned char  data_hex, u8* array);
char FSK_IN(char* array);

/*FSK发送字符串*/
void FSK_Send_String(char* Temp_Buf,  u8 Length);
/*设置高低频率*/
void FSK_Send_Sin(u8 i);
/*发送一个字节--加校验*/
void FSK_Send_Char_2(unsigned char  data_hex, u8* array);
void FAN_delay_us(u16 time);

/*连续发8个1代表1个1*/
void FSK_SEND_1(void);
void FSK_SEND_HEAD(void);
void FSK_SEND_0(void);
void FSK_SEND_END(void);
#endif
#endif
#endif
