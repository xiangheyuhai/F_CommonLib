#ifndef __F_KEY_H
#define __F_KEY_H
#include "all_config.h"
#ifdef Service_Input_Key





extern u8 F_key_Value;
extern u8 F_Key_Scan;
extern u8 F_Key_Flag;
extern u8 F_Key_Count;


#define KEY1_SHORT 1
#define KEY1_LONG  2
#define KEY2_SHORT 3
#define KEY2_LONG  4
#define KEY3_SHORT 5
#define KEY3_LONG  6
#define KEY4_SHORT 7
#define KEY4_LONG  8
#define KEY5_SHORT 9
#define KEY5_LONG  10



typedef struct
{
	uint8_t READ;
	unsigned int TIME;
}KeyType;



u8 Key_Scan(void);
void Key_Refresh(unsigned char i);
void Key_Init(void);


#endif
#endif
