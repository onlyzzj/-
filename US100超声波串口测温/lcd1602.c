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



void display_temperature(uchar tempa)
{
	uchar shiwei,gewei;	
	if(tempa<115&&tempa>25)      //�����¶ȷ�Χ-20~+70��
	{
		if(tempa>=45)
		{
			tempa=tempa-45;
			write_char(2,0,'+');
		}
		else
		{
			tempa=45-tempa;
			write_char(2,0,'-');
		}
	}
	else
	{
		write_string(0,0,"error");
	}
	shiwei=tempa/10;
	gewei=tempa%10;	
	write_string(0,0,"T:");
	write_char(3,0,shiwei+0x30);
	write_char(4,0,gewei+0x30);
}





