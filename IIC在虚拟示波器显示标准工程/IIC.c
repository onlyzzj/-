#include "IIC.h"
#include "delay.h"


//I2C��ʼ�ź�
void IIC_Start(void)
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}



//I2Cֹͣ�ź�
void IIC_Stop(void)
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    delay5us();                 //��ʱ
    SDA = 1;                    //����������
    delay5us();                 //��ʱ
}



//I2C����Ӧ���ź�
//��ڲ���:ack (0:ACK 1:NAK)
void IIC_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    delay5us();                 //��ʱ
}



//I2C����Ӧ���ź�
bit IIC_RecvACK(void)
{
    SCL = 1;                    //����ʱ����
    delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    delay5us();                 //��ʱ
    return CY;
}



//��I2C���߷���һ���ֽ�����
void IIC_SendByte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        delay5us();             //��ʱ
    }
    IIC_RecvACK();
}






//��I2C���߽���һ���ֽ�����
uchar IIC_RecvByte(void)
{
    uchar i;
    uchar dat = 0;
    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        delay5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        delay5us();             //��ʱ
    }
    return dat;
}




//��I2C�豸д��һ���ֽ�����
void Single_WriteIIC(uchar address,uchar dat)
{
    IIC_Start();                  //����
    IIC_SendByte(SlaveAddress);   //������д�������豸��ַ+д�źţ�
    IIC_SendByte(address);    //�����豸�洢��Ԫ(�Ĵ���)��ַ
    IIC_SendByte(dat);       //д���豸�洢��Ԫ(�Ĵ���)����
    IIC_Stop();                   //ֹͣ�ź�
}




//��I2C�豸��ȡһ���ֽ�����
uchar Single_ReadIIC(uchar address)
{
	uchar dat;
	IIC_Start();                   //����
	IIC_SendByte(SlaveAddress);    //������д�������豸��ַ+д�źţ�
	IIC_SendByte(address);     //�����豸�洢��Ԫ(�Ĵ���)��ַ	
	IIC_Start();                   //����
	IIC_SendByte(SlaveAddress+1);  //�����ֶ��������豸��ַ+���źţ�
	dat=IIC_RecvByte();       //�����豸�洢��Ԫ(�Ĵ���)����
	IIC_SendACK(1);                //��Ӧ��
	IIC_Stop();                    //ֹͣ�ź�
	return dat;
}