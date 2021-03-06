#ifndef __F_OLED_SPI_DRV_STM32F1_H
#define __F_OLED_SPI_DRV_STM32F1_H
#include "all_config.h"
#ifdef Service_Display_OLED_SPI
#ifdef F_STM32_F1


/*
  * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 *
  * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 *
 * */
#define OLED_IIC_CLK_Port  GPIOE
#define OLED_IIC_CLK_Pin   GPIO_PIN_1

#define OLED_IIC_DATA_Port GPIOE
#define OLED_IIC_DATA_Pin  GPIO_PIN_2


//IO操作函数
#define OLED_IIC_SCL    PEout(1) //SCL
#define OLED_IIC_SDA    PEout(2) //SDA
#define OLED_READ_SDA   PEin(2)  //输入SDA


void OLED_IIC_Drv_Init(void);                //初始化IIC的IO口
void OLED_SDA_Input(void);
void OLED_SDA_Output(void);



#endif
#endif
#endif
