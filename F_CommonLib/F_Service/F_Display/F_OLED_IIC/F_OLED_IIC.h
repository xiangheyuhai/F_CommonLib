#ifndef __F_OLED_IIC_H
#define __F_OLED_IIC_H
#include "all_config.h"

#ifdef Service_Display_OLED_IIC

/*USER*/
/*
  * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 *
  * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 *
 * */
#define OLED_IIC_SCL_Pin 		GPIO_PIN_1
#define OLED_IIC_SCL_GPIO_Port  GPIOE

#define OLED_IIC_SDA_Pin 		GPIO_PIN_0
#define OLED_IIC_SDA_GPIO_Port  GPIOE

#define OLED_IIC_SCL_SDA_GPIO_Port GPIOE
/*USER*/


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


//-----------------OLED IIC端口定义----------------

//IO操作函数
/*SET*/
#define OLED_IIC_SCL_SET	HAL_GPIO_WritePin(OLED_IIC_SCL_GPIO_Port, OLED_IIC_SCL_Pin, GPIO_PIN_SET)
#define OLED_IIC_SDA_SET	HAL_GPIO_WritePin(OLED_IIC_SDA_GPIO_Port, OLED_IIC_SDA_Pin, GPIO_PIN_SET)

/*RESET*/
#define OLED_IIC_SCL_RESET	HAL_GPIO_WritePin(OLED_IIC_SCL_GPIO_Port, OLED_IIC_SCL_Pin, GPIO_PIN_RESET)
#define OLED_IIC_SDA_RESET	HAL_GPIO_WritePin(OLED_IIC_SDA_GPIO_Port, OLED_IIC_SDA_Pin, GPIO_PIN_RESET)

/*READ*/
#define OLED_IIC_SDA_READ    HAL_GPIO_ReadPin(OLED_IIC_SDA_GPIO_Port,  OLED_IIC_SDA_Pin)


#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void OLED_IIC_SDA_INPUT_INIT(void);/*设置SDA为输入模式*/
void OLED_IIC_SDA_OUTPUT_INIT(void);/*设置SDA为输出模式*/
u8 IIC_Wait_Ack();




#endif
#endif

