#include "./F_Key.h"


#ifdef Service_Input_Key
#define F_Key_Num 2

/*需要extern，在外部调用，10ms刷新一次*/
extern u8 F_key_scan = 0;
u8 F_KEY_FLAG = 0;
u16 F_KEY_COUNT = 0;
KeyType KEY[F_Key_Num + 1];


unsigned char KEY_SCAN(void)
{
	unsigned char return_num = 0;				//返回值
	if (F_KEY_FLAG)
	{
		u8 i;									//循环使用
		KEY_FLAG = 0;							//滴答定时器flag
		for (i = 1; i <= F_Key_Num; i++)
		{
			KEY_Refresh(i);						//刷新结构体中的电平状态
			if (KEY[i].READ == 0)
			{
				KEY[i].TIME++;
				/***********************判断长按***************************/
				if (KEY[i].TIME > 50)			//长按超过0.5秒，一直返回LONG
				{
					return_num = i*2;		return return_num;
				}
			}
			KEY_Refresh(i);						//刷新电平
			/***************************判断短按****************************/
			if (KEY[i].READ == 1 && KEY[i].TIME > 0 && KEY[i].TIME < 14)
			{
				KEY[i].TIME = 0;
				return_num = i*2-1;		return return_num;
			}
			if (KEY[i].READ == 1) 			//不论长按短按，松手后都会清掉计数值
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
			KEY[1].READ = KEY1;	break;
  	case 2:
			KEY[2].READ = KEY2;	break;
	case 3:
  			KEY[3].READ = KEY3;	break;
  	case 4:
  			KEY[4].READ = KEY4;	break;
	default:
  			break;
  }
}

u8 TEST_FUN( u8 i)
{
	i+=1;
	return i;
}




#endif
