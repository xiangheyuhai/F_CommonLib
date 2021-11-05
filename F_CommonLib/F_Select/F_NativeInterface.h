#ifndef __F_NATIVEINTERFACE_H
#define __F_NATIVEINTERFACE_H
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "main.h"
#include "./F_MyFunction.h"
#include "./all_config.h"

/***********************************************F_Analog***********************************************/
/*ADC*/
#ifdef F_ADC
#include "stm32f4xx_hal_adc.h"
#include "F_Analog/F_ADC/F_ADC.c"
#include "F_Analog/F_ADC/F_ADC.h"
#endif


/*DAC*/
#ifdef F_DAC
#include "stm32f4xx_hal_dac.h"
#include "./F_Analog/F_DAC/F_DAC.c"
#include "./F_Analog/F_DAC/F_DAC.h"
#ifdef F_STM32_F4
#include "./F_Analog/F_DAC/F_DAC_Drv/F_DAC_Drv_STM32F4/F_DAC_Drv_STM32F4.c"
#include "./F_Analog/F_DAC/F_DAC_Drv/F_DAC_Drv_STM32F4/F_DAC_Drv_STM32F4.h"
#endif
#endif


/*FFT*/
#ifdef F_FFT
#ifdef F_STM32_F4
//#include "arm_math.h"
#include "F_Analog/F_FFT/F_FFT_STM32F4/F_FFT_STM32F4.c"
#include "F_Analog/F_FFT/F_FFT_STM32F4/F_FFT_STM32F4.h"
#endif
#endif


/***********************************************F_Chip***********************************************/
/*F_AD8302*/
#ifdef F_AD8302
#include "F_Chip/F_AD8302/F_AD8302.c"
#include "F_Chip/F_AD8302/F_AD8302.h"
#endif


/*F_AD9954*/
#ifdef F_AD9954
#include "stm32f4xx_hal_gpio.h"
#include "F_Chip/F_AD9954/F_AD9954.c"
#include "F_Chip/F_AD9954/F_AD9954.h"
#endif


/*F_AD9959*/
#ifdef F_AD9959
#include "stm32f4xx_hal_gpio.h"
#ifdef F_STM32_F4
#include "F_Chip/F_AD9959/F_AD9959_Drv/F_AD9959_Drv_STM32F4/F_AD9959_Drv_STM32F4.c"
#include "F_Chip/F_AD9959/F_AD9959_Drv/F_AD9959_Drv_STM32F4/F_AD9959_Drv_STM32F4.h"
#endif
#include "F_Chip/F_AD9959/F_AD9959.c"
#include "F_Chip/F_AD9959/F_AD9959.h"
#endif


/*ADF4002*/
#ifdef F_ADF4002
#include "stm32f4xx_hal_gpio.h"
#include "F_Chip/F_ADF4002/F_ADF4002.c"
#include "F_Chip/F_ADF4002/F_ADF4002.h"
#ifdef F_STM32_F4
#include "F_Chip/F_ADF4002/F_ADF4002_Drv/F_ADF4002_Drv_STM32F4/F_ADF4002_Drv_STM32F4.c"
#include "F_Chip/F_ADF4002/F_ADF4002_Drv/F_ADF4002_Drv_STM32F4/F_ADF4002_Drv_STM32F4.h"
#endif
#endif


/*ADF4351*/
#ifdef F_ADF4351
#include "stm32f4xx_hal_gpio.h"
#include "F_Chip/F_ADF4351/F_ADF4351.c"
#include "F_Chip/F_ADF4351/F_ADF4351.h"
#endif


/*MB1504*/
#ifdef F_MB1504
#include "stm32f4xx_hal_gpio.h"
#include "F_Chip/F_MB1504/F_MB1504.c"
#include "F_Chip/F_MB1504/F_MB1504.h"
#include "F_Chip/F_MB1504/F_MB1504_Drv/F_MB1504_Drv_STM32F4/F_MB1504_Drv_STM32F4.c"
#include "F_Chip/F_MB1504/F_MB1504_Drv/F_MB1504_Drv_STM32F4/F_MB1504_Drv_STM32F4.h"
#endif


/*F_RDA5820*/
#ifdef F_RDA5820
#ifdef F_STM32_F4
#include "F_Chip/F_RDA5820/F_RDA5820_Drv/F_RDA5820_Drv_STM32F4/F_RDA5820_Drv_STM32F4.c"
#include "F_Chip/F_RDA5820/F_RDA5820_Drv/F_RDA5820_Drv_STM32F4/F_RDA5820_Drv_STM32F4.h"
#endif
#include "F_Chip/F_RDA5820/F_RDA5820_Drv/F_RDA5820_Drv.c"
#include "F_Chip/F_RDA5820/F_RDA5820_Drv/F_RDA5820_Drv.h"
#include "F_Chip/F_RDA5820/F_RDA5820.c"
#include "F_Chip/F_RDA5820/F_RDA5820.h"
#endif


/*W_RDA5820*/
#ifdef W_RDA5820
#include "F_Chip/W_RDA5820/RDA5820_drv.c"
#include "F_Chip/W_RDA5820/RDA5820_drv.h"
#include "F_Chip/W_RDA5820/RDA5820.c"
#include "F_Chip/W_RDA5820/RDA5820.h"
#endif


/***********************************************F_Connectivity***********************************************/
/*FSK*/
#ifdef F_FSK
#include "./F_Connectivity/F_FSK/F_FSK.c"
#include "./F_Connectivity/F_FSK/F_FSK.h"
#endif


/*IIC_F4*/
#ifdef F_IIC
#ifdef F_STM32_F4
#include "stm32f4xx_hal_gpio.h"
#include "./F_Drv/F_IIC/F_IIC_F4/F_IIC_F4.c"
#include "./F_Drv/F_IIC/F_IIC_F4/F_IIC_F4.h"
#endif
#endif


/*串口*/
#ifdef F_USART
#include "stm32f4xx_hal_uart.h"
#include "./F_Connectivity/F_USART/F_USART_F4/F_USART_F4.c"
#include "./F_Connectivity/F_USART/F_USART_F4/F_USART_F4.h"
#endif


/***********************************************F_Display***********************************************/
/*串口屏*/
#ifdef Service_Display_HMI
#ifdef F_STM32_F4
#include "stm32f4xx_hal_uart.h"
#include "./F_Service/F_Display/F_HMI/F_HMI_Drv/F_HMI_Drv_STM32F4/F_HMI_Drv_STM32F4.c"
#include "./F_Service/F_Display/F_HMI/F_HMI_Drv/F_HMI_Drv_STM32F4/F_HMI_Drv_STM32F4.h"
#endif
#include "./F_Service/F_Display/F_HMI/F_HMI.c"
#include "./F_Service/F_Display/F_HMI/F_HMI.h"
#endif


/*LCD_240*/
#ifdef Service_Display_LCD_240
#include "stm32f4xx_hal_gpio.h"
#include "./F_Service/F_Display/F_LCD_240/F_LCD_240.c"
#include "./F_Service/F_Display/F_LCD_240/F_LCD_240.h"
#include "./F_Service/F_Display/F_LCD_240/F_LCD_240_FONT.h"
#endif


/*LCD_240 带字库*/
#ifdef Service_Display_LCD_240_FontLib
#include "stm32f4xx_hal_gpio.h"
#include "./F_Service/F_Display/F_LCD_240_FontLib/F_LCD_240_FontLib.c"
#include "./F_Service/F_Display/F_LCD_240_FontLib/F_LCD_240_FontLib_Lib.c"
#include "./F_Service/F_Display/F_LCD_240_FontLib/F_LCD_240_FontLib.h"
#include "./F_Service/F_Display/F_LCD_240_FontLib/F_LCD_240_FontLib_FONT.h"
#ifdef F_STM32_F4
#include "F_Service/F_Display/F_LCD_240_FontLib/F_LCD_240_FontLib_Drv/F_LCD_240_FontLib_Drv_STM32F4/F_LCD_240_FontLib_Drv_STM32F4.c"
#include "F_Service/F_Display/F_LCD_240_FontLib/F_LCD_240_FontLib_Drv/F_LCD_240_FontLib_Drv_STM32F4/F_LCD_240_FontLib_Drv_STM32F4.h"
#endif
#endif


/*LCD_240 并口*/
#ifdef Service_Display_LCD_240_ParallelPort
#include "stm32f4xx_hal_gpio.h"
#include "./F_Service/F_Display/F_LCD_240_ParallelPort/F_LCD_240_ParallelPort.c"
#include "./F_Service/F_Display/F_LCD_240_ParallelPort/F_LCD_240_ParallelPort.h"
#include "./F_Service/F_Display/F_LCD_240_ParallelPort/F_LCD_240_ParallelPort_FONT.h"
#ifdef F_STM32_F4
#include "F_Service/F_Display/F_LCD_240_ParallelPort/F_LCD_240_ParallelPort_Drv/F_LCD_240_ParallelPort_Drv_STM32F4/F_LCD_240_ParallelPort_Drv_STM32F4.c"
#include "F_Service/F_Display/F_LCD_240_ParallelPort/F_LCD_240_ParallelPort_Drv/F_LCD_240_ParallelPort_Drv_STM32F4/F_LCD_240_ParallelPort_Drv_STM32F4.h"
#endif
#endif


/*LCD_480*/
#ifdef Service_Display_LCD_480
#include "./F_Service/F_Display/F_LCD_480/F_LCD_480.c"
#include "./F_Service/F_Display/F_LCD_480/F_LCD_480.h"
#endif


/*LED*/
#ifdef F_LED_Blink
#ifdef F_STM32_F4
#include "stm32f4xx_hal_gpio.h"
#include "./F_Service/F_Display/F_LED/F_LED.c"
#include "./F_Service/F_Display/F_LED/F_LED.h"
#ifdef F_STM32_F4
#include "./F_Service/F_Display/F_LED/F_LED_Drv/F_LED_Drv_STM32F4/F_LED_Drv_STM32F4.c"
#include "./F_Service/F_Display/F_LED/F_LED_Drv/F_LED_Drv_STM32F4/F_LED_Drv_STM32F4.h"
#endif
#endif
#endif


/*NOKIA_5110*/
#ifdef Service_Display_NOKIA_5110
#include "stm32f4xx_hal_gpio.h"
#include "./F_Service/F_Display/F_NOKIA_5110/F_NOKIA_5110.c"
#include "./F_Service/F_Display/F_NOKIA_5110/F_NOKIA_5110.h"
#include "./F_Service/F_Display/F_NOKIA_5110/F_NOKIA_5110_Font.h"
#ifdef F_STM32_F4
#include "./F_Service/F_Display/F_NOKIA_5110/F_NOKIA_5110_Drv/F_NOKIA_5110_Drv_STM32F4/F_NOKIA_5110_Drv_STM32F4.c"
#include "./F_Service/F_Display/F_NOKIA_5110/F_NOKIA_5110_Drv/F_NOKIA_5110_Drv_STM32F4/F_NOKIA_5110_Drv_STM32F4.h"
#endif
#endif



/*OLED_IIC*/
#ifdef Service_Display_OLED_IIC
#include "stm32f4xx_hal_gpio.h"
#ifdef F_STM32_F4
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC_Drv/F_OLED_IIC_Drv_STM32F4/F_OLED_IIC_Drv_STM32F4.c"
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC_Drv/F_OLED_IIC_Drv_STM32F4/F_OLED_IIC_Drv_STM32F4.h"
#endif
#ifdef F_STM32_F1
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC_Drv/F_OLED_IIC_Drv_STM32F1/F_OLED_IIC_Drv_STM32F1.c"
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC_Drv/F_OLED_IIC_Drv_STM32F1/F_OLED_IIC_Drv_STM32F1.h"
#endif
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC_Drv/F_OLED_IIC_Drv.c"
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC_Drv/F_OLED_IIC_Drv.h"
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC.c"
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC.h"
#include "F_Service/F_Display/F_OLED_IIC/F_OLED_IIC_FONT.h"
#endif


/*OLED_SPI*/
#ifdef Service_Display_OLED_SPI
#include "stm32f4xx_hal_gpio.h"
#ifdef F_STM32_F4
#include "F_Service/F_Display/F_OLED_SPI/F_OLED_SPI_Drv/F_OLED_SPI_Drv_STM32F4/F_OLED_SPI_Drv_STM32F4.c"
#include "F_Service/F_Display/F_OLED_SPI/F_OLED_SPI_Drv/F_OLED_SPI_Drv_STM32F4/F_OLED_SPI_Drv_STM32F4.h"
#endif
#ifdef F_STM32_F1
#include "F_Service/F_Display/F_OLED_SPI/F_OLED_SPI_Drv/F_OLED_SPI_Drv_STM32F4/F_OLED_SPI_Drv_STM32F1.c"
#include "F_Service/F_Display/F_OLED_SPI/F_OLED_SPI_Drv/F_OLED_SPI_Drv_STM32F4/F_OLED_SPI_Drv_STM32F1.h"
#endif
#include "F_Service/F_Display/F_OLED_SPI/F_OLED_SPI.c"
#include "F_Service/F_Display/F_OLED_SPI/F_OLED_SPI.h"
#include "F_Service/F_Display/F_OLED_SPI/F_OLED_SPI_FONT.h"
#endif


/*SEG595*/
#ifdef Service_Display_SEG_TM1637
#include "stm32f4xx_hal_gpio.h"
#include "F_Service/F_Display/F_SEG_TM1637/F_SEG_TM1637.c"
#include "F_Service/F_Display/F_SEG_TM1637/F_SEG_TM1637.h"
#ifdef F_STM32_F4
#include "F_Service/F_Display/F_SEG_TM1637/F_SEG_TM1637_Drv/F_SEG_TM1637_Drv_STM32F4/F_SEG_TM1637_Drv_STM32F4.c"
#include "F_Service/F_Display/F_SEG_TM1637/F_SEG_TM1637_Drv/F_SEG_TM1637_Drv_STM32F4/F_SEG_TM1637_Drv_STM32F4.h"
#endif
#endif


/*SEG595*/
#ifdef Service_Display_SEG595
#include "stm32f4xx_hal_gpio.h"
#include "F_Service/F_Display/F_SEG595/F_SEG595.c"
#include "F_Service/F_Display/F_SEG595/F_SEG595.h"
#ifdef F_STM32_F4
#include "F_Service/F_Display/F_SEG595/F_SEG595_Drv/F_SEG595_Drv_STM32F4/F_SEG595_Drv_STM32F4.c"
#include "F_Service/F_Display/F_SEG595/F_SEG595_Drv/F_SEG595_Drv_STM32F4/F_SEG595_Drv_STM32F4.h"
#endif
#endif


/*TOUCH*/
#ifdef Service_TOUCH
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH.c"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH.h"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Test.h"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_IIC/F_TOUCH_Drv_IIC.c"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_IIC/F_TOUCH_Drv_IIC.h"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_24CXX/F_TOUCH_Drv_24CXX.c"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_24CXX/F_TOUCH_Drv_24CXX.h"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_24CXX/F_TOUCH_Drv_24CXX_IIC.c"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_24CXX/F_TOUCH_Drv_24CXX_IIC.h"
#ifdef Service_TOUCH_FT5206
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_FT5206/F_TOUCH_Drv_FT5206.c"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_FT5206/F_TOUCH_Drv_FT5206.h"
#endif
#ifdef Service_TOUCH_GT9147
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_GT9147/F_TOUCH_Drv_GT9147.c"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_GT9147/F_TOUCH_Drv_GT9147.h"
#endif
#ifdef Service_TOUCH_OTT2001A
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_OTT2001A/F_TOUCH_Drv_OTT2001A.c"
#include "./F_Service/F_Display/F_TOUCH/F_TOUCH_Drv_OTT2001A/F_TOUCH_Drv_OTT2001A.h"
#endif
#endif


/***********************************************F_Input***********************************************/
/*按键*/
#ifdef Service_Input_Key
#include "stm32f4xx_hal_gpio.h"
#include "F_Service/F_Input/F_Key/F_Key.c"
#include "F_Service/F_Input/F_Key/F_Key.h"
#ifdef F_STM32_F4
#include "F_Service/F_Input/F_Key/F_Key_Drv/F_Key_Drv_STM32F4/F_Key_Drv_STM32F4.C"
#include "F_Service/F_Input/F_Key/F_Key_Drv/F_Key_Drv_STM32F4/F_Key_Drv_STM32F4.h"
#endif
#endif


/*矩阵按键*/
#ifdef Service_Input_Keypad
#include "stm32f4xx_hal_gpio.h"
#include "F_Service/F_Input/F_Keypad/F_Keypad_F4/F_Keypad_F4.c"
#include "F_Service/F_Input/F_Keypad/F_Keypad_F4/F_Keypad_F4.h"
#endif


/*矩阵按键*/
#ifdef SERVICE_KEYPAD
#include "stm32f4xx_hal_gpio.h"
#include "./F_Service/F_Input/Keypad/Keypad.c"
#include "./F_Service/F_Input/Keypad/Keypad.h"
#ifdef F_STM32_F4
#include "./F_Service/F_Input/Keypad/Keypad_Drv/Keypad_Drv_STM32F4/Keypad_Drv_STM32F4.c"
#include "./F_Service/F_Input/Keypad/Keypad_Drv/Keypad_Drv_STM32F4/Keypad_Drv_STM32F4.h"
#endif
#endif



/***********************************************F_Timer***********************************************/
#ifdef F_Capture_STM32F4
#include "stm32f4xx_hal_tim.h"
#include "F_Timers\F_Capture\F_Capture_STM32F4\F_Capture_STM32F4.c"
#include "F_Timers\F_Capture\F_Capture_STM32F4\F_Capture_STM32F4.h"
#endif


/*用户函数*/
#ifdef Service_UserCode
#include "F_User/F_UserCode.c"
#include "F_User/F_UserCode.h"
#endif

#endif
