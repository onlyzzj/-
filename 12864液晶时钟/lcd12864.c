#include "lcd12864.h"
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


void init_lcd12864(void)//��ʼ��
{
//	beiguang=1;
	PSB=1;            //ѡ����
	write_com(0x30);  //��������
	delayms(5); 
	write_com(0x0c);  //��ʾ��,�α��
	delayms(5);
	write_com(0x01);  //��ʾ����
	delayms(5);		
}


void write_string(uchar x,uchar y,char *z)
{
	if(y==0)
	{
		write_com(0x80+x);
	}
	else if(y==1) 
	{
		write_com(0x90+x);	
	}
	else if(y==2) 
	{
		write_com(0x88+x);	
	}
	else if(y==3) 
	{
		write_com(0x98+x);	
	}
	while(*z)
	{
		write_data(*z);
		z++;
	}
}
