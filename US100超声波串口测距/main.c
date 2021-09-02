#include "delay.h"
#include "lcd1602.h"




uchar GLengthHigh,GLengthLow,GTempera,LastRcvData,RcvIndex;
uint PreLength;




void init_UART(void)//������9600
{ 
	TMOD=0x20;//�趨T1��ʱ��������ʽ2
	TH1=0xfd;//װ��ֵ
	TL1=0xfd;//װ��ֵ
	TR1=1;//������ʱ��
	SM0=0;
	SM1=1;//�趨���ڹ�����ʽ1
	REN=1;//�����ڽ���
	EA=1;//�����ж�
	ES=1;//�������ж�
}






void UART_Send(uchar dat)         
{
	SBUF=dat;
	while(!TI);	
	TI=0;		
}






void MeterLenByUART(void)         //Trig/TX�ܽ�����0x55
{
	RcvIndex=0;
	UART_Send(0X55);
}




void main(void)
{
	init_UART();
	init_lcd1602();
	while(1)
	{
		MeterLenByUART();
		PreLength=(GLengthHigh<<8)+GLengthLow;
		display_distance(PreLength);
		delayms(500);
	}
}




	
void UART_Receive(void) interrupt 4    //Echo/RX�ܽ����
{   
	if(RI)
	{
		RI=0;
		LastRcvData=SBUF;
		if(RcvIndex==0)
		{
			GLengthHigh=LastRcvData;
			RcvIndex++;
		}
		else if(RcvIndex==1)
		{
			GLengthLow=LastRcvData;
			RcvIndex=150;
		}
		else if(RcvIndex==100)
		{
			GTempera=LastRcvData;
			RcvIndex++;
		}			
	}	
}






