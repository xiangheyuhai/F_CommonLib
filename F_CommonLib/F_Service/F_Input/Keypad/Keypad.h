#ifndef SERVICE_KEYPAD_KEYPAD_H
#define SERVICE_KEYPAD_KEYPAD_H
#include "all_config.h"
#ifdef SERVICE_KEYPAD



typedef enum
{
  KEY_Release = 0,
  KEY_Press
}KEY_STATE;

#define DELAY_MAX_TIME 100
#define PULL_UP 1 //up set 1
#define ROW_NUM '4'
#define COL_NUM '4'


extern int Keypad_Num;
extern char Keypad_Mean;

void initKeypad(void (*callback)(unsigned char x, unsigned char y));
void ROW_scan(unsigned char index);
int scanKeypad();
void keypad_callback(unsigned char x, unsigned char y);
void Keypad_Init(void);


#endif
#endif
