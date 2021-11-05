#ifndef __F_DAC_DRV_STM32F4_H
#define __F_DAC_DRV_STM32F4_H
#include "all_config.h"
#ifdef F_DAC
#ifdef F_STM32_F4


#define DAC_SIN_Length 83	//�????????个周期点�????????
u16 DAC_SIN_Count = 0;					//用于生成波形数组
u16 DAC_SIN_TAB[DAC_SIN_Length] = {0};	//sin数组


void DAC_Drv_Init(void);

#endif
#endif
#endif
