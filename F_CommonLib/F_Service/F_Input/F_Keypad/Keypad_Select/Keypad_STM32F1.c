#include "../F_Keypad.h"


#ifdef Service_Input_Keypad
#ifdef F_STM32_F1

/*
 * 	用户修改
 * 		按键个数
 * 		按键接口
*/
#define F_Key_Num 2
#define F_Key1_Port GPIOE
#define F_Key1_Pin  GPIO_PIN_4
#define F_Key2_Port GPIOE
#define F_Key2_Pin  GPIO_PIN_3

/*读取电平*/
#define F_KEY1 HAL_GPIO_ReadPin(F_Key1_Port,F_Key1_Pin)
#define F_KEY2 HAL_GPIO_ReadPin(F_Key2_Port,F_Key2_Pin)

/*返回值*/
#define F_KEY1_SHORT 1
#define F_KEY1_LONG  2
#define F_KEY2_SHORT 3
#define F_KEY2_LONG  4
#define F_KEY3_SHORT 5
#define F_KEY3_LONG  6
#define F_KEY4_SHORT 7
#define F_KEY4_LONG  8


#endif

#endif
