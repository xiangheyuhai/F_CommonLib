#include "./F_FSK.h"
#include "all_config.h"
#ifdef F_FSK
#ifdef F_AD9959
#include "../../F_Chip/F_AD9959/F_AD9959.h"
#endif

uint32_t DAC_MAX = 1240;

/*
 * 模拟IO输出
 * */
void FSK_Drv_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStructure.Pin = FSK_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(FSK_GPIO_Port, &GPIO_InitStructure);

    FSK_Out = 0;
}


/*
 * 发帧头
 * 高电平时间是16100-16600us
 * 包络检波之后的结果是高点平持续30ms，低电平持续5ms
 *
 * */
void FSK_Send_Head(void)
{
	FSK_Set_Fre(1);
	HAL_Delay(FSK_Head_HTime);
	FSK_Set_Fre(0);
	HAL_Delay(FSK_D_HTime);
}


/*
 * 发1
 * 高电平时间是11100-11500us
 * 包络检波之后的结果是高点平持续20ms，低电平持续5ms
 * */
void FSK_Send_1(void)
{
	FSK_Set_Fre(1);
	HAL_Delay(FSK_1_HTime);//原来是20
	FSK_Set_Fre(0);
	HAL_Delay(FSK_D_HTime);
}


/*
 * 发0
 * 高电平时间是6050-6600us
 * 包络检波之后的结果是高点平持续10ms，低电平持续5ms
 * */
void FSK_Send_0(void)
{
	FSK_Set_Fre(1);
	HAL_Delay(FSK_0_HTime);//原来是10
	FSK_Set_Fre(0);
	HAL_Delay(FSK_D_HTime);
}


/*
 * 发帧尾
 * 高电平时间是16100-16600us
 * 包络检波之后的结果是高点平持续50ms，低电平持续20ms
 * */
void FSK_Send_End(void)
{
	FSK_Set_Fre(1);
	HAL_Delay(FSK_End_HTime);
	FSK_Set_Fre(0);
	HAL_Delay(FSK_D_HTime);
}


/*
 * 发校验位--仅针对2021电赛的4位数字的校验
 * 把数组的前四个数字加起来，对2取余
 * */
u8 FSK_Send_Check(u8* array)
{
	u8 i, sum = 0, res = 0;
	for (i = 0; i <=3; i++)
		sum+=array[i];
	res = sum%2;
//	printf("%d, %d\r\n", sum, res);
	return res;
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
	{
		#ifdef F_AD9959
		Write_frequence(0,15000);//9959给频率,15KHz
		#endif

		#ifdef F_DAC_SinWave
		TIM6->ARR = 15;	//12KHz
		#endif
		FSK_Out = 0;
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0);
	}

	else
	{
		#ifdef F_AD9959
		Write_frequence(0,10000);//9959给频率,10KHz
		#endif

		#ifdef F_DAC_SinWave
		TIM6->ARR = 17;	//11KHz
		#endif
		FSK_Out = 1;
		HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, DAC_MAX);
	}
}


/*
 * 用ASCII码的形式发发送一个字符,8位
 * 入口参数的八位数组是把char型的变量拆分为01后的结果,仅仅是便于查看拆分效果
 *
 * */
void FSK_Send_Char(unsigned char  data_hex, u8* array)
{
	u8 i = 0;

	for (i = 0; i < 8; i++)
	{
		if (data_hex & 0x80)
		{
			array[i] = 1;
			FSK_Send_1(); //发1
		}
		else
		{
			array[i] = 0;
			FSK_Send_0(); //发0
		}
//		printf("%d", array[i]);//打印查看效果
		data_hex <<= 1;    //左移1位
	}
//	printf("\r\n");//打印查看效果
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
	FSK_Send_Head();//发送帧头
	for (i = 0; i < Length; i++)
	{
		FSK_Send_Char(Temp_Buf[i], temp_buffer);
	}
	FSK_Send_End();//帧尾
}


/*
 * 用8421BCD码的形式发发送一个0-10的数,4位
 * 入口参数的八位数组是把char型的变量拆分为01后的结果,仅仅是便于查看拆分效果
 *
 * */
void FSK_Send_8421BCD(int data)
{
	int data_foremost = 0;
	int i = 0;
	u8 yushu = 0;
	u8 array[4] = {0};
	data_foremost = data;//保存原来的数据，方便打印
	for (i = 3; i >= 0; i--)
	{
		yushu = data % 2;
		data = data / 2;
		array[i] = yushu;
	}

	for (i = 0; i < 4; i++)
	{
		if (array[i])
			FSK_Send_1(); //发1
		else
			FSK_Send_0(); //发0
//		printf("%d", array[i]);//打印查看效果
	}
//	printf(", %d send ok\r\n", data_foremost);//打印查看效果.


//	测试用
//	printf("8421BCD:%d-->", data);
//	for (i = 0; i < 4; i++)
//		printf("%d", array[i]);
//	printf("end_output\r\n\r\n");
}


/*
 * 用8421BCD码的形式发发送一个字符,4位
 * 入口参数的八位数组是把char型的变量拆分为01后的结果,仅仅是便于查看拆分效果
 *
 * */
u8 FSK_Receive_8421BCD(u8* array)
{
	u8 res = 8*array[0] + 4*array[1] + 2*array[2] + 1*array[3];
	return res;
}


/*
 * FSK发送4位数字--仅针对此道退题目
 * 入口参数: 存放了4个数的数组
 */
void FSK_Send_8421BCD_4(u8* array)
{
	u8 i = 0;
	u8 check = 2;
	check = FSK_Send_Check(array);

	FSK_Send_Head();			//发送帧头
	for (i = 0; i < 4; i++)
		FSK_Send_8421BCD(array[i]);

	if (check)					//校验
		FSK_Send_1();
	else
		FSK_Send_0();

	if (!check)					//再次校验,跟上一次的相反
		FSK_Send_1();
	else
		FSK_Send_0();
	printf("Check:%d\r\n", check);
	FSK_Send_End();				//帧尾
}


/*
 * 测试
 * */
void FSK_Test(void)
{
	//把这里边的复制到while(1)中测试
//	 F_key_Value = Key_Scan();
//	  if (F_key_Value == 1)
//	  {
//		  FSK_Send_Head();
//		  printf("FSK_Send_Head\r\n");
//	  }
//	  if (F_key_Value == 3)
//	  {
//		  FSK_Send_1();
//		  printf("FSK_Send_1\r\n");
//	  }
//	  if (F_key_Value == 5)
//	  {
//		  FSK_Send_0();
//		  printf("FSK_Send_0\r\n");
//	  }
//	  if (F_key_Value == 7)
//	  {
//		  FSK_Send_Char('B', buffer);
//		  printf("FSK_Send_Head\r\n");
//	  }
}



#endif
