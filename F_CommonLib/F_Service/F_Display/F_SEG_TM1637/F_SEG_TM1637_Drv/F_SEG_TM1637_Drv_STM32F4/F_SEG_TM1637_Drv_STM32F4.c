#include "./F_SEG_TM1637_Drv_STM32F4.h"
#include "all_config.h"
#ifdef Service_Display_SEG_TM1637
#ifdef F_STM32_F4

void SEG_TM1637_Drv_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  GPIO_InitStruct.Pin = SEG_TM1637_IIC_CLK_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(SEG_TM1637_IIC_CLK_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = SEG_TM1637_IIC_SDA_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(SEG_TM1637_IIC_SDA_GPIO_Port, &GPIO_InitStruct);
}

#endif
#endif
