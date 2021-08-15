#include "./F_Touch_Drv_IIC.h"
#ifdef Service_TOUCH
#ifdef F_STM32_F4

//控制I2C速度的延时
void CT_Delay(void)
{
	F_HAL_Delay_us(2);
}
//电容触摸芯片IIC接口初始化
void CT_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();   		//使能GPIOB时钟
	__HAL_RCC_GPIOF_CLK_ENABLE();   		//使能GPIOF时钟

    //PB0,PF11
    GPIO_Initure.Pin=GPIO_PIN_0;			//PB0设置为推挽输出
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

	GPIO_Initure.Pin=GPIO_PIN_11;			//PF11设置推挽输出
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);

    CT_IIC_SDA=1;
	CT_IIC_SCL=1;
}
//产生IIC起始信号
void CT_IIC_Start(void)
{
	CT_SDA_OUT();     //sda线输出
	CT_IIC_SDA=1;
	CT_IIC_SCL=1;
	F_HAL_Delay_us(30);
 	CT_IIC_SDA=0;//START:when CLK is high,DATA change form high to low
	CT_Delay();
	CT_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void CT_IIC_Stop(void)
{
	CT_SDA_OUT();//sda线输出
	CT_IIC_SCL=1;
	F_HAL_Delay_us(30);
	CT_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	CT_Delay();
	CT_IIC_SDA=1;//发送I2C总线结束信号
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 CT_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	CT_SDA_IN();      //SDA设置为输入
	CT_IIC_SDA=1;
	CT_IIC_SCL=1;
	CT_Delay();
	while(CT_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			CT_IIC_Stop();
			return 1;
		}
		CT_Delay();
	}
	CT_IIC_SCL=0;//时钟输出0
	return 0;
}
//产生ACK应答
void CT_IIC_Ack(void)
{
	CT_IIC_SCL=0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA=0;
	CT_Delay();
	CT_IIC_SCL=1;
	CT_Delay();
	CT_IIC_SCL=0;
}
//不产生ACK应答
void CT_IIC_NAck(void)
{
	CT_IIC_SCL=0;
	CT_SDA_OUT();
	CT_Delay();
	CT_IIC_SDA=1;
	CT_Delay();
	CT_IIC_SCL=1;
	CT_Delay();
	CT_IIC_SCL=0;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void CT_IIC_Send_Byte(u8 txd)
{
    u8 t;
	CT_SDA_OUT();
    CT_IIC_SCL=0;//拉低时钟开始数据传输
	CT_Delay();
	for(t=0;t<8;t++)
    {
        CT_IIC_SDA=(txd&0x80)>>7;
        txd<<=1;
		CT_IIC_SCL=1;
		CT_Delay();
		CT_IIC_SCL=0;
		CT_Delay();
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 CT_IIC_Read_Byte(unsigned char ack)
{
	u8 i,receive=0;
 	CT_SDA_IN();//SDA设置为输入
 	F_HAL_Delay_us(30);
	for(i=0;i<8;i++ )
	{
		CT_IIC_SCL=0;
		CT_Delay();
		CT_IIC_SCL=1;
		receive<<=1;
		if(CT_READ_SDA)receive++;
        CT_Delay();
	}
	if (!ack)CT_IIC_NAck();//发送nACK
	else CT_IIC_Ack(); //发送ACK
 	return receive;
}



#endif
#endif
