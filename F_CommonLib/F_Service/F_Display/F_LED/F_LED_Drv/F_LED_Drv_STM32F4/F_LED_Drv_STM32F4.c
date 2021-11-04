#include "./F_LED_Drv_STM32F4.h"
#include "all_config.h"
#ifdef F_LED_Blink
#ifdef F_STM32_F4


void LED_Drv_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();

	#ifdef F_LED_Blink_LED0
    GPIO_InitStructure.Pin = LED0_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED0_GPIO_Port, &GPIO_InitStructure);
	HAL_GPIO_WritePin(LED0_GPIO_Port,  LED0_Pin,  GPIO_PIN_SET);
	#endif

	#ifdef F_LED_Blink_LED1
    GPIO_InitStructure.Pin = LED1_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStructure);
	HAL_GPIO_WritePin(LED1_GPIO_Port,  LED1_Pin,  GPIO_PIN_SET);
	#endif
}
#endif
#endif

