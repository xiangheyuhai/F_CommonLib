#include "./Keypad_Drv_STM32F4.h"
#include "all_config.h"
#ifdef SERVICE_KEYPAD
#ifdef F_STM32_F4

void writeRow(char GPIO,char State)
{
	switch(GPIO)
	{
		case '1': HAL_GPIO_WritePin(ROW1_GPIO_Port,ROW1_GPIO_PIN,State); break;
		case '2': HAL_GPIO_WritePin(ROW2_GPIO_Port,ROW2_GPIO_PIN,State); break;
		case '3': HAL_GPIO_WritePin(ROW3_GPIO_Port,ROW3_GPIO_PIN,State); break;
		case '4': HAL_GPIO_WritePin(ROW4_GPIO_Port,ROW4_GPIO_PIN,State); break;
		case 'A':
		{
			HAL_GPIO_WritePin(ROW1_GPIO_Port,ROW1_GPIO_PIN,State);
			HAL_GPIO_WritePin(ROW2_GPIO_Port,ROW2_GPIO_PIN,State);
			HAL_GPIO_WritePin(ROW3_GPIO_Port,ROW3_GPIO_PIN,State);
			HAL_GPIO_WritePin(ROW4_GPIO_Port,ROW4_GPIO_PIN,State);
		}
		break;
	default: break;
	}
}
uint8_t readCol(char GPIO)
{
	uint8_t state;
	switch(GPIO)
	{
		case '1': state = HAL_GPIO_ReadPin(COL1_GPIO_Port,COL1_GPIO_PIN); break;
		case '2': state = HAL_GPIO_ReadPin(COL2_GPIO_Port,COL2_GPIO_PIN); break;
		case '3': state = HAL_GPIO_ReadPin(COL3_GPIO_Port,COL3_GPIO_PIN); break;
		case '4': state = HAL_GPIO_ReadPin(COL4_GPIO_Port,COL4_GPIO_PIN); break;
	default : break;
	}
	return state;
}


void Keypad_Drv_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();
	  __HAL_RCC_GPIOG_CLK_ENABLE();

	  //行--设置为输入
	  GPIO_InitStruct.Pin = ROW1_GPIO_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(ROW1_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = ROW2_GPIO_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(ROW2_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = ROW3_GPIO_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(ROW3_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = ROW4_GPIO_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(ROW4_GPIO_Port, &GPIO_InitStruct);

	  //列--上拉输入
	  GPIO_InitStruct.Pin = COL1_GPIO_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(COL1_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = COL2_GPIO_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(COL2_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = COL3_GPIO_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(COL3_GPIO_Port, &GPIO_InitStruct);

	  GPIO_InitStruct.Pin = COL4_GPIO_PIN;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_PULLUP;
	  HAL_GPIO_Init(COL4_GPIO_Port, &GPIO_InitStruct);
}
#endif
#endif
