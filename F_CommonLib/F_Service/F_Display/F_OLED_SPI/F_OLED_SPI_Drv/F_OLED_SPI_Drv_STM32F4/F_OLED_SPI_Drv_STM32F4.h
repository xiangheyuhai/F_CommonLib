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
#define OLED_SPI_SCL_Pin 	    GPIO_PIN_1	//D0
#define OLED_SPI_SCL_GPIO_Port  GPIOE

#define OLED_SPI_SDA_Pin 	    GPIO_PIN_2	//D1
#define OLED_SPI_SDA_GPIO_Port  GPIOE

#define OLED_SPI_RES_Pin 	    GPIO_PIN_3
#define OLED_SPI_RES_GPIO_Port  GPIOE

#define OLED_SPI_DC_Pin 	   	GPIO_PIN_5
#define OLED_SPI_DC_GPIO_Port   GPIOE

#define OLED_SPI_CS_Pin 	    GPIO_PIN_6
#define OLED_SPI_CS_GPIO_Port   GPIOE


#define OLED_SPI_SCL    PEout(1) //SCL-D0
#define OLED_SPI_SDA    PEout(2) //SDA-D1
#define OLED_SPI_RES    PEout(3) //RES
#define OLED_SPI_DC     PEout(5) //DC
#define OLED_SPI_CS     PEout(6) //CS




void OLED_SPI_Drv_Init(void);




#endif
#endif
#endif
