#ifdef F_STM32_F1

#include "F_CommonLib/F_Drv/F_SPI/SPI.h"

//写入数据
void soft_SPI_Write_MODE00(uint write_data)
{
	CS = 0; //选中从机
	SCK = 0; //SCK空闲时为低电平 —— MODE0
    for (uint i = 0; i < 8; i++) //写入数据，从高位开始 一个位有8个字节
    {
        if (write_data & 0x80) //判断最高位是否等于1
        {
            MOSI = 1; //是1就将输出线拉高
        }
        else
        {
            MOSI = 0; //不是1就拉低
        }
        SCK = 1; //时钟拉高 上升沿处传输一个字节数据
        write_data <<= 1;
        SCK = 0; //时钟拉低等待下一位数据的传输
        //8个字节都传输完后就是从高位开始的2进制代码
    }
    CS = 1; //片选拉高结束这一位通讯
}

//读取数据
uchar soft_SPI_Read_Mode00(void)
{
    uchar read_data = 0;

    CS = 0;
    SCK = 0;
    for (uint i = 0; i < 8; i++) //读取数据，从高位开始
    {
        read_data <<= 1;
        if (MISO) //如果传回来的数是1
        {
            read_data |= 0x01; //就让读出来的数值与之相或，以这种办法来把数据线上的1转换成代码的1
        }
        SCK = 1; //时钟拉高，上升沿传输一个字节数据
        SCK = 0; //时钟拉低等待下一位数据的传输
    } //8个字节都传输完后，也就是一位传输完后就是从高位开始的2进制代码。
	CS = 1;

    return read_data;
}
#endif
