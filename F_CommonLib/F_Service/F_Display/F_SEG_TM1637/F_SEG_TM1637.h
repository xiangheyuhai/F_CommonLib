#ifndef __F_SEG_TM1637_H
#define __F_SEG_TM1637_H
#include "all_config.h"
#ifdef Service_Display_SEG_TM1637

#define SEG_TM1637_IIC_CLK_Pin 			GPIO_PIN_6
#define SEG_TM1637_IIC_CLK_GPIO_Port 	GPIOB
#define SEG_TM1637_IIC_SDA_Pin 			GPIO_PIN_7
#define SEG_TM1637_IIC_SDA_GPIO_Port 	GPIOB


#define SEG_TM1637CLK_0 	HAL_GPIO_WritePin(SEG_TM1637_IIC_CLK_GPIO_Port, SEG_TM1637_IIC_CLK_Pin, GPIO_PIN_RESET)
#define SEG_TM1637CLK_1 	HAL_GPIO_WritePin(SEG_TM1637_IIC_CLK_GPIO_Port, SEG_TM1637_IIC_CLK_Pin, GPIO_PIN_SET)

#define SEG_TM1637DIO_0 	HAL_GPIO_WritePin(SEG_TM1637_IIC_SDA_GPIO_Port, SEG_TM1637_IIC_SDA_Pin, GPIO_PIN_RESET)
#define SEG_TM1637DIO_1 	HAL_GPIO_WritePin(SEG_TM1637_IIC_SDA_GPIO_Port, SEG_TM1637_IIC_SDA_Pin, GPIO_PIN_SET)

extern unsigned char tab[];

//相关函数声明
/************************************
TM1637_DATA_Config
参数
unsigned char fb			(88):88 显示数字设置
unsigned char fb_show_flag	(88):88 显示开关设置	1:显示  0不显示
unsigned char sb			 88:(88) 显示数字设置
unsigned char sb_show_flag	 88:(88) 显示开关设置	1:显示  0不显示
unsigned char dot			 88(:)88 显示开关设置	1:显示  0不显示

使用例程 ：
TM1637_DATA_Config(11,1,22,1,1);
TM1637_DATA_Display();
显示效果 ：11:22

使用例程 ：
TM1637_DATA_Config(12,0,34,1,1);
TM1637_DATA_Display();
显示效果 ：__:34

使用例程 ：
TM1637_DATA_Config(12,0,34,0,1);
TM1637_DATA_Display();
显示效果 ：__:__
**************************************/
void SEG_TM1637_DATA_Config(unsigned char fb,unsigned char fb_show_flag,unsigned char sb,unsigned char sb_show_flag,unsigned char dot);
void SEG_TM1637_I2C_Start(void);
void SEG_TM1637_I2C_stop(void);
void SEG_TM1637_WriteBit(unsigned char mBit);
void SEG_TM1637_WriteByte(unsigned char Byte);
void SEG_TM1637_WriteCommand(unsigned char mData);
void SEG_TM1637_WriteData(unsigned char addr,unsigned char mData);
void SEG_TM1637_DATA_Display(uint8_t light);
#endif
#endif







