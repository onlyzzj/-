#include "common.h"
#include  "led.h"
#include"key.h"


char miao=55,fen=59; 
uint num=0;


void init_timer0_ms1(void)
{
	TMOD=0x01;//定时器0工作模式1
	TH0=(65536-10000)/256;//赋初值
	TL0=(65536-10000)%256;//赋初值
	ET0=1;//定时器0中断允许位
	EA=1;//总中断允许位
	TR0=1;//启动定时器0开始计数	
}


void init_timer0_ms2(void)
{
	TMOD=0x02;//定时器0工作模式2
	TH0=(256-200);//赋初值
	TL0=(256-200);//赋初值
	ET0=1;//定时器0中断允许位
	EA=1;//总中断允许位
	TR0=1;//启动定时器0开始计数	
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
//	TH0=(65536-10000)/256;//赋初值
//	TL0=(65536-10000)%256;//赋初值
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