#include "./F_DAC_Drv_STM32F4.h"
#include "all_config.h"
#ifdef F_DAC
#ifdef F_STM32_F4


void DAC_Drv_Init(void)
{
  for(DAC_SIN_Count = 0; DAC_SIN_Count < DAC_SIN_Length; DAC_SIN_Count++)
  {
      DAC_SIN_TAB[DAC_SIN_Count] = 2047.0*(sin(2*3.1415926*DAC_SIN_Count/DAC_SIN_Length)+1)*8/10+500;	//防止出现底部失真;
  }
  HAL_TIM_Base_Start(&htim6);//打开定时�????????
  HAL_DAC_Start_DMA(&hdac,DAC_CHANNEL_1,(uint32_t *)&DAC_SIN_TAB[0],DAC_SIN_Length,DAC_ALIGN_12B_R);//启动DMA
}




#endif
#endif
