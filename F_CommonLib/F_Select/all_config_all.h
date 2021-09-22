#ifndef __ALL_CONFIG_ALL_H
#define __ALL_CONFIG_ALL_H

//*******************************选择服务*******************************//
#define F_Interrupt
#define F_LED_Blink


//*******************************选择MCU*******************************//
//#define F_STM32_F1
#define F_STM32_F4


//*******************************选择芯片*******************************//
//#define F_AD9959
//#define F_AD9959_Sweep_Fre
//#define F_AD9959_Sweep_Pha
//#define F_AD9954
//#define F_ADF4351
//#define F_AD8302
// #define F_RDA5820
//#define W_RDA5820


//*******************************选择模拟输入输出***********************//
//#define F_ADC
//#define F_DAC
//#define F_DAC_Sin_Wave
//#define F_FFT


//*******************************TIMER***********************//
//#define F_Capture_STM32F4




//*******************************选择协议*******************************//
//#define F_IIC
//#define F_SPI
#define F_USART
#define F_Printf_USART1
//#define F_Printf_USART2
//#define F_FSK


//*******************************选择外设*******************************//
//#define Service_Display_HMI					//串口屏

//#define Service_Display_LCD_240	            //LCD_240
//#define Service_Display_LCD_240_Hardware

//#define Service_Display_LCD_240_FontLib	    //LCD240*240 带字库
//#define Service_Display_LCD_240_FontLib_Hardware

// #define Service_Display_LCD_240_ParallelPort	//LCD240*240 并口

//#define Service_Display_LCD_480             	//LCD_480

#define F_LED									//LED

//#define Service_Display_OLED_IIC	//OLED_IIC

//#define Service_Display_OLED_SPI	//OLED_SPI
//#define Service_Display_OLED_SPI_Hardware

//#define Service_TOUCH
//#define Service_TOUCH_FT5206
//#define Service_TOUCH_GT9147
//#define Service_TOUCH_OTT2001A

//#define Service_Input_Key			            //按键

//#define Service_Input_Keypad		            //矩阵键盘

//#define Service_UserCode			//用户函数



#endif
