#ifndef __F_KEY_DRV_STM32F4_H
#define __F_KEY_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Input_Key
#ifdef F_STM32_F4


/***********************************USER修改***********************************/
#define F_Key_Num 5					//按键个数
#define F_Key_Valid_Status   0		//有效状态，即按下之后的电平状态
#define F_Key_Invalid_Status 1		//无效状态，即按下之前的电平状态

#define KEY_1_Pin 		 GPIO_PIN_6
#define KEY_1_GPIO_Port  GPIOB

#define KEY_2_Pin 		 GPIO_PIN_5
#define KEY_2_GPIO_Port  GPIOB

#define KEY_3_Pin 		 GPIO_PIN_4
#define KEY_3_GPIO_Port  GPIOB

#define KEY_4_Pin 		 GPIO_PIN_3
#define KEY_4_GPIO_Port  GPIOB

#define KEY_5_Pin 		 GPIO_PIN_15
#define KEY_5_GPIO_Port  GPIOA
/***********************************USER修改***********************************/

#define KEY1_READ HAL_GPIO_ReadPin(KEY_1_GPIO_Port,  KEY_1_Pin)
#define KEY2_READ HAL_GPIO_ReadPin(KEY_2_GPIO_Port,  KEY_2_Pin)
#define KEY3_READ HAL_GPIO_ReadPin(KEY_3_GPIO_Port,  KEY_3_Pin)
#define KEY4_READ HAL_GPIO_ReadPin(KEY_4_GPIO_Port,  KEY_4_Pin)
#define KEY5_READ HAL_GPIO_ReadPin(KEY_5_GPIO_Port,  KEY_5_Pin)


void Key_Drv_Init(void);

#endif
#endif
#endif
