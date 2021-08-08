/*
 * keypad.c
 *
 *  Created on: May 8, 2021
 *      Author: zoe
 */

#include "keypad.h"
#include "math.h"
/**键盘说明
 * s1-s10:1,2,3,4,5,6,7,8,9,0
 * s11:set minval
 * s12:set maxval
 * s13:ok
 * s14:display the range of frequence
 * s15:start scan freq
 * **/
uint8_t HMI_T[]={"n0.val=360"};
unsigned char i,j,k,x,y,sum = 0,lensize,widsize;
PinState write_pin_state,set_pin_state;

void setOut(char target, PinState state)
{
	writeRow(target, state);
}
void writeRow(char index, PinState state)
{
	switch (index)
	{
	case 0:
		/****/
		HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, state);
		break;

	case 1:
		/****/
		HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, state);
		break;

	case 2:
		/****/
		HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, state);
		break;

	case 3:
		/****/
		HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, state);
		break;

	}
}
PinState readCol(char index)
{
	switch (index)
	{
	case 0:
		/****/
		flag = HAL_GPIO_ReadPin(COL1_GPIO_Port, COL1_Pin);
		break;

	case 1:
		/****/
		flag = HAL_GPIO_ReadPin(COL2_GPIO_Port, COL2_Pin);
		break;

	case 2:
		/****/
		flag = HAL_GPIO_ReadPin(COL3_GPIO_Port, COL3_Pin);
		break;

	case 3:
		/****/
		flag = HAL_GPIO_ReadPin(COL4_GPIO_Port, COL4_Pin);
		break;

	}
	return flag;
}



void keypad_init(keypad_select_mode mode,unsigned char len_size,unsigned char wid_size)
{
	lensize = len_size;
	widsize = wid_size;
	if(mode == Pull_Down)
	{
		write_pin_state = PIN_SET;
		set_pin_state = PIN_RESET;
		printf("keymode is pull_down\r\n");
	}
	if(mode == Pull_Up)
	{
		write_pin_state = PIN_RESET;
		set_pin_state = PIN_SET;
		printf("keymode is pull_up\r\n");
	}
	printf("key_init is ok\r\n");
}

unsigned char keypad_scan(void)
{
	static unsigned int cnt[36] = {0};

	for(j=0;j<widsize;j++)
	{
		for(i=0;i<widsize;i++)
		{
			writeRow(i,write_pin_state);
		}
		setOut(j,set_pin_state);
		for(k=0;k<lensize;k++)
		{
			if(readCol(k) == set_pin_state)
			{
				if(cnt[widsize*j+k] <= 200)
				{
					cnt[widsize*j+k]++;
				}
			}
			else
			{
				cnt[widsize*j+k] = 0;
			}
			if(cnt[widsize*j+k] == 200)
			{
				x=k+1;
				y=j+1;
				sum = lensize*(y-1)+x;

				sum_event(sum);
				return sum;
			}
		}
	}
	return 0;
}

void repeat(callback function,unsigned char x,unsigned char y)
{
	cfunction = function;
	cfunction(x,y);
}
void sum_event(unsigned char sum)
{

	switch (sum)
	{
	case 0:
		repeat(function0,x,y);
		break;

	case 1:
		repeat(function1,x,y);
		break;

	case 2:
		repeat(function2,x,y);
		break;

	case 3:
		repeat(function3,x,y);
		break;
	case 4:
		repeat(function4,x,y);
		break;
	case 5:
		repeat(function5,x,y);
		break;
	case 6:
		repeat(function6,x,y);
		break;
	case 7:
		repeat(function7,x,y);
		break;
	case 8:
		repeat(function8,x,y);
		break;
	case 9:
		repeat(function9,x,y);
		break;
	case 10:
		repeat(function10,x,y);
		break;
	case 11:
		repeat(function11,x,y);
		break;
	case 12:
		repeat(function12,x,y);
		break;
	case 13:
		repeat(function13,x,y);
		break;
	case 14:
		repeat(function14,x,y);
		break;
	case 15:
		repeat(function15,x,y);
		break;
	case 16:
		repeat(function16,x,y);
		break;
	}
}


/******应用函数在下面设计******/
void function0(unsigned char x,unsigned char y)
{
	printf(" **no press** \r\n");
	HAL_Delay(1000);
}
void function1(unsigned char x,unsigned char y)
{

	printf("You pressed 1 \r\n");
//	if(set_minval_flag||set_maxval_flag)
//	{
		num++;
		shuzhi[num]=1;
		printf("num:%d ,shuzhi[num]:%d\r\n",num,shuzhi[num]);
//	}


}
void function2(unsigned char x,unsigned char y)
{
	printf("You pressed 2 \r\n");
//	if(set_minval_flag||set_maxval_flag)
//	{
		num++;
		shuzhi[num]=2;
		printf("num:%d ,shuzhi[num]:%d\r\n",num,shuzhi[num]);
//	}
}
void function3(unsigned char x,unsigned char y)
{
	printf("You pressed 3 \r\n");
//	if(set_minval_flag||set_maxval_flag)
//	{
		num++;
		shuzhi[num]=3;
		printf("num:%d ,shuzhi[num]:%d\r\n",num,shuzhi[num]);
//	}
}
void function4(unsigned char x,unsigned char y)
{
	printf("You pressed 4 \r\n");
//	if(set_minval_flag||set_maxval_flag)
//	{
		num++;
		shuzhi[num]=4;
		printf("num:%d ,shuzhi[num]:%d\r\n",num,shuzhi[num]);
//	}
}
void function5(unsigned char x,unsigned char y)
{
	printf("You pressed 5 \r\n");
//	if(set_minval_flag||set_maxval_flag)
//	{
		num++;
		shuzhi[num]=5;
		printf("num:%d ,shuzhi[num]:%d\r\n",num,shuzhi[num]);
//	}
}
void function6(unsigned char x,unsigned char y)
{

	printf("You pressed 6 \r\n");
//	if(set_minval_flag||set_maxval_flag)
//	{
		num++;
		shuzhi[num]=6;
		printf("num:%d ,shuzhi[num]:%d\r\n",num,shuzhi[num]);
//	}

}
void function7(unsigned char x,unsigned char y)
{
	printf("You pressed 7 \r\n");
//	if(set_minval_flag||set_maxval_flag)
//	{
		num++;
		shuzhi[num]=7;
		printf("num:%d ,shuzhi[num]:%d\r\n",num,shuzhi[num]);
//	}
}
void function8(unsigned char x,unsigned char y)
{
	printf("You pressed 8 \r\n");
//	if(set_minval_flag||set_maxval_flag)
//	{
		num++;
		shuzhi[num]=8;
		printf("num:%d ,shuzhi[num]:%d\r\n",num,shuzhi[num]);
//	}
}

void function9(unsigned char x,unsigned char y)
{
	printf("You pressed 9 \r\n");
//	if(set_minval_flag||set_maxval_flag)
//	{
		num++;
		shuzhi[num]=9;
		printf("num:%d ,shuzhi[num]:%d\r\n",num,shuzhi[num]);
//	}
}
void function10(unsigned char x,unsigned char y)
{
	printf("You pressed 0 \r\n");
//	if(set_minval_flag||set_maxval_flag)
//	{
		num++;
		shuzhi[num]=0;
		printf("num:%d ,shuzhi[num]:%d\r\n",num,shuzhi[num]);
//	}
}

void function11(unsigned char x,unsigned char y)
{//设置最小值键
	printf("You pressed min \r\n");
	set_minval_flag = !set_minval_flag;
	num = 0;
	printf("num:%d, min_flag:%d, max_flag:%d \r\n",num,set_minval_flag,set_maxval_flag);
}
void function12(unsigned char x,unsigned char y)
{//设置最大值键
	printf("You pressed max \r\n");
	set_maxval_flag = !set_maxval_flag;
	num = 0;
	printf("num:%d, min_flag:%d, max_flag:%d \r\n",num,set_minval_flag,set_maxval_flag);
}
void function13(unsigned char x,unsigned char y)
{//确认键  frequen[0]-min  frequen[1]-max
	printf("You pressed ok \r\n");
	freq_num = 0;
	if(set_minval_flag)
	{
		freq_num=1;
	}
	else if(set_maxval_flag)
	{
		freq_num=2;
	}
	set_minval_flag = 0;
	set_maxval_flag = 0;

	for(i=1;i<=num;i++)
	{
		sum_val += shuzhi[i]*pow(10,(num-i));
	}
	frequen[freq_num] = sum_val;
	sum_val = 0;
	set_minval_flag = 0;
	set_maxval_flag = 0;
	num = 0;
	printf("num:%d, min_flag:%d, max_flag:%d \r\n",num,set_minval_flag,set_maxval_flag);
	printf("frequen:%ld, freq_num:%d \r\n",frequen[freq_num],freq_num);
}
void function14(unsigned char x,unsigned char y)
{
	auto_flag = !auto_flag;
//	printf("freq_sta=%ldHz,range[%ld,%ld] Hz \r\n",frequen[0],frequen[1],frequen[2]);
	UART_HMI_Send_setrange(7,frequen[1],frequen[2]);
//	UART_HMI_Send_nval(0,-90);
//	UART_HMI_Send_xval(0,-112);
}
void function15(unsigned char x,unsigned char y)
{
//	printf("you press 15\r\n");
	s15_flag=!s15_flag;

}
void function16(unsigned char x,unsigned char y)
{
//	printf("you press 16\r\n");

}

