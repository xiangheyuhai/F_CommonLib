#include "./F_Key.h"
#include "all_config.h"
#ifdef Service_Input_Key
/*
F_key_num = KEY_SCAN();
if (F_key_num == 1)
	Refresh_AD9959_Data();

 * */

/*需要extern，在外部调用，10ms刷新一次*/
u8 F_key_num = 0;
u8 F_Key_Scan = 0;
u8 F_KEY_FLAG = 0;
u16 F_KEY_COUNT = 0;
KeyType KEY[F_Key_Num + 1];


u8 KEY_SCAN(void)
{
	u8 i;
	u8 return_num = 0;				//返回值
	if (F_KEY_FLAG)
	{
		F_KEY_FLAG = 0;							//滴答定时器flag
		for (i = 1; i <= F_Key_Num; i++)
		{
			KEY_Refresh(i);						//刷新结构体中的电平状态
			if (KEY[i].READ == F_Key_Valid_Status)
			{
				KEY[i].TIME++;
//				 printf("%d,%d\r\n", i, KEY[i].TIME);
				/***********************判断长按***************************/
				if (KEY[i].TIME > 80)			//长按超过0.5秒，一直返回LONG
				{
					return_num = i*2;		return return_num;
				}
			}
			KEY_Refresh(i);						//刷新电平
			/***************************判断短按****************************/
			if (KEY[i].READ == F_Key_Invalid_Status && KEY[i].TIME > 8 && KEY[i].TIME < 40)
			{
				KEY[i].TIME = 0;
				return_num = i*2-1;		return return_num;
			}
			if (KEY[i].READ == F_Key_Invalid_Status) 			//不论长按短按，松手后都会清掉计数值
			{
				KEY[i].TIME = 0;
			}
		}
		return 0;								//没有按键按下，返回0
	}
}



void KEY_Refresh(unsigned char i)
{
	//刷新读取电平
	switch (i)
  {
  	case 1:
			KEY[1].READ = KEY1_READ;	break;
  	case 2:
			KEY[2].READ = KEY2_READ;	break;
  	case 3:
			KEY[3].READ = KEY3_READ;	break;
  	case 4:
			KEY[4].READ = KEY4_READ;	break;
  	case 5:
			KEY[5].READ = KEY5_READ;	break;

	default:
  			break;
  }
}


/*设置SDA为输入模式*/
void KEY_INPUT_INIT(void)
{
	u8 i = 0;
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/*如果修改了IO口，需要修改这个*/
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(KEY_1_GPIO_Port, KEY_1_Pin | KEY_2_Pin | KEY_3_Pin | KEY_4_Pin | KEY_5_Pin, GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = KEY_1_Pin | KEY_2_Pin | KEY_3_Pin | KEY_4_Pin | KEY_5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(KEY_1_GPIO_Port, &GPIO_InitStruct);



	for (i = 1; i <= F_Key_Num; i++)
	{
		KEY[i].TIME = 0;
	}
}







#endif
