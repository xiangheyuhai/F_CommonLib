#ifndef __ALL_CONFIG_ALL_H
#define __ALL_CONFIG_ALL_H

//*******************************选择服务*******************************//
#define F_Interrupt
#define F_LED_Blink


//*******************************选择MCU*******************************//
//#define F_STM32_F1
#define F_STM32_F4




//*******************************选择芯片*******************************//
#define F_AD9959
//#define F_AD9959_Sweep_Fre
//#define F_AD9959_Sweep_Pha
//#define F_ADF4351
//#define F_AD8302




//*******************************选择模拟输入输出***********************//
#define F_ADC
//#define F_DAC
//#define F_DAC_Sin_Wave


//*******************************TIMER***********************//
//#define F_Capture_STM32F4




//*******************************选择协议*******************************//
//#define F_IIC
//#define F_SPI
#define F_USART
//#define F_FSK


//*******************************选择外设*******************************//
#define Service_Input_Key			//按键
//#define Service_Input_Keypad		//矩阵键盘
//#define Service_Display_LCD_240	//lcd
//#define Service_Display_LCD_480	//lcd
//#define Service_Display_OLED_IIC	//oled
//#define Service_Display_HMI		//串口屏
//#define Service_UserCode			//用户函数



#endif