#include "./F_HMI_Drv_STM32F4.h"
#include "all_config.h"
#ifdef Service_Display_HMI
#ifdef F_STM32_F4


#ifdef F_Printf_USART1
extern UART_HandleTypeDef huart1;
#endif

#ifdef F_Printf_USART3
extern UART_HandleTypeDef huart3;
#endif


/*
 * USART相关
 * */
#define RXBUFFERSIZE  255      //最大接收字节数
char RxBuffer[RXBUFFERSIZE];   //接收数据
uint8_t aRxBuffer;			//接收中断缓冲
uint8_t Uart1_Rx_Cnt = 0;		//接收缓冲计数


/*
 * HMI相关
 * */
char HMI_Num = 0;				//倒数第三位 即标志位
char HMI_Buffer[255];	//接收到的数组
char HMI_Count = 0;				//接收到的数组长度


/*
 * printf重定向
 * */
int __io_putchar(int ch)
{
	#ifdef F_Printf_USART1
	HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1,HAL_MAX_DELAY);
	#endif

	#ifdef F_Printf_USART3
	HAL_UART_Transmit(&huart3, (uint8_t*)&ch, 1,HAL_MAX_DELAY);
	#endif

	return ch;
}


/*
  * 接收中断服务函数
 * */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(Uart1_Rx_Cnt >= 255)  //溢出判断
	{
		Uart1_Rx_Cnt = 0;
		memset(RxBuffer,0x00,sizeof(RxBuffer));
		HAL_UART_Transmit(&huart1, (uint8_t *)"数据溢出", 10,0xFFFF);
	}
	//如果没有溢出
	else
	{
		RxBuffer[Uart1_Rx_Cnt++] = aRxBuffer;   //接收数据转存
		if((RxBuffer[Uart1_Rx_Cnt-1] == 0x0A)&&(RxBuffer[Uart1_Rx_Cnt-2] == 0x0D)) //判断结束位
		{
//			HAL_UART_Transmit(&huart1, (uint8_t *)&RxBuffer, Uart1_Rx_Cnt,0xFFFF); //将收到的信息发送出去
//			while(HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX);//检测UART发送结束

			/*获得接收的数据*/
			memcpy(HMI_Buffer, RxBuffer, Uart1_Rx_Cnt);					  //将RxBuffer中的数据给FAN
			HMI_Count = Uart1_Rx_Cnt;
			HMI_Num = RxBuffer[Uart1_Rx_Cnt-3];

			printf("%d, %x\r\n", HMI_Count, HMI_Num);
			Uart1_Rx_Cnt = 0;
			memset(RxBuffer,0x00,sizeof(RxBuffer)); //清空数组
		}
	}
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&aRxBuffer, 1);   //再开启接收中断
}


#endif
#endif
