#ifndef __F_AD9959_H
#define __F_AD9959_H
#include "all_config.h"
#ifdef F_AD9959

extern u32 FRE_Send;


#define AD9959_Mode_Sweep    1	    //模式--扫频
#define AD9959_Mode_FixedFre 2		//模式--点频
#define AD9959_Mode_FHSS     3		//模式--跳频


extern u8 AD9959_Mode;				//扫频或者点频
extern u8 AD9959_Wave_Show_Mode;	//跟随扫频--1  不跟随扫频--0

extern u32 AD9959_SweepMaxFre; 		//最大扫频频率--Hz
extern u32 AD9959_SweepMinFre;  	//最小扫频频率--Hz
extern u32 AD9959_SweepStepFre;   	//扫频步进频率--Hz
extern u32 AD9959_SweepTime;    	//扫频间隔时间--ms
extern u8  AD9959_SweepWaveFlag;   	//是否显示波形
extern u32 AD9959_SweepCount;    	//extern到定时器中--ms
extern u32 AD9959_SweepCountTimes; 	//extern到定时器中

extern u32 AD9959_SweepMaxPha; 	//最大扫描相位
extern u32	AD9959_SweepMinPha;  	//最小扫描相位
extern u32 AD9959_SweepStepPha;   	//扫相步进相位



extern u32 AD9959_FixedMaxFre; 		//最大固定输出频率--Hz
extern u32 AD9959_FixedMinFre;  	//最小固定输出频率--Hz
extern u32 AD9959_FixedStepFre; 	//步进固定输出频率--Hz
extern u32 AD9959_FixedAmpli; 	    //最大输出频率幅度--Hz
extern u32 AD9959_FixedNowFre; 		//此时输出频率--Hz

extern u32 AD9959_NowSinFre[5];
extern u32 AD9959_NowSinAmp[5];
extern u32 AD9959_NowSinPhr[5];



//AD9959寄存器地址定义
#define CSR_ADD   0x00   //CSR 通道选择寄存器
#define FR1_ADD   0x01   //FR1 功能寄存器1
#define FR2_ADD   0x02   //FR2 功能寄存器2
#define CFR_ADD   0x03   //CFR 通道功能寄存器
#define CFTW0_ADD 0x04   //CTW0 通道频率转换字寄存器
#define CPOW0_ADD 0x05   //CPW0 通道相位转换字寄存器
#define ACR_ADD   0x06   //ACR 幅度控制寄存器
#define LSRR_ADD  0x07   //LSR 通道线性扫描寄存器
#define RDW_ADD   0x08   //RDW 通道线性向上扫描寄存器
#define FDW_ADD   0x09   //FDW 通道线性向下扫描寄存器



//延时
void delay1 (u32 length);
//IO口初始化
void Intserve(void);
//AD9959复位
void IntReset(void);
 //AD9959更新数据
void IO_Update(void);
/*--------------------------------------------
函数功能：控制器通过SPI向AD9959写数据
RegisterAddress: 寄存器地址
NumberofRegisters: 所含字节数
*RegisterData: 数据起始地址
temp: 是否更新IO寄存器
----------------------------------------------*/
void WriteData_AD9959(u8 RegisterAddress, u8 NumberofRegisters, u8 *RegisterData,u8 temp);
/*---------------------------------------
函数功能：设置通道输出频率
Channel:  输出通道
Freq:     输出频率
---------------------------------------*/
void Write_frequence(u8 Channel,u32 Freq);
/*---------------------------------------
函数功能：设置通道输出幅度
Channel:  输出通道
Ampli:    输出幅度
---------------------------------------*/
void Write_Amplitude(u8 Channel, u16 Ampli);
/*---------------------------------------
函数功能：设置通道输出相位
Channel:  输出通道
Phase:    输出相位,范围：0~16383(对应角度：0°~360°)
---------------------------------------*/
void Write_Phase(u8 Channel,u16 Phase);
/*---------------------------------------
函数功能：AD9959初始化
---------------------------------------*/
void AD9959_Init(void);


#endif
#endif
