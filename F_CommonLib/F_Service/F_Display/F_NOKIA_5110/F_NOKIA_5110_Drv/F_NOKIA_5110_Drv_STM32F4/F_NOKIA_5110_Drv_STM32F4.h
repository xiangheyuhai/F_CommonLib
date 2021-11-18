#ifndef __F_NOKIA_5110_DRV_STM32F4_H
#define __F_NOKIA_5110_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_NOKIA_5110
#ifdef F_STM32_F4


/**************************USER修改**************************/
#define NOKIA_5110_BLK_Pin 	    	GPIO_PIN_15
#define NOKIA_5110_BLK_GPIO_Port  	GPIOB

#define NOKIA_5110_SCL_Pin 	    	GPIO_PIN_0	//D0
#define NOKIA_5110_SCL_GPIO_Port  	GPIOF

#define NOKIA_5110_SDA_Pin 	    	GPIO_PIN_2	//D1
#define NOKIA_5110_SDA_GPIO_Port  	GPIOF

#define NOKIA_5110_DC_Pin 	   		GPIO_PIN_4
#define NOKIA_5110_DC_GPIO_Port  	GPIOF

#define NOKIA_5110_CE_Pin 	    	GPIO_PIN_9
#define NOKIA_5110_CE_GPIO_Port   	GPIOD

#define NOKIA_5110_RES_Pin 	    	GPIO_PIN_14
#define NOKIA_5110_RES_GPIO_Port  	GPIOD


#define NOKIA_5110_BLK 	PBout(15)
#define NOKIA_5110_SCL 	PFout(0)
#define NOKIA_5110_SDA 	PFout(2)
#define NOKIA_5110_DC 	PFout(4)
#define NOKIA_5110_CE 	PDout(9)
#define NOKIA_5110_RES  PDout(14)
/**************************USER修改**************************/

void NOKIA_5110_Drv_Init(void);


#endif
#endif
#endif
