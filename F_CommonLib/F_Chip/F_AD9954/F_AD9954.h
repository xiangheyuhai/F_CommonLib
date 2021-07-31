#ifndef __F_AD9954_H
#define __F_AD9954_H
#include "all_config.h"
#ifdef F_AD9954



#define AD9954_CS 	PDout(12)
#define AD9954_SCLK PFout(5)
#define AD9954_SDIO PBout(12)
#define AD9954_OSK 	PFout(7)
#define AD9954_PS0 	PFout(11)
#define AD9954_PS1 	PBout(2)
#define AD9954_IOUPDATE 	PFout(8)

#define AD9954_SDO	PDin(13)
#define AD9954_IOSY PDout(11)
#define AD9954_RES 	PBout(13)
#define AD9954_PWR 	PFout(6)


#define CFR1	0X00
#define CFR2    0X01
#define ASF     0X02
#define ARR     0X03
#define FTW0    0X04
#define POW0    0X05
#define FTW1    0X06
#define NLSCW   0X07
#define PLSCW   0X08
#define RSCW0   0X07
#define RSCW1   0X08
#define RSCW2   0X09
#define RSCW3   0X0A
#define RAM     0X0B

#define No_Dwell 0X80

typedef enum {
	DownScan  =   0,
	UpScan,
	DoubleScan
}ScanMode;

typedef enum
{ Bit_RESET = 0,
  Bit_SET
}BitAction;


void AD9954_INIT(void);
void AD9954_SETFRE(double f);//single tone
void Single_Tone(double Freq);
//void AD9954_Init(void);
//void Single_Tone(double Freq);
void Linear_Sweep(
    double  MinFreq, double MaxFreq,
    double  UpStepFreq, u8 UpStepTime,
    double  DownStepFreq, u8 DownStepTime,
    ScanMode      Mode
);


void PS0_WriteBit(BitAction BitVal);
void SetASF(u16 data);
void Generate_PSK(float f, u16 *phase);
void DirectSwitchFSK(double f1, double f2, double f3, double f4);
void DirectSwitchPSK(float f, float phase1, float phase2, float phase3, float phase4);
void AM_Init(void);
void Write_ASF(u16 factor);  //2ASK
u32 Read_Vau1(void);
u32 Read_Vau2(void);
void LINEARSWEEP(float f1,float f2);//linear sweep mode
void AD9954_GPIO_INIT(void);
u32 Get_FTW(double Real_fH);

#endif
#endif
