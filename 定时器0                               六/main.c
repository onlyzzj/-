#include "common.h"
#include  "led.h"
#include"key.h"


char miao=55,fen=59; 
uint num=0;


void init_timer0_ms1(void)
{
	TMOD=0x01;//��ʱ��0����ģʽ1
	TH0=(65536-10000)/256;//����ֵ
	TL0=(65536-10000)%256;//����ֵ
	ET0=1;//��ʱ��0�ж�����λ
	EA=1;//���ж�����λ
	TR0=1;//������ʱ��0��ʼ����	
}


void init_timer0_ms2(void)
{
	TMOD=0x02;//��ʱ��0����ģʽ2
	TH0=(256-200);//����ֵ
	TL0=(256-200);//����ֵ
	ET0=1;//��ʱ��0�ж�����λ
	EA=1;//���ж�����λ
	TR0=1;//������ʱ��0��ʼ����	
}

void main(void)
{
//	init_timer0_ms1();
	init_timer0_ms2();
	while(1)
	{
		key();
		miaobiao(fen,miao);
	}
}


//void timer0(void) interrupt	1
//{
//	TH0=(65536-10000)/256;//����ֵ
//	TL0=(65536-10000)%256;//����ֵ
//	num++;
//	if(num>50)
//	{
//		num=0;		
//		led=!led;
//	}
//}




void timer0(void) interrupt	1
{
	num++;
	if(num>=5000)
	{
		num=0;		
		miao++;
		if(miao>=60)
		{			  
			miao=0;
			fen++;
			if(fen>=60)
			{	   
				fen=0;
			}
		}
	}
}