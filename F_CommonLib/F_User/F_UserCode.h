#ifndef __F_USERCODE_H
#define __F_USERCODE_H
#include "all_config.h"
#ifdef Service_UserCode


extern u8 Set_Fre;
extern u8 ADF4351_Show_1_Flag;
extern u16 ADF4351_Show_1_Count;
extern u16 ADF4351_Set_Fre;
extern u8 ADF4351_Set_Fre_Flag;


void ADF4351_Show_0(void);
void ADF4351_Show_1(void);
void ADF4351_Show_2(void);
void ADF4351_Set_Show_Cursor(void);
void ADF4351_Set_Show_Fre(void);
void ADF4351_Get_Fre(void);




#endif
#endif
