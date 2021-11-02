#include "./F_UserCode.h"
#include "all_config.h"
#ifdef Service_UserCode

u8 ADF4351_Page_Flag = 1;		//第一页，第二页
u8 ADF4351_Show_1_Flag = 0;		//标志频率的位数  1--修改千位，2--修改百位，3--修改十位，4--修改个位
u16 ADF4351_Show_1_Count = 0;
u16 ADF4351_Set_Fre = 100;
u8 ADF4351_Set_Fre_Flag = 1;


/*初始化后显示*/
void ADF4351_Show_0(void)
{
	  sprintf((char *)OLED_SPI_SHOW_BUF, "    ADF4351     ");
	  OLED_SPI_ShowString(0,0, OLED_SPI_SHOW_BUF, 16, 1);

	  sprintf((char *)OLED_SPI_SHOW_BUF, "Key:+,-,<-,->,Re");
	  OLED_SPI_ShowString(0,16, OLED_SPI_SHOW_BUF, 16, 1);

	  sprintf((char *)OLED_SPI_SHOW_BUF, "  Fre:%1d,%3dMHz  ", ADF4351_Set_Fre/1000, ADF4351_Set_Fre-ADF4351_Set_Fre/1000*1000);
	  OLED_SPI_ShowString(0,32, OLED_SPI_SHOW_BUF, 16, 1);

	  sprintf((char *)OLED_SPI_SHOW_BUF, "Press any to set");
	  OLED_SPI_ShowString(0,48, OLED_SPI_SHOW_BUF, 16, 1);
	  OLED_SPI_Refresh();
}


/*显示第一页的闪烁内容*/
void ADF4351_Show_1(void)
{
	if (ADF4351_Show_1_Flag == 1)
	{
		  sprintf((char *)OLED_SPI_SHOW_BUF, "Press any to set");
		  OLED_SPI_ShowString(0,48, OLED_SPI_SHOW_BUF, 16, 1);
		  OLED_SPI_Refresh();
	}
	else if(ADF4351_Show_1_Flag == 2)
	{
		  sprintf((char *)OLED_SPI_SHOW_BUF, "                ");
		  OLED_SPI_ShowString(0,48, OLED_SPI_SHOW_BUF, 16, 1);
		  OLED_SPI_Refresh();
	}
	else
	{}
}


/*第二页--设置频率*/
void ADF4351_Show_2(void)
{
	if (F_key_Value)
	{
		if (F_key_Value == 5)				//光标左移
		{
			F_key_Value = 0;
			ADF4351_Set_Fre_Flag--;
			if(ADF4351_Set_Fre_Flag <= 0)
				ADF4351_Set_Fre_Flag = 4;
			ADF4351_Set_Show_Cursor();
		}

		if (F_key_Value == 7)				//光标右移
		{
			F_key_Value = 0;
			ADF4351_Set_Fre_Flag++;
			if(ADF4351_Set_Fre_Flag >= 5)
				ADF4351_Set_Fre_Flag = 1;
			ADF4351_Set_Show_Cursor();
		}

		if (F_key_Value == 1 || F_key_Value == 3)	//数字加减
		{
			ADF4351_Set_Show_Fre();
			ADF4351WriteFreq(ADF4351_Set_Fre);//设置最终的频率，单位是MHz
		}
	}

}

/*显示设置时的光标*/
void ADF4351_Set_Show_Cursor(void)
{
	switch(ADF4351_Set_Fre_Flag)
	{
	case 1:
		  sprintf((char *)OLED_SPI_SHOW_BUF, "      -         ");
		  OLED_SPI_ShowString(0,52, OLED_SPI_SHOW_BUF, 16, 1);
		  OLED_SPI_Refresh();
		  break;

	case 2:
		  sprintf((char *)OLED_SPI_SHOW_BUF, "        -       ");
		  OLED_SPI_ShowString(0,52, OLED_SPI_SHOW_BUF, 16, 1);
		  OLED_SPI_Refresh();
		  break;
		break;

	case 3:
		  sprintf((char *)OLED_SPI_SHOW_BUF, "         -      ");
		  OLED_SPI_ShowString(0,52, OLED_SPI_SHOW_BUF, 16, 1);
		  OLED_SPI_Refresh();
		  break;
		break;

	case 4:
		  sprintf((char *)OLED_SPI_SHOW_BUF, "          -     ");
		  OLED_SPI_ShowString(0,52, OLED_SPI_SHOW_BUF, 16, 1);
		  OLED_SPI_Refresh();
		  break;
		break;

	default:
		break;
	}
}


/*显示设置时的频率*/
void ADF4351_Set_Show_Fre(void)
{
	ADF4351_Get_Fre();	//得到设置后的频率
	if (ADF4351_Set_Fre < 35)
		ADF4351_Set_Fre = 35;
	if (ADF4351_Set_Fre > 4400)
		ADF4351_Set_Fre = 4400;

	/*频率没有问题之后再显示出来*/
	sprintf((char *)OLED_SPI_SHOW_BUF, "  Fre:%1d,%03dMHz  ", ADF4351_Set_Fre/1000, ADF4351_Set_Fre - ADF4351_Set_Fre/1000*1000);
	OLED_SPI_ShowString(0,36, OLED_SPI_SHOW_BUF, 16, 1);
	OLED_SPI_Refresh();
}


/*刷新得到每次改变后的频率*/
void ADF4351_Get_Fre(void)
{
	int ge, shi, bai, qian = 0;

	/*分别得到现在的实际频率*/
	qian = ADF4351_Set_Fre / 1000;
	bai  = ADF4351_Set_Fre /100 % 10;
	shi  = ADF4351_Set_Fre /10 % 10;
	ge   = ADF4351_Set_Fre % 10;

	switch(ADF4351_Set_Fre_Flag)
	{
	/*修改千位*/
	case 1:
		if (F_key_Value == 1)				//数字加
		{
			F_key_Value = 0;
			qian++;
			if(qian > 4)	qian = 0;
		}
		else if (F_key_Value == 3)			//数字减
		{
			F_key_Value = 0;
			qian--;
			if(qian < 0)	qian = 4;
		}
		ADF4351_Set_Fre = qian*1000 + bai*100 + shi*10 + ge;
		break;

	/*修改百位*/
	case 2:
		if (F_key_Value == 1)				//数字加
		{
			F_key_Value = 0;
			bai++;
			if(bai > 9)	bai = 0;
		}
		else if (F_key_Value == 3)			//数字减
		{
			F_key_Value = 0;
			bai--;
			if(bai < 0)	bai = 9;
		}
		ADF4351_Set_Fre = qian*1000 + bai*100 + shi*10 + ge;
		break;

	/*修改十位*/
	case 3:
		if (F_key_Value == 1)				//数字加
		{
			F_key_Value = 0;
			shi++;
			if(shi > 9)	shi = 0;
		}
		else if (F_key_Value == 3)			//数字减
		{
			F_key_Value = 0;
			shi--;
			if(shi < 0)	shi = 9;
		}
		ADF4351_Set_Fre = qian*1000 + bai*100 + shi*10 + ge;
		break;

	/*修改个位*/
	case 4:
		if (F_key_Value == 1)				//数字加
		{
			F_key_Value = 0;
			ge++;
			if(ge > 9)	ge = 0;
		}
		else if (F_key_Value == 3)			//数字减
		{
			F_key_Value = 0;
			ge--;
			if(ge < 0)	ge = 9;
		}
		ADF4351_Set_Fre = qian*1000 + bai*100 + shi*10 + ge;
		break;

	default:
		break;
	}
}
#endif
