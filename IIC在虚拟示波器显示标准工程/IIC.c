#include "IIC.h"
#include "delay.h"


//I2C起始信号
void IIC_Start(void)
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}



//I2C停止信号
void IIC_Stop(void)
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    delay5us();                 //延时
}



//I2C发送应答信号
//入口参数:ack (0:ACK 1:NAK)
void IIC_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    delay5us();                 //延时
}



//I2C接收应答信号
bit IIC_RecvACK(void)
{
    SCL = 1;                    //拉高时钟线
    delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    delay5us();                 //延时
    return CY;
}



//向I2C总线发送一个字节数据
void IIC_SendByte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        delay5us();             //延时
        SCL = 0;                //拉低时钟线
        delay5us();             //延时
    }
    IIC_RecvACK();
}






//从I2C总线接收一个字节数据
uchar IIC_RecvByte(void)
{
    uchar i;
    uchar dat = 0;
    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        delay5us();             //延时
    }
    return dat;
}




//向I2C设备写入一个字节数据
void Single_WriteIIC(uchar address,uchar dat)
{
    IIC_Start();                  //启动
    IIC_SendByte(SlaveAddress);   //控制字写（发送设备地址+写信号）
    IIC_SendByte(address);    //发送设备存储单元(寄存器)地址
    IIC_SendByte(dat);       //写入设备存储单元(寄存器)数据
    IIC_Stop();                   //停止信号
}




//从I2C设备读取一个字节数据
uchar Single_ReadIIC(uchar address)
{
	uchar dat;
	IIC_Start();                   //启动
	IIC_SendByte(SlaveAddress);    //控制字写（发送设备地址+写信号）
	IIC_SendByte(address);     //发送设备存储单元(寄存器)地址	
	IIC_Start();                   //启动
	IIC_SendByte(SlaveAddress+1);  //控制字读（发送设备地址+读信号）
	dat=IIC_RecvByte();       //读出设备存储单元(寄存器)数据
	IIC_SendACK(1);                //非应答
	IIC_Stop();                    //停止信号
	return dat;
}