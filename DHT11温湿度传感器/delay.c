#include "delay.h"



void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=114;j>0;j--);
}




void delay10us(void)
{
	uchar i;
	i=2;
	while(--i);
}

