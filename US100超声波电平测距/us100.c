#include "us100.h"



void init_timer1(void)
{
	TMOD=0x11;//定时器1工作模式1
	TCON=0X00;//关闭定时器1
	TH1=0;//赋初值
	TL1=0;//赋初值
	ET1=1;//定时器1中断允许位
	EA=1;//总中断允许位
}



ulong Dianping_distance(void)
{
	uchar i;
	uint time;
	ulong distance;	
	init_timer1();
	//Trig/TX管脚输入一个10us以上的高电平	
	Trig_Pin=0;
	for(i=0;i<10;i++)
	{
		Trig_Pin=1;
	}
	Trig_Pin=0;
	//Echo/RX管脚输出
	while(1)
	{
		if(Echo_Pin==1)
		{
			TCON=0X40;//启动定时器1,开始计数	
			break;
		}
	}
	while(1)
	{
		if(Echo_Pin==0)
		{
			TCON=0X00;//关闭定时器1
			break;
		}
	}
	time=(TH1<<8)+TL1;//计算定时器计数时间  单位：us
	distance=time*0.017*1000;//  1distance==1000cm
	return distance;
}





