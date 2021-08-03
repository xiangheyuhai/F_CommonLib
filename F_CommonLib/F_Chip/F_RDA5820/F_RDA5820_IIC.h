#ifndef __F_RDA5820_IIC_H
#define __F_RDA5820_IIC_H
#include "all_config.h"
#ifdef F_RDA5820


#define RDA5820_CLK_Port GPIOE
#define RDA5820_DATA_Port GPIOE

#define RDA5820_CLK_Pin GPIO_PIN_1
#define RDA5820_DATA_Pin GPIO_PIN_0
//IO操作函数
#define RDA5820_IIC_SCL    PEout(1) //SCL
#define RDA5820_IIC_SDA    PEout(0) //SDA
#define RDA5820_READ_SDA   PEin(0)  //输入SDA



//IIC所有操作函数
void RDA5820_IIC_Start(void);				//发送IIC开始信号
void RDA5820_IIC_Stop(void);	  			//发送IIC停止信号
u8 RDA5820_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void RDA5820_IIC_Ack(void);					//IIC发送ACK信号
void RDA5820_IIC_NAck(void);				//IIC不发送ACK信号
void RDA5820_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 RDA5820_(unsigned char ack);//IIC读取一个字节
void RDA5820_IIC_Init(void);
void RDA5820_SDA_Input(void);
void RDA5820_SDA_Output(void);

#endif
#endif















