#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int



uchar flag,a;

void main(void)
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
	while(1)
	{
//		if(flag==1)
//		{
//			ES=0;
//			flag=0;
//			SBUF=a;
//			while(!TI);
//			TI=0;
//			ES=1;
//		}
	}
}


void ser()interrupt 4
{
	RI=0;
	P0=SBUF;
//	a=SBUF;
//	flag=1;
}