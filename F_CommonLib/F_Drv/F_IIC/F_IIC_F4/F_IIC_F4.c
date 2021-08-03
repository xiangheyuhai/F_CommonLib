#include "./F_IIC_F4.h"
#ifdef F_IIC
#ifdef F_STM32_F4
#include "all_config.h"

//产生IIC起始信号
void IIC_Start(void)
{
	SDA_Output();     //sda线输出
	IIC_SDA=1;
	IIC_SCL=1;
	F_HAL_Delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low
 	F_HAL_Delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_Output();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	F_HAL_Delay_us(4);
	IIC_SCL=1;
	IIC_SDA=1;//发送I2C总线结束信号
	F_HAL_Delay_us(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_Input();      //SDA设置为输入
	IIC_SDA=1;F_HAL_Delay_us(1);
	IIC_SCL=1;F_HAL_Delay_us(1);
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0
	return 0;
}
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_Output();
	IIC_SDA=0;
	F_HAL_Delay_us(2);
	IIC_SCL=1;
	F_HAL_Delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_Output();
	IIC_SDA=1;
	F_HAL_Delay_us(2);
	IIC_SCL=1;
	F_HAL_Delay_us(2);
	IIC_SCL=0;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC_Send_Byte(u8 txd)
{
    u8 t;
	SDA_Output();
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
        IIC_SDA=(txd&0x80)>>7;
        txd<<=1;
        F_HAL_Delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		F_HAL_Delay_us(2);
		IIC_SCL=0;
		F_HAL_Delay_us(2);
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_Input();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0;
        F_HAL_Delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;
        F_HAL_Delay_us(1);
    }
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;
}


/**/
void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure = {0},GPIO_InitStructure_1 = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStructure.Pin = IIC_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(IIC_DATA_Port, &GPIO_InitStructure);


    GPIO_InitStructure_1.Pin = IIC_CLK_Pin;
    GPIO_InitStructure_1.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStructure_1.Pull = GPIO_PULLUP;
    GPIO_InitStructure_1.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(IIC_CLK_Port, &GPIO_InitStructure_1);
}



void SDA_Input(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStructure.Pin = IIC_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    GPIO_InitStructure.Pull = GPIO_PULLUP;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(IIC_DATA_Port, &GPIO_InitStructure);
}


void SDA_Output(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_InitStructure.Pin = IIC_DATA_Pin;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(IIC_DATA_Port, &GPIO_InitStructure);
}
#endif
#endif

