#ifndef __F_NOKIA_5110_H
#define __F_NOKIA_5110_H
#include "all_config.h"
#ifdef Service_Display_NOKIA_5110

extern char NOKIA_5110_SHOW_BUF[30];




void NOKIA_5110_Init(void);
void NOKIA_5110_Clear(void);
void NOKIA_5110_Set_XY(unsigned char X, unsigned char Y);
void NOKIA_5110_Write_char(unsigned char c);
void NOKIA_5110_Write_english_string(unsigned char X,unsigned char Y,char *s);
void NOKIA_5110_Write_chinese_string(unsigned char X, unsigned char Y,
                   unsigned char ch_with,unsigned char num,
                   unsigned char line,unsigned char row);
void NOKIA_5110_Draw_bmp_pixel(unsigned char X,unsigned char Y,unsigned char *map,
                  unsigned char Pix_x,unsigned char Pix_y);
void NOKIA_5110_Write_byte(unsigned char dat, unsigned char command);



#endif
#endif
