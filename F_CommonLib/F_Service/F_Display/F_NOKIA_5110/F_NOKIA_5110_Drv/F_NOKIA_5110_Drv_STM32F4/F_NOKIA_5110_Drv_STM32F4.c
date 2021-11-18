#include "./F_NOKIA_5110_Drv_STM32F4.h"
#include "all_config.h"
#ifdef Service_Display_NOKIA_5110
#ifdef F_STM32_F4

void NOKIA_5110_Drv_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();

    GPIO_InitStructure.Pin = NOKIA_5110_BLK_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(NOKIA_5110_BLK_GPIO_Port, &GPIO_InitStructure);
    NOKIA_5110_BLK = 0;

    GPIO_InitStructure.Pin = NOKIA_5110_SCL_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(NOKIA_5110_SCL_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = NOKIA_5110_SDA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(NOKIA_5110_SDA_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = NOKIA_5110_DC_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(NOKIA_5110_DC_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = NOKIA_5110_CE_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(NOKIA_5110_CE_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = NOKIA_5110_RES_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(NOKIA_5110_RES_GPIO_Port, &GPIO_InitStructure);
}
#endif
#endif
