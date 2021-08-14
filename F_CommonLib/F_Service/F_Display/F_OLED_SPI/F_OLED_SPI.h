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


void OLED_SPI_WR_Byte(u8 dat,u8 cmd);
void OLED_SPI_ColorTurn(u8 i);
void OLED_SPI_DisplayTurn(u8 i);
void OLED_SPI_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_SPI_Refresh(void);
void OLED_SPI_Clear(void);
void OLED_SPI_DrawPoint(u8 x,u8 y,u8 t);
void OLED_SPI_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2,u8 mode);
void OLED_SPI_DrawCircle(u8 x,u8 y,u8 r);
void OLED_SPI_ShowChar(u8 x,u8 y,u8 chr,u8 size1,u8 mode);
void OLED_SPI_ShowString(u8 x,u8 y,u8 *chr,u8 size1,u8 mode);
u32 OLED_SPI_Pow(u8 m,u8 n);
void OLED_SPI_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1,u8 mode);
void OLED_SPI_ShowChinese(u8 x,u8 y,u8 num,u8 size1,u8 mode);
void OLED_SPI_ScrollDisplay(u8 num,u8 space,u8 mode);
void OLED_SPI_ShowPicture(u8 x,u8 y,u8 sizex,u8 sizey,u8 BMP[],u8 mode);
void OLED_SPI_Init(void);


#endif
#endif
