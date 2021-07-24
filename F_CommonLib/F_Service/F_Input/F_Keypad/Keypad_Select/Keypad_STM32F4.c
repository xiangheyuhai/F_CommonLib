#include "../F_Keypad.h"

/*
 * V1-2021.07.02
  * 描述：使用外部中断+读取函数完成
  * 外部中断-行		读取电平-列
  * 正面朝上，下边从左到右为行1 2 3 4-列1 2 3 4
  * 接口为：PB15 PF0 PF2...
 *
 * */
#ifdef Service_Input_Keypad
#ifdef F_STM32_F4

void KEY_PAD_INIT_STM32F4(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOF_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOE_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();

	  /*Configure GPIO pins : PF0 PF2 PF4 */
	  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_4;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);


	  /*Configure GPIO pin : PE8 */
	  GPIO_InitStruct.Pin = GPIO_PIN_8;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	  /*Configure GPIO pin : PB15 */
	  GPIO_InitStruct.Pin = GPIO_PIN_15;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  /*Configure GPIO pins : PD9 PD14 PD15 */
	  GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_14|GPIO_PIN_15;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	  /* EXTI interrupt init*/
	  HAL_NVIC_SetPriority(EXTI0_IRQn, 3, 0);
	  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	  HAL_NVIC_SetPriority(EXTI2_IRQn, 3, 0);
	  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

	  HAL_NVIC_SetPriority(EXTI4_IRQn, 3, 0);
	  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

	  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 3, 0);
	  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}


static u8 key_val = 1;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	u8 row, colum = 0;
	if (key_val != 0)
		return;

	if (GPIO_Pin == GPIO_PIN_15)
	{
		row = 0x10;
	}
	else if (GPIO_Pin == GPIO_PIN_0)
	{
		row = 0x20;
	}
	else if (GPIO_Pin == GPIO_PIN_2)
	{
		row = 0x30;
	}
	else if (GPIO_Pin == GPIO_PIN_4)
	{
		row = 0x40;
	}

	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9))
	{
		colum = 0x01;
	}
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14))
	{
		colum = 0x02;
	}
	else if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15))
	{
		colum = 0x03;
	}
	else if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_8))
	{
		colum = 0x04;
	}

	if (row != 0 && colum != 0)
	{
		key_val = row | colum;
	}
}

u8 F_KEYPAD_NUM = 0;
int F_KEYPAD_COUNT = 0;
u8 F_KEYPAD_FLAG = 0;
uint8_t Get_Key(void)
{
	uint8_t ch = 0;
	if (F_KEYPAD_FLAG)
	{
		F_KEYPAD_FLAG = 0;
		if (key_val != 0 )
		{
			if (key_val == 0x11)		ch = 1;
			else if (key_val == 0x12)	ch = 2;
			else if (key_val == 0x13)	ch = 3;
			else if (key_val == 0x14)	ch = 4;

			else if (key_val == 0x21)	ch = 5;
			else if (key_val == 0x22)	ch = 6;
			else if (key_val == 0x23)	ch = 7;
			else if (key_val == 0x24)	ch = 8;

			else if (key_val == 0x31)	ch = 9;
			else if (key_val == 0x32)	ch = 10;
			else if (key_val == 0x33)	ch = 11;
			else if (key_val == 0x34)	ch = 12;

			else if (key_val == 0x41)	ch = 13;
			else if (key_val == 0x42)	ch = 14;
			else if (key_val == 0x43)	ch = 15;
			else if (key_val == 0x44)	ch = 16;

			key_val = 0x00;
		}
	}
	return ch;
}



#endif
#endif
