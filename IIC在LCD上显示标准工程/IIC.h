#ifndef  __IIC_h_
#define  __IIC_h_
#include "common.h"


sbit    SCL=P2^7;			//IICʱ�����Ŷ���
sbit    SDA=P2^6;			//IIC�������Ŷ���


void  IIC_Start(void);
void  IIC_Stop(void);
void  IIC_SendACK(bit ack);
bit   IIC_RecvACK(void);
void  IIC_SendByte(uchar dat);
uchar IIC_RecvByte(void);
uchar Single_ReadIIC(uchar address);//��ȡI2C����
void  Single_WriteIIC(uchar address,uchar dat);//��I2Cд������


#endif