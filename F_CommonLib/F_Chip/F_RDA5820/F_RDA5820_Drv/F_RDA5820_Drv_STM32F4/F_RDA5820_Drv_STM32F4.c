#include "./F_RDA5820_Drv_STM32F4.h"
#ifdef F_RDA5820
#ifdef F_STM32_F4



void RDA5820_IIC_Drv_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0},GPIO_InitStructure_1 = {0};

	__HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = RDA5820_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RDA5820_DATA_Port, &GPIO_InitStructure);


    GPIO_InitStructure_1.Pin = RDA5820_CLK_Pin;
    GPIO_InitStructure_1.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure_1.Pull = GPIO_PULLUP;
    GPIO_InitStructure_1.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RDA5820_CLK_Port, &GPIO_InitStructure_1);
}



void RDA5820_SDA_Input(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = RDA5820_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RDA5820_DATA_Port, &GPIO_InitStructure);
}


void RDA5820_SDA_Output(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = RDA5820_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RDA5820_DATA_Port, &GPIO_InitStructure);
}

#endif
#endif
