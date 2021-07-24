#ifndef __F_KEYPAD_H__
#define __F_KEYPAD_H__

#include "all_config.h"


#ifdef Service_Input_Keypad

extern u8 F_KEYPAD_FLAG;
extern int F_KEYPAD_COUNT;
extern u8 F_KEYPAD_NUM;

void KEY_PAD_INIT_STM32F4(void);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
uint8_t Get_Key(void);






#endif
#endif
