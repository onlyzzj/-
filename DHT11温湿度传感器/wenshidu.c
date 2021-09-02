#include "wenshidu.h"
#include "delay.h"



uchar comdata=0,flag,temp,RH_data_H_temp,RH_data_L_temp,T_data_H_temp,T_data_L_temp,check_data,check_data_temp,RH_data_H,RH_data_L,T_data_H,T_data_L;




void com(void)
{
	uchar i;
	for(i=0;i<8;i++)	   
	{
		//每一bit数据都以50us低电平时隙开始
		flag=2;	
		while((!P2_0)&&flag++);//P2_0=1或flag自增到0时退出该循环
		delay10us();
		delay10us();
		delay10us();
		temp=0;      //高电平保持26~28us表示数据“0”
		if(P2_0)
		{
			temp=1;    //高电平保持70us表示数据“1”
		}
		flag=2;
		while((P2_0)&&flag++);//P2_0=0或flag自增到0时退出该循环	  
		if(flag==1)
		{
			break;//超时则跳出for循环	
		}
		comdata<<=1;
		comdata|=temp;  
	}
}




//湿度整数数据：RH_data_H
//湿度小数数据：RH_data_L
//温度整数数据：T_data_H
//温度小数数据：T_data_L
//校验和：check_data
void wenshidu(void)
{
	//主机把总线拉低至少18ms(开始信号)，保证DHT11能检测到开始信号
	P2_0=0;
	delayms(20);
	//主机发送开始信号结束后，延时等待20~40us后，读取DHT11的响应信号
	P2_0=1;
	delay10us();
	delay10us();
	delay10us();
	delay10us();
	//主机发送开始信号结束后,可以切换到输入模式，或者输出高电平均可，总线由上拉电阻拉高
	P2_0=1; 
	//DHT11接到主机的开始信号后，等待主机开始信号结束后，然后发送80us低电平响应信号    	
	if(!P2_0)	
	{
		//判断从机发出80us的低电平响应信号是否结束	
		flag=2; 
		while((!P2_0)&&flag++);//P2_0=1或flag自增到0时退出该循环
		//DHT11发送响应信号后，再把总线拉高80us，准备发送数据
		flag=2;
		while((P2_0)&&flag++);//P2_0=0或flag自增到0时退出该循环	 	
		//数据发送				
		com();
		RH_data_H_temp=comdata;
		com();
		RH_data_L_temp=comdata;
		com();
		T_data_H_temp=comdata;
		com();
		T_data_L_temp=comdata;
		com();
		check_data=comdata;
		P2_0=1;//DHT11拉低总线50us,随后总线由上拉电阻拉高进入空闲状态
		check_data_temp=(RH_data_H_temp+RH_data_L_temp+T_data_H_temp+T_data_L_temp);//数据校验 
		if(check_data==check_data_temp)
		{
			RH_data_H=RH_data_H_temp;
			RH_data_L=RH_data_L_temp;
			T_data_H=T_data_H_temp;
			T_data_L=T_data_L_temp;
		}
	}
}