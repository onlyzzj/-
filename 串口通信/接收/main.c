#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int



uchar flag,a;

void main(void)
{
	TMOD=0x20;//设定T1计时器工作方式2
	TH1=0xfd;//装初值
	TL1=0xfd;//装初值
	TR1=1;//启动计时器
	SM0=0;
	SM1=1;//设定串口工作方式1
	REN=1;//允许串口接收
	EA=1;//开总中断
	ES=1;//开串口中断
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