#include "F_CommonLib/F_Select/all_config.h"
#include "F_CommonLib/F_Drv/nativeInterface.h"

#ifndef __F_SPI_H__
#define __F_SPI_H__


#define CS          PBout(12)
#define SCK         PBout(13)
#define MOSI        PBout(15)
#define MISO        PBout(14)


//几种mcu都包含这几个函数，所以直接声明就行
void soft_SPI_Write_MODE00(uint write_data);
uchar soft_SPI_Read_Mode00(void);

#endif

