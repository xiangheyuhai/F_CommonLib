#ifndef __F_KEYPAD_F4_H__
#define __F_KEYPAD_F4_H__
#include "all_config.h"
#ifdef Service_Input_Keypad
#ifdef F_STM32_F4



extern u8 F_KEYPAD_FLAG;
extern int F_KEYPAD_COUNT;
extern u8 F_KEYPAD_NUM;

void KEY_PAD_Init_F4(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
uint8_t Get_Key(void);






#endif
#endif
#endif
