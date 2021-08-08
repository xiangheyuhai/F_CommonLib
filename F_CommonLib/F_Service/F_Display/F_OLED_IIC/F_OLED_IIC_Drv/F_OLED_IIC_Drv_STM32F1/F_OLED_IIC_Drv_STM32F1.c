#include "./F_OLED_IIC_Drv_STM32F1.h"
#ifdef Service_Display_OLED_IIC
#ifdef F_STM32_F1
#include "all_config.h"


void OLED_IIC_Drv_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0},GPIO_InitStructure_1 = {0};

	__HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = OLED_IIC_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OLED_IIC_DATA_Port, &GPIO_InitStructure);


    GPIO_InitStructure_1.Pin = OLED_IIC_CLK_Pin;
    GPIO_InitStructure_1.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure_1.Pull = GPIO_PULLUP;
    GPIO_InitStructure_1.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OLED_IIC_CLK_Port, &GPIO_InitStructure_1);
}



void OLED_SDA_Input(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = OLED_IIC_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OLED_IIC_DATA_Port, &GPIO_InitStructure);
}


void OLED_SDA_Output(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = OLED_IIC_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OLED_IIC_DATA_Port, &GPIO_InitStructure);
}
#endif
#endif

