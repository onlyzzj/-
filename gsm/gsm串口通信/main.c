#include "common.h"
#include "gsm.h"
#include"delay.h"

void init_ck(void)
{
 	SCON = 0x50 ;  //SCON: serail mode 1, 8-bit UART, enable ucvr
    //UART为模式1，8位数据，允许接收
    TMOD |= 0x20 ; //TMOD: timer 1, mode 2, 8-bit reload
    //定时器1为模式2,8位自动重装
    PCON |= 0x80 ; //SMOD=1;
    TH1 = 0xFA ;   //Baud:9600 fosc="11".0592MHz
    TL1=0xFA;
    IE |= 0x90 ;     //Enable Serial Interrupt
    TR1 = 1 ;       // timer 1 run
    TI=1;
    ES=1;	
}

void main(void)
{
	init_ck();//初始化串口
	init_gsm();//初始化gsm模块
	send_call1();
}



void ser(void) interrupt 4
{

    if(RI==1)
    {  aa[j]=SBUF;//命令存到命令数组

        RI=0; //软件清除接收中断
        j++;
    }


}