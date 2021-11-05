#ifndef  __FAN_INTERRUPT_H
#define  __FAN_INTERRUPT_H
#include "./all_config_all.h"

#ifdef F_LED_Blink
u16 F_LED_COUNT = 0;
#endif
u8 SEG_Count = 0;


#ifdef F_Interrupt
void SysTick_Handler(void)
{
	HAL_IncTick();


	#ifdef Service_Input_Keypad
	F_KEYPAD_COUNT++;
	if (F_KEYPAD_COUNT >= 200)
	{
		F_KEYPAD_COUNT = 0;		F_KEYPAD_FLAG = 1;
	}
	#endif


	#ifdef Service_Input_Key
	F_Key_Count++;
	if (F_Key_Count >= 10)
	{
		F_Key_Count = 0;		F_Key_Flag = 1;
	}
	#endif


	#ifdef F_LED_Blink
	F_LED_COUNT++;
	if (F_LED_COUNT >= 1000)
	{
		F_LED_COUNT = 0;
		#ifdef F_LED_Blink_LED0
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		#endif
		#ifdef F_LED_Blink_LED1
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		#endif
//		SEG_Count++;
//		SEG_DATA[0] = SEG_Count;
//		SEG_DATA[1] = SEG_Count;
//		SEG_DATA[2] = SEG_Count;
//		SEG_DATA[3] = SEG_Count;
//		if (SEG_Count > 9)
//			SEG_Count = 0;
	}
	#endif


	#ifdef F_ADC
	ADC_Fliter_Count++;
	if (ADC_Fliter_Count >= 2)
	{
		ADC_Fliter_Count = 0;
		ADC_Fliter_Flag = 1;
	}
	#endif

	#ifdef F_AD9959
	#ifdef F_AD9959_Sweep_Fre
	if (AD9959_Mode == AD9959_Mode_Sweep)
	{
		AD9959_SweepCount++;
		if (AD9959_SweepCount >= AD9959_SweepTime)//大于间隔时间扫一次
		{
			AD9959_SweepCount = 0;//计时清零
			AD9959_NowSinFre[0] = AD9959_SweepMinFre + AD9959_SweepStepFre*AD9959_SweepCountTimes;
			AD9959_SweepCountTimes++;
			if (AD9959_NowSinFre[0] > AD9959_SweepMaxFre)
			{
				AD9959_SweepCountTimes = 0;
			}
			Write_frequence(0,AD9959_NowSinFre[0]);

			if (AD9959_SweepWaveFlag == 1)
			{
//				HMI_Send_ADC_Wave(ADC_Value_DMA_1[1],ADC_Value_DMA_1[2]);
			}
		}
	}
	#endif


	#ifdef F_AD9959_Sweep_Pha
	if (AD9959_Mode == AD9959_Mode_Sweep)
	{
		AD9959_SweepCount++;
		if (AD9959_SweepCount >= AD9959_SweepTime)
		{
			AD9959_SweepCount = 0;
			AD9959_NowSinPhr[0] = AD9959_SweepMinPha + AD9959_SweepStepPha*AD9959_SweepCountTimes;
			AD9959_SweepCountTimes++;
			if (AD9959_NowSinPhr[0] > AD9959_SweepMaxPha)
				AD9959_SweepCountTimes = 0;
			Write_Phase(0, AD9959_NowSinPhr[0]);
		}
	}
	#endif
	#endif

}
#endif





#ifdef Service_Input_Keypad
void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_11);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
}
void EXTI9_5_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
}
#endif

#endif









