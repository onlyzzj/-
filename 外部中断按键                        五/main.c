//#include  "led.h"
#include"key.h"



void init_int0(void)//�ⲿ�ж�0��ʼ������
{
	IT0=1;//������ʽ
	EX0=1;//�ⲿ�ж�0�ж�����λ
	EA=1;//���ж�����λ
//	IE=0x81;
}




void main(void)
{
	init_int0();
	while(1);
}




void  int0(void)interrupt 0	 //��ڵ�ַ
{
//	IE0=0;//����ⲿ�ж�0��־λ
	 key();
}