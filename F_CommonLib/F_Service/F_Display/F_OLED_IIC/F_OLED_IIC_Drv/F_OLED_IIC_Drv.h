#ifndef __F_OLED_IIC_DRV_H
#define __F_OLED_IIC_DRV_H
#include "all_config.h"
#ifdef Service_Display_OLED_IIC



//IIC所有操作函数
void OLED_IIC_Start(void);				//发送IIC开始信号
void OLED_IIC_Stop(void);	  			//发送IIC停止信号
u8 OLED_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void OLED_IIC_Ack(void);					//IIC发送ACK信号
void OLED_IIC_NAck(void);				//IIC不发送ACK信号
void OLED_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 OLED_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节


#endif
#endif
