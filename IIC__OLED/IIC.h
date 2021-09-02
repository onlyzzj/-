#ifndef  __IIC_h_
#define  __IIC_h_
#include "common.h"


sbit SDA=P1^2;//IIC�������Ŷ���
sbit SCL=P1^3;//IICʱ�����Ŷ���


void  IIC_Start(void);
void  IIC_Stop(void);
void  IIC_SendACK(bit ack);
bit   IIC_RecvACK(void);
void  IIC_SendByte(uchar dat);
uchar IIC_RecvByte(void);
uchar Single_ReadIIC(uchar SlaveAddress,uchar address);//��ȡI2C����
void  Single_WriteIIC(uchar SlaveAddress,uchar address,uchar dat);//��I2Cд������


#endif