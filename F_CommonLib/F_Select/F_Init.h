#ifndef  __FAN_INIT_H
#define  __FAN_INIT_H
#include "F_NativeInterface.h"



void F_Init(void)
{
	printf("F_Init_Began\r\n");

	/*DAC*/
	#ifdef F_DAC
	DAC_Init();
	printf("DAC_Ok\r\n");
	#endif

	/*LED*/
	#ifdef F_LED_Blink
	LED_Init();
	printf("LED_Ok\r\n");
	#endif


	/*矩阵按键*/
	#ifdef Service_Input_Keypad
	KEY_PAD_Init_F4();
	printf("Keypad_Ok\r\n");
	#endif


	/*独立按键*/
	#ifdef Service_Input_Key
	Key_Init();
	printf("Key_Ok\r\n");
	#endif


	/*矩阵按键*/
	#ifdef SERVICE_KEYPAD
	Keypad_Init();
	printf("W_Keypad_Ok\r\n");
	#endif


	/*中断*/
	#ifdef F_Interrupt
	#ifdef F_LED_Blink
	#ifdef F_LED_Blink_LED0
	HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
	#endif
	#ifdef F_LED_Blink_LED1
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	#endif
	printf("Interrupt_Ok\r\n");
	#endif
	#endif


	/*串口*/
	#ifdef F_STM32_F4
	#ifdef F_USART
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);
	printf("USART_Ok\r\n");
	#endif
	#endif


	/*串口屏*/
	#ifdef Service_Display_HMI
	#ifdef F_STM32_F4
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


	#ifdef Service_Display_NOKIA_5110
	#ifdef F_STM32_F4
	NOKIA_5110_Init();
	NOKIA_5110_Clear();
	NOKIA_5110_Write_english_string(0,0,"2021.11.04_test");
	printf("NOKIA_5110_Ok\r\n");
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
	sprintf((char *)OLED_SPI_SHOW_BUF, "FJX_TEST");
	OLED_SPI_ShowString(0,1, OLED_SPI_SHOW_BUF, 16, 1);

	sprintf((char *)OLED_SPI_SHOW_BUF, "FJX_TEST2");
	OLED_SPI_ShowString(0,16, OLED_SPI_SHOW_BUF, 16, 1);
	OLED_SPI_Refresh();
	printf("OLED_SPI_Ok\r\n");
	#endif


	/*SEG_TM1637*/
	#ifdef Service_Display_SEG_TM1637
	SEG_TM1637_DATA_Config(1,1,22,1,0);
	SEG_TM1637_DATA_Display(8);
	#endif


	/*SEG_595*/
	#ifdef Service_Display_SEG595
	SEG595_Init();
	printf("SEG_595_Ok\r\n");
	#endif


	/*240*240LCD*/
	#ifdef Service_Display_LCD_240
	LCD_240_Init();		//初始化
	LCD_Clear(BLACK);	//清屏
	sprintf((char *)LCD_240_SHOW_BUF, "FJX_TEST");
	LCD_ShowString(0, 0, LCD_240_SHOW_BUF, WHITE, BLACK, 24, 0);
	printf("240*240LCD_Ok\r\n");
	#endif


	/*240*240LCD 带字库*/
	#ifdef Service_Display_LCD_240_FontLib
	LCD_240_FontLib_Init();
	LCD_Clear(WHITE);
	sprintf((char *)LCD_240_FontLib_SHOW_BUF, "FJX_TEST");
	LCD_ShowString(0, 0, LCD_240_FontLib_SHOW_BUF, RED, WHITE,16,0);
	printf("240*240LCD_FontLib_Ok\r\n");
	#endif


	/*240*240LCD 并口*/
	#ifdef Service_Display_LCD_240_ParallelPort
	LCD_240_ParallelPort_Init();
	LCD_Clear(WHITE);
	sprintf((char *)LCD_240_ParallelPort_SHOW_BUF, "FJX_TEST");
	LCD_ShowString(0, 0, LCD_240_ParallelPort_SHOW_BUF, RED, WHITE,16,0);
	printf("240*240LCD_ParallelPort_Ok\r\n");
	#endif


	/*800*480LCD*/
	#ifdef Service_Display_LCD_480
	LCD_480_Init();		//初始化
	POINT_COLOR=BLACK;    //画笔颜色：红色
	LCD_Clear(WHITE);	//清屏
	memset(LCD_480_SHOW_BUF,0x00,sizeof(LCD_480_SHOW_BUF)); //清空数组
	sprintf((char *)LCD_480_SHOW_BUF, "FJX_TEST_123");
	LCD_ShowString(30,40,210,24,24,LCD_480_SHOW_BUF);
	printf("800*480LCD_Ok\r\n");
	#endif


	/*TOUCH*/
	#ifdef Service_TOUCH
	#ifdef F_STM32_F4
	tp_dev.init();//触摸屏初始化
	if(tp_dev.touchtype&0X80)
//		TOUCH_Test();//电容屏测试，这里便是个死循环！！！
	printf("TOUCH_Ok\r\n");
	#endif
	#endif


	/*AD9959*/
	#ifdef F_AD9959
	AD9959_Init();	//初始化
	#ifdef F_AD9959_Sweep_Fre
	AD9959_Mode = AD9959_Mode_Sweep;//扫频
	#endif
	#ifdef F_AD9959_Sweep_Pha
	AD9959_Mode = AD9959_Mode_Sweep;//扫相
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
	ADF4351WriteFreq(ADF4351_Set_Fre);//单位是MHz
	printf("ADF4351_Ok\r\n");
	#endif


	#ifdef F_MB1504
	MB1504_Init();
	MB1504_SetF(32,MB1504_Fre);
	printf("MB1504_Ok\r\n");
	#endif


	/*RDA5820*/
	#ifdef F_RDA5820
	RDA5820_Init();
	if (RDA5820_Init())
		printf("RDA5820 Error\r\n");
	else
		printf("RDA5820 Ok\r\n");
	RDA5820_Band_Set(0);		//设置频段为87~108Mhz
	RDA5820_Space_Set(0);		//设置步进为100Khz
	RDA5820_TxPGA_Set(3);		//信号增益设置为3
	RDA5820_TxPAG_Set(63);		//发射功率为最大.
	RDA5820_TX_Mode();			//发送模式
	RDA5820_Freq_Set(RDA5820_Fre);	//设置频率
	RDA5820_Vol_Set(15);		//设置声音最大
	RDA5820_Show_Msg();
	#endif


	/*RDA5820*/
	#ifdef W_RDA5820
	RDA5820_Init();
	if (RDA5820_Init())
		printf("RDA5820 Error\r\n");
	else
		printf("RDA5820 Ok\r\n");
	RDA5820_Band_Set(0);		//设置频段为87~108Mhz
	RDA5820_Space_Set(0);		//设置步进为100Khz
	RDA5820_TxPGA_Set(3);		//信号增益设置为3
	RDA5820_TxPAG_Set(63);		//发射功率为最大.
	RDA5820_TX_Mode();			//发送模式
	RDA5820_Freq_Set(RDA5820_Fre);	//设置频率
	RDA5820_Freq_Set(RDA5820_Fre);	//设置频率
	RDA5820_Vol_Set(15);		//设置声音最大
	RDA5820_Show_Msg();
	#endif


	#ifdef F_ADC
//	HAL_TIM_Base_Start(&htim3);
//	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_1_Value_DMA, 1);//转换后的结果放到ADC_Value_DMA_1
//	HAL_ADC_Start_DMA(&hadc2, (uint32_t *)ADC_2_Value_DMA, 1);//转换后的结果放到ADC_Value_DMA_1
//	HAL_ADC_Start(&hadc1);     //启动ADC转换
	printf("ADC_Ok\r\n");
	#endif

	printf("F_Init_Ok\r\n");
}















#endif

