#include "delay.h"
#include "lcd1602.h"




uchar GLengthHigh,GLengthLow,GTempera,LastRcvData,RcvIndex;
uint PreLength;




void init_UART(void)//波特率9600
{ 
	TMOD=0x20;//设定T1计时器工作方式2
	TH1=0xfd;//装初值
	TL1=0xfd;//装初值
	TR1=1;//启动计时器
	SM0=0;
	SM1=1;//设定串口工作方式1
	REN=1;//允许串口接收
	EA=1;//开总中断
	ES=1;//开串口中断
}






void UART_Send(uchar dat)         
{
	SBUF=dat;
	while(!TI);	
	TI=0;		
}






void MeterLenByUART(void)         //Trig/TX管脚输入0x55
{
	RcvIndex=0;
	UART_Send(0X55);
}




void main(void)
{
	init_UART();
	init_lcd1602();
	while(1)
	{
		MeterLenByUART();
		PreLength=(GLengthHigh<<8)+GLengthLow;
		display_distance(PreLength);
		delayms(500);
	}
}




	
void UART_Receive(void) interrupt 4    //Echo/RX管脚输出
{   
	if(RI)
	{
		RI=0;
		LastRcvData=SBUF;
		if(RcvIndex==0)
		{
			GLengthHigh=LastRcvData;
			RcvIndex++;
		}
		else if(RcvIndex==1)
		{
			GLengthLow=LastRcvData;
			RcvIndex=150;
		}
		else if(RcvIndex==100)
		{
			GTempera=LastRcvData;
			RcvIndex++;
		}			
	}	
}






