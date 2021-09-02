#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit EN1=P1^1;
sbit EN2=P1^2;
uint flag1=0;
uint flag2=0;
sbit in1=P0^0;    //iN1 iN2 为右电机    //in1=0;in2=1;前转
sbit in2=P0^1;	  						
sbit in3=P0^2;    //iN3 iN4 为左电机	//in3=1;in4=0;前转
sbit in4=P0^3;
void main()
{
	EA=1;
	TMOD=0x01;
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	ET0=1;
	TR0=1;
	EN1=0;
	EN2=0;
	while(1)
	{
	 	in1=0;
		in2=1;
		in3=1;
		in4=0;
	}
}
void timer0() interrupt 1
{
	TH0=(65536-1000)/256;
	TL0=(65536-1000)%256;
	flag1++;
	if(flag1==50)
	{
		flag1=0;
	}
	if(flag1>=20)
	{
		EN1=1;
	}
	else
	{
		EN1=0;
	}
	flag2++;
	if(flag2==50)
	{
		flag2=0;
	}
	if(flag2>=19)
	{
		EN2=1;
	}
	else
	{
		EN2=0;
	}
			
}

