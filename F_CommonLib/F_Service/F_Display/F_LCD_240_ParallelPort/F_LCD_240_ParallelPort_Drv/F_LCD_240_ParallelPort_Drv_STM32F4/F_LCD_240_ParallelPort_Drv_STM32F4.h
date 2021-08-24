#ifndef __F_LCD_240_PARALLEL_PORT_DRV_STM32F4_H
#define __F_LCD_240_PARALLEL_PORT_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_LCD_240_ParallelPort
#ifdef F_STM32_F4

/*引脚功能
 *3  SCL	SPI时钟线
 *4  SDA	SPI数据线
 *5  RES	LCD复位
 *6  DC		LCD数据/命令选择脚
 *7  CS1	显示屏片选信号
 *8  BLK	背光控制开关，默认打开背光，低电平关闭背光
 *9  FSO	字库数据输出(输入模式)
 *10 CS2	字库芯片片选
 * */

/*
 * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 * */
//8位


#define LCD_240_D0_Pin 	   		 GPIO_PIN_0
#define LCD_240_D0_GPIO_Port 	 GPIOB

#define LCD_240_D1_Pin 	   		 GPIO_PIN_1
#define LCD_240_D1_GPIO_Port 	 GPIOB

#define LCD_240_D2_Pin 	   		 GPIO_PIN_2
#define LCD_240_D2_GPIO_Port 	 GPIOB

#define LCD_240_D3_Pin 	   		 GPIO_PIN_3
#define LCD_240_D3_GPIO_Port 	 GPIOB

#define LCD_240_D4_Pin 	   		 GPIO_PIN_4
#define LCD_240_D4_GPIO_Port 	 GPIOB

#define LCD_240_D5_Pin 	   		 GPIO_PIN_5
#define LCD_240_D5_GPIO_Port 	 GPIOB

#define LCD_240_D6_Pin 	   		 GPIO_PIN_6
#define LCD_240_D6_GPIO_Port 	 GPIOB

#define LCD_240_D7_Pin 	   		 GPIO_PIN_7
#define LCD_240_D7_GPIO_Port 	 GPIOB

//5位
#define LCD_240_RES_Pin 	     GPIO_PIN_2
#define LCD_240_RES_GPIO_Port    GPIOA

#define LCD_240_CS_Pin 	   	     GPIO_PIN_3
#define LCD_240_CS_GPIO_Port     GPIOA

#define LCD_240_DC_Pin 	   	     GPIO_PIN_4
#define LCD_240_DC_GPIO_Port     GPIOA

#define LCD_240_WR_Pin 	     	 GPIO_PIN_5
#define LCD_240_WR_GPIO_Port     GPIOA

#define LCD_240_RD_Pin 	   		 GPIO_PIN_6
#define LCD_240_RD_GPIO_Port 	 GPIOA


/*Set Reset*/
#define LCD_RES_Clr()  PAout(2) = 0	//RES
#define LCD_RES_Set()  PAout(2) = 1

#define LCD_CS_Clr()   PAout(3) = 0	//CS
#define LCD_CS_Set()   PAout(3) = 1

#define LCD_DC_Clr()   PAout(4) = 0	//DC
#define LCD_DC_Set()   PAout(4) = 1

#define LCD_WR_Clr()   PAout(5) = 0	//WR
#define LCD_WR_Set()   PAout(5) = 1

#define LCD_RD_Clr()   PAout(6) = 0	//WD
#define LCD_RD_Set()   PAout(6) = 1

#define DATAOUT(x) GPIOB->ODR=x; //数据输出

//函数声明
void LCD_240_ParallelPort_Drv_Init(void);


#endif
#endif
#endif
