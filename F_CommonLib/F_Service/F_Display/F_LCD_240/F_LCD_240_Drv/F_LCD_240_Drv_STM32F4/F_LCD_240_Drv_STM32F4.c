#include "./F_LCD_240_Drv_STM32F4.h"
#ifdef Service_Display_LCD_240
#ifdef F_STM32_F4
#include "all_config.h"

void LCD_240_Drv_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();
	  __HAL_RCC_GPIOE_CLK_ENABLE();

	  //3  SCL	SPI时钟线
	  #ifndef Service_Display_LCD_240_Hardware
	  GPIO_InitStruct.Pin = LCD_240_SCL_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_SCL_GPIO_Port, &GPIO_InitStruct);

	  //4  SDA	SPI数据线
	  GPIO_InitStruct.Pin = LCD_240_SDA_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_SDA_GPIO_Port, &GPIO_InitStruct);
	  #endif

	  //5  RES	复位
	  GPIO_InitStruct.Pin = LCD_240_RES_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_RES_GPIO_Port, &GPIO_InitStruct);

	  //6  DC	数据/命令选择脚
	  GPIO_InitStruct.Pin = LCD_240_DC_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_DC_GPIO_Port, &GPIO_InitStruct);

	  //7	BLK	背光控制开关，默认打开背光，低电平关闭背光
	  GPIO_InitStruct.Pin = LCD_240_BLK_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_BLK_GPIO_Port, &GPIO_InitStruct);


	  //勿删
	  #ifndef Service_Display_LCD_240_Hardware
	  HAL_GPIO_WritePin(LCD_240_SCL_GPIO_Port, LCD_240_SCL_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_SDA_GPIO_Port, LCD_240_SCL_Pin, GPIO_PIN_SET);
	  #endif
	  HAL_GPIO_WritePin(LCD_240_SCL_GPIO_Port, LCD_240_SCL_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_SDA_GPIO_Port, LCD_240_SCL_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_RES_GPIO_Port, LCD_240_RES_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_DC_GPIO_Port,  LCD_240_DC_Pin,  GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_BLK_GPIO_Port, LCD_240_BLK_Pin, GPIO_PIN_SET);
}

#endif
#endif

