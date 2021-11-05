#ifndef __F_ADF4002_H
#define __F_ADF4002_H
#include "all_config.h"
#ifdef F_ADF4002

#define R_Address 0X000000
#define N_Address 0X000001
#define F_Address 0X000002
#define I_Address 0X000003
#define Pre_R 0X000000          //X000,0000,DAT(14),00
#define Pre_N 0X000000          //XX0,DAT(13),XXXXXX,01

//管脚声明
//GND
#define PLL_SCK PCout(6)// PA8
#define PLL_SDI PCout(7)// PD2
#define PLL_SEN PCout(8)// PD2

#define PLL_SCK_0 PLL_SCK = 0
#define PLL_SCK_1 PLL_SCK = 1

#define PLL_SDI_0 PLL_SDI = 0
#define PLL_SDI_1 PLL_SDI = 1

#define PLL_SEN_0 PLL_SEN = 0
#define PLL_SEN_1 PLL_SEN = 1


void InitPll(void);
void testADF4002(void);
//void Delay(unsigned int z);
void SendDataPll(unsigned long int Data);
void SetFrequency(u32 fvco);
void RDivideTest(u16 RData);


#endif
#endif
