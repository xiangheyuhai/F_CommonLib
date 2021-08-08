#ifndef __F_FSK_H
#define __F_FSK_H
#include "all_config.h"
#ifdef F_FSK

void FSK_SEND_HEAD(void);
void FSK_SEND_END(void);
void FSK_SEND_1(void);
void FSK_SEND_0(void);
void FSK_Set_Fre(u8 i);
void FSK_Send_Char(unsigned char  data_hex, u8* array);
char FSK_IN(char* array);
void FSK_Send_String(char* Temp_Buf,  u8 Length);








#endif
#endif
