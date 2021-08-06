#ifndef __F_OLED_IIC_DRV_STM32F4_H
#define __F_OLED_IIC_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_OLED_IIC
#ifdef F_STM32_F4


/*
  * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 *
  * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 *
 * */
#define OLED_IIC_CLK_Port  GPIOE
#define OLED_IIC_CLK_Pin   GPIO_PIN_1

#define OLED_IIC_DATA_Port GPIOE
#define OLED_IIC_DATA_Pin  GPIO_PIN_2


//IO操作函数
#define OLED_IIC_SCL    PEout(1) //SCL
#define OLED_IIC_SDA    PEout(2) //SDA
#define OLED_READ_SDA   PEin(2)  //输入SDA



//IIC所有操作函数
void OLED_IIC_Start(void);				//发送IIC开始信号
void OLED_IIC_Stop(void);	  			//发送IIC停止信号
u8 OLED_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void OLED_IIC_Ack(void);					//IIC发送ACK信号
void OLED_IIC_NAck(void);				//IIC不发送ACK信号
void OLED_IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 OLED_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
void OLED_IIC_Drv_Init(void);                //初始化IIC的IO口
void OLED_SDA_Input(void);
void OLED_SDA_Output(void);
//void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
//u8 IIC_Read_One_Byte(u8 daddr,u8 addr);


#endif
#endif
#endif
