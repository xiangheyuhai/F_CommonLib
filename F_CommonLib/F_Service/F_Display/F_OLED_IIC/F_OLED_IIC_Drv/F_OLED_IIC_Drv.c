#include "./F_OLED_IIC_Drv.h"
#ifdef Service_Display_OLED_IIC
#include "all_config.h"


//产生IIC起始信号
void OLED_IIC_Start(void)
{
	OLED_SDA_Output();     //sda线输出
	OLED_IIC_SDA=1;
	OLED_IIC_SCL=1;
	F_HAL_Delay_us(4);
	OLED_IIC_SDA=0;//START:when CLK is high,DATA change form high to low
 	F_HAL_Delay_us(4);
 	OLED_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void OLED_IIC_Stop(void)
{
	OLED_SDA_Output();//sda线输出
	OLED_IIC_SCL=0;
	OLED_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	F_HAL_Delay_us(4);
	OLED_IIC_SCL=1;
	OLED_IIC_SDA=1;//发送I2C总线结束信号
	F_HAL_Delay_us(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 OLED_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	OLED_SDA_Input();      //SDA设置为输入
	OLED_IIC_SDA=1;F_HAL_Delay_us(1);
	OLED_IIC_SCL=1;F_HAL_Delay_us(1);
	while(OLED_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			OLED_IIC_Stop();
			return 1;
		}
	}
	OLED_IIC_SCL=0;//时钟输出0
	return 0;
}
//产生ACK应答
void OLED_IIC_Ack(void)
{
	OLED_IIC_SCL=0;
	OLED_SDA_Output();
	OLED_IIC_SDA=0;
	F_HAL_Delay_us(2);
	OLED_IIC_SCL=1;
	F_HAL_Delay_us(2);
	OLED_IIC_SCL=0;
}
//不产生ACK应答
void OLED_IIC_NAck(void)
{
	OLED_IIC_SCL=0;
	OLED_SDA_Output();
	OLED_IIC_SDA=1;
	F_HAL_Delay_us(2);
	OLED_IIC_SCL=1;
	F_HAL_Delay_us(2);
	OLED_IIC_SCL=0;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void OLED_IIC_Send_Byte(u8 txd)
{
    u8 t;
    OLED_SDA_Output();
    OLED_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
    	OLED_IIC_SDA=(txd&0x80)>>7;
        txd<<=1;
        F_HAL_Delay_us(2);   //对TEA5767这三个延时都是必须的
        OLED_IIC_SCL=1;
		F_HAL_Delay_us(2);
		OLED_IIC_SCL=0;
		F_HAL_Delay_us(2);
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	OLED_SDA_Input();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
    	OLED_IIC_SCL=0;
        F_HAL_Delay_us(2);
        OLED_IIC_SCL=1;
        receive<<=1;
        if(OLED_READ_SDA)receive++;
        F_HAL_Delay_us(1);
    }
    if (!ack)
    	OLED_IIC_NAck();//发送nACK
    else
    	OLED_IIC_Ack(); //发送ACK
    return receive;
}
#endif
