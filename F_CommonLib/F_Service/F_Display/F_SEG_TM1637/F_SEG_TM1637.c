#include "./F_SEG_TM1637.h"
#include "all_config.h"
#ifdef Service_Display_SEG_TM1637
#include "./F_SEG_TM1637_Drv/F_SEG_TM1637_Drv_STM32F4/F_SEG_TM1637_Drv_STM32F4.h"

unsigned char SEG_dt=20; //延时时间参数
unsigned char dpFlag = 0;//主函数有说明
unsigned char Data[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00};
unsigned char DataDp[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef,0x80};

struct {
	char shi;
	char ge;
}FB;

struct {
	char shi;
	char ge;
}SB;


/*
 * 入口参数：前两个数码管的数字
 * 		  前两个数码管是否亮
 * 		  后两个数码管的数字
 * 		  后两个数码管的数字
 * 		  中间的两个点是否亮
 * */
void SEG_TM1637_DATA_Config(unsigned char fb,unsigned char fb_show_flag,unsigned char sb,unsigned char sb_show_flag,unsigned char dot)
{

	SEG_TM1637_Drv_Init();

	if(fb_show_flag==1)
	{
		FB.shi = fb/10;
		FB.ge =  fb%10;
	}
	else
	{
		FB.shi=FB.ge=10;
	}
	if(sb_show_flag==1)
	{
		SB.shi = sb/10;
		SB.ge =  sb%10;
	}
	else
	{
		SB.shi=SB.ge=10;
	}
	dpFlag = dot;

}

void SEG_TM1637_I2C_Start(void)
{
	SEG_TM1637CLK_1;
	SEG_TM1637DIO_1;
	F_HAL_Delay_us(SEG_dt);
	SEG_TM1637DIO_0;
	F_HAL_Delay_us(SEG_dt);
	SEG_TM1637CLK_0;
	F_HAL_Delay_us(SEG_dt);
}

void SEG_TM1637_I2C_stop(void)
{
	SEG_TM1637CLK_0;
	F_HAL_Delay_us(SEG_dt);
	SEG_TM1637DIO_0;
	F_HAL_Delay_us(SEG_dt);
	SEG_TM1637CLK_1;
	F_HAL_Delay_us(SEG_dt);
	SEG_TM1637DIO_1;
	F_HAL_Delay_us(SEG_dt);
}


void SEG_TM1637_WriteBit(unsigned char mBit)
{
	SEG_TM1637CLK_0;
	F_HAL_Delay_us(SEG_dt);
	if(mBit)
		SEG_TM1637DIO_1;
	else
		SEG_TM1637DIO_0;
	F_HAL_Delay_us(SEG_dt);
	SEG_TM1637CLK_1;
	F_HAL_Delay_us(SEG_dt);
}


void SEG_TM1637_WriteByte(unsigned char Byte)
{
	char loop = 0;
	for(loop = 0;loop<8;loop++)
	{
		SEG_TM1637_WriteBit((Byte>>loop) & 0x01);//先写低位
	}
	SEG_TM1637CLK_0;
	F_HAL_Delay_us(SEG_dt);
	SEG_TM1637DIO_1;
	F_HAL_Delay_us(SEG_dt);
	SEG_TM1637CLK_1;
}


void SEG_TM1637_WriteCommand(unsigned char mData)
{
	SEG_TM1637_I2C_Start();
	SEG_TM1637_WriteByte(mData);
	SEG_TM1637_I2C_stop();
}


/*
 * 写入地址和数据
 * */
void SEG_TM1637_WriteData(unsigned char addr,unsigned char mData)
{
	SEG_TM1637_I2C_Start();
	SEG_TM1637_WriteByte(addr);
	SEG_TM1637_WriteByte(mData);
	SEG_TM1637_I2C_stop();
}


/*
 * 亮度调节
 * 0--灭
 * 8--最亮
 * */
void SEG_TM1637_DATA_Display(uint8_t light)//light 0-8
{
	SEG_TM1637_WriteCommand(0x44);
	SEG_TM1637_WriteData(0xc0,Data[FB.shi]);
	if(dpFlag)
		SEG_TM1637_WriteData(0xc1,DataDp[FB.ge]);
	else
		SEG_TM1637_WriteData(0xc1,Data[FB.ge]);

	SEG_TM1637_WriteData(0xc2, Data[SB.shi]);
	SEG_TM1637_WriteData(0xc3, Data[SB.ge]);
	if (light) light |= 0x08;
    light |= 0x80;
    SEG_TM1637_WriteCommand(light);
 }


#endif

