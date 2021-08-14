#include "./F_OLED_SPI_Drv_STM32F4.h"
#ifdef Service_Display_OLED_SPI
#ifdef F_STM32_F4
#include "all_config.h"



void OLED_SPI_Drv_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	__HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = OLED_SPI_SCL_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OLED_SPI_SCL_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = OLED_SPI_SDA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OLED_SPI_SDA_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = OLED_SPI_RES_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OLED_SPI_RES_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = OLED_SPI_DC_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OLED_SPI_DC_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = OLED_SPI_CS_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(OLED_SPI_CS_GPIO_Port, &GPIO_InitStructure);


}
#endif
#endif
