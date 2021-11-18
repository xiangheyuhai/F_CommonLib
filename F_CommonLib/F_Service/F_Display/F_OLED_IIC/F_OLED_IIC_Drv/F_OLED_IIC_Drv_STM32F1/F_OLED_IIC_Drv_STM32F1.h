#ifndef __F_OLED_IIC_DRV_STM32F1_H
#define __F_OLED_IIC_DRV_STM32F1_H
#include "all_config.h"
#ifdef Service_Display_OLED_IIC
#ifdef F_STM32_F1


/*
  * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 *
  * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 *
 * */
#define OLED_IIC_CLK_Port  GPIOA
#define OLED_IIC_CLK_Pin   GPIO_PIN_5

#define OLED_IIC_DATA_Port GPIOA
#define OLED_IIC_DATA_Pin  GPIO_PIN_7


//IO操作函数
#define OLED_IIC_SCL    PAout(5) //SCL
#define OLED_IIC_SDA    PAout(7) //SDA
#define OLED_READ_SDA   PEAin(7)  //输入SDA


void OLED_IIC_Drv_Init(void);                //初始化IIC的IO口
void OLED_SDA_Input(void);
void OLED_SDA_Output(void);



#endif
#endif
#endif
