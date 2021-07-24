#ifndef __F_KEY_H__
#define __F_KEY_H__
#include "all_config.h"
#ifdef Service_Input_Key


/*USER*/
/*
  * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 *
  * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 *
 * */
#define F_Key_Num 2		//按键个数

#define F_Key_Valid_Status   1		//有效状态，即按下之后的电平状态
#define F_Key_Invalid_Status 0		//无效状态，即按下之前的电平状态

#define KEY_1_Pin 		 GPIO_PIN_4
#define KEY_1_GPIO_Port  GPIOE

#define KEY_2_Pin 		 GPIO_PIN_0
#define KEY_2_GPIO_Port  GPIOA

/*USER*/
extern u8 F_key_num;
extern u8 F_Key_Scan;
extern u8 F_KEY_FLAG;
extern u16 F_KEY_COUNT;


#define KEY1_READ HAL_GPIO_ReadPin(KEY_1_GPIO_Port,  KEY_1_Pin)
#define KEY2_READ HAL_GPIO_ReadPin(KEY_2_GPIO_Port,  KEY_2_Pin)


#define KEY1_SHORT 1
#define KEY1_LONG  2
#define KEY2_SHORT 3
#define KEY2_LONG  4



typedef struct
{
	uint8_t READ;
	unsigned int TIME;
}KeyType;




void KEY_INIT(void);
unsigned char KEY_SCAN(void);
void KEY_Refresh(u8 i);
void KEY_INPUT_INIT(void);
#endif





#endif
