#ifndef __F_OLED_SPI_DRV_STM32F4_H
#define __F_OLED_SPI_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_OLED_SPI
#ifdef F_STM32_F4


/*
  * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 *
  * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 *
 * */
#define OLED_SPI_SCL_Pin 	    GPIO_PIN_5	//D0
#define OLED_SPI_SCL_GPIO_Port  GPIOA

#define OLED_SPI_SDA_Pin 	    GPIO_PIN_7	//D1
#define OLED_SPI_SDA_GPIO_Port  GPIOA

#define OLED_SPI_RES_Pin 	    GPIO_PIN_3
#define OLED_SPI_RES_GPIO_Port  GPIOA

#define OLED_SPI_DC_Pin 	   	GPIO_PIN_2
#define OLED_SPI_DC_GPIO_Port   GPIOA

#define OLED_SPI_CS_Pin 	    GPIO_PIN_1
#define OLED_SPI_CS_GPIO_Port   GPIOA


#define OLED_SPI_SCL    PAout(5) //SCL-D0
#define OLED_SPI_SDA    PAout(7) //SDA-D1
#define OLED_SPI_RES    PAout(3) //RES
#define OLED_SPI_DC     PAout(2) //DC
#define OLED_SPI_CS     PAout(1) //CS




void OLED_SPI_Drv_Init(void);




#endif
#endif
#endif
