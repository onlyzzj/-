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
	led1=0;
	led2=1;
	led3=0;
	led4=1;
	led5=0;
	led6=1;
	led7=0;
	led8=1;
}