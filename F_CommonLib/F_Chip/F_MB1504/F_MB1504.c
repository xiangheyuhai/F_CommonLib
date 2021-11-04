#include "./F_MB1504.h"
#include "all_config.h"
#ifdef F_MB1504
#include "./F_MB1504_Drv/F_MB1504_Drv_STM32F4/F_MB1504_Drv_STM32F4.h"

unsigned long MB1504_Fre = 60000000;


//设置R: P预分频数（32/64） R programmable reference divider
void MB1504_SetR(unsigned char P, unsigned long R)
{
	unsigned char i;
	unsigned int Temp_R;

	MB1504_LE = 0;
	MB1504_CLK = 0;

	if(P == 32)
		MB1504_DATA = 1;
	else if(P == 64)
		MB1504_DATA = 0;
	else
		return;
	F_HAL_Delay_us(1);
	MB1504_CLK = 1;
	F_HAL_Delay_us(1);
	MB1504_CLK = 0;
	F_HAL_Delay_us(1);

	Temp_R = R;
	Temp_R <<= 2;
	for(i=0; i<14; i++)
	{
		if((Temp_R & 0x8000) == 0x8000)
			MB1504_DATA = 1;
		else
			MB1504_DATA = 0;
		F_HAL_Delay_us(1);
		MB1504_CLK = 1;
		F_HAL_Delay_us(1);
		MB1504_CLK = 0;
		F_HAL_Delay_us(1);
		Temp_R <<= 1;
	}

	MB1504_DATA = 1;
	F_HAL_Delay_us(1);
	MB1504_CLK = 1;
	F_HAL_Delay_us(1);
	MB1504_CLK = 0;
	F_HAL_Delay_us(1);

	MB1504_LE = 1;
	F_HAL_Delay_us(1);
	MB1504_LE = 0;
}

//设置N和A N programmable counter divider A swallow counter	divider
void MB1504_SetNA(unsigned long N, unsigned char A)
{
	unsigned char i, Temp_A;
	unsigned int	Temp_N;

	MB1504_LE = 0;
	MB1504_CLK = 0;

	Temp_N = N;
	Temp_N <<= 5;
	for(i=0; i<11; i++)
	{
		if((Temp_N & 0x8000) == 0x8000)
			MB1504_DATA = 1;
		else
			MB1504_DATA = 0;
		F_HAL_Delay_us(1);
		MB1504_CLK = 1;
		F_HAL_Delay_us(1);
		MB1504_CLK = 0;
		F_HAL_Delay_us(1);
		Temp_N <<= 1;
	}

	Temp_A = A;
	Temp_A <<= 1;
	for(i=0; i<7; i++)
	{
		if((Temp_A & 0x80) == 0x80)
			MB1504_DATA = 1;
		else
			MB1504_DATA = 0;
		F_HAL_Delay_us(1);
		MB1504_CLK = 1;
		F_HAL_Delay_us(1);
		MB1504_CLK = 0;
		F_HAL_Delay_us(1);
		Temp_A <<= 1;
	}

	MB1504_DATA = 0;
	F_HAL_Delay_us(1);
	MB1504_CLK = 1;
	F_HAL_Delay_us(1);
	MB1504_CLK = 0;
	F_HAL_Delay_us(1);

	MB1504_LE = 1;
	F_HAL_Delay_us(1);
	MB1504_LE = 0;
}


//设置MB1504的锁定频率 P 32/64 f xxKHz
void MB1504_SetF(unsigned char P, unsigned long f)
{
	unsigned long R, N;
	unsigned char A;
	R = F_Osc / F_Step;
	if(P == 32)
	{
		N = ((f / F_Step) / 32);
		A = ((f / F_Step) % 32);
	}
	else if(P == 64)
	{
		N = ((f / F_Step) / 64);
		A = ((f / F_Step) % 64);
	}
	else
		return;
	MB1504_SetR(P, R);
	MB1504_SetNA(N, A);
}

//MB1504初始化
void MB1504_Init(void)
{
	MB1504_Drv_Init();
}


#endif
