#ifndef __F_RDA5820_DRV_SM32F4_H
#define __F_RDA5820_DRV_SM32F4_H
#include "all_config.h"
#ifdef F_RDA5820
#ifdef F_STM32_F4


/*IO口宏定义*/
#define RDA5820_CLK_Port GPIOB
#define RDA5820_CLK_Pin GPIO_PIN_6


#define RDA5820_DATA_Port GPIOB
#define RDA5820_DATA_Pin GPIO_PIN_7


#define RDA5820_IIC_SCL    PBout(6) //SCL
#define RDA5820_IIC_SDA    PBout(7) //SDA
#define RDA5820_READ_SDA   PBin(7)  //输入SDA


void RDA5820_IIC_Drv_Init(void);
void RDA5820_SDA_Input(void);
void RDA5820_SDA_Output(void);

#endif
#endif
#endif
