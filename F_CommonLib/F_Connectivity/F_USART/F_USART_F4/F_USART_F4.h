#ifndef __F_USART_H
#define __F_USART_H
#include "all_config.h"
#ifdef F_USART
#ifdef F_STM32_F4

extern char USART_RX_Buffer[255];	//接收到的数组
extern char USART_RX_Count;				//接收到的数组长度


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
#endif
#endif
#endif
