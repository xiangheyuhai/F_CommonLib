#include "./F_AD9959_Drv_STM32F4.h"
#ifdef F_AD9959
#ifdef F_STM32_F4

/*STM32F4_Drv*/
void AD9959_Drv_Init(void)
{
	  /* GPIO Ports Clock Enable */
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOF_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOG_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();


	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOG, AD9959_SDIO3_Pin|AD9959_SDIO2_Pin|AD9959_Reset_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, AD9959_PS0_Pin|AD9959_SCLK_Pin|AD9959_SDIO1_Pin|AD9959_PS2_Pin
	                          |AD9959_UPDATE_Pin|AD9959_CS_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(AD9959_SDIO0_GPIO_Port, AD9959_SDIO0_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOD, AD9959_PS3_Pin|AD9959_PWR_Pin|AD9959_PS1_Pin, GPIO_PIN_RESET);


	  /*Configure GPIO pins : PGPin PGPin PGPin */
	  GPIO_InitStruct.Pin = AD9959_SDIO3_Pin|AD9959_SDIO2_Pin|AD9959_Reset_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	  /*Configure GPIO pins : PCPin PCPin PCPin PCPin
	                           PCPin PCPin */
	  GPIO_InitStruct.Pin = AD9959_PS0_Pin|AD9959_SCLK_Pin|AD9959_SDIO1_Pin|AD9959_PS2_Pin
	                          |AD9959_UPDATE_Pin|AD9959_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pin : PtPin */
	  GPIO_InitStruct.Pin = AD9959_SDIO0_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(AD9959_SDIO0_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : PDPin PDPin PDPin */
	  GPIO_InitStruct.Pin = AD9959_PS3_Pin|AD9959_PWR_Pin|AD9959_PS1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}


#endif
#endif
