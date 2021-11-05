#include "./F_SEG595.h"
#include "all_config.h"
#ifdef Service_Display_SEG595
#include "math.h"
#include "./F_SEG595_Drv/F_SEG595_Drv_STM32F4/F_SEG595_Drv_STM32F4.h"


/*使用方法，放到循环中
SEG595_Display(SEG_DATA);
 * */

uint8_t SEG_DATA[4] = {8,9,6,7};


const uint8_t SEG_NB[] =
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};

/*
 * 注意：这个函数必须放到while中
 * */
void SEG595_Display(uint8_t *data)
{
	const uint8_t *MbPointer;
	uint8_t Data,i;

	for (i=0;i<4;i++){
		MbPointer = SEG_NB+data[i];
		Data = *MbPointer;
		SEG595_SendData(Data);
		SEG595_SendData(pow(2,i));
		HAL_Delay(1);
		SEG595_RCLK = 0;
		SEG595_RCLK = 1;
	}
}


void SEG595_SendData(uint8_t data)
{
	uint8_t i;
	for (i=8;i>=1;i--){
		if (data&0x80) SEG595_DIO = 1; else SEG595_DIO = 0;
		data<<=1;
		SEG595_SCLK = 0;
		SEG595_SCLK = 1;
	}
}

void SEG595_Init(void)
{
	SEG595_Drv_Init();
}
#endif

