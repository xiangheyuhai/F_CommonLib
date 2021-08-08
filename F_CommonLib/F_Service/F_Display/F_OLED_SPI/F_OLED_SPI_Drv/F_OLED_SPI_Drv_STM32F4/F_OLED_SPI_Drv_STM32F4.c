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

	 #if OLED_SPI_MODE==1

	GPIO_InitStructure.GPIO_Pin =0xFF; //PC0~7 OUT推挽输出
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC,0xFF); //PC0~7输出高

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //PG13,14,15 OUT推挽输出
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_SetBits(GPIOG,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);						 //PG13,14,15 OUT  输出高

	 #else

// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 //PC0,1 OUT推挽输出
// 	GPIO_Init(GPIOC, &GPIO_InitStructure);
// 	GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1);						 //PC0,1 OUT  输出高
//
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 //PG15 OUT推挽输出	  RST
// 	GPIO_Init(GPIOG, &GPIO_InitStructure);
// 	GPIO_SetBits(GPIOG,GPIO_Pin_15);						 //PG15 OUT  输出高
#endif

}
#endif
#endif
