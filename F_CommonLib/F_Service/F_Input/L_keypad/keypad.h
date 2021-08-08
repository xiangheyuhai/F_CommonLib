/*
 * keypad.h
 *
 *  Created on: May 8, 2021
 *      Author: zoe
 */

#ifndef MYDRV_KEYPAD_KEYPAD_H_
#define MYDRV_KEYPAD_KEYPAD_H_
#include "main.h"
#include "usart.h"

#define COL4_Pin GPIO_PIN_0
#define COL4_GPIO_Port GPIOG
#define COL3_Pin GPIO_PIN_1
#define COL3_GPIO_Port GPIOG
#define COL2_Pin GPIO_PIN_2
#define COL2_GPIO_Port GPIOG
#define COL1_Pin GPIO_PIN_3
#define COL1_GPIO_Port GPIOG
#define ROW4_Pin GPIO_PIN_4
#define ROW4_GPIO_Port GPIOG
#define ROW3_Pin GPIO_PIN_5
#define ROW3_GPIO_Port GPIOG
#define ROW2_Pin GPIO_PIN_6
#define ROW2_GPIO_Port GPIOG
#define ROW1_Pin GPIO_PIN_7
#define ROW1_GPIO_Port GPIOG

typedef enum
{
  PIN_RESET = 0u,
  PIN_SET
} PinState;

PinState flag;

extern unsigned char i,j,k,x,y,sum;

typedef void (*callback)(unsigned char x,unsigned char y);
callback cfunction;

typedef enum
{
    Pull_Up,
    Pull_Down,
}keypad_select_mode;
/***底层函数如下***/
void setOut(char target, PinState state);
void writeRow(char index,PinState state);
PinState readCol(char index);
/**调用函数如下**/
void keypad_init(keypad_select_mode mode,unsigned char len_size,unsigned char wid_size);
unsigned char keypad_scan(void);
/**其他如下**/
void repeat(callback function,unsigned char x,unsigned char y);
void sum_event(unsigned char sum);

/************应用函数在此定义**************/
void function0(unsigned char x,unsigned char y);
void function1(unsigned char x,unsigned char y);
void function2(unsigned char x,unsigned char y);
void function3(unsigned char x,unsigned char y);
void function4(unsigned char x,unsigned char y);
void function5(unsigned char x,unsigned char y);
void function6(unsigned char x,unsigned char y);
void function7(unsigned char x,unsigned char y);
void function8(unsigned char x,unsigned char y);
void function9(unsigned char x,unsigned char y);
void function10(unsigned char x,unsigned char y);
void function11(unsigned char x,unsigned char y);
void function12(unsigned char x,unsigned char y);
void function13(unsigned char x,unsigned char y);
void function14(unsigned char x,unsigned char y);
void function15(unsigned char x,unsigned char y);
void function16(unsigned char x,unsigned char y);
/****************************/
#endif /* MYDRV_KEYPAD_KEYPAD_H_ */
