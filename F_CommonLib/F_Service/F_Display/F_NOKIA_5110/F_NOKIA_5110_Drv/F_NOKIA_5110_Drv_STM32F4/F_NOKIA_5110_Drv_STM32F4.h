#ifndef __F_NOKIA_5110_DRV_STM32F4_H
#define __F_NOKIA_5110_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_NOKIA_5110
#ifdef F_STM32_F4


/**************************USER修改**************************/
#define NOKIA_5110_SCL_Pin 	    	GPIO_PIN_12	//D0
#define NOKIA_5110_SCL_GPIO_Port  	GPIOC

#define NOKIA_5110_SDA_Pin 	    	GPIO_PIN_11	//D1
#define NOKIA_5110_SDA_GPIO_Port  	GPIOC

#define NOKIA_5110_DC_Pin 	   		GPIO_PIN_15
#define NOKIA_5110_DC_GPIO_Port  	GPIOG

#define NOKIA_5110_CE_Pin 	    	GPIO_PIN_6
#define NOKIA_5110_CE_GPIO_Port   	GPIOD

#define NOKIA_5110_RES_Pin 	    	GPIO_PIN_6
#define NOKIA_5110_RES_GPIO_Port  	GPIOC


#define NOKIA_5110_SCL 	PCout(12)
#define NOKIA_5110_SDA 	PCout(11)
#define NOKIA_5110_DC 	PGout(15)
#define NOKIA_5110_CE 	PDout(6)
#define NOKIA_5110_RES  PCout(6)
/**************************USER修改**************************/

void NOKIA_5110_Drv_Init(void);


#endif
#endif
#endif
