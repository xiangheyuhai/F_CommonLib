#ifndef __F_FSK_H
#define __F_FSK_H
#include "all_config.h"
#ifdef F_FSK


#define FSK_Pin 	   GPIO_PIN_2
#define FSK_GPIO_Port  GPIOA

#define FSK_Out			PAout(2)



void FSK_Drv_Init(void);
void FSK_Send_Head(void);
void FSK_Send_End(void);
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
