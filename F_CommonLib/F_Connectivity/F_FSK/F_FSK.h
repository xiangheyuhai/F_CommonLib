#ifndef __F_FSK_H
#define __F_FSK_H
#include "all_config.h"
#ifdef F_FSK


#define FSK_Head_HTime 200	//发帧头的时候高电平持续时间
#define FSK_1_HTime 70	//发1的时候的高电平持续时间
#define FSK_0_HTime 35	//发0的时候的高电平持续时间
#define FSK_End_HTime 100	//发帧尾的时候高电平持续时间

#define FSK_D_HTime 40	//帧间隔时间

uint32_t DAC_MAX;



#define FSK_Pin 	   GPIO_PIN_2
#define FSK_GPIO_Port  GPIOA

#define FSK_Out			PAout(2)



void FSK_Drv_Init(void);
void FSK_Send_Head(void);
void FSK_Send_End(void);
u8 FSK_Send_Check(u8* array);
void FSK_Send_1(void);
void FSK_Send_0(void);
void FSK_Set_Fre(u8 i);
void FSK_Send_Char(unsigned char  data_hex, u8* array);
char FSK_IN(char* array);
void FSK_Send_String(char* Temp_Buf,  u8 Length);
void FSK_Send_8421BCD(int data);
u8 FSK_Receive_8421BCD(u8* array);
void FSK_Send_8421BCD_4(u8* array);
void FSK_Test(void);






#endif
#endif
