#ifndef SERVICE_KEYPAD_KEYPAD_DRV_H_
#define SERVICE_KEYPAD_KEYPAD_DRV_H_
#include "all_config.h"
#ifdef SERVICE_KEYPAD
#ifdef F_STM32_F4

//行
#define ROW1_GPIO_Port  GPIOE
#define ROW2_GPIO_Port  GPIOE
#define ROW3_GPIO_Port  GPIOE
#define ROW4_GPIO_Port  GPIOD

#define ROW1_GPIO_PIN 	GPIO_PIN_9
#define ROW2_GPIO_PIN 	GPIO_PIN_7
#define ROW3_GPIO_PIN 	GPIO_PIN_15
#define ROW4_GPIO_PIN 	GPIO_PIN_8

//列
#define COL1_GPIO_Port  GPIOD
#define COL2_GPIO_Port  GPIOF
#define COL3_GPIO_Port  GPIOF
#define COL4_GPIO_Port  GPIOF

#define COL1_GPIO_PIN	GPIO_PIN_10
#define COL2_GPIO_PIN 	GPIO_PIN_3
#define COL3_GPIO_PIN 	GPIO_PIN_1
#define COL4_GPIO_PIN 	GPIO_PIN_12



void writeRow(char GPIO,char State);
uint8_t readCol(char GPIO);
void Keypad_Drv_Init(void);


#endif
#endif
#endif
