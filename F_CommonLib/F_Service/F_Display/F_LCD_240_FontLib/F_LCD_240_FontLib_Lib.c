#include "./F_LCD_240_FontLib.h"
#ifdef Service_Display_LCD_240_FontLib
#ifdef F_STM32_F4
#include "./F_LCD_240_FontLib_Drv/F_LCD_240_FontLib_Drv_STM32F4/F_LCD_240_FontLib_Drv_STM32F4.h"

u8 FontBuf[130];//字库缓存
/******************************************************************************
      函数说明：向字库写入命令
      入口数据：dat  要写入的命令
      返回值：  无
******************************************************************************/
void ZK_command(u8 dat)
{
	#ifndef Service_Display_LCD_240_FontLib_Hardware
	u8 i;
	#endif

	#ifdef Service_Display_LCD_240_FontLib_Hardware
	HAL_SPI_Transmit_DMA(&hspi1,&dat,1);

	#else
	for(i=0;i<8;i++)
	{
		LCD_SCLK_Clr();
		if(dat&0x80)
		{
		   LCD_MOSI_Set();
		}
		else
		{
		   LCD_MOSI_Clr();
		}
		LCD_SCLK_Set();
		dat<<=1;
	}
	#endif
 }

/******************************************************************************
      函数说明：从字库读取数据
      入口数据：无
      返回值：  ret_data 读取的数据
******************************************************************************/
u8 get_data_from_ROM(void)
{
	u8 ret_data=0; //返回数据初始化

	#ifndef Service_Display_LCD_240_FontLib_Hardware
	u8 i;
	#endif

	#ifdef Service_Display_LCD_240_FontLib_Hardware
	HAL_SPI_Receive_DMA(&hspi1,&ret_data,1);
	#else
	for(i=0;i<8;i++)
	{
		LCD_SCLK_Clr();  //字库时钟拉低
		ret_data<<=1;
		if(ZK_MISO)
		{
			ret_data++;
		}
		LCD_SCLK_Set(); //字库时钟拉高
	}
	#endif
	return ret_data;    //返回读出的一个字节
}

/******************************************************************************
      函数说明：读取N个数据
      入口数据：AddrHigh  写地址高字节
                AddrMid   写地址中字节
                AddrLow   写地址低字节
                *pBuff    读取的数据
                DataLen   读取数据的长度
      返回值：  无
******************************************************************************/
void get_n_bytes_data_from_ROM(u8 AddrHigh,u8 AddrMid,u8 AddrLow,u8 *pBuff,u8 DataLen)
{
 	u8 i;
	ZK_CS_Clr(); //字库片选
	ZK_command(0x03);//写指令
	ZK_command(AddrHigh);//写地址高字节
	ZK_command(AddrMid);//写地址中字节
	ZK_command(AddrLow);//写地址低字节
	for(i=0;i<DataLen;i++)
	{
	   *(pBuff+i) =get_data_from_ROM();//读一个字节数据
	}

	ZK_CS_Set();//取消字库片选
}

/******************************************************************************
      函数说明：显示汉字
      入口数据：x,y      写入的坐标
                zk_num   1:12*12,  2:15*16,  3:24*24,  4:32*32
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_GB2312(u16 x,u16 y,u8 zk_num,u16 fc,u16 bc)
{
  u8 i,k,n,d,m=0;
	switch(zk_num)
	{
		// n:字符所占字节数  d：字间距
		case 12 :  n=24;  d=12; break;   // 12*12
		case 16 :  n=32;  d=16; break;   // 15*16
		case 24 :  n=72;  d=24; break;   // 24*24
		case 32 :  n=128; d=32; break;   // 32*32
	}
	LCD_Address_Set(x,y,x+d-1,y+d-1);
	for(i=0;i<n;i++)
	{
		for(k=0;k<8;k++)
		{
			if((FontBuf[i]&(0x80>>k)))
			{
			  LCD_WR_DATA(fc);
			}
			else
			{
			  LCD_WR_DATA(bc);
			}
			m++;
			if(m%zk_num==0)
			{
				m=0;
				break;
			}
		}
	}
}


/******************************************************************************
      函数说明：显示汉字
      入口数据：zk_num    1:12*12,  2:15*16,  3:24*24,  4:32*32
                x,y       坐标
                text[]    要显示的汉字
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_GB2312_String(u16 x,u16 y,u8 zk_num,u8 text[],u16 fc,u16 bc)
{
	u8 i= 0;
	u8 AddrHigh,AddrMid,AddrLow ; //字高、中、低地址
	u32 FontAddr=0; //字地址
	u32 BaseAdd=0; //字库基地址
	u8 n,d;// 不同点阵字库的计算变量
	switch(zk_num)
	{
		// n:字符所占字节数  d：字间距
		case 12 :  BaseAdd=0x00;    n=24;  d=12; break;   // 12*12
		case 16 :  BaseAdd=0x2C9D0; n=32;  d=16; break;   // 15*16
		case 24 :  BaseAdd=0x68190; n=72;  d=24; break;   // 24*24
		case 32 :  BaseAdd=0xEDF00; n=128; d=32; break;   // 32*32
	}
	while((text[i]>0x00))
	{
		if(((text[i]>=0xA1)&&(text[i]<=0xA9))&&(text[i+1]>=0xA1))
		{
			//国标简体（GB2312）汉字在 字库IC中的地址由以下公式来计算：//
			//Address = ((MSB - 0xA1) * 94 + (LSB - 0xA1))*n+ BaseAdd; 分三部取地址///
			FontAddr = (text[i]- 0xA1)*94;
			FontAddr += (text[i+1]-0xA1);
			FontAddr = (unsigned long)((FontAddr*n)+BaseAdd);

			AddrHigh = (FontAddr&0xff0000)>>16;  //地址的高8位,共24位//
			AddrMid = (FontAddr&0xff00)>>8;      //地址的中8位,共24位//
			AddrLow = FontAddr&0xff;	     //地址的低8位,共24位//
			get_n_bytes_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n );//取一个汉字的数据，存到"FontBuf[]"
			Display_GB2312(x,y,zk_num,fc,bc);//显示一个汉字到LCD上/
		}
		else if(((text[i]>=0xB0) &&(text[i]<=0xF7))&&(text[i+1]>=0xA1))
		{
			//国标简体（GB2312） 字库IC中的地址由以下公式来计算：//
			//Address = ((MSB - 0xB0) * 94 + (LSB - 0xA1)+846)*n+ BaseAdd; 分三部取地址//
			FontAddr = (text[i]- 0xB0)*94;
			FontAddr += (text[i+1]-0xA1)+846;
			FontAddr = (unsigned long)((FontAddr*n)+BaseAdd);

			AddrHigh = (FontAddr&0xff0000)>>16;  //地址的高8位,共24位//
			AddrMid = (FontAddr&0xff00)>>8;      //地址的中8位,共24位//
			AddrLow = FontAddr&0xff;	     //地址的低8位,共24位//
			get_n_bytes_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n );//取一个汉字的数据，存到"FontBuf[ ]"
			Display_GB2312(x,y,zk_num,fc,bc);//显示一个汉字到LCD上/
		}
		x+=d; //下一个字坐标
		i+=2;  //下个字符
	}
}

/******************************************************************************
      函数说明：显示ASCII码
      入口数据：x,y      写入的坐标
                zk_num   1:5*7   2:7*8   3:6*12,  4:8*16,  5:12*24,  6:16*32
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_Asc(u16 x,u16 y,u8 zk_num,u16 fc,u16 bc)
{
  u8 i,k,n,x0,y0,m=0;
	switch(zk_num)
	{
		// n:字符所占字节数  d：字间距
		case 7:   n=7;  x0=5;  y0=7;  break;	 //	  5x7 ASCII
		case 8:   n=8;  x0=7;  y0=8;  break;	 //   7x8 ASCII
		case 12:  n=12; x0=6;  y0=12; break;	 //  6x12 ASCII
	  case 16:  n=16; x0=8;  y0=16; break;	 //  8x16 ASCII
	  case 24:  n=48; x0=12; y0=24; break;	 //  12x24 ASCII
	 	case 32:  n=64; x0=16; y0=32; break;	 //  16x32 ASCII
	}
	LCD_Address_Set(x,y,x+x0-1,y+y0-1);
	for(i=0;i<n;i++)
	{
		for(k=0;k<8;k++)
		{
			if((FontBuf[i]&(0x80>>k)))
			{
			  LCD_WR_DATA(fc);
			}
			else
			{
			  LCD_WR_DATA(bc);
			}
			m++;
			if(m%x0==0)
			{
				m=0;
				break;
			}
		}
	}
}

/******************************************************************************
      函数说明：显示ASCII码
      入口数据：x,y      写入的坐标
                zk_num   1:5*7   2:7*8   3:6*12,  4:8*16,  5:12*24,  6:16*32
                text[]   要显示的字符串
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_Asc_String(u16 x,u16 y,u16 zk_num,u8 text[],u16 fc,u16 bc)
{
	u8 i= 0;
	u8 AddrHigh,AddrMid,AddrLow ; //字高、中、低地址
	u32 FontAddr=0; //字地址
	u32 BaseAdd=0; //字库基地址
  u8 n,d;// 不同点阵字库的计算变量
	switch(zk_num)
	{
		//n个数，d:字间距
		case 7:   BaseAdd=0x1DDF80; n=8;  d=6;  break;	 //	  5x7 ASCII
		case 8:   BaseAdd=0x1DE280; n=8;  d=7;  break;	 //   7x8 ASCII
		case 12:  BaseAdd=0x1DBE00; n=12; d=6;  break;	 //  6x12 ASCII
		case 16:  BaseAdd=0x1DD780; n=16; d=8;  break;	 //  8x16 ASCII
		case 24:  BaseAdd=0x1DFF00; n=48; d=12; break;	 //  12x24 ASCII
	 	case 32:  BaseAdd=0x1E5A50; n=64; d=16; break;	 //  16x32 ASCII
	}
	while((text[i]>0x00))
	{
	  if((text[i] >= 0x20) &&(text[i] <= 0x7E))
		{
		  FontAddr = 	text[i]-0x20;
			FontAddr = (unsigned long)((FontAddr*n)+BaseAdd);

			AddrHigh = (FontAddr&0xff0000)>>16;  /*地址的高8位,共24位*/
			AddrMid = (FontAddr&0xff00)>>8;      /*地址的中8位,共24位*/
			AddrLow = FontAddr&0xff;	     /*地址的低8位,共24位*/
			get_n_bytes_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n );/*取一个汉字的数据，存到"FontBuf[]"*/
			Display_Asc(x,y,zk_num,fc,bc);/*显示一个ascii到LCD上 */
		}
    i++;  //下个数据
		x+=d;//下一个字坐标
	}
}


/******************************************************************************
      函数说明：显示ASCII码(Arial&Times New Roman)
      入口数据：x,y      写入的坐标
                zk_num   1:8*12,  2:12*16,  3:16*24,  4:24*32
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_Arial_TimesNewRoman(u16 x,u16 y,u8 zk_num,u16 fc,u16 bc)
{
  u8 i,k,n,x0,y0,m=0;
	switch(zk_num)
	{
		// n:字符所占字节数  d:字间距
		case 12:  n=26;  x0=10; y0=12; break;	 //  8x12 ASCII
	  case 16:  n=34;  x0=12; y0=16; break;	 //  12x16 ASCII
	  case 24:  n=74;  x0=20; y0=24; break;	 //  16x24 ASCII
	 	case 32:  n=130; x0=25; y0=32; break;	 //  24x32 ASCII
	}
	LCD_Address_Set(x,y,x+x0-1,y+y0-1);
	for(i=2;i<n;i++)
	{
		for(k=0;k<8;k++)
		{
			if((FontBuf[i]&(0x80>>k)))
			{
			  LCD_WR_DATA(fc);
			}
			else
			{
			  LCD_WR_DATA(bc);
			}
			m++;
			if(m%x0==0)
			{
				m=0;
				break;
			}
		}
	}
}



/******************************************************************************
      函数说明：显示ASCII(Arial类型)
      入口数据：x,y      写入的坐标
                zk_num   1:8*12,  2:12*16,  3:16*24,  4:24*32
                text[]   要显示的字符串
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_Arial_String(u16 x,u16 y,u16 zk_num,u8 text[],u16 fc,u16 bc)
{
	u8 i= 0;
	u8 AddrHigh,AddrMid,AddrLow ; //字高、中、低地址
	u32 FontAddr=0; //字地址
	u32 BaseAdd=0; //字库基地址
	u8 n,d;// 不同点阵字库的计算变量
	switch(zk_num)
	{
		//n:个数，d:字间距
		case 12:  BaseAdd=0x1DC400; n=26;  d=10; break;	 //  8x12 ASCII(Arial类型)
		case 16:  BaseAdd=0x1DE580; n=34;  d=12; break;	 //  12x16 ASCII(Arial类型)
		case 24:  BaseAdd=0x1E22D0; n=74;  d=20; break;	 //  16x24 ASCII(Arial类型)
	 	case 32:  BaseAdd=0x1E99D0; n=130; d=25; break;	 //  24x32 ASCII(Arial类型)
	}
	while((text[i]>0x00))
	{
	  if((text[i] >= 0x20) &&(text[i] <= 0x7E))
		{
		  FontAddr = 	text[i]-0x20;
			FontAddr = (unsigned long)((FontAddr*n)+BaseAdd);

			AddrHigh = (FontAddr&0xff0000)>>16;  /*地址的高8位,共24位*/
			AddrMid = (FontAddr&0xff00)>>8;      /*地址的中8位,共24位*/
			AddrLow = FontAddr&0xff;	     /*地址的低8位,共24位*/
			get_n_bytes_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n );/*取一个汉字的数据，存到"FontBuf[]"*/
			Display_Arial_TimesNewRoman(x,y,zk_num,fc,bc);/*显示一个ascii到LCD上 */
		}
    i++;  //下个数据
		x+=d;//下一个字坐标
	}
}


/******************************************************************************
      函数说明：显示ASCII(Arial类型)
      入口数据：x,y      写入的坐标
                zk_num   1:8*12,  2:12*16,  3:16*24,  4:24*32
                text[]   要显示的字符串
                fc 字体颜色
                bc 背景颜色
      返回值：  无
******************************************************************************/
void Display_TimesNewRoman_String(u16 x,u16 y,u16 zk_num,u8 text[],u16 fc,u16 bc)
{
	u8 i= 0;
	u8 AddrHigh,AddrMid,AddrLow ; //字高、中、低地址
	u32 FontAddr=0; //字地址
	u32 BaseAdd=0; //字库基地址
  u8 n,d;// 不同点阵字库的计算变量
	switch(zk_num)
	{
		//n:个数，d:字间距
		case 12:  BaseAdd=0x1DCDC0; n=26;  d=10; break;	 //  8x12 ASCII(TimesNewRoman类型)
		case 16:  BaseAdd=0x1DF240; n=34;  d=12; break;	 //  12x16 ASCII(TimesNewRoman类型)
		case 24:  BaseAdd=0x1E3E90; n=74;  d=20; break;	 //  16x24 ASCII(TimesNewRoman类型)
	 	case 32:  BaseAdd=0x1ECA90; n=130; d=25; break;	 //  24x32 ASCII(TimesNewRoman类型)
	}
	while((text[i]>0x00))
	{
	  if((text[i] >= 0x20) &&(text[i] <= 0x7E))
		{
		  FontAddr = 	text[i]-0x20;
			FontAddr = (unsigned long)((FontAddr*n)+BaseAdd);
			AddrHigh = (FontAddr&0xff0000)>>16;  /*地址的高8位,共24位*/
			AddrMid = (FontAddr&0xff00)>>8;      /*地址的中8位,共24位*/
			AddrLow = FontAddr&0xff;	     /*地址的低8位,共24位*/
			get_n_bytes_data_from_ROM(AddrHigh,AddrMid,AddrLow,FontBuf,n );/*取一个汉字的数据，存到"FontBuf[]"*/
			Display_Arial_TimesNewRoman(x,y,zk_num,fc,bc);/*显示一个ascii到LCD上 */
		}
    i++;  //下个数据
		x+=d;//下一个字坐标
	}
}


#endif
#endif


