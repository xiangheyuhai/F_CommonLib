#include "./F_LCD_240_ParallelPort_Drv_STM32F4.h"
#include "all_config.h"
#ifdef Service_Display_LCD_240_ParallelPort
#ifdef F_STM32_F4



void LCD_240_ParallelPort_Drv_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  GPIO_InitStruct.Pin = LCD_240_D0_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_D0_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_D1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_D1_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_D2_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_D2_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_D3_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_D3_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_D4_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_D4_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_D5_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_D5_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_D6_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_D6_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_D7_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_D7_GPIO_Port, &GPIO_InitStruct);

	  //5位
	  GPIO_InitStruct.Pin = LCD_240_RES_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_RES_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_DC_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_DC_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_CS_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_WR_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(LCD_240_WR_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_RD_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_RD_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = LCD_240_BLK_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_BLK_GPIO_Port, &GPIO_InitStruct);

	  //误删
	  HAL_GPIO_WritePin(LCD_240_D0_GPIO_Port, LCD_240_D0_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_D1_GPIO_Port, LCD_240_D1_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_D2_GPIO_Port, LCD_240_D2_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_D3_GPIO_Port, LCD_240_D3_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_D4_GPIO_Port, LCD_240_D4_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_D5_GPIO_Port, LCD_240_D5_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_D6_GPIO_Port, LCD_240_D6_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_D7_GPIO_Port, LCD_240_D7_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_RES_GPIO_Port,LCD_240_RES_Pin,GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_DC_GPIO_Port, LCD_240_DC_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_CS_GPIO_Port, LCD_240_CS_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_WR_GPIO_Port, LCD_240_WR_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_RD_GPIO_Port, LCD_240_RD_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_BLK_GPIO_Port, LCD_240_BLK_Pin, GPIO_PIN_SET);
}

#endif
#endif

