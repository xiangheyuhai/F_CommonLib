#ifndef __F_ADF4351_H
#define __F_ADF4351_H
#include "all_config.h"
#ifdef F_ADF4351




//引脚定义
//读取
#define ADF4351_INPUT_DATA_Pin 			GPIO_PIN_1
#define ADF4351_INPUT_DATA_GPIO_Port 	GPIOB

//写入
#define ADF4351_ALL_GPIO_Port 			GPIOB

#define ADF4351_CLK_Pin 				GPIO_PIN_0
#define ADF4351_CLK_GPIO_Port 			GPIOB

#define ADF4351_OUTPUT_DATA_Pin 		GPIO_PIN_1
#define ADF4351_OUTPUT_DATA_GPIO_Port 	GPIOB

#define ADF4351_LE_Pin 					GPIO_PIN_2
#define ADF4351_LE_GPIO_Port 			GPIOB

#define ADF4351_CE_Pin 					GPIO_PIN_10
#define ADF4351_CE_GPIO_Port 			GPIOB


/*SET*/
#define ADF4351_OUTPUT_DATA_SET		HAL_GPIO_WritePin(ADF4351_OUTPUT_DATA_GPIO_Port, ADF4351_OUTPUT_DATA_Pin, GPIO_PIN_SET)
#define ADF4351_CLK_SET				HAL_GPIO_WritePin(ADF4351_CLK_GPIO_Port,     	 ADF4351_CLK_Pin,   	  GPIO_PIN_SET)
#define ADF4351_LE_SET				HAL_GPIO_WritePin(ADF4351_LE_GPIO_Port,     	 ADF4351_LE_Pin,   		  GPIO_PIN_SET)
#define ADF4351_CE_SET				HAL_GPIO_WritePin(ADF4351_CE_GPIO_Port,     	 ADF4351_CE_Pin,   		  GPIO_PIN_SET)


/*RESET*/
#define ADF4351_OUTPUT_DATA_RESET	HAL_GPIO_WritePin(ADF4351_OUTPUT_DATA_GPIO_Port, ADF4351_OUTPUT_DATA_Pin, GPIO_PIN_RESET)
#define ADF4351_CLK_RESET			HAL_GPIO_WritePin(ADF4351_CLK_GPIO_Port,     	 ADF4351_CLK_Pin,   	  GPIO_PIN_RESET)
#define ADF4351_LE_RESET			HAL_GPIO_WritePin(ADF4351_LE_GPIO_Port,        	 ADF4351_LE_Pin,   		  GPIO_PIN_RESET)
#define ADF4351_CE_RESET			HAL_GPIO_WritePin(ADF4351_CE_GPIO_Port,     	 ADF4351_CE_Pin,   		  GPIO_PIN_RESET)


/*READ_GPIO*/
#define ADF4351_INPUT_DATA 			HAL_GPIO_ReadPin(ADF4351_INPUT_DATA_GPIO_Port, 	 ADF4351_INPUT_DATA_Pin)

#define ADF4351_RF_OFF	((u32)0XEC801C)


void ADF4351_GPIO_Output_Init(void);
void ADF4351_GPIO_Iutput_Init(void);
void ADF4351_delay(int length);
void WriteToADF4351(u8 count, u8 *buf);
void ReadToADF4351(u8 count, u8 *buf);
void F_ADF4351_Init(void);
void WriteOneRegToADF4351(u32 Regster);
void ADF4351_Init_some(void);
void ADF4351WriteFreq(float Fre);		//	(xx.x) M Hz




#endif
#endif
