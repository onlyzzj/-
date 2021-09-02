#include "common.h"
#include "gsm.h"
#include"delay.h"

void init_ck(void)
{
 	SCON = 0x50 ;  //SCON: serail mode 1, 8-bit UART, enable ucvr
    //UARTΪģʽ1��8λ���ݣ��������
    TMOD |= 0x20 ; //TMOD: timer 1, mode 2, 8-bit reload
    //��ʱ��1Ϊģʽ2,8λ�Զ���װ
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
	init_ck();//��ʼ������
	init_gsm();//��ʼ��gsmģ��
	send_call1();
}



void ser(void) interrupt 4
{

    if(RI==1)
    {  aa[j]=SBUF;//����浽��������

        RI=0; //�����������ж�
        j++;
    }


}