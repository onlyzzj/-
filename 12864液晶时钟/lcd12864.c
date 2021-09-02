#include "lcd12864.h"
#include "delay.h"


void write_com(uchar com)//写命令
{
	rs=0;//写命令
	rw=0;//写操作
	en=1; //下降沿写入数据
	DATAPORT=com;//写命令数据
	delayms(5);//等待数据稳定
	en=0;
}


void write_data(uchar dat)//写数据
{
	rs=1;//写数据
	rw=0;//写操作
	en=1; //下降沿写入数据
	DATAPORT=dat;//写数据数据
	delayms(5);//等待数据稳定
	en=0;
}


void init_lcd12864(void)//初始化
{
//	beiguang=1;
	PSB=1;            //选择并行
	write_com(0x30);  //基本设置
	delayms(5); 
	write_com(0x0c);  //显示开,游标关
	delayms(5);
	write_com(0x01);  //显示清零
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
