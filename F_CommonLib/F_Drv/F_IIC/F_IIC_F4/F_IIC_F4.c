#include "./F_IIC_F4.h"
#ifdef F_IIC
#ifdef F_STM32_F4


/**********************************************
//IIC Start
**********************************************/
void IIC_Start(void)
{
	IIC_SDA_OUTPUT_INIT();     //sda线输出
	IIC_SDA_SET;
	IIC_SCL_SET;
	F_HAL_Delay_us(4);
	IIC_SDA_RESET;			//START:when CLK is high,DATA change form high to low
	F_HAL_Delay_us(4);
	IIC_SCL_RESET;			//钳住I2C总线，准备发送或接收数据
}


/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop(void)
{
	IIC_SDA_OUTPUT_INIT();//sda线输出
	IIC_SCL_RESET;
	IIC_SDA_RESET;//STOP:when CLK is high DATA change form low to high
	F_HAL_Delay_us(4);
	IIC_SCL_SET;
	IIC_SDA_SET;//发送I2C总线结束信号
	F_HAL_Delay_us(4);
}


/**********************************************
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
**********************************************/
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	IIC_SDA_INPUT_INIT();      //SDA设置为输入
	IIC_SDA_SET;	F_HAL_Delay_us(1);
	IIC_SCL_SET;	F_HAL_Delay_us(1);
	while(IIC_SDA_READ)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_RESET;//时钟输出0
	return 0;
}


/**********************************************
//产生ACK应答
**********************************************/
void IIC_Ack(void)
{
	IIC_SCL_RESET;	IIC_SDA_OUTPUT_INIT();
	IIC_SDA_RESET;	F_HAL_Delay_us(2);
	IIC_SCL_SET;	F_HAL_Delay_us(2);
	IIC_SCL_RESET;
}


/**********************************************
//不产生ACK应答
**********************************************/
void IIC_NAck(void)
{
	IIC_SCL_RESET;	IIC_SDA_OUTPUT_INIT();
	IIC_SDA_SET;	F_HAL_Delay_us(2);
	IIC_SCL_SET;	F_HAL_Delay_us(2);
	IIC_SCL_RESET;
}


/**********************************************
// IIC Write byte
**********************************************/
void IIC_Write_Byte(unsigned char txd)
{
    u8 t;
    IIC_SDA_OUTPUT_INIT();
    IIC_SCL_RESET;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
        if ((txd&0x80)>>7)
        	IIC_SDA_SET;
        else
        	IIC_SDA_RESET;
        txd<<=1;
        F_HAL_Delay_us(2);   //对TEA5767这三个延时都是必须的
        IIC_SCL_SET;
		F_HAL_Delay_us(2);
		IIC_SCL_RESET;
		F_HAL_Delay_us(2);
    }
}


/**********************************************
// IIC Read byte
// ack=1 时，发送 ACK，ack=0，发送 nACK
**********************************************/
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	IIC_SDA_INPUT_INIT();//SDA 设置为输入
	for(i=0;i<8;i++ )
	{
		IIC_SCL_RESET;	F_HAL_Delay_us(2);
		IIC_SCL_SET;
		receive<<=1;
		if(IIC_SDA_READ)receive++;
		F_HAL_Delay_us(1);
	}
	if(!ack)
		IIC_NAck();//发送 nACK
	else
		IIC_Ack(); //发送 ACK
	return receive;
}





/**********************************************
// IIC 引脚初始化
**********************************************/
void IIC_GPIO_INIT(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  __HAL_RCC_GPIOE_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(OLED_IIC_SCL_SDA_GPIO_Port, OLED_IIC_SDA_Pin | OLED_IIC_SCL_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pins : ADF4351_UTPUT_DATA_Pin ADF4351_CLK_Pin ADF4351_CE_Pin ADF4351_LE_Pin */
	  GPIO_InitStruct.Pin = OLED_IIC_SDA_Pin | OLED_IIC_SCL_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(OLED_IIC_SCL_SDA_GPIO_Port, &GPIO_InitStruct);
}


/**********************************************
// 设置SDA为输入模式
**********************************************/
void IIC_SDA_INPUT_INIT(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /*如果修改了IO口，需要修改这个*/
	  __HAL_RCC_GPIOE_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(OLED_IIC_SDA_GPIO_Port, OLED_IIC_SDA_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin : ADF4351_INPUT_DATA_Pin */
	  GPIO_InitStruct.Pin = OLED_IIC_SDA_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(OLED_IIC_SDA_GPIO_Port, &GPIO_InitStruct);
}


/**********************************************
// 设置SDA为输出模式
**********************************************/
void IIC_SDA_OUTPUT_INIT(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  __HAL_RCC_GPIOE_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(OLED_IIC_SDA_GPIO_Port, OLED_IIC_SDA_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pins : ADF4351_UTPUT_DATA_Pin ADF4351_CLK_Pin ADF4351_CE_Pin ADF4351_LE_Pin */
	  GPIO_InitStruct.Pin = OLED_IIC_SDA_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  HAL_GPIO_Init(OLED_IIC_SDA_GPIO_Port, &GPIO_InitStruct);
}
#endif
#endif

