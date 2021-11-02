#ifndef __F_LED_DRV_STM32F4_H
#define __F_LED_DRV_STM32F4_H
#include "all_config.h"
#ifdef F_LED_Blink
#ifdef F_STM32_F4


#define LED0_Pin 	    GPIO_PIN_12
#define LED0_GPIO_Port  GPIOA
#define LED1_Pin 	    GPIO_PIN_10
#define LED1_GPIO_Port  GPIOF

void LED_Drv_Init(void);


#endif
#endif
#endif
