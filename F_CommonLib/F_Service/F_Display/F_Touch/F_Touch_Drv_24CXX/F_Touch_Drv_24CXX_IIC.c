#include "./F_Touch_Drv_24CXX_IIC.h"
#ifdef Service_TOUCH
#ifdef F_STM32_F4




//IIC初始化
void EEPROM_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOB_CLK_ENABLE();   //使能GPIOB时钟

    //PH4,5初始化设置
    GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_9;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FAST;     //快速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);

    EEPROM_IIC_SDA=1;
    EEPROM_IIC_SCL=1;
}


//产生IIC起始信号
void EEPROM_IIC_Start(void)
{
	EEPROM_SDA_OUT();     //sda线输出
	EEPROM_IIC_SDA=1;
	EEPROM_IIC_SCL=1;
	F_HAL_Delay_us(4);
	EEPROM_IIC_SDA=0;//START:when CLK is high,DATA change form high to low
	F_HAL_Delay_us(4);
	EEPROM_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据
}


//产生IIC停止信号
void EEPROM_IIC_Stop(void)
{
	EEPROM_SDA_OUT();//sda线输出
	EEPROM_IIC_SCL=0;
	EEPROM_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
	F_HAL_Delay_us(4);
 	EEPROM_IIC_SCL=1;
 	EEPROM_IIC_SDA=1;//发送I2C总线结束信号
 	F_HAL_Delay_us(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 EEPROM_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	EEPROM_SDA_IN();      //SDA设置为输入
	EEPROM_IIC_SDA=1;F_HAL_Delay_us(1);
	EEPROM_IIC_SCL=1;F_HAL_Delay_us(1);
	while(EEPROM_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			EEPROM_IIC_Stop();
			return 1;
		}
	}
	EEPROM_IIC_SCL=0;//时钟输出0
	return 0;
}
//产生ACK应答
void EEPROM_IIC_Ack(void)
{
	EEPROM_IIC_SCL=0;
	EEPROM_SDA_OUT();
	EEPROM_IIC_SDA=0;
	F_HAL_Delay_us(2);
	EEPROM_IIC_SCL=1;
	F_HAL_Delay_us(2);
	EEPROM_IIC_SCL=0;
}
//不产生ACK应答
void EEPROM_IIC_NAck(void)
{
	EEPROM_IIC_SCL=0;
	EEPROM_SDA_OUT();
	EEPROM_IIC_SDA=1;
	F_HAL_Delay_us(2);
	EEPROM_IIC_SCL=1;
	F_HAL_Delay_us(2);
	EEPROM_IIC_SCL=0;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void EEPROM_IIC_Send_Byte(u8 txd)
{
    u8 t;
    EEPROM_SDA_OUT();
    EEPROM_IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
    	EEPROM_IIC_SDA=(txd&0x80)>>7;
        txd<<=1;
        F_HAL_Delay_us(2);   //对TEA5767这三个延时都是必须的
		EEPROM_IIC_SCL=1;
		F_HAL_Delay_us(2);
		EEPROM_IIC_SCL=0;
		F_HAL_Delay_us(2);
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 EEPROM_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	EEPROM_SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
    	EEPROM_IIC_SCL=0;
    	F_HAL_Delay_us(2);
        EEPROM_IIC_SCL=1;
        receive<<=1;
        if(EEPROM_READ_SDA)receive++;
        F_HAL_Delay_us(1);
    }
    if (!ack)
    	EEPROM_IIC_NAck();//发送nACK
    else
    	EEPROM_IIC_Ack(); //发送ACK
    return receive;
}


#endif
#endif
