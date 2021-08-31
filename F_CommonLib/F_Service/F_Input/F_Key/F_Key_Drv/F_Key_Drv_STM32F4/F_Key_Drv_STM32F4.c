#include "./F_Key_Drv_STM32F4.h"

#ifdef Service_Input_Key
#ifdef F_STM32_F4


void Key_Drv_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*如果修改了IO口，需要修改这个*/
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = KEY_1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(KEY_1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = KEY_2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(KEY_2_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = KEY_3_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(KEY_3_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = KEY_4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(KEY_4_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = KEY_5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(KEY_5_GPIO_Port, &GPIO_InitStruct);

}





#endif
#endif
