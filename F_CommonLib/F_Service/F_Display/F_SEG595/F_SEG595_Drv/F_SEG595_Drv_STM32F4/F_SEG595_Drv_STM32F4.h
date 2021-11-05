#ifndef __F_SEG595_DRV_STM32F4_H
#define __F_SEG595_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_SEG595
#ifdef F_STM32_F4




#define SEG595_SCLK_Pin 		GPIO_PIN_11
#define SEG595_SCLK_GPIO_Port  	GPIOE

#define SEG595_DIO_Pin 			GPIO_PIN_15
#define SEG595_DIO_GPIO_Port  	GPIOE

#define SEG595_RCLK_Pin 		GPIO_PIN_13
#define SEG595_RCLK_GPIO_Port  	GPIOE


#define SEG595_SCLK PEout(11)
#define SEG595_DIO  PEout(15)
#define SEG595_RCLK PEout(13)


void SEG595_Drv_Init(void);

#endif
#endif
#endif
