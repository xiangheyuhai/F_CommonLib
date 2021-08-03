/*
 * RDA5820_drv.h
 *
 *  Created on: 2021年7月27日
 *      Author: Mr.Wu
 */

#ifndef SERVICE_RDA5820_RDA5820_DRV_H_
#define SERVICE_RDA5820_RDA5820_DRV_H_
#include "all_config.h"
#ifdef W_RDA5820


#define RDA5820_CLK_Port GPIOE
#define RDA5820_DATA_Port GPIOE

#define RDA5820_CLK_Pin GPIO_PIN_1
#define RDA5820_DATA_Pin GPIO_PIN_0

void RDA5820_IIC_Start(void);
void RDA5820_IIC_Stop(void);
unsigned char RDA5820_IIC_Wait_Ack(void);
void RDA5820_IIC_SendAck(void);
void RDA5820_IIC_SendNotAck(void);
void RDA5820_IIC_Send_Byte(unsigned char cSendByte);
unsigned char RDA5820_IIC_ReceiveByte(void);
void RDA5820_IIC_Init(void);






#endif
#endif /* SERVICE_RDA5820_RDA5820_DRV_H_ */
