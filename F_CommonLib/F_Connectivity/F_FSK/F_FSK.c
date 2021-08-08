#include "./F_FSK.h"
#ifdef F_FSK
#include "../../F_Chip/F_AD9959/F_AD9959.h"


/*
  * 发帧头
  * 高电平时间是16100-16600us
  * 包络检波之后的结果是高点平持续30ms，低电平持续5ms
 *
 * */
void FSK_SEND_HEAD(void)
{
	FSK_Set_Fre(1);
	HAL_Delay(30);
	FSK_Set_Fre(0);
	HAL_Delay(5);
}
/*
  * 发帧尾
  * 高电平时间是16100-16600us
  * 包络检波之后的结果是高点平持续50ms，低电平持续20ms
 * */
void FSK_SEND_END(void)
{
	FSK_Set_Fre(1);
	HAL_Delay(50);
	FSK_Set_Fre(0);
	HAL_Delay(20);
}
/*
  * 发1
  * 高电平时间是11100-11500us
  * 包络检波之后的结果是高点平持续20ms，低电平持续5ms
 * */
void FSK_SEND_1(void)
{
	FSK_Set_Fre(1);
	HAL_Delay(20);
	FSK_Set_Fre(0);
	HAL_Delay(5);
}

/*
  * 发0
  * 高电平时间是6050-6600us
  * 包络检波之后的结果是高点平持续10ms，低电平持续5ms
 * */
void FSK_SEND_0(void)
{
	FSK_Set_Fre(1);
	HAL_Delay(10);
	FSK_Set_Fre(0);
	HAL_Delay(5);
}


/*
 * 设置高低频率
 * 1--10k--包络检波之后为高电平
 * 1--15k--包络检波之后为低电平
 *
 * */
void FSK_Set_Fre(u8 i)		//入口为1--10K, 入口为0--15K
{
	if (i == 0)
		Write_frequence(0,15000);//9959给频率
	else
		Write_frequence(0,10000);//9959给频率
}


/*
  * 发送一个字节--加校验
  * 入口参数为的八位数组是把char型的变量拆分为01后的结果
 *
 * */
void FSK_Send_Char(unsigned char  data_hex, u8* array)
{
	u8 i = 0;
	FSK_SEND_HEAD();
	for (i = 0; i < 8; i++)
	{
		if (data_hex & 0x80)
		{
			array[i] = 1;
			FSK_SEND_1(); //发1
		}
		else
		{
			array[i] = 0;
			FSK_SEND_0(); //发0
		}
//		printf("%d", array[i]);
		data_hex <<= 1;    //左移1位
	}
}

/*
 * FSK接收八位数据，转化为相应的ASCII码
  * 入口参数 存放八位数据的数组
 */
char FSK_IN(char* array)
{
	char data_temp = 0;
	u8 i = 0;
	for (i = 0; i < 8; i++)
	{
		data_temp<<=1;
		data_temp+=array[i];
	}
	return data_temp;
}


/*
 * FSK发送字符串
 * 入口参数: 存放字符串的数组 数组长度
 */
void FSK_Send_String(char* Temp_Buf,  u8 Length)
{
	u8 i = 0;
	u8 temp_buffer[100] = {0};
	for (i = 0; i < Length; i++)
	{
		FSK_Send_Char(Temp_Buf[i], temp_buffer);
	}
	FSK_SEND_END();//帧尾
}


#endif
