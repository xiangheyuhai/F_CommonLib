#ifndef __F_AD9959_DRV_STM32F4_H
#define __F_AD9959_DRV_STM32F4_H
#include "all_config.h"
#ifdef F_AD9959
#ifdef F_STM32_F4
extern u32 FRE_Send;



//引脚定义
#define AD9959_PS0_Pin GPIO_PIN_7
#define AD9959_PS0_GPIO_Port GPIOC

#define AD9959_PS1_Pin GPIO_PIN_7
#define AD9959_PS1_GPIO_Port GPIOD

#define AD9959_PS2_Pin GPIO_PIN_10
#define AD9959_PS2_GPIO_Port GPIOC

#define AD9959_PS3_Pin GPIO_PIN_2
#define AD9959_PS3_GPIO_Port GPIOD

#define AD9959_SDIO0_Pin GPIO_PIN_8
#define AD9959_SDIO0_GPIO_Port GPIOA

#define AD9959_SDIO1_Pin GPIO_PIN_9
#define AD9959_SDIO1_GPIO_Port GPIOC

#define AD9959_SDIO2_Pin GPIO_PIN_7
#define AD9959_SDIO2_GPIO_Port GPIOG





#define AD9959_PWR_Pin GPIO_PIN_6
#define AD9959_PWR_GPIO_Port GPIOD

#define AD9959_UPDATE_Pin GPIO_PIN_11
#define AD9959_UPDATE_GPIO_Port GPIOC

#define AD9959_Reset_Pin GPIO_PIN_15
#define AD9959_Reset_GPIO_Port GPIOG

#define AD9959_CS_Pin GPIO_PIN_12
#define AD9959_CS_GPIO_Port GPIOC

#define AD9959_SCLK_Pin GPIO_PIN_8
#define AD9959_SCLK_GPIO_Port GPIOC

#define AD9959_SDIO3_Pin GPIO_PIN_6
#define AD9959_SDIO3_GPIO_Port GPIOG


























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







/*SET*/
#define AD9959_PS0_SET		HAL_GPIO_WritePin(AD9959_PS0_GPIO_Port,     AD9959_PS0_Pin,   GPIO_PIN_SET)
#define AD9959_PS1_SET		HAL_GPIO_WritePin(AD9959_PS1_GPIO_Port,     AD9959_PS1_Pin,   GPIO_PIN_SET)
#define AD9959_PS2_SET		HAL_GPIO_WritePin(AD9959_PS2_GPIO_Port,     AD9959_PS2_Pin,   GPIO_PIN_SET)
#define AD9959_PS3_SET		HAL_GPIO_WritePin(AD9959_PS3_GPIO_Port,     AD9959_PS3_Pin,   GPIO_PIN_SET)
#define AD9959_SDIO0_SET	HAL_GPIO_WritePin(AD9959_SDIO0_GPIO_Port,   AD9959_SDIO0_Pin, GPIO_PIN_SET)
#define AD9959_SDIO1_SET	HAL_GPIO_WritePin(AD9959_SDIO1_GPIO_Port,   AD9959_SDIO1_Pin, GPIO_PIN_SET)
#define AD9959_SDIO2_SET	HAL_GPIO_WritePin(AD9959_SDIO2_GPIO_Port,   AD9959_SDIO2_Pin, GPIO_PIN_SET)


#define AD9959_PWR_SET		HAL_GPIO_WritePin(AD9959_PWR_GPIO_Port,     AD9959_PWR_Pin,    GPIO_PIN_SET)
#define AD9959_Reset_SET	HAL_GPIO_WritePin(AD9959_Reset_GPIO_Port,   AD9959_Reset_Pin,  GPIO_PIN_SET)
#define AD9959_UPDATE_SET	HAL_GPIO_WritePin(AD9959_UPDATE_GPIO_Port,  AD9959_UPDATE_Pin, GPIO_PIN_SET)
#define AD9959_CS_SET		HAL_GPIO_WritePin(AD9959_CS_GPIO_Port,      AD9959_CS_Pin,     GPIO_PIN_SET)
#define AD9959_SCLK_SET		HAL_GPIO_WritePin(AD9959_SCLK_GPIO_Port,    AD9959_SCLK_Pin,   GPIO_PIN_SET)
#define AD9959_SDIO3_SET	HAL_GPIO_WritePin(AD9959_SDIO3_GPIO_Port,   AD9959_SDIO3_Pin,  GPIO_PIN_SET)


/*RESET*/
#define AD9959_PS0_RESET	HAL_GPIO_WritePin(AD9959_PS0_GPIO_Port,     AD9959_PS0_Pin,    GPIO_PIN_RESET)
#define AD9959_PS1_RESET	HAL_GPIO_WritePin(AD9959_PS1_GPIO_Port,     AD9959_PS1_Pin,    GPIO_PIN_RESET)
#define AD9959_PS2_RESET	HAL_GPIO_WritePin(AD9959_PS2_GPIO_Port,     AD9959_PS2_Pin,    GPIO_PIN_RESET)
#define AD9959_PS3_RESET	HAL_GPIO_WritePin(AD9959_PS3_GPIO_Port,     AD9959_PS3_Pin,    GPIO_PIN_RESET)
#define AD9959_SDIO0_RESET	HAL_GPIO_WritePin(AD9959_SDIO0_GPIO_Port,   AD9959_SDIO0_Pin,  GPIO_PIN_RESET)
#define AD9959_SDIO1_RESET	HAL_GPIO_WritePin(AD9959_SDIO1_GPIO_Port,   AD9959_SDIO1_Pin,  GPIO_PIN_RESET)
#define AD9959_SDIO2_RESET	HAL_GPIO_WritePin(AD9959_SDIO2_GPIO_Port,   AD9959_SDIO2_Pin,  GPIO_PIN_RESET)


#define AD9959_PWR_RESET	HAL_GPIO_WritePin(AD9959_PWR_GPIO_Port,     AD9959_PWR_Pin,    GPIO_PIN_RESET)
#define AD9959_Reset_RESET	HAL_GPIO_WritePin(AD9959_Reset_GPIO_Port,   AD9959_Reset_Pin,  GPIO_PIN_RESET)
#define AD9959_UPDATE_RESET	HAL_GPIO_WritePin(AD9959_UPDATE_GPIO_Port,  AD9959_UPDATE_Pin, GPIO_PIN_RESET)
#define AD9959_CS_RESET		HAL_GPIO_WritePin(AD9959_CS_GPIO_Port,      AD9959_CS_Pin,     GPIO_PIN_RESET)
#define AD9959_SCLK_RESET	HAL_GPIO_WritePin(AD9959_SCLK_GPIO_Port,    AD9959_SCLK_Pin,   GPIO_PIN_RESET)
#define AD9959_SDIO3_RESET	HAL_GPIO_WritePin(AD9959_SDIO3_GPIO_Port,   AD9959_SDIO3_Pin,  GPIO_PIN_RESET)


/*STM32F4_Drv*/
void AD9959_Drv_Init(void);

#endif
#endif
#endif