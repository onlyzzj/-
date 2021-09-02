#include <reg52.h>	
#include <math.h>     
#include <stdio.h>   	
#include <intrins.h>


typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;


// 定义51单片机端口
#define DataPort P0		    //LCD1602数据端口
sbit    LCM_RS=P2^0;		//LCD1602命令端口		
sbit    LCM_RW=P2^1;		//LCD1602命令端口		
sbit    LCM_EN=P2^2;		//LCD1602命令端口 
sbit    SCL=P1^0;			//IIC时钟引脚定义
sbit    SDA=P1^1;			//IIC数据引脚定义


// 定义MPU6050内部地址
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取


//MPU6050操作函数
void  InitMPU6050();//初始化MPU6050
void  Delay5us();
void  I2C_Start();//I2C起始信号
void  I2C_Stop();//I2C停止信号
void  I2C_SendACK(bit ack);//I2C发送应答信号
bit   I2C_RecvACK();//I2C接收应答信号
void  I2C_SendByte(uchar dat);//向I2C总线发送一个字节数据
uchar I2C_RecvByte();//从I2C总线接收一个字节数据
void  display_ACCEL_x();//显示加速计X轴
void  display_ACCEL_y();//显示加速计Y轴
void  display_ACCEL_z();//显示加速计Z轴
uchar Single_ReadI2C(uchar REG_Address);//从I2C总线接收一个字节数据
void  Single_WriteI2C(uchar REG_Address,uchar REG_data);//从I2C设备读取一个字节数据


//初始化MPU6050
void InitMPU6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);//解除休眠状态
	Single_WriteI2C(SMPLRT_DIV, 0x07);//陀螺仪采样率
	Single_WriteI2C(CONFIG, 0x06);//低通滤波频率
	Single_WriteI2C(GYRO_CONFIG, 0x18);//陀螺仪自检及测量范围
	Single_WriteI2C(ACCEL_CONFIG, 0x01);//加速计自检、测量范围及高通滤波频率
}



//I2C起始信号
void I2C_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}



//I2C停止信号
void I2C_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}



//I2C发送应答信号
//入口参数:ack (0:ACK应答    1:NAK非应答)
void I2C_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}




//I2C接收应答信号
bit I2C_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
    return CY;
}




//向I2C总线发送一个字节数据
void I2C_SendByte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    I2C_RecvACK();
}




//从I2C总线接收一个字节数据
uchar I2C_RecvByte()
{
    uchar i;
    uchar dat = 0;
    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    return dat;
}



//向I2C设备写入一个字节数据
void Single_WriteI2C(uchar REG_Address,uchar REG_data)
{
    I2C_Start();                  //起始信号
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号
    I2C_SendByte(REG_Address);    //内部寄存器地址，
    I2C_SendByte(REG_data);       //内部寄存器数据，
    I2C_Stop();                   //发送停止信号
}



//从I2C设备读取一个字节数据
uchar Single_ReadI2C(uchar REG_Address)
{
	uchar REG_data;
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress);    //发送设备地址+写信号
	I2C_SendByte(REG_Address);     //发送存储单元地址，从0开始	
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress+1);  //发送设备地址+读信号
	REG_data=I2C_RecvByte();       //读出寄存器数据
	I2C_SendACK(1);                //接收应答信号
	I2C_Stop();                    //停止信号
	return REG_data;
}


void main()
{ 
	delay(500);		//上电延时		
	InitLcd();		//液晶初始化
	InitMPU6050();	//初始化MPU6050
	delay(150);
	while(1)
	{
		Display10BitData(GetData(ACCEL_XOUT_H),2,0);	//显示X轴加速度
		Display10BitData(GetData(ACCEL_YOUT_H),7,0);	//显示Y轴加速度
		Display10BitData(GetData(ACCEL_ZOUT_H),12,0);	//显示Z轴加速度
		Display10BitData(GetData(GYRO_XOUT_H),2,1);	//显示X轴角速度
		Display10BitData(GetData(GYRO_YOUT_H),7,1);	//显示Y轴角速度
		Display10BitData(GetData(GYRO_ZOUT_H),12,1);	//显示Z轴角速度
		delay(500);
	}
}