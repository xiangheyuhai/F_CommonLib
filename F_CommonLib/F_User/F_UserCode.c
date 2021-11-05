#include "./F_UserCode.h"
#include "all_config.h"
#ifdef Service_UserCode
#include "./F_Service/F_Display/F_NOKIA_5110/F_NOKIA_5110.h"
#include "./F_Connectivity/F_FSK/F_FSK.h"


u8 Send_Num[5] = {0};
char Send_Num_Char[5] = {' ', ' ', ' ', ' ', ' '};
u8 Send_Flag = 0;
u8 Send_Flag_Control = 0;//0--不发送, 1--发送


void Show_Message_Begin(void)
{
	NOKIA_5110_Clear();

	sprintf((char *)NOKIA_5110_SHOW_BUF, "  Input Num  ");
	NOKIA_5110_Write_english_string(0, 0, NOKIA_5110_SHOW_BUF);

	sprintf((char *)NOKIA_5110_SHOW_BUF, "  %c  %c  %c  %c  ", Send_Num_Char[1], Send_Num_Char[2], Send_Num_Char[3], Send_Num_Char[4]);
	NOKIA_5110_Write_english_string(0, 2, NOKIA_5110_SHOW_BUF);
}


void Send_Num_Pro(void)
{
	u8 i = 0;
	if ((Keypad_Num==1 || Keypad_Num==2 || Keypad_Num==3 || Keypad_Num==5 || Keypad_Num==6 || Keypad_Num==7 || Keypad_Num==9 || Keypad_Num==10 || Keypad_Num==11 || Keypad_Num==14) && Send_Flag>=0 && Send_Flag<4)
	{
		Send_Flag++;
		sprintf((char *)NOKIA_5110_SHOW_BUF, "              ");
		NOKIA_5110_Write_english_string(0, 4, NOKIA_5110_SHOW_BUF);

		switch(Keypad_Num)
		{
		case 1:		Send_Num_Char[Send_Flag] = '1';		Send_Num[Send_Flag-1] = 1;	break;
		case 2:		Send_Num_Char[Send_Flag] = '2';		Send_Num[Send_Flag-1] = 2;	break;
		case 3:		Send_Num_Char[Send_Flag] = '3';		Send_Num[Send_Flag-1] = 3;	break;
		case 5:		Send_Num_Char[Send_Flag] = '4';		Send_Num[Send_Flag-1] = 4;	break;
		case 6:		Send_Num_Char[Send_Flag] = '5';		Send_Num[Send_Flag-1] = 5;	break;
		case 7:		Send_Num_Char[Send_Flag] = '6';		Send_Num[Send_Flag-1] = 6;	break;
		case 9:		Send_Num_Char[Send_Flag] = '7';		Send_Num[Send_Flag-1] = 7;	break;
		case 10:	Send_Num_Char[Send_Flag] = '8';		Send_Num[Send_Flag-1] = 8;	break;
		case 11:	Send_Num_Char[Send_Flag] = '9';		Send_Num[Send_Flag-1] = 9;	break;
		case 14:	Send_Num_Char[Send_Flag] = '0';		Send_Num[Send_Flag-1] = 0;	break;
		default:break;
		}
		sprintf((char *)NOKIA_5110_SHOW_BUF, "  %c  %c  %c  %c  ", Send_Num_Char[1], Send_Num_Char[2], Send_Num_Char[3], Send_Num_Char[4]);
		NOKIA_5110_Write_english_string(0, 2, NOKIA_5110_SHOW_BUF);//一行可以显示14个字符
		Keypad_Num = 0;//必须清0
	}

	//确认发送
	if (Keypad_Num == 16 && Send_Flag == 4)
	{
		Send_Flag++;
		Send_Flag_Control = 1;//开始循环发送
		for (i = 0; i < 4; i++)
			printf("%d", Send_Num[i]);
		printf("\r\n");
		sprintf((char *)NOKIA_5110_SHOW_BUF, "   Sending    ");
		NOKIA_5110_Write_english_string(0, 4, NOKIA_5110_SHOW_BUF);
		Keypad_Num = 0;//必须清0
	}

	//停止发送
	if (Keypad_Num == 4 && Send_Flag == 5)
	{
		Send_Flag = 0;
		Send_Flag_Control = 0;//停止发送
		for (i = 1; i <= 4; i++)
			Send_Num_Char[i] = ' ';

		sprintf((char *)NOKIA_5110_SHOW_BUF, "              ");
		NOKIA_5110_Write_english_string(0, 2, NOKIA_5110_SHOW_BUF);

		sprintf((char *)NOKIA_5110_SHOW_BUF, "   Send End   ");
		NOKIA_5110_Write_english_string(0, 4, NOKIA_5110_SHOW_BUF);
		Keypad_Num = 0;//必须清0
	}
}


void Send_Control(void)
{
	if (Send_Flag_Control)//1--发送
	{
		Send_Flag_Control = 0;
		FSK_Send_8421BCD_4(Send_Num);
	}
}











#endif
