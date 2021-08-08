/*
 * RDA5820_stm32f4.c
 *
 *  Created on: 2021年7月27日
 *      Author: Mr.Wu
 */


#include "./RDA5820_drv.h"

#ifdef W_RDA5820

#define DELAY_TIME	20


/**
  * @brief SDA线输入模式配置
  * @param None
  * @retval None
  */
void SDA_Input_Mode()
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = RDA5820_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RDA5820_DATA_Port, &GPIO_InitStructure);
}

/**
  * @brief SDA线输出模式配置
  * @param None
  * @retval None
  */
void SDA_Output_Mode()
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = RDA5820_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RDA5820_DATA_Port, &GPIO_InitStructure);
}

/**
  * @brief SDA线输出一个位
  * @param val 输出的数据
  * @retval None
  */
void SDA_Output( uint16_t val )
{
    if ( val )
    {
    	HAL_GPIO_WritePin(RDA5820_DATA_Port,RDA5820_DATA_Pin,SET);
    }
    else
    {
    	HAL_GPIO_WritePin(RDA5820_DATA_Port,RDA5820_DATA_Pin,RESET);
    }
}

/**
  * @brief SCL线输出一个位
  * @param val 输出的数据
  * @retval None
  */
void SCL_Output( uint16_t val )
{
    if ( val )
    {
    	HAL_GPIO_WritePin(RDA5820_CLK_Port,RDA5820_CLK_Pin,SET);
    }
    else
    {
    	HAL_GPIO_WritePin(RDA5820_CLK_Port,RDA5820_CLK_Pin,RESET);
    }
}

/**
  * @brief SDA输入一位
  * @param None
  * @retval GPIO读入一位
  */
uint8_t SDA_Input(void)
{
	if(HAL_GPIO_ReadPin(RDA5820_DATA_Port, RDA5820_DATA_Pin) == GPIO_PIN_SET){
		return 1;
	}else{
		return 0;
	}
}


/**
  * @brief RDA5820_IIC_的短暂延时
  * @param None
  * @retval None
  */
//static void delay1(unsigned int n)
//{
//    uint32_t i;
//    for ( i = 0; i < n; ++i);
//}

/**
  * @brief RDA5820_IIC_起始信号
  * @param None
  * @retval None
  */
void RDA5820_IIC_Start(void)
{
    SDA_Output(1);
    delay1(DELAY_TIME);
    SCL_Output(1);
    delay1(DELAY_TIME);
    SDA_Output(0);
    delay1(DELAY_TIME);
    SCL_Output(0);
    delay1(DELAY_TIME);
}

/**
  * @brief RDA5820_IIC_结束信号
  * @param None
  * @retval None
  */
void RDA5820_IIC_Stop(void)
{
    SCL_Output(0);
    delay1(DELAY_TIME);
    SDA_Output(0);
    delay1(DELAY_TIME);
    SCL_Output(1);
    delay1(DELAY_TIME);
    SDA_Output(1);
    delay1(DELAY_TIME);

}

/**
  * @brief RDA5820_IIC_等待确认信号
  * @param None
  * @retval None
  */
unsigned char RDA5820_IIC_Wait_Ack(void)
{
    unsigned short cErrTime = 5;
    SDA_Input_Mode();
    delay1(DELAY_TIME);
    SCL_Output(1);
    delay1(DELAY_TIME);
    while(SDA_Input())
    {
        cErrTime--;
        delay1(DELAY_TIME);
        if (0 == cErrTime)
        {
            SDA_Output_Mode();
            RDA5820_IIC_Stop();
            return ERROR;
        }
    }
    SDA_Output_Mode();
    SCL_Output(0);
    delay1(DELAY_TIME);
    return SUCCESS;
}

/**
  * @brief RDA5820_IIC_发送确认信号
  * @param None
  * @retval None
  */
void RDA5820_IIC_SendAck(void)
{
    SDA_Output(0);
    delay1(DELAY_TIME);
    delay1(DELAY_TIME);
    SCL_Output(1);
    delay1(DELAY_TIME);
    SCL_Output(0);
    delay1(DELAY_TIME);

}

/**
  * @brief RDA5820_IIC_发送非确认信号
  * @param None
  * @retval None
  */
void RDA5820_IIC_SendNotAck(void)
{
    SDA_Output(1);
    delay1(DELAY_TIME);
    delay1(DELAY_TIME);
    SCL_Output(1);
    delay1(DELAY_TIME);
    SCL_Output(0);
    delay1(DELAY_TIME);

}

/**
  * @brief RDA5820_IIC_发送一个字节
  * @param cSendByte 需要发送的字节
  * @retval None
  */
void RDA5820_IIC_Send_Byte(unsigned char cSendByte)
{
    unsigned char  i = 8;
    while (i--)
    {
        SCL_Output(0);
        delay1(DELAY_TIME);
        SDA_Output(cSendByte & 0x80);
        delay1(DELAY_TIME);
        cSendByte += cSendByte;
        delay1(DELAY_TIME);
        SCL_Output(1);
        delay1(DELAY_TIME);
    }
    SCL_Output(0);
    delay1(DELAY_TIME);
}

/**
  * @brief RDA5820_IIC_接收一个字节
  * @param None
  * @retval 接收到的字节
  */
unsigned char RDA5820_IIC_ReceiveByte(void)
{
    unsigned char i = 8;
    unsigned char cR_Byte = 0;
    SDA_Input_Mode();
    while (i--)
    {
        cR_Byte += cR_Byte;
        SCL_Output(0);
        delay1(DELAY_TIME);
        delay1(DELAY_TIME);
        SCL_Output(1);
        delay1(DELAY_TIME);
        cR_Byte |=  SDA_Input();
    }
    SCL_Output(0);
    delay1(DELAY_TIME);
    SDA_Output_Mode();
    return cR_Byte;
}

//
void RDA5820_IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0},GPIO_InitStructure_1 = {0};

	__HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitStructure.Pin = RDA5820_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RDA5820_DATA_Port, &GPIO_InitStructure);


    GPIO_InitStructure_1.Pin = RDA5820_CLK_Pin;
    GPIO_InitStructure_1.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure_1.Pull = GPIO_PULLUP;
    GPIO_InitStructure_1.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(RDA5820_CLK_Port, &GPIO_InitStructure_1);
}

#endif
