#ifndef  __FAN_INTERRUPT_H__
#define  __FAN_INTERRUPT_H__


/*仅用来计数*/
u16 F_LED_COUNT = 0;


#ifdef F_Interrupt
void SysTick_Handler(void)
{
	HAL_IncTick();

	#ifdef Service_Input_Keypad
	F_KEYPAD_COUNT++;
	if (F_KEYPAD_COUNT >= 500)
	{
		F_KEYPAD_COUNT = 0;		F_KEYPAD_FLAG = 1;
	}
	#endif

	#ifdef F_LED_Blink
	F_LED_COUNT++;
	if (F_LED_COUNT >= 500)
	{
		F_LED_COUNT = 0;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
		HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	}
	#endif


	#ifdef F_ADC
	ADC_Fliter_Count++;
	if (ADC_Fliter_Count >= 50)
	{
		ADC_Fliter_Count = 0;
		ADC_Fliter_Flag = 1;
	}
	#endif



	#ifdef F_AD9959
	if (AD9959_Mode == AD9959_Mode_Sweep)
	{
		AD9959_SweepCount++;
		if (AD9959_SweepCount >= AD9959_SweepTime)
		{
			AD9959_SweepCount = 0;
			AD9959_NowSinFre[0] = AD9959_SweepMinFre + AD9959_SweepStepFre*AD9959_SweepCountTimes;
			AD9959_SweepCountTimes++;
			if (AD9959_NowSinFre[0] > AD9959_SweepMaxFre)
			{
				AD9959_SweepCountTimes = 0;

				if (AD9959_SweepWaveFlag)
				{
//					HMI_Clear_ADC_Wave(1);
				}
			}
			Write_frequence(0,AD9959_NowSinFre[0]);
			Write_frequence(1,AD9959_NowSinFre[0]);
			if (AD9959_SweepWaveFlag == 1)
			{
//				HMI_Send_ADC_Wave(ADC_Value_DMA_1[1],ADC_Value_DMA_1[2]);
			}
		}
	}
	#endif




}
#endif





#ifdef Service_Input_Keypad
void EXTI0_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

void EXTI2_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

void EXTI4_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);

}
void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_15);
}
#endif



#endif











