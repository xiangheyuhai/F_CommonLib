#ifndef __F_MB1504_DRV_STM32F4_H
#define __F_MB1504_DRV_STM32F4_H
#include "all_config.h"
#ifdef F_MB1504
#ifdef F_STM32_F4




#define MB1504_GPIO_Port 	GPIOB
#define MB1504_LE_Pin 		GPIO_PIN_0
#define MB1504_DATA_Pin 	GPIO_PIN_1
#define MB1504_CLK_Pin 		GPIO_PIN_2

#define	MB1504_LE 		 	PBout(0)
#define	MB1504_DATA 	 	PBout(1)    //low
#define	MB1504_CLK 		 	PBout(2)


void MB1504_Drv_Init(void);




#endif
#endif
#endif
