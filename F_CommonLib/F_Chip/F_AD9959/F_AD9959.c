#include "./F_AD9959.h"
#include "all_config.h"
#ifdef F_AD9959




u8 AD9959_Mode = 1;					//扫频或者点频
u8 AD9959_Wave_Show_Mode = 1;		//跟随扫频--1  不跟随扫频--0


/********************************扫频/扫相*********************************/
/*
  * 通用
 * */
u8  AD9959_SweepWaveFlag = 0;    	//是否显示波形
u32 AD9959_SweepCount = 0;    		//extern到定时器中--ms
u32 AD9959_SweepCountTimes = 0;     //extern到定时器中
u32 AD9959_SweepTime = 100;    		//扫频间隔时间--ms


/*
  * 扫频
 * */
u32 AD9959_SweepMaxFre = 100000; 	//最大扫频频率--Hz
u32	AD9959_SweepMinFre =  1000;  		//最小扫频频率--Hz
u32 AD9959_SweepStepFre =  1000;   	//扫频步进频率--Hz


/*
  * 扫相0~16383(对应角度：0°~360°)
 * */
u32 AD9959_SweepMaxPha = 16383; 	//最大扫描相位
u32	AD9959_SweepMinPha =  0;  	//最小扫描相位
u32 AD9959_SweepStepPha =  450;   	//扫相步进相位


/********************************点频*********************************/
u32 AD9959_FixedMaxFre = 20000; 	//最大固定输出频率--Hz
u32	AD9959_FixedMinFre = 200;  		//最小固定输出频率--Hz
u32 AD9959_FixedStepFre = 200; 		//步进固定输出频率--Hz
u32 AD9959_FixedAmpli = 1023; 	    //最大输出频率幅度--Hz
u32 AD9959_FixedNowFre = 15000; 		//此时输出频率--Hz


u32 AD9959_NowSinFre[5] = {0};
u32 AD9959_NowSinAmp[5] = {0};
u32 AD9959_NowSinPhr[5] = {0};


int AD9959_FixedPhase_Differ = 0; 	    //相位
int AD9959_FixedPhase_Differ_Last = 0; 	//相位
u8 AD9959_FixedAmpli_Differ = 0; 		//幅度
int AD9959_FixedAmpli_Eror = -40;		//相位计算校准




u8 CSR_DATA0[1] = {0x10};      // 开 CH0
u8 CSR_DATA1[1] = {0x20};      // 开 CH1
u8 CSR_DATA2[1] = {0x40};      // 开 CH2
u8 CSR_DATA3[1] = {0x80};      // 开 CH3


u8 FR2_DATA[2] = {0x00,0x00};//default Value = 0x0000
u8 CFR_DATA[3] = {0x00,0x03,0x02};//default Value = 0x000302

u8 CPOW0_DATA[2] = {0x00,0x00};//default Value = 0x0000   @ = POW/2^14*360



u8 LSRR_DATA[2] = {0x00,0x00};//default Value = 0x----

u8 RDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------

u8 FDW_DATA[4] = {0x00,0x00,0x00,0x00};//default Value = 0x--------


u32 SinFre[5] = {10000, 10000, 10000, 10000};
u32 SinAmp[5] = {1023, 1023, 1023, 1023};
u32 SinPhr[5] = {0, 4096-1, 4096*2-1, 4096*3-1};



//延时
void delay1 (u32 length)
{
	length = length*12;
   while(length--);
}
//IO口初始化
void Intserve(void)
{
	AD9959_PWR_RESET;
	AD9959_CS_SET;
    AD9959_SCLK_RESET;
    AD9959_UPDATE_RESET;
    AD9959_PS0_RESET;
    AD9959_PS1_RESET;
    AD9959_PS2_RESET;
    AD9959_PS3_RESET;
    AD9959_SDIO0_RESET;
    AD9959_SDIO1_RESET;
    AD9959_SDIO2_RESET;
    AD9959_SDIO3_RESET;
}
//AD9959复位
void IntReset(void)
{
	AD9959_Reset_RESET;
	delay1(1);//1
	AD9959_Reset_SET;
	delay1(30);//30
	AD9959_Reset_RESET;
}
 //AD9959更新数据
void IO_Update(void)
{
	AD9959_UPDATE_RESET;
	delay1(2); //2
	AD9959_UPDATE_SET;
	delay1(4); //4
	AD9959_UPDATE_RESET;
}
/*--------------------------------------------
函数功能：控制器通过SPI向AD9959写数据
RegisterAddress: 寄存器地址
NumberofRegisters: 所含字节数
*RegisterData: 数据起始地址
temp: 是否更新IO寄存器
----------------------------------------------*/
void WriteData_AD9959(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData,u8 temp)
{
	u8	ControlValue = 0;
	u8	ValueToWrite = 0;
	u8	RegisterIndex = 0;
	u8	i = 0;

	ControlValue = RegisterAddress;
	//写入地址
	AD9959_SCLK_RESET;
	AD9959_CS_RESET;
	for(i=0; i<8; i++)
	{
		AD9959_SCLK_RESET;
		if(0x80 == (ControlValue & 0x80))
			AD9959_SDIO0_SET;
		else
			AD9959_SDIO0_RESET;
		AD9959_SCLK_SET;
		ControlValue <<= 1;
	}
	AD9959_SCLK_RESET;
	//写入数据
	for (RegisterIndex=0; RegisterIndex<NumberofRegisters; RegisterIndex++)
	{
		ValueToWrite = RegisterData[RegisterIndex];
		for (i=0; i<8; i++)
		{
			AD9959_SCLK_RESET;
			if(0x80 == (ValueToWrite & 0x80))
				AD9959_SDIO0_SET;
			else
				AD9959_SDIO0_RESET;
			AD9959_SCLK_SET;
			ValueToWrite <<= 1;
		}
		AD9959_SCLK_RESET;
	}
	if(temp != 0)
		IO_Update();
	AD9959_CS_SET;
}
/*---------------------------------------
函数功能：设置通道输出频率
Channel:  输出通道
Freq:     输出频率
---------------------------------------*/
void Write_frequence(u8 Channel,u32 Freq)
{
	u8 CFTW0_DATA[4] ={0x00,0x00,0x00,0x00};	//中间变量
	  u32 Temp;
	  Temp=(u32)Freq*8.589934592;	   //将输入频率因子分为四个字节  8.589934592=(2^32)/500000000 其中500M=25M*20(倍频数可编程)
	  CFTW0_DATA[3]=(u8)Temp;
	  CFTW0_DATA[2]=(u8)(Temp>>8);
	  CFTW0_DATA[1]=(u8)(Temp>>16);
	  CFTW0_DATA[0]=(u8)(Temp>>24);
	  if(Channel==0)
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);//控制寄存器写入CH0通道
			WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH0设定频率
	  }
	  else if(Channel==1)
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);//控制寄存器写入CH1通道
			WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH1设定频率
	  }
	  else if(Channel==2)
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);//控制寄存器写入CH2通道
			WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH2设定频率
	  }
	  else if(Channel==3)
	  {
			WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);//控制寄存器写入CH3通道
			WriteData_AD9959(CFTW0_ADD,4,CFTW0_DATA,1);//CTW0 address 0x04.输出CH3设定频率
	  }

}
/*---------------------------------------
函数功能：设置通道输出幅度
Channel:  输出通道
Ampli:    输出幅度
---------------------------------------*/
void Write_Amplitude(u8 Channel, u16 Ampli)
{
	u16 A_temp;//=0x23ff;
	u8 ACR_DATA[3] = {0x00,0x00,0x00};//default Value = 0x--0000 Rest = 18.91/Iout
	A_temp=Ampli|0x1000;
	ACR_DATA[2] = (u8)A_temp;  //低位数据
	ACR_DATA[1] = (u8)(A_temp>>8); //高位数据

	if(Channel==0)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
	}

	else if(Channel==1)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
	}

	else if(Channel==2)
	{
	  WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);
	  WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
	}

	else if(Channel==3)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);
		WriteData_AD9959(ACR_ADD,3,ACR_DATA,1);
	}
}
/*---------------------------------------
函数功能：设置通道输出相位
Channel:  输出通道
Phase:    输出相位,范围：0~16383(对应角度：0°~360°)
---------------------------------------*/
void Write_Phase(u8 Channel,u16 Phase)
{
	u16 P_temp=0;
	P_temp=(u16)Phase;
	CPOW0_DATA[1]=(u8)P_temp;
	CPOW0_DATA[0]=(u8)(P_temp>>8);
	if(Channel==0)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA0,1);
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,1);
	}

	else if(Channel==1)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA1,1);
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,1);
	}

	else if(Channel==2)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA2,1);
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,1);
	}

	else if(Channel==3)
	{
		WriteData_AD9959(CSR_ADD,1,CSR_DATA3,1);
		WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,1);
	}
}


//AD9959初始化
void AD9959_GPIO_Init(void)
{
	u8 FR1_DATA[3] = {0xD0,0x00,0x00};//20倍频 Charge pump control = 75uA FR1<23> -- VCO gain control =0时 system clock below 160 MHz;
	  /* GPIO Ports Clock Enable */
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOF_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOG_CLK_ENABLE();
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOD_CLK_ENABLE();


	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOG, AD9959_SDIO3_Pin|AD9959_SDIO2_Pin|AD9959_Reset_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOC, AD9959_PS0_Pin|AD9959_SCLK_Pin|AD9959_SDIO1_Pin|AD9959_PS2_Pin
	                          |AD9959_UPDATE_Pin|AD9959_CS_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(AD9959_SDIO0_GPIO_Port, AD9959_SDIO0_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(GPIOD, AD9959_PS3_Pin|AD9959_PWR_Pin|AD9959_PS1_Pin, GPIO_PIN_RESET);


	  /*Configure GPIO pins : PGPin PGPin PGPin */
	  GPIO_InitStruct.Pin = AD9959_SDIO3_Pin|AD9959_SDIO2_Pin|AD9959_Reset_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	  /*Configure GPIO pins : PCPin PCPin PCPin PCPin
	                           PCPin PCPin */
	  GPIO_InitStruct.Pin = AD9959_PS0_Pin|AD9959_SCLK_Pin|AD9959_SDIO1_Pin|AD9959_PS2_Pin
	                          |AD9959_UPDATE_Pin|AD9959_CS_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	  /*Configure GPIO pin : PtPin */
	  GPIO_InitStruct.Pin = AD9959_SDIO0_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(AD9959_SDIO0_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pins : PDPin PDPin PDPin */
	  GPIO_InitStruct.Pin = AD9959_PS3_Pin|AD9959_PWR_Pin|AD9959_PS1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);




	 Intserve();  //IO口初始化
	IntReset();  //AD9959复位

  WriteData_AD9959(FR1_ADD,3,FR1_DATA,1);//写功能寄存器1
  WriteData_AD9959(FR2_ADD,2,FR2_DATA,1);



//  WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);
//  WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
//  WriteData_AD9959(ACR_ADD,3,ACR_DATA,0);
//  WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,0);
//  WriteData_AD9959(RDW_ADD,2,RDW_DATA,0);
//  WriteData_AD9959(FDW_ADD,4,FDW_DATA,1);




   //写入初始频率
	Write_frequence(3,SinFre[3]);
	Write_frequence(0,SinFre[0]);
	Write_frequence(1,SinFre[1]);
	Write_frequence(2,SinFre[2]);

	Write_Phase(3, SinPhr[3]);
	Write_Phase(0, SinPhr[0]);
	Write_Phase(1, SinPhr[1]);
	Write_Phase(2, SinPhr[2]);

	Write_Amplitude(3, SinAmp[3]);
	Write_Amplitude(0, SinAmp[0]);
	Write_Amplitude(1, SinAmp[1]);
	Write_Amplitude(2, SinAmp[2]);
}





#endif









