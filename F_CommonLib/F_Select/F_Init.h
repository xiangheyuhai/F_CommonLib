#ifndef  __FAN_INIT_H__
#define  __FAN_INIT_H__

#include "F_NativeInterface.h"



void F_INIT(void)
{
	#ifdef Service_Input_Keypad
	KEY_PAD_INIT_STM32F4();
	#endif

	#ifdef Service_Input_Key
	KEY_INPUT_INIT();
	#endif

	/*串口*/
	#ifdef F_STM32_F4
	#ifdef F_USART
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
	#endif
	#endif

	/*串口屏*/
	#ifdef F_STM32_F4
	#ifdef Service_Display_HMI
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
	#endif
	#endif

	/*OLED_IIC*/
	#ifdef Service_Display_OLED_IIC
	OLED_IIC_INIT();
	OLED_Clear();
	sprintf((char *)OLED_IIC_SHOW_BUF, "FJX");
	OLED_ShowString(0,0, OLED_IIC_SHOW_BUF,16);
	#endif


	/*AD9959*/
	#ifdef F_AD9959
	AD9959_GPIO_Init();
	Write_frequence(0,15000);//15000Hz
	#endif


	/*ADF4351*/
	#ifdef F_ADF4351
	F_ADF4351_Init();
	ADF4351WriteFreq(300);//300KHz
	#endif


	#ifdef F_DAC
	#ifdef F_DAC_Sin_Wave
	for(DAC_SIN_Count = 0; DAC_SIN_Count < DAC_SIN_Length; DAC_SIN_Count++)
	{
		DAC_SIN_TAB[DAC_SIN_Count] = 2047.0*(sin(2*3.1415926*DAC_SIN_Count/DAC_SIN_Length)+1)*8/10+500;	//防止出现底部失真;
	}
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(uint32_t *)&DAC_SIN_TAB[0],DAC_SIN_Length,DAC_ALIGN_12B_R);
	#endif
	#endif


	#ifdef F_ADC
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_1_Value_DMA, 3);//转换后的结果放到ADC_Value_DMA_1
	#endif


}















#endif

