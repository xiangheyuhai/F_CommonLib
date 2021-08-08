#ifndef __F_OLED_IIC_H
#define __F_OLED_IIC_H
#include "all_config.h"

#ifdef Service_Display_OLED_IIC


extern unsigned char OLED_IIC_SHOW_BUF[30];



#define OLED_MODE 0
//#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED_IIC驱动
void IIC_IIC_Write_Command(unsigned char IIC_Command);
void IIC_IIC_Write_Data(unsigned char IIC_Data);
void OLED_IIC_WR_Byte(unsigned dat,unsigned cmd);

//OLED通用
void OLED_IIC_Fill_Picture(unsigned char fill_Data);
void OLED_IIC_Set_Pos(unsigned char x, unsigned char y);
void OLED_IIC_Display_On(void);
void OLED_IIC_Display_Off(void);
void OLED_IIC_Clear(void);
//void OLED_IIC_On(void);
void OLED_IIC_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_IIC_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size);
u32 Oled_IIC_Pow(u8 m,u8 n);
void OLED_IIC_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_IIC_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_IIC_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_IIC_Init(void);





#endif
#endif

