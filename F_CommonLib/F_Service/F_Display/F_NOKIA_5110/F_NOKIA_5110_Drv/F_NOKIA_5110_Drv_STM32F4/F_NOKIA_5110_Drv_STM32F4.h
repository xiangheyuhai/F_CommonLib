#ifndef __F_NOKIA_5110_DRV_STM32F4_H
#define __F_NOKIA_5110_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_NOKIA_5110
#ifdef F_STM32_F4


/**************************USER修改**************************/
#define NOKIA_5110_SCL_Pin 	    GPIO_PIN_1	//D0
#define NOKIA_5110_SCL_GPIO_Port  GPIOA

#define NOKIA_5110_SDA_Pin 	    GPIO_PIN_2	//D1
#define NOKIA_5110_SDA_GPIO_Port  GPIOA

#define NOKIA_5110_DC_Pin 	   	GPIO_PIN_3
#define NOKIA_5110_DC_GPIO_Port   GPIOA

#define NOKIA_5110_CE_Pin 	    GPIO_PIN_4
#define NOKIA_5110_CE_GPIO_Port   GPIOA

#define NOKIA_5110_RES_Pin 	    GPIO_PIN_5
#define NOKIA_5110_RES_GPIO_Port  GPIOA


#define NOKIA_5110_SCL 	PAout(1)
#define NOKIA_5110_SDA 	PAout(2)
#define NOKIA_5110_DC 	PAout(3)
#define NOKIA_5110_CE 	PAout(4)
#define NOKIA_5110_RES  PAout(5)
/**************************USER修改**************************/

void NOKIA_5110_Drv_Init(void);


#endif
#endif
#endif
