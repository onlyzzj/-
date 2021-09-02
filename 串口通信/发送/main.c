#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

sbit led1=P0^0;
sbit key1=P2^0;
sbit jiao=P3^4;


void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}


void send(uchar keynum)
{
//	ES=0;
	SBUF=keynum;
	while(!TI);
	TI=0;
//	ES=1;
}

void key(void)
{
	if(key1==0)
	{
		delayms(10);
		if(key1==0)
		{
//			jiao=0;
			while(!key1);
//			jiao=1;
			send(key1);
		}	 
	}
}



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
		key();	
	}
}



//void ser()interrupt 4
//{
//	RI=0;
//	P0=SBUF;
//}
