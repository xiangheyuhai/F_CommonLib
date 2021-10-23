#include "./F_RDA5820.h"
#include "all_config.h"
#ifdef F_RDA5820

#ifdef F_RDA5820_IIC_Hardware
extern I2C_HandleTypeDef hi2c1;
#endif


u16 RDA5820_Fre = 9800;		//单位是10KHz  默认为93.6Mhz

//初始化
//0,初始化成功;
//其他,初始化失败.
u8 RDA5820_Init(void)
{
	u16 id;
	#ifndef F_RDA5820_IIC_Hardware
	RDA5820_IIC_Drv_Init();						//初始化IIC口
	#endif
	id=RDA5820_RD_Reg(RDA5820_R00);	//读取ID =0X5805
	printf("RDA5820_ID:%x\r\n", id);
	if(id==0X5805)					//读取ID正确
	{
	 	RDA5820_WR_Reg(RDA5820_R02,0x0002);	//软复位
		HAL_Delay(50);
	 	RDA5820_WR_Reg(RDA5820_R02,0xC001);	//立体声,上电
	 	HAL_Delay(600);						//等待时钟稳定
	 	RDA5820_WR_Reg(RDA5820_R05,0X884F);	//搜索强度8,LNAN,1.8mA,VOL最大
 	 	RDA5820_WR_Reg(0X07,0X7800);		// 
	 	RDA5820_WR_Reg(0X13,0X0008);		// 
	 	RDA5820_WR_Reg(0X15,0x1420);		//VCO设置  0x17A0/0x1420
	 	RDA5820_WR_Reg(0X16,0XC000);		//  
	 	RDA5820_WR_Reg(0X1C,0X3126);		// 
	 	RDA5820_WR_Reg(0X22,0X9C24);		//fm_true 
	 	RDA5820_WR_Reg(0X47,0XF660) ;		//tx rds 
 	}else return 1;//初始化失败
	return 0;
}

//写RDA5820寄存器
void RDA5820_WR_Reg(u8 addr,u16 val)
{
	#ifndef F_RDA5820_IIC_Hardware
	RDA5820_IIC_Start();
	RDA5820_IIC_Send_Byte(RDA5820_WRITE);	//发送写命令
	RDA5820_IIC_Wait_Ack();
	RDA5820_IIC_Send_Byte(addr);   			//发送地址
	RDA5820_IIC_Wait_Ack();
	RDA5820_IIC_Send_Byte(val>>8);     		//发送高字节
	RDA5820_IIC_Wait_Ack();
	RDA5820_IIC_Send_Byte(val&0XFF);     	//发送低字节
	RDA5820_IIC_Wait_Ack();
 	RDA5820_IIC_Stop();						//产生一个停止条件
	#else

	HAL_I2C_Master_Transmit(&hi2c1, addr, val>>8, 1, 1000);
	HAL_I2C_Master_Transmit(&hi2c1, addr, val&0XFF, 1, 1000);
// 	HAL_I2C_Mem_Write(&hi2c3,RDA5820_WRITE,addr,I2C_MEMADD_SIZE_8BIT,val>>8,2,10);
	#endif
}

//	RDA5820_u8 data[3];
//	RDA5820_u16 Temp=val;
//	data[0]=addr;
//	data[1]=Temp>>8;
//	data[2]=val&0xFF;
//	HAL_I2C_Master_Transmit(&hi2c3,RDA5820_WRITE,data,3,10);
	//HAL_I2C_Mem_Write(&hi2c3,RDA5820_WRITE,addr,I2C_MEMADD_SIZE_8BIT,data,2,10);






//读RDA5820寄存器
u16 RDA5820_RD_Reg(u8 addr)
{
	#ifndef F_RDA5820_IIC_Hardware
	u16 res;
	RDA5820_IIC_Start();
	RDA5820_IIC_Send_Byte(RDA5820_WRITE);	//发送写命令
	RDA5820_IIC_Wait_Ack();
	RDA5820_IIC_Send_Byte(addr);   			//发送地址
	RDA5820_IIC_Wait_Ack();
	RDA5820_IIC_Start();
	RDA5820_IIC_Send_Byte(RDA5820_READ);    //发送读命令
	RDA5820_IIC_Wait_Ack();
 	res=RDA5820_IIC_Read_Byte(1);     		//读高字节,发送ACK
  	res<<=8;
  	res|=RDA5820_IIC_Read_Byte(0);     		//读低字节,发送NACK
  	RDA5820_IIC_Stop();						//产生一个停止条件
  	return res;								//返回读到的数据
	#else

  	u16 res;
  	u8 data[10],Temp=0x88;
  	HAL_I2C_Master_Transmit(&hi2c1,RDA5820_WRITE,addr,1,10);
  	HAL_I2C_Master_Receive(&hi2c1,RDA5820_READ,data,2,10);
  	res = data[0]<<8;
  	res |= data[1];
	return res;								//返回读到的数据
	#endif
}
//	RDA5820_u8 data[10],Temp=0x88;
//	RDA5820_u16 temp;
//
//	HAL_I2C_Mem_Read(&hi2c3,RDA5820_WRITE,addr,I2C_MEMADD_SIZE_8BIT,data,2,10);
////	HAL_I2C_Master_Transmit(&hi2c1,RDA5820_WRITE,addr,1,10);
////	HAL_I2C_Master_Receive(&hi2c1,RDA5820_WRITE,data,2,10);
//	temp=data[0]<<8;
//	temp|=data[1];
//	//printf("data: %2x,%2x\n\r",data[0],data[1]);
//	return temp;						//返回读到的数据




//设置RDA5820为RX模式
void RDA5820_RX_Mode(void)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X40);		//读取0X40的内容
	temp&=0xfff0;					//RX 模式
	RDA5820_WR_Reg(0X40,temp) ;		//FM RX模式
}			
//设置RDA5820为TX模式
void RDA5820_TX_Mode(void)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X40);		//读取0X40的内容
	temp&=0xfff0;
	temp|=0x0001;				    //TX 模式
	RDA5820_WR_Reg(0X40,temp) ;		//FM TM 模式
}
//得到信号强度
//返回值范围:0~127
u8 RDA5820_Rssi_Get(void)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X0B);		//读取0X0B的内容
	return temp>>9;                 //返回信号强度
}
//设置音量ok
//vol:0~15;
void RDA5820_Vol_Set(u8 vol)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X05);		//读取0X05的内容
	temp&=0XFFF0;
	temp|=vol&0X0F;				   		 
	RDA5820_WR_Reg(0X05,temp) ;		//设置音量
}
//静音设置
//mute:0,不静音;1,静音
void RDA5820_Mute_Set(u8 mute)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X02);		//读取0X02的内容
	if(mute)temp|=1<<14;
	else temp&=~(1<<14);	    		   		 
	RDA5820_WR_Reg(0X02,temp) ;		//设置MUTE
}
//设置灵敏度
//rssi:0~127;
void RDA5820_Rssi_Set(u8 rssi)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X05);		//读取0X05的内容
	temp&=0X80FF;
	temp|=(u16)rssi<<8;				   		 
	RDA5820_WR_Reg(0X05,temp) ;		//设置RSSI
}
//设置TX发送功率
//gain:0~63
void RDA5820_TxPAG_Set(u8 gain)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X42);		//读取0X42的内容
	temp&=0XFFC0;
	temp|=gain;				   		//GAIN
	RDA5820_WR_Reg(0X42,temp) ;		//设置PA的功率
}
//设置TX 输入信号增益
//gain:0~7
void RDA5820_TxPGA_Set(u8 gain)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X42);		//读取0X42的内容
	temp&=0XF8FF;
	temp|=gain<<8;			    	//GAIN
	RDA5820_WR_Reg(0X42,temp) ;		//设置PGA
}
//设置RDA5820的工作频段
//band:0,87~108Mhz;1,76~91Mhz;2,76~108Mhz;3,用户自定义(53H~54H)
void RDA5820_Band_Set(u8 band)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X03);		//读取0X03的内容
	temp&=0XFFF3;
	temp|=band<<2;			     
	RDA5820_WR_Reg(0X03,temp) ;		//设置BAND
}
//设置RDA5820的步进频率
//band:0,100Khz;1,200Khz;3,50Khz;3,保留
void RDA5820_Space_Set(u8 spc)
{
	u16 temp;
	temp=RDA5820_RD_Reg(0X03);		//读取0X03的内容
	temp&=0XFFFC;
	temp|=spc;			     
	RDA5820_WR_Reg(0X03,temp) ;		//设置BAND
}
//设置RDA5820的频率
//freq:频率值(单位为10Khz),比如10805,表示108.05Mhz
void RDA5820_Freq_Set(u16 freq)
{
	u16 temp;
	u8 spc=0,band=0;
	u16 fbtm,chan;
	temp=RDA5820_RD_Reg(0X03);	//读取0X03的内容
	temp&=0X001F;
	band=(temp>>2)&0x03;		//得到频带
	spc=temp&0x03; 				//得到分辨率
	if(spc==0)spc=10;
	else if(spc==1)spc=20;
	else spc=5;
	if(band==0)fbtm=8700;
	else if(band==1||band==2)fbtm=7600;
	else 
	{
		fbtm=RDA5820_RD_Reg(0X53);//得到bottom频率
		fbtm*=10;
	}
	if(freq<fbtm)return;
	chan=(freq-fbtm)/spc;		//得到CHAN应该写入的值
	chan&=0X3FF;				//取低10位
	temp|=chan<<6;
	temp|=1<<4;					//TONE ENABLE			     
	RDA5820_WR_Reg(0X03,temp) ;	//设置频率
	HAL_Delay(20);				//等待20ms
	while((RDA5820_RD_Reg(0X0B)&(1<<7))==0);//等待FM_READY
	
}
//得到当前频率
//返回值:频率值(单位10Khz)
u16 RDA5820_Freq_Get(void)
{
	u16 temp;
	u8 spc=0,band=0;
	u16 fbtm,chan;
	temp=RDA5820_RD_Reg(0X03);		//读取0X03的内容
	chan=temp>>6;   
	band=(temp>>2)&0x03;		//得到频带
	spc=temp&0x03; 				//得到分辨率
	if(spc==0)spc=10;
	else if(spc==1)spc=20;
	else spc=5;
	if(band==0)fbtm=8700;
	else if(band==1||band==2)fbtm=7600;
	else 
	{
		fbtm=RDA5820_RD_Reg(0X53);//得到bottom频率
		fbtm*=10;
	}
 	temp=fbtm+chan*spc;				 
	return temp;//返回频率值
}


//显示频率、信号强度等信息
void RDA5820_Show_Msg(void)
{
	u8 rssi;
	u16 freq;
	freq=RDA5820_Freq_Get();				//读取设置到的频率值
	rssi=RDA5820_Rssi_Get();				//得到信号强度

	#ifdef Service_Display_OLED_IIC
	sprintf((char *)OLED_IIC_SHOW_BUF, "Fre:%d", freq);
//	sprintf((char *)OLED_IIC_SHOW_BUF, "Fre:%.2fMHz", (float)freq/100);
	OLED_IIC_ShowString(0,3, OLED_IIC_SHOW_BUF,16);

	sprintf((char *)OLED_IIC_SHOW_BUF, "Rssi:%3d", rssi);
	OLED_IIC_ShowString(0,5, OLED_IIC_SHOW_BUF,16);
	#endif
}


/*
  * 频率加
  * 单位为10Khz
 * */
void RDA5820_Add_Fre(u16 Step_Fre)
{
	u16 freq;
	freq=RDA5820_Freq_Get();				//读取设置到的频率值

	if(freq<10800)
		freq+=Step_Fre;   //频率增加100Khz
 	else
 		freq=8700;				//回到起点
	RDA5820_Freq_Set(freq);		//设置频率
}

/*
  * 频率减
  * 单位为10Khz
 * */
void RDA5820_Reduce_Fre(u16 Step_Fre)
{
	u16 freq;
	freq=RDA5820_Freq_Get();				//读取设置到的频率值

	if(freq>8700)
		freq-=Step_Fre;   //频率增加100Khz
 	else
 		freq=10800;				//回到起点
	RDA5820_Freq_Set(freq);		//设置频率
}
#endif
