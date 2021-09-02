#include "lcd1602.h"
#include "delay.h"


void write_com(uchar com)//д����
{
	rs=0;//д����
	rw=0;//д����
	en=1; //�½���д������
	DATAPORT=com;//д��������
	delayms(5);//�ȴ������ȶ�
	en=0;
}


void write_data(uchar dat)//д����
{
	rs=1;//д����
	rw=0;//д����
	en=1; //�½���д������
	DATAPORT=dat;//д��������
	delayms(5);//�ȴ������ȶ�
	en=0;
}


void init_lcd1602(void)
{
	write_com(0x01);//����
	write_com(0x06);//���뷽ʽ����
	write_com(0X38);//��ʾģʽ����
	write_com(0x0c);//��ʾ���ؿ���	
} 


void write_char(uchar x,uchar y,char z)
{
	if(y==0)
	{
		write_com(0x80+x);
	}
	else if(y==1) 
	{
		write_com(0x80+0x40+x);	
	}
	write_data(z);
}


void write_string(uchar x,uchar y,char *z)
{
	if(y==0)
	{
		write_com(0x80+x);
	}
	else if(y==1) 
	{
		write_com(0x80+0x40+x);	
	}
	while(*z)
	{
		write_data(*z);
		z++;
	}
}



void display_distance(ulong number)
{
	uchar baiwei,shiwei,gewei,xiaoshu;
	if(number>3000&&number<450000)           //�������뷶Χ3cm~4.5m
	{
		baiwei=number/100000;
	  shiwei=number%100000/10000;
		gewei=number%10000/1000;
		xiaoshu=number%1000/100;
		write_char(0,0,baiwei+0x30);
		write_char(1,0,shiwei+0x30);
		write_char(2,0,gewei+0x30);
		write_char(3,0,'.');
		write_char(4,0,xiaoshu+0x30);
		write_char(5,0,'c');
		write_char(6,0,'m');
	}
	else
	{
		write_string(0,0,"error       ");
	}
}





