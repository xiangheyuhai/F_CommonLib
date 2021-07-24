#ifndef  __F_CAPATURE_STM32F4_H__
#define  __F_CAPATURE_STM32F4_H__
#include "all_config.h"
#ifdef F_Capture_STM32F4
#ifdef F_STM32_F4



extern u8 Capture_Mode;		 //状态标志
extern u8 Capture_Fliter_Flag;
extern u32 Capture_Buf[3];        //存放计数值  上升沿时的计数值 下降沿时的计数值 下一个上升沿时的计数值
extern u32 Capture_Buf_Real[3];   //存放计数值  上升沿时的计数值 下降沿时的计数值 下一个上升沿时的计数值
extern uint_least64_t Capture_Sum[3];        //存放计数值  上升沿时的计数值 下降沿时的计数值 下一个上升沿时的计数值 分别的总和（滤波用）
extern u8 Capture_Duty;			  //占空比
extern u32  Capture_Frequency;	  //频率



extern u8 FSK_Reveive_Count[100];
extern u8 FSK_Reveive[8];


//void Capture_Fliter(u8 Capture_Fliter_Times);
void Capture_Pro(void);
void FSK_Receive_Data(u8* array_count, u8* array_data);
/*获取前八个高电平的平均值*/
u16 FSK_Judge_Begin(u8* array_count, u8 count);



#endif
#endif
#endif











