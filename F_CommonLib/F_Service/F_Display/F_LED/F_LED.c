#include "F_LED.h"


void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	__HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitStructure.Pin = LED0_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = LED1_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStructure);

	HAL_GPIO_WritePin(LED0_GPIO_Port,  LED0_Pin,  GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED1_GPIO_Port,  LED1_Pin,  GPIO_PIN_SET);
}

