#ifndef __F_LCD_240_DRV_STM32F4_H
#define __F_LCD_240_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_LCD_240
#ifdef F_STM32_F4


/*
  * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 *
  * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 *
 * */
#define LCD_240_SCL_Pin 	   GPIO_PIN_5
#define LCD_240_SCL_GPIO_Port  GPIOA

#define LCD_240_SDA_Pin 	   GPIO_PIN_7
#define LCD_240_SDA_GPIO_Port  GPIOA

#define LCD_240_RES_Pin 	   GPIO_PIN_0
#define LCD_240_RES_GPIO_Port  GPIOE

#define LCD_240_DC_Pin 	   	   GPIO_PIN_1
#define LCD_240_DC_GPIO_Port   GPIOE

#define LCD_240_BLK_Pin 	   GPIO_PIN_3
#define LCD_240_BLK_GPIO_Port  GPIOE


/*set reset*/
#define LCD_SCLK_Clr() PAout(5) = 0		//CLK
#define LCD_SCLK_Set() PAout(5) = 1

#define LCD_MOSI_Clr() PAout(7) = 0		//DIN
#define LCD_MOSI_Set() PAout(7) = 1

#define LCD_RES_Clr()  PEout(0) = 0	//RES
#define LCD_RES_Set()  PEout(0) = 1

#define LCD_DC_Clr()   PEout(1) = 0	//DC
#define LCD_DC_Set()   PEout(1) = 1

#define LCD_BLK_Clr()  PEout(3) = 0	//BLK
#define LCD_BLK_Set()  PEout(3) = 1


void LCD_240_Drv_Init(void);


#endif
#endif
#endif
