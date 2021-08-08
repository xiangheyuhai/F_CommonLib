#ifndef __F_OLED_SPI_H
#define __F_OLED_SPI_H
#include "all_config.h"
#ifdef Service_Display_OLED_SPI


extern unsigned char OLED_SPI_SHOW_BUF[30];



//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_SPI_MODE 0


#define SIZE 16
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF
#define X_WIDTH 	128
#define Y_WIDTH 	64



#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED_SPI驱动
void OLED_SPI_WR_Byte(u8 dat,u8 cmd);

//OLED通用
void OLED_SPI_Fill_Picture(unsigned char fill_Data);
void OLED_SPI_Set_Pos(unsigned char x, unsigned char y);
void OLED_SPI_Display_On(void);
void OLED_SPI_Display_Off(void);
void OLED_SPI_Clear(void);
void OLED_SPI_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_SPI_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size);
u32 OLED_SPI_Pow(u8 m,u8 n);
void OLED_SPI_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_SPI_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_SPI_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void OLED_SPI_Init(void);


#endif
#endif
