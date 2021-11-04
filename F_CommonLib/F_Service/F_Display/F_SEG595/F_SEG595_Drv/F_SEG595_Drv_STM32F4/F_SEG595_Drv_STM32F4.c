#include "./F_SEG595_Drv_STM32F4.h"
#include "all_config.h"
#ifdef Service_Display_SEG595
#ifdef F_STM32_F4

void SEG595_Drv_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();


    GPIO_InitStructure.Pin = SEG595_SCLK_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SEG595_SCLK_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = SEG595_DIO_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SEG595_DIO_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = SEG595_RCLK_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SEG595_RCLK_GPIO_Port, &GPIO_InitStructure);
}

#endif
#endif

