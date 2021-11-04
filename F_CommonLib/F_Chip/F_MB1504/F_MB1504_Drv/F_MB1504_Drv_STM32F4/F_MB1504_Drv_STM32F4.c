#include "./F_MB1504_Drv_STM32F4.h"
#include "all_config.h"
#ifdef F_MB1504
#ifdef F_STM32_F4



//MB1504初始化
void MB1504_Drv_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStructure.Pin = MB1504_LE_Pin | MB1504_DATA_Pin | MB1504_CLK_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(MB1504_GPIO_Port, &GPIO_InitStructure);
}

#endif
#endif
