#ifndef __F_IIC_F4_H
#define __F_IIC_F4_H
#include "all_config.h"
#ifdef F_IIC
#ifdef F_STM32_F4


/*
  * 若修改的端口不是GPIOE,则需要修改.c中三个初始化中的端口定义
 *
  * 即修改__HAL_RCC_GPIOE_CLK_ENABLE();
 *
 * */
#define OLED_IIC_SCL_Pin 		GPIO_PIN_1
#define OLED_IIC_SCL_GPIO_Port  GPIOE

#define OLED_IIC_SDA_Pin 		GPIO_PIN_0
#define OLED_IIC_SDA_GPIO_Port  GPIOE

#define OLED_IIC_SCL_SDA_GPIO_Port GPIOE



//-----------------OLED IIC端口定义----------------
/*SET*/
#define IIC_SCL_SET	HAL_GPIO_WritePin(OLED_IIC_SCL_GPIO_Port, OLED_IIC_SCL_Pin, GPIO_PIN_SET)
#define IIC_SDA_SET	HAL_GPIO_WritePin(OLED_IIC_SDA_GPIO_Port, OLED_IIC_SDA_Pin, GPIO_PIN_SET)

/*RESET*/
#define IIC_SCL_RESET	HAL_GPIO_WritePin(OLED_IIC_SCL_GPIO_Port, OLED_IIC_SCL_Pin, GPIO_PIN_RESET)
#define IIC_SDA_RESET	HAL_GPIO_WritePin(OLED_IIC_SDA_GPIO_Port, OLED_IIC_SDA_Pin, GPIO_PIN_RESET)

/*READ*/
#define IIC_SDA_READ    HAL_GPIO_ReadPin(OLED_IIC_SDA_GPIO_Port,  OLED_IIC_SDA_Pin)




void IIC_Start(void);
void IIC_Stop(void);
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Write_Byte(unsigned char txd);
u8 IIC_Read_Byte(unsigned char ack);
void IIC_GPIO_INIT(void);
void IIC_SDA_INPUT_INIT(void);
void IIC_SDA_OUTPUT_INIT(void);

#endif
#endif
#endif
