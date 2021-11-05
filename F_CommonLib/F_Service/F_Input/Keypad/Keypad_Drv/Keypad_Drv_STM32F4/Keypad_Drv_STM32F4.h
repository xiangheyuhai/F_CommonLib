#ifndef SERVICE_KEYPAD_KEYPAD_DRV_H_
#define SERVICE_KEYPAD_KEYPAD_DRV_H_
#include "all_config.h"
#ifdef SERVICE_KEYPAD
#ifdef F_STM32_F4

//行
#define ROW1_GPIO_Port  GPIOC
#define ROW2_GPIO_Port  GPIOD
#define ROW3_GPIO_Port  GPIOC
#define ROW4_GPIO_Port  GPIOD

#define ROW1_GPIO_PIN GPIO_PIN_7
#define ROW2_GPIO_PIN GPIO_PIN_7
#define ROW3_GPIO_PIN GPIO_PIN_10
#define ROW4_GPIO_PIN GPIO_PIN_2

//列
#define COL1_GPIO_Port  GPIOA
#define COL2_GPIO_Port  GPIOC
#define COL3_GPIO_Port  GPIOG
#define COL4_GPIO_Port  GPIOA

#define COL1_GPIO_PIN GPIO_PIN_8
#define COL2_GPIO_PIN GPIO_PIN_9
#define COL3_GPIO_PIN GPIO_PIN_7
#define COL4_GPIO_PIN GPIO_PIN_11



void writeRow(char GPIO,char State);
uint8_t readCol(char GPIO);
void Keypad_Drv_Init(void);


#endif
#endif
#endif
