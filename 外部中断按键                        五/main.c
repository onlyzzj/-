//#include  "led.h"
#include"key.h"



void init_int0(void)//外部中断0初始化函数
{
	IT0=1;//触发方式
	EX0=1;//外部中断0中断允许位
	EA=1;//总中断允许位
//	IE=0x81;
}




void main(void)
{
	init_int0();
	while(1);
}




void  int0(void)interrupt 0	 //入口地址
{
//	IE0=0;//清除外部中断0标志位
	 key();
}