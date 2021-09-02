#include "us100.h"



void init_timer1(void)
{
	TMOD=0x11;//��ʱ��1����ģʽ1
	TCON=0X00;//�رն�ʱ��1
	TH1=0;//����ֵ
	TL1=0;//����ֵ
	ET1=1;//��ʱ��1�ж�����λ
	EA=1;//���ж�����λ
}



ulong Dianping_distance(void)
{
	uchar i;
	uint time;
	ulong distance;	
	init_timer1();
	//Trig/TX�ܽ�����һ��10us���ϵĸߵ�ƽ	
	Trig_Pin=0;
	for(i=0;i<10;i++)
	{
		Trig_Pin=1;
	}
	Trig_Pin=0;
	//Echo/RX�ܽ����
	while(1)
	{
		if(Echo_Pin==1)
		{
			TCON=0X40;//������ʱ��1,��ʼ����	
			break;
		}
	}
	while(1)
	{
		if(Echo_Pin==0)
		{
			TCON=0X00;//�رն�ʱ��1
			break;
		}
	}
	time=(TH1<<8)+TL1;//���㶨ʱ������ʱ��  ��λ��us
	distance=time*0.017*1000;//  1distance==1000cm
	return distance;
}





