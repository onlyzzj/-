#include "lcd12864.h"
#include "delay.h"


void write_com(uchar com)//д����
{
	rs=0;//д����
	rw=0;//д����
	en=1; //�½���д������
	DATAPORT=com;//д��������
	delayms(1);//�ȴ������ȶ�
	en=0;
}


void write_data(uchar dat)//д����
{
	rs=1;//д����
	rw=0;//д����
	en=1; //�½���д������
	DATAPORT=dat;//д��������
	delayms(1);//�ȴ������ȶ�
	en=0;
}


void init_lcd12864(void)//��ʼ��
{
//	beiguang=1;
	PSB=1;            //ѡ����
	write_com(0x36);  //��������
	delayms(5); 
	write_com(0x3e);  //��ʾ��,�α��
	delayms(5);
	write_com(0x01);  //��ʾ����
	delayms(5);		
}


void display_bmp(uchar *address)	
{
	uchar i,j;
	write_com(0x34);
	for(i=0;i<32;i++)		
	{
		write_com(0x80+i);//���ʹ�ֱ��ַ 
		write_com(0x80);  //����ˮƽ��ַ ----��ʾͼƬ���ϰ벿�� 
		for(j=0;j<16;j++)
		{
			write_data(*address);
			address++;
		}
	}
	for(i=0;i<32;i++)
	{
		write_com(0x80+i);	//���ʹ�ֱ��ַ
		write_com(0x88);	//��ʾͼƬ���°벿�� 
		for(j=0;j<16;j++)
		{
		 	write_data(*address);
			address++;			//ָ���ַָ���¸�λ�� 
		}
	}
	write_com(0x36);
}



void clear_bmp_RAM()//���ͼƬ��ʾRAM�������ݣ�������ָ��write_LCD_command(0x01)��ͬ 
{
	uchar i,j;
//	write_com(0x34);
	for(i=0;i<32;i++)
	{
		write_com(0x80+i);
		write_com(0x80);
		for(j=0;j<16;j++)
		{
			write_data(0);//��0 
		}
	}
	
	for(i=0;i<32;i++)
	{
		write_com(0x80+i);
		write_com(0x88);
		for(j=0;j<16;j++)
		{
			write_data(0);//��0
		}
	}
//	write_com(0x36);	
}