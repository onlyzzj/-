#include  "led.h"
#include  "delay.h"
int i;
uint j;
uchar code shumaguan[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x98};




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



void shumaguan__jt(void)
{
	wei1=0;
	wei2=0;
	wei3=0;
	wei4=0;
	duanxuan=shumaguan[7];

}





void shumaguan__dt(void)
{
	wei1=0;
	wei2=1;
	wei3=1;
	wei4=1;
	duanxuan=shumaguan[1];
	delayms(1);
	wei1=1;
	wei2=0;
	wei3=1;
	wei4=1;
	duanxuan=shumaguan[2];
	delayms(1);
	wei1=1;
	wei2=1;
	wei3=0;
	wei4=1;
	duanxuan=shumaguan[3];
	delayms(1);
	wei1=1;
	wei2=1;
	wei3=1;
	wei4=0;
	duanxuan=shumaguan[4];
	delayms(1);
}





void shumaguan__dtx(uint num)
{			   
	uchar g,s,b,q;
	g=num%10,s=num/10%10,b=num/100%10,q=num/1000;
	wei1=0;
	wei2=1;
	wei3=1;
	wei4=1;
	duanxuan=shumaguan[q];
	delayms(1);
	wei1=1;
	wei2=0;
	wei3=1;
	wei4=1;
	duanxuan=shumaguan[b];
	delayms(1);
	wei1=1;
	wei2=1;
	wei3=0;
	wei4=1;
	duanxuan=shumaguan[s];
	delayms(1);
	wei1=1;
	wei2=1;
	wei3=1;
	wei4=0;
	duanxuan=shumaguan[g];
	delayms(1);


}



void miaobiao(uchar num1,uchar num2)
{			   
	uchar g,s,b,q;
	g=num2%10,s=num2/10,b=num1%10,q=num1/10;
	wei1=0;
	wei2=1;
	wei3=1;
	wei4=1;
	duanxuan=shumaguan[q];
	delayms(1);
	wei1=1;
	wei2=0;
	wei3=1;
	wei4=1;
	duanxuan=shumaguan[b];
	delayms(1);
	wei1=1;
	wei2=1;
	wei3=0;
	wei4=1;
	duanxuan=shumaguan[s];
	delayms(1);
	wei1=1;
	wei2=1;
	wei3=1;
	wei4=0;
	duanxuan=shumaguan[g];
	delayms(1);
}