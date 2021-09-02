#ifndef  __IIC_h_
#define  __IIC_h_
#include "common.h"


sbit SDA=P1^2;//IIC数据引脚定义
sbit SCL=P1^3;//IIC时钟引脚定义


void  IIC_Start(void);
void  IIC_Stop(void);
void  IIC_SendACK(bit ack);
bit   IIC_RecvACK(void);
void  IIC_SendByte(uchar dat);
uchar IIC_RecvByte(void);
uchar Single_ReadIIC(uchar SlaveAddress,uchar address);//读取I2C数据
void  Single_WriteIIC(uchar SlaveAddress,uchar address,uchar dat);//向I2C写入数据


#endif