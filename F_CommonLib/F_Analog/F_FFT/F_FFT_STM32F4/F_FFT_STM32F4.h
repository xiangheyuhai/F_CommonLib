#ifndef __F_FFT_STM32F4_H
#define __F_FFT_STM32F4_H
#include "all_config.h"
#ifdef F_FFT
#ifdef F_STM32_F4

#define FFT_LENGTH		64 		//FFT长度，默认是1024点FFT



extern float FFT_InputBuf[FFT_LENGTH*2];	//FFT输入数组
extern float FFT_OutputBuf[FFT_LENGTH];	//FFT输出数组
extern u16 ADC_1_Value_DMA[FFT_LENGTH];
extern u16 LCD_Show_Clear[240];

void LCD_Show_FFT(float *str, u16 *str_clear);
void OLED_Show_FFT(float *str);
void LCD_Show_FFT_Clear(u16 *str_clear);

#endif
#endif
#endif
