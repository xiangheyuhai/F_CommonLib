#ifndef __F_NATIVEINTERFACE_H
#define __F_NATIVEINTERFACE_H

#include "main.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "main.h"

#include "./F_Select/F_MyFunction.h"


//获取原来平台的一些函数，通过宏定义判断需要包括什么
#ifdef F_USART
#include "stm32f4xx_hal_uart.h"
#include "./F_Drv/F_USART/F_USART_F4/F_USART_F4.c"
#include "./F_Drv/F_USART/F_USART_F4/F_USART_F4.h"
#endif


/*IIC_F4*/
#ifdef F_IIC
#ifdef F_STM32_F4
#include "stm32f4xx_hal_gpio.h"
#include "./F_Drv/F_IIC/F_IIC_F4/F_IIC_F4.c"
#include "./F_Drv/F_IIC/F_IIC_F4/F_IIC_F4.h"
#endif
#endif


/*FSK*/
#ifdef F_FSK
#include "./F_Drv\F_FSK\F_FSK.c"
#include "./F_Drv\F_FSK\F_FSK.h"
#endif

/*串口屏*/
#ifdef Service_Display_HMI
#include "stm32f4xx_hal_uart.h"
#include "./F_Service/F_Display/F_HMI/F_HMI_STM32F4/F_HMI_STM32F4.c"
#include "./F_Service/F_Display/F_HMI/F_HMI_STM32F4/F_HMI_STM32F4.h"
#endif


/*LCD_480*/
#ifdef Service_Display_LCD_480
#include "./F_Service/F_Display/F_LCD_480/F_LCD_480.c"
#include "./F_Service/F_Display/F_LCD_480/F_LCD_480.h"
#include "./F_Service/F_Display/F_LCD_480/F_LCD_FONT.h"
#endif


/*LCD_240*/
#ifdef Service_Display_LCD_240
#include "stm32f4xx_hal_gpio.h"
#include "./F_Service\F_Display\F_LCD_240\F_LCD_240.c"
#include "./F_Service\F_Display\F_LCD_240\F_LCD_240.h"
#include "./F_Service\F_Display\F_LCD_240\F_LCD_240_FONT.h"
#endif


/*OLED_IIC*/
#ifdef Service_Display_OLED_IIC
#include "stm32f4xx_hal_gpio.h"
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC.c"
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC.h"
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC_FONT.h"
#endif


/*矩阵按键*/
#ifdef Service_Input_Keypad
#include "stm32f4xx_hal_gpio.h"
#include "F_Service/F_Input/F_Keypad/Keypad_Select/Keypad_STM32F1.c"
#include "F_Service/F_Input/F_Keypad/Keypad_Select/Keypad_STM32F4.c"
#include "F_Service/F_Input/F_Keypad/F_Keypad.c"
#include "F_Service/F_Input/F_Keypad/F_Keypad.h"
#endif


/*按键*/
#ifdef Service_Input_Key
#include "stm32f4xx_hal_gpio.h"
#include "F_Service/F_Input/F_Key/F_Key.c"
#include "F_Service/F_Input/F_Key/F_Key.h"
#endif


/*用户函数*/
#ifdef Service_UserCode
//#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_gpio.h"
#include "F_User\F_UserCode.c"
#include "F_User\F_UserCode.h"
#endif


/*AD9959*/
#ifdef F_AD9959
#include "stm32f4xx_hal_gpio.h"
#include "F_Chip/F_AD9959/F_AD9959.c"
#include "F_Chip/F_AD9959/F_AD9959.h"
#endif


/*AD9954*/
#ifdef F_AD9954
#include "stm32f4xx_hal_gpio.h"
#include "F_Chip/F_AD9954/F_AD9954.c"
#include "F_Chip/F_AD9954/F_AD9954.h"
#endif


/*ADF4351*/
#ifdef F_ADF4351
#include "stm32f4xx_hal_gpio.h"
#include "F_Chip/F_ADF4351/F_ADF4351.c"
#include "F_Chip/F_ADF4351/F_ADF4351.h"
#endif


/*AD8302*/
#ifdef F_AD8302
#include "F_Chip/F_AD8302/F_AD8302.c"
#include "F_Chip/F_AD8302/F_AD8302.h"
#endif


/*RDA5820*/
#ifdef F_RDA5820
#include "F_Chip/F_RDA5820/F_RDA5820.c"
#include "F_Chip/F_RDA5820/F_RDA5820.h"
#endif


/*DAC*/
#ifdef F_DAC
#include "stm32f4xx_hal_dac.h"
#include "F_Analog/F_DAC/F_DAC.c"
#include "F_Analog/F_DAC/F_DAC.h"
#endif


/*ADC*/
#ifdef F_ADC
#include "stm32f4xx_hal_adc.h"
#include "F_Analog/F_ADC/F_ADC.c"
#include "F_Analog/F_ADC/F_ADC.h"
#endif



#ifdef F_Capture_STM32F4
#include "stm32f4xx_hal_tim.h"
#include "F_Timers\F_Capture\F_Capture_STM32F4\F_Capture_STM32F4.c"
#include "F_Timers\F_Capture\F_Capture_STM32F4\F_Capture_STM32F4.h"
#endif

#endif
