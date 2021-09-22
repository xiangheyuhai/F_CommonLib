#ifndef __F_LED_H
#define __F_LED_H
#include "all_config.h"
#ifdef F_LED
#ifdef F_STM32_F4


#define LED0_Pin 	    GPIO_PIN_9
#define LED0_GPIO_Port  GPIOF
#define LED1_Pin 	    GPIO_PIN_10
#define LED1_GPIO_Port  GPIOF

void LED_Init(void);

#endif
#endif
#endif
