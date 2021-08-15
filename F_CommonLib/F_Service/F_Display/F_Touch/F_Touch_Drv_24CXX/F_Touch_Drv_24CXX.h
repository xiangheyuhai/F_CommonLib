#ifndef __F_TOUCH_DRV_24CXX_H
#define __F_TOUCH_DRV_24CXX_H
#include "all_config.h"
#ifdef Service_TOUCH
#ifdef F_STM32_F4



#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767
//STM32F429开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE AT24C02




void AT24CXX_Init(void);
u8 AT24CXX_ReadOneByte(u16 ReadAddr);
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite);
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len);
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len);
u8 AT24CXX_Check(void);
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);


#endif
#endif
#endif
