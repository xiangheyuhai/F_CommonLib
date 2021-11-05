#include "./Keypad.h"
#include "./Keypad_Drv/Keypad_Drv_STM32F4/Keypad_Drv_STM32F4.h"
#include "all_config.h"
#ifdef SERVICE_KEYPAD


/*使用方法
 * 放到while(1)中
scanKeypad();
initKeypad(keypad_callback);
if (Keypad_Num != 0)
{
  printf("%d, %c\r\n", Keypad_Num, Keypad_Mean);
  Keypad_Num = 0;Keypad_Mean = 0;
}
* * * * */
int Keypad_Num = 0;
char Keypad_Mean = 0;

unsigned char CONTROL  = PULL_UP;
unsigned char SCAN_ROW = '0';
unsigned char SCAN_COL = '0';

unsigned char SCAN_ROW_temp = '0';
unsigned char SCAN_COL_temp = '0';


void initKeypad(void (*callback)(unsigned char x, unsigned char y))
{
	callback(SCAN_ROW,SCAN_COL);
	SCAN_COL = SCAN_ROW = '0';
}

void ROW_scan(unsigned char index)
{
	char i;
	SCAN_COL_temp = index;
	for(i='1'; i <= ROW_NUM; i++)
	{
		writeRow('A',CONTROL);
		writeRow(i,!CONTROL);
		if(readCol(index)==!CONTROL)
		{
			SCAN_ROW_temp=i;
			break;
		}
	}
}

int scanKeypad()
{
	char i;
	int j;
	static uint32_t tick = 0;
	static KEY_STATE key_state[4] = {KEY_Release, KEY_Release, KEY_Release, KEY_Release};
	SCAN_ROW = SCAN_COL = '0';
	writeRow('A', !CONTROL);
	for (i='1', j=0; i<=COL_NUM,j<=4; i++,j++)
	{
		switch (key_state[j])
		{
			case KEY_Release:
			{
				if (readCol(i) == !CONTROL)
				{
					tick = F_Get_Times();
					key_state[j] = KEY_Press;
				}
				else
					key_state[j] = KEY_Release;
				break;
			}
			case KEY_Press:
			{
				ROW_scan(i);
				if (readCol(i) == CONTROL)
				{
					//printf("error: %d\n\r",myGetMs()-tick);
					if(F_Get_Times()-tick>=DELAY_MAX_TIME)
					{
						key_state[j] = KEY_Release;
						tick = 0;
						SCAN_COL=SCAN_COL_temp;
						SCAN_ROW=SCAN_ROW_temp;
					}
					else
						key_state[j]=KEY_Release;
				}
			}
		}
	}
}




void keypad_callback(unsigned char x, unsigned char y)
{
	switch (x) {
	case '1': {
		switch (y) {
		case '1':
			Keypad_Num = 1;	Keypad_Mean = '1';
			break;
		case '2':
			Keypad_Num = 2;	Keypad_Mean = '2';
			break;
		case '3':
			Keypad_Num = 3;	Keypad_Mean = '3';
			break;
		case '4':
			Keypad_Num = 4;	Keypad_Mean = 'A';
			break;
		default:
			break;
		}
	}
		break;
	case '2': {
		switch (y) {
		case '1':
			Keypad_Num = 5;	Keypad_Mean = '4';
			break;
		case '2':
			Keypad_Num = 6;	Keypad_Mean = '5';
			break;
		case '3':
			Keypad_Num = 7;	Keypad_Mean = '6';
			break;
		case '4':
			Keypad_Num = 8;	Keypad_Mean = 'B';
			break;
		default:
			break;
		}
	}
		break;
	case '3': {
		switch (y) {
		case '1':
			Keypad_Num = 9;	Keypad_Mean = '7';
			break;
		case '2':
			Keypad_Num = 10;	Keypad_Mean = '8';
			break;
		case '3':
			Keypad_Num = 11;	Keypad_Mean = '9';
			break;
		case '4':
			Keypad_Num = 12;	Keypad_Mean = 'C';
			break;
		default:
			break;
		}
	}
		break;
	case '4': {
		switch (y) {
		case '1':
			Keypad_Num = 13;	Keypad_Mean = '*';
			break;
		case '2':
			Keypad_Num = 14;	Keypad_Mean = '0';
			break;
		case '3':
			Keypad_Num = 15;	Keypad_Mean = '#';
			break;
		case '4':
			Keypad_Num = 16;	Keypad_Mean = 'D';
			break;
		default:
			break;
		}
	}
	break;
	}
}

void Keypad_Init(void)
{
	Keypad_Drv_Init();
}

#endif
