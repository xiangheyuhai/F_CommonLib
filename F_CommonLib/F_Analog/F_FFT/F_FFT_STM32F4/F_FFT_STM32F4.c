#include "./F_FFT_STM32F4.h"
#include "all_config.h"
#ifdef F_FFT
#ifdef F_STM32_F4
#include "arm_math.h"


float FFT_InputBuf[FFT_LENGTH*2];	//FFT输入数组
float FFT_OutputBuf[FFT_LENGTH];	//FFT输出数组
float FFT_Result[FFT_LENGTH/2-1];	//FFT输出数组,31
u16 ADC_1_Value_DMA[FFT_LENGTH] = {0};
u16 LCD_Show_Clear[240] = {0};





#ifdef Service_Display_OLED_SPI
void OLED_Show_FFT(float *str)
{
  u16 i, j = 0;
  u16 high = 0;
  float32_t temp_str[4] = {0};
  float32_t Result = 0;

  for (i = 0; i < 128; i++)
  {
	  for (j = 0; j < 4; j++)
		  temp_str[j] = str[4*i+j];
	  arm_mean_f32(temp_str,4,&Result);//计算得到相邻四个点的平均值
	  high = (u16)(0.000125 * Result * 8);
	  if(high >= 30)
		  high = 30;
//	  printf("%d, %f\r\n",i, Result);
	  if (i == 0)
		  high = 0;
	  OLED_SPI_DrawLine(i, 32-high, i, 32+high, 1);
  }
}
#endif


void FFT_TEST(arm_cfft_radix4_instance_f32 scfft)
{
	u16 i = 0;
	for(i=0;i<FFT_LENGTH;i++)//生成信号序列
	{
	  FFT_InputBuf[2*i]=100+
						10*arm_sin_f32(2*PI*i/FFT_LENGTH)+
						30*arm_sin_f32(2*PI*i*4/FFT_LENGTH)+
						50*arm_cos_f32(2*PI*i*8/FFT_LENGTH);	//生成输入信号实部
	  FFT_InputBuf[2*i+1]=0;//虚部全部�????????????0
	}


	//打印信号数组
	printf("FFT Signal:\r\n");
	for(i=0;i<FFT_LENGTH;i++)
	{
	  printf("FFT_InputBuf[%d]:%f\r\n", i, FFT_InputBuf[i]);
	}
	printf("\r\n\r\n\r\n\r\n\r\n\r\n");


	arm_cfft_radix4_f32(&scfft,FFT_InputBuf);	//FFT计算
	arm_cmplx_mag_f32(FFT_InputBuf,FFT_OutputBuf,FFT_LENGTH);	//把运算结果复数求模得幅�??


	//打印结果数组
	printf("FFT Result:\r\n");
	for(i=0;i<FFT_LENGTH;i++)
	{
	  printf("FFT_OutputBuf[%d]:%f\r\n", i, FFT_OutputBuf[i]);
	}
}
#endif
#endif
