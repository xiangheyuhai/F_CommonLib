#include "../LCD_480.h"

#ifdef F_STM32_F4
#ifdef Service_Display_LCD_480
//static u32 fac_us=0;							//us延时倍乘数
//void delay_us(u32 nus)
//{
//	u32 ticks;
//	u32 told,tnow,tcnt=0;
//	u32 reload=SysTick->LOAD;				//LOAD的值
//	ticks=nus*fac_us; 						//需要的节拍数
//	told=SysTick->VAL;        				//刚进入时的计数器值
//	while(1)
//	{
//		tnow=SysTick->VAL;
//		if(tnow!=told)
//		{
//			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
//			else tcnt+=reload-tnow+told;
//			told=tnow;
//			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
//		}
//	};
//}
//
////延时nms
////nms:要延时的ms数
//void delay_ms(u16 nms)
//{
//	u32 i;
//	for(i=0;i<nms;i++) delay_us(1000);
//}

void HAL_Delay_us(uint32_t nus)
{
	//将systic设置为1us中断
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000000);
	//延时nus
	HAL_Delay(nus-1);
	//恢复systic中断为1ms
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
}


#endif
#endif
