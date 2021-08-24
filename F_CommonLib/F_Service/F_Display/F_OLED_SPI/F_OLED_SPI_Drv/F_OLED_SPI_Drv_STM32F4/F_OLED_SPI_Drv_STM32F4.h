#ifndef __F_OLED_SPI_DRV_STM32F4_H
#define __F_OLED_SPI_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_OLED_SPI
#ifdef F_STM32_F4

/*引脚功能
 *D0	SPI时钟线
 *D1	SPI数据线
 *RES	复位
 *DC	数据/命令选择脚
 *CS	片选信号，低电平有效
 * */

/*
  * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
  * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 * */
#define OLED_SPI_SCL_Pin 	    GPIO_PIN_5	//D0
#define OLED_SPI_SCL_GPIO_Port  GPIOA

#define OLED_SPI_SDA_Pin 	    GPIO_PIN_7	//D1
#define OLED_SPI_SDA_GPIO_Port  GPIOA

#define OLED_SPI_RES_Pin 	    GPIO_PIN_12
#define OLED_SPI_RES_GPIO_Port  GPIOB

#define OLED_SPI_DC_Pin 	   	GPIO_PIN_13
#define OLED_SPI_DC_GPIO_Port   GPIOB

#define OLED_SPI_CS_Pin 	    GPIO_PIN_14
#define OLED_SPI_CS_GPIO_Port   GPIOB


#define OLED_SPI_SCL    PAout(5) //SCL-D0
#define OLED_SPI_SDA    PAout(7) //SDA-D1
#define OLED_SPI_RES    PBout(12) //RES
#define OLED_SPI_DC     PBout(13) //DC
#define OLED_SPI_CS     PBout(14) //CS




void OLED_SPI_Drv_Init(void);




#endif
#endif
#endif
