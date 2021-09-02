#include  "led.h"
#include  "delay.h"
int i;
uint j;




void diyigeliang(void)
{
 led=0;
}


void shanshuo1(void)
{ 
	led=0;
	i=-30000;
	while(i++);
	led=1;
	i=-30000;
	while(i++);
}




void shanshuo2(void)
{
	led=0;
	i=50000;
	while(i--);
 	led=1;
 	i=50000;
 	while(i--);
}

void shanshuo3(void)
{
	led=0;
	for(j=50000;j>0;j--);
	led=1;
    for(j=50000;j>0;j--);
}



void shanshuo4(void)
{
	led=0;
	delayms(500);
	led=1;
    delayms(500);
}




void liushuideng1(void)
{
	P0=0xfe;
	for(i=8;i>0;i--)
	{	
		delayms(500);
		P0=(P0<<1)+1;
	}	
}



void liushuideng2(void)
{
	uchar a,b;
	P0=0xfe;
	for(i=0;i<7;i++)
	{
		delayms(200);
		a=P0<<1;
		b=P0>>7;
		P0=a|b;
		delayms(200);
	}
}