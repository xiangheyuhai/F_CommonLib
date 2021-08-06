#ifndef __F_OLED_IIC_H
#define __F_OLED_IIC_H
#include "all_config.h"

#ifdef Service_Display_OLED_IIC


extern unsigned char OLED_IIC_SHOW_BUF[30];



#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
void IIC_Write_Command(unsigned char IIC_Command);
void IIC_Write_Data(unsigned char IIC_Data);
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void fill_picture(unsigned char fill_Data);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_On(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size);
u32 oled_pow(u8 m,u8 n);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_IIC_Init(void);





#endif
#endif

