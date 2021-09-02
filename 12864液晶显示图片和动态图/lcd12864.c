#include "lcd12864.h"
#include "delay.h"


void write_com(uchar com)//写命令
{
	rs=0;//写命令
	rw=0;//写操作
	en=1; //下降沿写入数据
	DATAPORT=com;//写命令数据
	delayms(1);//等待数据稳定
	en=0;
}


void write_data(uchar dat)//写数据
{
	rs=1;//写数据
	rw=0;//写操作
	en=1; //下降沿写入数据
	DATAPORT=dat;//写数据数据
	delayms(1);//等待数据稳定
	en=0;
}


void init_lcd12864(void)//初始化
{
//	beiguang=1;
	PSB=1;            //选择并行
	write_com(0x36);  //基本设置
	delayms(5); 
	write_com(0x3e);  //显示开,游标关
	delayms(5);
	write_com(0x01);  //显示清零
	delayms(5);		
}


void display_bmp(uchar *address)	
{
	uchar i,j;
	write_com(0x34);
	for(i=0;i<32;i++)		
	{
		write_com(0x80+i);//先送垂直地址 
		write_com(0x80);  //再送水平地址 ----显示图片的上半部分 
		for(j=0;j<16;j++)
		{
			write_data(*address);
			address++;
		}
	}
	for(i=0;i<32;i++)
	{
		write_com(0x80+i);	//先送垂直地址
		write_com(0x88);	//显示图片的下半部分 
		for(j=0;j<16;j++)
		{
		 	write_data(*address);
			address++;			//指针地址指向下个位置 
		}
	}
	write_com(0x36);
}



void clear_bmp_RAM()//清除图片显示RAM区的数据，与清屏指令write_LCD_command(0x01)不同 
{
	uchar i,j;
//	write_com(0x34);
	for(i=0;i<32;i++)
	{
		write_com(0x80+i);
		write_com(0x80);
		for(j=0;j<16;j++)
		{
			write_data(0);//清0 
		}
	}
	
	for(i=0;i<32;i++)
	{
		write_com(0x80+i);
		write_com(0x88);
		for(j=0;j<16;j++)
		{
			write_data(0);//清0
		}
	}
//	write_com(0x36);	
}