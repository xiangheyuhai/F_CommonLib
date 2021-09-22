#ifndef __F_LCD_240_PARALLEL_PORT_DRV_STM32F4_H
#define __F_LCD_240_PARALLEL_PORT_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_LCD_240_ParallelPort
#ifdef F_STM32_F4

/*引脚功能
 *并口(15)
 *1  	DC		并口模式时为数据和命令控制管脚，SPI模式时为SPI时钟线
 *2  	CS		显示屏片选信号,低电平有效
 *3  	RD		并口读
 *4  	SDC(WR)	并口时为并口写，SPI模式时为SPI的DC脚
 *5  	D0		并口数据线D0
 *7  	D2		并口数据线D2
 *8 	D1		并口数据线D1
 *9  	D4		并口数据线D4
 *10  	D3		并口数据线D3
 *11  	RES		复位,低电平有效
 *12  	D5		并口数据线D5
 *13	D7		并口数据线D7
 *14	D6		并口数据线D6
 *17	VCC
 *18	GND

 *SPI(7)
 *1  	DC		并口模式时为数据和命令控制管脚，SPI模式时为SPI时钟线
 *2  	CS		显示屏片选信号,低电平有效
 *4  	SDC(WR)	并口时为并口写，SPI模式时为SPI的DC脚
 *6		SDA		SPI通信数据线
 *11  	RES		复位,低电平有效
 *17	VCC
 *18	GND
 * */

/*
 * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 * */
//8位并口数据线
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

#define LCD_240_BLK_Pin 	   	 GPIO_PIN_7
#define LCD_240_BLK_GPIO_Port 	 GPIOA

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




//函数声明
void LCD_240_ParallelPort_Drv_Init(void);


#endif
#endif
#endif
