#include <reg52.h>	
#include <math.h>     
#include <stdio.h>   	
#include <intrins.h>


typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;


// ����51��Ƭ���˿�
#define DataPort P0		    //LCD1602���ݶ˿�
sbit    LCM_RS=P2^0;		//LCD1602����˿�		
sbit    LCM_RW=P2^1;		//LCD1602����˿�		
sbit    LCM_EN=P2^2;		//LCD1602����˿� 
sbit    SCL=P1^0;			//IICʱ�����Ŷ���
sbit    SDA=P1^1;			//IIC�������Ŷ���


// ����MPU6050�ڲ���ַ
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
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
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define	SlaveAddress	0xD0	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ


//MPU6050��������
void  InitMPU6050();//��ʼ��MPU6050
void  Delay5us();
void  I2C_Start();//I2C��ʼ�ź�
void  I2C_Stop();//I2Cֹͣ�ź�
void  I2C_SendACK(bit ack);//I2C����Ӧ���ź�
bit   I2C_RecvACK();//I2C����Ӧ���ź�
void  I2C_SendByte(uchar dat);//��I2C���߷���һ���ֽ�����
uchar I2C_RecvByte();//��I2C���߽���һ���ֽ�����
void  display_ACCEL_x();//��ʾ���ټ�X��
void  display_ACCEL_y();//��ʾ���ټ�Y��
void  display_ACCEL_z();//��ʾ���ټ�Z��
uchar Single_ReadI2C(uchar REG_Address);//��I2C���߽���һ���ֽ�����
void  Single_WriteI2C(uchar REG_Address,uchar REG_data);//��I2C�豸��ȡһ���ֽ�����


//��ʼ��MPU6050
void InitMPU6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);//�������״̬
	Single_WriteI2C(SMPLRT_DIV, 0x07);//�����ǲ�����
	Single_WriteI2C(CONFIG, 0x06);//��ͨ�˲�Ƶ��
	Single_WriteI2C(GYRO_CONFIG, 0x18);//�������Լ켰������Χ
	Single_WriteI2C(ACCEL_CONFIG, 0x01);//���ټ��Լ졢������Χ����ͨ�˲�Ƶ��
}



//I2C��ʼ�ź�
void I2C_Start()
{
    SDA = 1;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 0;                    //�����½���
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
}



//I2Cֹͣ�ź�
void I2C_Stop()
{
    SDA = 0;                    //����������
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SDA = 1;                    //����������
    Delay5us();                 //��ʱ
}



//I2C����Ӧ���ź�
//��ڲ���:ack (0:ACKӦ��    1:NAK��Ӧ��)
void I2C_SendACK(bit ack)
{
    SDA = ack;                  //дӦ���ź�
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
}




//I2C����Ӧ���ź�
bit I2C_RecvACK()
{
    SCL = 1;                    //����ʱ����
    Delay5us();                 //��ʱ
    CY = SDA;                   //��Ӧ���ź�
    SCL = 0;                    //����ʱ����
    Delay5us();                 //��ʱ
    return CY;
}




//��I2C���߷���һ���ֽ�����
void I2C_SendByte(uchar dat)
{
    uchar i;
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;              //�Ƴ����ݵ����λ
        SDA = CY;               //�����ݿ�
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    I2C_RecvACK();
}




//��I2C���߽���һ���ֽ�����
uchar I2C_RecvByte()
{
    uchar i;
    uchar dat = 0;
    SDA = 1;                    //ʹ���ڲ�����,׼����ȡ����,
    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        SCL = 1;                //����ʱ����
        Delay5us();             //��ʱ
        dat |= SDA;             //������               
        SCL = 0;                //����ʱ����
        Delay5us();             //��ʱ
    }
    return dat;
}



//��I2C�豸д��һ���ֽ�����
void Single_WriteI2C(uchar REG_Address,uchar REG_data)
{
    I2C_Start();                  //��ʼ�ź�
    I2C_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    I2C_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ��
    I2C_SendByte(REG_data);       //�ڲ��Ĵ������ݣ�
    I2C_Stop();                   //����ֹͣ�ź�
}



//��I2C�豸��ȡһ���ֽ�����
uchar Single_ReadI2C(uchar REG_Address)
{
	uchar REG_data;
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress);    //�����豸��ַ+д�ź�
	I2C_SendByte(REG_Address);     //���ʹ洢��Ԫ��ַ����0��ʼ	
	I2C_Start();                   //��ʼ�ź�
	I2C_SendByte(SlaveAddress+1);  //�����豸��ַ+���ź�
	REG_data=I2C_RecvByte();       //�����Ĵ�������
	I2C_SendACK(1);                //����Ӧ���ź�
	I2C_Stop();                    //ֹͣ�ź�
	return REG_data;
}


void main()
{ 
	delay(500);		//�ϵ���ʱ		
	InitLcd();		//Һ����ʼ��
	InitMPU6050();	//��ʼ��MPU6050
	delay(150);
	while(1)
	{
		Display10BitData(GetData(ACCEL_XOUT_H),2,0);	//��ʾX����ٶ�
		Display10BitData(GetData(ACCEL_YOUT_H),7,0);	//��ʾY����ٶ�
		Display10BitData(GetData(ACCEL_ZOUT_H),12,0);	//��ʾZ����ٶ�
		Display10BitData(GetData(GYRO_XOUT_H),2,1);	//��ʾX����ٶ�
		Display10BitData(GetData(GYRO_YOUT_H),7,1);	//��ʾY����ٶ�
		Display10BitData(GetData(GYRO_ZOUT_H),12,1);	//��ʾZ����ٶ�
		delay(500);
	}
}