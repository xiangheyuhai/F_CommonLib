#ifndef  __FAN_INIT_H__
#define  __FAN_INIT_H__

#include "F_NativeInterface.h"



void F_Init(void)
{
	#ifdef Service_Input_Keypad
	KEY_PAD_Init_F4();
	printf("Keypad_Ok\r\n");
	#endif

	#ifdef Service_Input_Key
	KEY_INPUT_INIT();
	printf("Key_Ok\r\n");
	#endif


	#ifdef F_Interrupt
	#ifdef F_LED_Blink
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, 0);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, 1);
	printf("Interrupt_Ok\r\n");
	#endif
	#endif

	#ifdef F_STM32_F4
	#ifdef F_USART
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
	printf("USART_Ok\r\n");
	#endif
	#endif


	#ifdef F_STM32_F4
	#ifdef Service_Display_HMI
	#ifdef F_Printf_USART1
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
	#endif
	#ifdef F_Printf_USART3
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
	#endif

	Refresh_AD9959_Data();
	printf("HMI_Ok\r\n");
	#endif
	#endif

	/*OLED_IIC*/
	#ifdef Service_Display_OLED_IIC
	OLED_IIC_Init();
	OLED_IIC_Clear();
	sprintf((char *)OLED_IIC_SHOW_BUF, "FJX_TEST_123");
	OLED_IIC_ShowString(0,1, OLED_IIC_SHOW_BUF,16);
	printf("OLED_IIC_Ok\r\n");
	#endif

	/*OLED_SPI*/
	#ifdef Service_Display_OLED_SPI
	OLED_SPI_Init();
	sprintf((char *)OLED_SPI_SHOW_BUF, "FJX_TEST_123");
	OLED_SPI_ShowString(0,1, OLED_SPI_SHOW_BUF, 16, 1);
	OLED_SPI_Refresh();
	printf("OLED_SPI_Ok\r\n");
	#endif


	/*800*480LCD*/
	#ifdef Service_Display_LCD_480
	LCD_480_Init();
	POINT_COLOR=BLACK;
	LCD_Clear(WHITE);
	memset(LCD_480_SHOW_BUF,0x00,sizeof(LCD_480_SHOW_BUF)); //娓呯┖鏁扮粍
	printf("800*480LCD_Ok\r\n");
	#endif


	/*240*240LCD*/
	#ifdef Service_Display_LCD_240
	LCD_240_Init();
	LCD_Clear(BLACK);
	sprintf((char *)LCD_240_SHOW_BUF, "FJX_TEST");
	LCD_ShowString(0, 0, LCD_240_SHOW_BUF, WHITE, BLACK, 24, 0);
	printf("240*240LCD_Ok\r\n");
	#endif


	#ifdef Service_Display_LCD_240_FontLib
	LCD_240_FontLib_Init();
	LCD_Clear(WHITE);
	sprintf((char *)LCD_240_FontLib_SHOW_BUF, "FJX_TEST");
	LCD_ShowString(0, 0, LCD_240_FontLib_SHOW_BUF, RED, WHITE,16,0);
	printf("240*240LCD_FontLib_Ok\r\n");
	#endif


	/*AD9959*/
	#ifdef F_AD9959
	AD9959_Init();
	#ifdef F_AD9959_Sweep_Fre
	AD9959_Mode = AD9959_Mode_Sweep;
	#endif
	#ifdef F_AD9959_Sweep_Pha
	AD9959_Mode = AD9959_Mode_Sweep;
	#endif
	printf("AD9959\r\n");
	#endif


	/*AD9954*/
	#ifdef F_AD9954
	AD9954_Init();
	AD9954_SETFRE(100000);
	printf("AD9954_Ok\r\n");
	#endif


	/*ADF4351*/
	#ifdef F_ADF4351
	F_ADF4351_Init();
	ADF4351WriteFreq(300);//300KHz
	printf("ADF4351_Ok\r\n");
	#endif


	/*RDA5820*/
	#ifdef F_RDA5820
	RDA5820_Init();
	if (RDA5820_Init())
		printf("RDA5820 Error\r\n");
	else
		printf("RDA5820 Ok\r\n");
	RDA5820_Band_Set(0);
	RDA5820_Space_Set(0);
	RDA5820_TxPGA_Set(3);
	RDA5820_TxPAG_Set(63);
	RDA5820_TX_Mode();
	RDA5820_Freq_Set(RDA5820_Fre);
	RDA5820_Vol_Set(15);
	RDA5820_Show_Msg();
	#endif


	/*RDA5820*/
	#ifdef W_RDA5820
	RDA5820_Init();
	if (RDA5820_Init())
		printf("RDA5820 Error\r\n");
	else
		printf("RDA5820 Ok\r\n");
	RDA5820_Band_Set(0);
	RDA5820_Space_Set(0);
	RDA5820_TxPGA_Set(3);
	RDA5820_TxPAG_Set(63);
	RDA5820_TX_Mode();
	RDA5820_Freq_Set(RDA5820_Fre);
	RDA5820_Freq_Set(RDA5820_Fre);
	RDA5820_Vol_Set(15);
	RDA5820_Show_Msg();
	#endif


	#ifdef F_DAC
	#ifdef F_DAC_Sin_Wave
	for(DAC_SIN_Count = 0; DAC_SIN_Count < DAC_SIN_Length; DAC_SIN_Count++)
	{
		DAC_SIN_TAB[DAC_SIN_Count] = 2047.0*(sin(2*3.1415926*DAC_SIN_Count/DAC_SIN_Length)+1)*8/10+500;
	}
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(uint32_t *)&DAC_SIN_TAB[0],DAC_SIN_Length,DAC_ALIGN_12B_R);
	#endif
	printf("DAC_Ok\r\n");
	#endif


	#ifdef F_ADC
//	HAL_TIM_Base_Start(&htim3);
//	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_1_Value_DMA, 1);
//	HAL_ADC_Start_DMA(&hadc2, (uint32_t *)ADC_2_Value_DMA, 1);
//	HAL_ADC_Start(&hadc1);
	printf("ADC_Ok\r\n");
	#endif

	printf("F_Init_Ok\r\n");
}















#endif

