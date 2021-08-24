#ifndef __F_LCD_240_DRV_STM32F4_H
#define __F_LCD_240_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_LCD_240
#ifdef F_STM32_F4

/*引脚功能
 *SCL	SPI时钟线
 *SDA	SPI数据线
 *RES	LCD复位
 *DC	LCD数据/命令选择脚
 *BLK	背光控制开关，默认打开背光，低电平关闭背光
 * */

/*
 * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 * */
#define LCD_240_SCL_Pin 	   GPIO_PIN_5
#define LCD_240_SCL_GPIO_Port  GPIOA

#define LCD_240_SDA_Pin 	   GPIO_PIN_7
#define LCD_240_SDA_GPIO_Port  GPIOA

#define LCD_240_RES_Pin 	   GPIO_PIN_12
#define LCD_240_RES_GPIO_Port  GPIOB

#define LCD_240_DC_Pin 	   	   GPIO_PIN_13
#define LCD_240_DC_GPIO_Port   GPIOB

#define LCD_240_BLK_Pin 	   GPIO_PIN_14
#define LCD_240_BLK_GPIO_Port  GPIOB


/*set reset*/
#define LCD_SCLK_Clr() HAL_GPIO_WritePin(LCD_240_SCL_GPIO_Port, LCD_240_SCL_Pin, GPIO_PIN_RESET)//CLK
#define LCD_SCLK_Set() HAL_GPIO_WritePin(LCD_240_SCL_GPIO_Port, LCD_240_SCL_Pin, GPIO_PIN_SET)

#define LCD_MOSI_Clr() HAL_GPIO_WritePin(LCD_240_SDA_GPIO_Port, LCD_240_SDA_Pin, GPIO_PIN_RESET)	//DIN
#define LCD_MOSI_Set() HAL_GPIO_WritePin(LCD_240_SDA_GPIO_Port, LCD_240_SDA_Pin, GPIO_PIN_SET)

#define LCD_RES_Clr()  HAL_GPIO_WritePin(LCD_240_RES_GPIO_Port, LCD_240_RES_Pin, GPIO_PIN_RESET)	//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(LCD_240_RES_GPIO_Port, LCD_240_RES_Pin, GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(LCD_240_DC_GPIO_Port, LCD_240_DC_Pin, GPIO_PIN_RESET)	//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(LCD_240_DC_GPIO_Port, LCD_240_DC_Pin, GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(LCD_240_BLK_GPIO_Port, LCD_240_BLK_Pin, GPIO_PIN_RESET)	//BLK
#define LCD_BLK_Set()  HAL_GPIO_WritePin(LCD_240_BLK_GPIO_Port, LCD_240_BLK_Pin, GPIO_PIN_SET)


void LCD_240_Drv_Init(void);


#endif
#endif
#endif
