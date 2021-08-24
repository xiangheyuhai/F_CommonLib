#include "./F_LCD_240_FontLib_Drv_STM32F4.h"
#ifdef Service_Display_LCD_240_FontLib
#ifdef F_STM32_F4
#include "all_config.h"

void LCD_240_FontLib_Drv_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOE_CLK_ENABLE();

	  //3  SCL	SPI时钟线
	  #ifdef Service_Display_LCD_240_FontLib_Hardware
	  #else
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
	  //5  RES	LCD复位
	  GPIO_InitStruct.Pin = LCD_240_RES_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_RES_GPIO_Port, &GPIO_InitStruct);

	  //6  DC	LCD数据/命令选择脚
	  GPIO_InitStruct.Pin = LCD_240_DC_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_DC_GPIO_Port, &GPIO_InitStruct);

	  //7  CS1	显示屏片选信号
	  GPIO_InitStruct.Pin = LCD_240_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_CS_GPIO_Port, &GPIO_InitStruct);

	  //8  BLK	背光控制开关，默认打开背光，低电平关闭背光
	  GPIO_InitStruct.Pin = LCD_240_BLK_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_BLK_GPIO_Port, &GPIO_InitStruct);

	  //9  FSO	字库数据输出(输入模式)
	  #ifndef Service_Display_LCD_240_FontLib_Hardware
	  GPIO_InitStruct.Pin = LCD_240_ZK_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(LCD_240_ZK_GPIO_Port, &GPIO_InitStruct);
	  #endif

	  //10 CS2	字库芯片片选
	  GPIO_InitStruct.Pin = LCD_240_ZK_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(LCD_240_ZK_CS_GPIO_Port, &GPIO_InitStruct);


	  //全部拉高--勿删
	  #ifdef Service_Display_LCD_240_FontLib_Hardware
	  #else
	  HAL_GPIO_WritePin(LCD_240_SCL_GPIO_Port,   LCD_240_SCL_Pin,   GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_SDA_GPIO_Port,   LCD_240_SCL_Pin,   GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_ZK_GPIO_Port,  	 LCD_240_ZK_Pin,    GPIO_PIN_SET);
	  #endif
	  HAL_GPIO_WritePin(LCD_240_RES_GPIO_Port,   LCD_240_RES_Pin,   GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_DC_GPIO_Port,    LCD_240_DC_Pin,    GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_CS_GPIO_Port, 	 LCD_240_CS_Pin,    GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_BLK_GPIO_Port, 	 LCD_240_BLK_Pin,   GPIO_PIN_SET);
	  HAL_GPIO_WritePin(LCD_240_ZK_CS_GPIO_Port, LCD_240_ZK_CS_Pin, GPIO_PIN_SET);
}

#endif
#endif

