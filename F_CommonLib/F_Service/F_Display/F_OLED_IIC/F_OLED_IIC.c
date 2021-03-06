#include "./F_OLED_IIC.h"
#include "all_config.h"

#ifdef Service_Display_OLED_IIC

#include "./F_OLED_IIC_FONT.h"
#include "F_Select\F_MyFunction.h"

unsigned char OLED_IIC_SHOW_BUF[30] = {0};


//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127


/**********************************************
// IIC Write Command
**********************************************/
void OLED_IIC_Write_Command(unsigned char IIC_Command)
{
	OLED_IIC_Start();
	OLED_IIC_Send_Byte(0x78);            //Slave address,SA0=0
	OLED_IIC_Wait_Ack();

	OLED_IIC_Send_Byte(0x00);			//write command
	OLED_IIC_Wait_Ack();

	OLED_IIC_Send_Byte(IIC_Command);
	OLED_IIC_Wait_Ack();

	OLED_IIC_Stop();
}


/**********************************************
// IIC Write Data
**********************************************/
void OLED_IIC_Write_Data(unsigned char IIC_Data)
{
	OLED_IIC_Start();
	OLED_IIC_Send_Byte(0x78);			//D/C#=0; R/W#=0
	OLED_IIC_Wait_Ack();

	OLED_IIC_Send_Byte(0x40);			//write data
	OLED_IIC_Wait_Ack();

	OLED_IIC_Send_Byte(IIC_Data);
	OLED_IIC_Wait_Ack();

	OLED_IIC_Stop();
}


/**********************************************
// OLED_WR_Byte
// dat:要写入的数据/命令    cmd:数据/命令标志 0,表示命令;1,表示数据
**********************************************/
void OLED_IIC_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		OLED_IIC_Write_Data(dat);
	}
	else
	{
		OLED_IIC_Write_Command(dat);
	}
}


/********************************************
// fill_Picture
********************************************/
void OLED_IIC_Fill_Picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_IIC_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_IIC_WR_Byte(0x00,0);		//low column start address
		OLED_IIC_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_IIC_WR_Byte(fill_Data,1);
			}
	}
}


/********************************************
// 坐标设置
********************************************/
void OLED_IIC_Set_Pos(unsigned char x, unsigned char y)
{ 	OLED_IIC_WR_Byte(0xb0+y,OLED_CMD);
	OLED_IIC_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_IIC_WR_Byte((x&0x0f),OLED_CMD);
}


/********************************************
// 开启OLED显示
********************************************/
void OLED_IIC_Display_On(void)
{
	OLED_IIC_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_IIC_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_IIC_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}


/********************************************
// 关闭OLED显示
********************************************/
void OLED_IIC_Display_Off(void)
{
	OLED_IIC_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_IIC_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_IIC_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}


/********************************************
// 清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样
********************************************/
void OLED_IIC_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_IIC_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_IIC_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_IIC_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
		for(n=0;n<128;n++)OLED_IIC_WR_Byte(0,OLED_DATA);
	} //更新显示
}



//void OLED_On(void)
//{
//	u8 i,n;
//	for(i=0;i<8;i++)
//	{
//		OLED_IIC_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
//		OLED_IIC_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
//		OLED_IIC_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
//		for(n=0;n<128;n++)OLED_IIC_WR_Byte(1,OLED_DATA);
//	} //更新显示
//}


/********************************************
// 在指定位置显示一个字符,包括部分字符
// x:0~127
// y:0~63
// mode:0,反白显示;1,正常显示
// size:选择字体 16/12
********************************************/
void OLED_IIC_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{
	unsigned char c=0,i=0;
		c=chr-' ';//得到偏移后的值
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
		{

			OLED_IIC_Set_Pos(x,y);
			for(i=0;i<8;i++)
				OLED_IIC_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_IIC_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_IIC_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
		else
		{
			OLED_IIC_Set_Pos(x,y);
			for(i=0;i<6;i++)
				OLED_IIC_WR_Byte(F6x8[c][i],OLED_DATA);
		}
}


/********************************************
// 显示一个字符号串
********************************************/
void OLED_IIC_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{
		OLED_IIC_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}


/********************************************
//m^n函数
********************************************/
u32 Oled_IIC_Pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)result*=m;
	return result;
}


/********************************************
// 显示2个数字
// x,y :起点坐标
// len :数字的位数
// size:字体大小
// mode:模式	0,填充模式;1,叠加模式
// num:数值(0~4294967295);
********************************************/
void OLED_IIC_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{
	u8 t,temp;
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/Oled_IIC_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_IIC_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1;

		}
	 	OLED_IIC_ShowChar(x+(size2/2)*t,y,temp+'0',size2);
	}
}


/********************************************
// 显示汉字
********************************************/
void OLED_IIC_ShowCHinese(u8 x,u8 y,u8 no)
{
	u8 t,adder=0;
	OLED_IIC_Set_Pos(x,y);
    for(t=0;t<16;t++)
		{
//				OLED_IIC_WR_Byte(Hzk[2*no][t],OLED_DATA);
				adder+=1;
     }
		OLED_IIC_Set_Pos(x,y+1);
    for(t=0;t<16;t++)
			{
//				OLED_IIC_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
				adder+=1;
      }
}


/********************************************
// 显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7
********************************************/
void OLED_IIC_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{
 unsigned int j=0;
 unsigned char x,y;

  if(y1%8==0) y=y1/8;
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_IIC_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {
	    	OLED_IIC_WR_Byte(BMP[j++],OLED_DATA);
	    }
	}
}


/********************************************
// 初始化SSD1306
********************************************/
void OLED_IIC_Init(void)
{
	OLED_IIC_Drv_Init();
	HAL_Delay(100);

  	OLED_IIC_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_IIC_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_IIC_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_IIC_WR_Byte(0x40,OLED_CMD);//--set start line address
	OLED_IIC_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_IIC_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_IIC_WR_Byte(0xFF,OLED_CMD);//--128
	OLED_IIC_WR_Byte(0xA1,OLED_CMD);//set segment remap
	OLED_IIC_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_IIC_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_IIC_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_IIC_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_IIC_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_IIC_WR_Byte(0x00,OLED_CMD);//

	OLED_IIC_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_IIC_WR_Byte(0x80,OLED_CMD);//

	OLED_IIC_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_IIC_WR_Byte(0x05,OLED_CMD);//

	OLED_IIC_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_IIC_WR_Byte(0xF1,OLED_CMD);//

	OLED_IIC_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_IIC_WR_Byte(0x12,OLED_CMD);//

	OLED_IIC_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_IIC_WR_Byte(0x30,OLED_CMD);//

	OLED_IIC_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_IIC_WR_Byte(0x14,OLED_CMD);//

	OLED_IIC_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}


#endif

