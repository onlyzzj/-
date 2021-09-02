#include<reg52.h>
sbit led1=P0^0;
sbit led2=P0^1;
sbit led3=P0^2;
sbit led4=P0^3;
sbit led5=P0^4;
sbit led6=P0^5;
sbit led7=P0^6;
sbit led8=P0^7;
void main(void)
{
	led1=1;
	led2=0;
	led3=1;
	led4=0;
	led5=1;
	led6=0;
	led7=1;
	led8=0;
}