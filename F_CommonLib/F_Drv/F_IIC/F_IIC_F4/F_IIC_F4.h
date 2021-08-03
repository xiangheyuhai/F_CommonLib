#ifndef __F_IIC_F4_H
#define __F_IIC_F4_H
#include "all_config.h"
#ifdef F_IIC
#ifdef F_STM32_F4


/*
  * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 *
  * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 *
 * */
#define IIC_CLK_Port  GPIOC
#define IIC_CLK_Pin   GPIO_PIN_1

#define IIC_DATA_Port GPIOC
#define IIC_DATA_Pin  GPIO_PIN_0


//IO操作函数
#define IIC_SCL    PCout(1) //SCL
#define IIC_SDA    PCout(0) //SDA
#define READ_SDA   PCin(0)  //输入SDA



//IIC所有操作函数
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
void IIC_Init(void);                //初始化IIC的IO口
void SDA_Input(void);
void SDA_Output(void);
//void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
//u8 IIC_Read_One_Byte(u8 daddr,u8 addr);


#endif
#endif
#endif
