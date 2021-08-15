#ifndef  __FAN_INIT_H__
#define  __FAN_INIT_H__

#include "F_NativeInterface.h"



void F_Init(void)
{
	/*矩阵按键*/
	#ifdef Service_Input_Keypad
	KEY_PAD_Init_F4();
	printf("Keypad_Ok\r\n");
	#endif

	/*独立按键*/
	#ifdef Service_Input_Key
	KEY_INPUT_INIT();
	printf("Key_Ok\r\n");
	#endif


	/*中断*/
	#ifdef F_Interrupt
	#ifdef F_LED_Blink
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, 0);
	HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, 1);
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
	LCD_480_Init();		//初始化
	POINT_COLOR=BLACK;    //画笔颜色：红色
	LCD_Clear(WHITE);	//清屏
	memset(LCD_480_SHOW_BUF,0x00,sizeof(LCD_480_SHOW_BUF)); //清空数组
	sprintf((char *)LCD_480_SHOW_BUF, "FJX_TEST_123");
	LCD_ShowString(30,40,210,24,24,LCD_480_SHOW_BUF);
	printf("800*480LCD_Ok\r\n");
	#endif

	#ifdef Service_Display_LCD_480
	#ifdef F_STM32_F4
	tp_dev.init();//触摸屏初始化
	printf("TOUCH_Ok\r\n");
	#endif
	#endif


	/*240*240LCD*/
	#ifdef Service_Display_LCD_240
	LCD_240_Init();		//初始化
	LCD_Clear(BLACK);	//清屏
	sprintf((char *)LCD_240_SHOW_BUF, "FJX_TEST");
	LCD_ShowString(0, 0, LCD_240_SHOW_BUF, WHITE, BLACK, 24, 0);
	printf("240*240LCD_Ok\r\n");
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


	#ifdef F_DAC
	#ifdef F_DAC_Sin_Wave
	for(DAC_SIN_Count = 0; DAC_SIN_Count < DAC_SIN_Length; DAC_SIN_Count++)
	{
		DAC_SIN_TAB[DAC_SIN_Count] = 2047.0*(sin(2*3.1415926*DAC_SIN_Count/DAC_SIN_Length)+1)*8/10+500;	//防止出现底部失真;
	}
	HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(uint32_t *)&DAC_SIN_TAB[0],DAC_SIN_Length,DAC_ALIGN_12B_R);
	#endif
	printf("DAC_Ok\r\n");
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

