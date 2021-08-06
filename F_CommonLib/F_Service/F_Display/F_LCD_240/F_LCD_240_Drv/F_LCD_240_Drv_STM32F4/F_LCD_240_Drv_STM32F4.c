#include "./F_LCD_240_Drv_STM32F4.h"
#ifdef Service_Display_LCD_240
#ifdef F_STM32_F4


void LCD_240_Drv_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  __HAL_RCC_GPIOE_CLK_ENABLE();

//	  HAL_GPIO_WritePin(LCD_240_ALL_GPIO_Port, LCD_240_SCL_Pin | LCD_240_SDA_Pin | LCD_240_RES_Pin | LCD_240_DC_Pin | LCD_240_BLK_Pin, GPIO_PIN_RESET);

	  GPIO_InitStruct.Pin = LCD_240_SCL_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_SCL_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_SDA_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_SDA_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_RES_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_RES_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_DC_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_DC_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_BLK_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_BLK_GPIO_Port, &GPIO_InitStruct);


	  //勿删
	  HAL_GPIO_WritePin(LCD_240_SCL_GPIO_Port, LCD_240_SCL_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_SDA_GPIO_Port, LCD_240_SCL_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_RES_GPIO_Port, LCD_240_RES_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_DC_GPIO_Port,  LCD_240_DC_Pin,  GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_BLK_GPIO_Port, LCD_240_BLK_Pin, GPIO_PIN_SET);
}

#endif
#endif

