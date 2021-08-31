#ifndef __F_TOUCH_DRV_24CXX_IIC_H
#define __F_TOUCH_DRV_24CXX_IIC_H
#include "all_config.h"
#ifdef Service_TOUCH
#ifdef F_STM32_F4


//IO方向设置
#define EEPROM_SDA_IN()  {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=0<<9*2;}	//PB9输入模式
#define EEPROM_SDA_OUT() {GPIOB->MODER&=~(3<<(9*2));GPIOB->MODER|=1<<9*2;} //PB9输出模式

//IO操作
#define EEPROM_IIC_SCL   PBout(8) //SCL
#define EEPROM_IIC_SDA   PBout(9) //SDA
#define EEPROM_READ_SDA  PBin(9)  //输入SDA


//IIC所有操作函数
void EEPROM_IIC_Init(void);
void EEPROM_IIC_Start(void);
void EEPROM_IIC_Stop(void);
u8 EEPROM_IIC_Wait_Ack(void);
void EEPROM_IIC_Ack(void);
void EEPROM_IIC_NAck(void);
void EEPROM_IIC_Send_Byte(u8 txd);
u8 EEPROM_IIC_Read_Byte(unsigned char ack);



#endif
#endif
#endif
