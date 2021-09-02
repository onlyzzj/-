#include "common.h"
#include "IIC.h"
#include "change.h"
#include "sds.h"

uchar x;
uchar  aa[20];

void init_MPU6050()
{
	Single_WriteIIC(PWR_MGMT_1,0x00);
	Single_WriteIIC(SMPLRT_DIV,0x07);
	Single_WriteIIC(CONFIG,0x06);
	Single_WriteIIC(GYRO_CONFIG,0x18);
	Single_WriteIIC(ACCEL_CONFIG,0x01);
}



void init_com(void)
{
 	SCON = 0x50 ;  //SCON: serail mode 1, 8-bit UART, enable ucvr
    //UARTΪģʽ1��8λ���ݣ��������
    TMOD |= 0x20 ; //TMOD: timer 1, mode 2, 8-bit reload
    //��ʱ��1Ϊģʽ2,8λ�Զ���װ
    PCON |= 0x80 ; //SMOD=1;
    TH1 = 0xFA ;   //Baud:9600 fosc="11".0592MHz
    TL1=0xFA;
    IE |= 0x90 ;     //Enable Serial Interrupt
    TR1 = 1 ;       // timer 1 run
    TI=1;
    ES=1;	
}


void main(void)
{
	init_com();//��ʼ������
	init_MPU6050();
	while(1)
	{	   
		OutData[0]=hecheng_data(ACCEL_XOUT_H);
		OutData[1]=hecheng_data(ACCEL_YOUT_H);
		OutData[2]=hecheng_data(ACCEL_ZOUT_H);
		OutData[3]=hecheng_data(GYRO_XOUT_H);
		OutPut_Data();
	}
}


void ser(void) interrupt 4
{
    if(RI==1)
    {  
		aa[x]=SBUF;//����浽��������
        RI=0; //�����������ж�
        x++;
    }
}

