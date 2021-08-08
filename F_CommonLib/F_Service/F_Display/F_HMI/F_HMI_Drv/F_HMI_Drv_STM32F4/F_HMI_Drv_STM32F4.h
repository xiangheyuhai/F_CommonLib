#ifndef __F_HMI_DRV_STM32F4_H
#define __F_HMI_DRV_STM32F4_H
#include "all_config.h"
#ifdef Service_Display_HMI
#ifdef F_STM32_F4


extern char HMI_Num;				//倒数第三位 即标志位
extern char HMI_Buffer[255];	//接收到的数组
extern char HMI_Count;				//接收到的数组长度


int __io_putchar(int ch);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);


#endif
#endif
#endif
