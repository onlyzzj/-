#include "common.h"
#include "lcd1602.h"
#include"key.h"
#include <stdio.h>

uint count=0;
uchar g,s;

void init_timer0(void)
{
	TMOD=0x02;
	TH0=56;
	TL0=56;
	EA=1;
	ET0=1;
	TR0=1;
}



//void init_int0(void)
//{
//	IT0=1;
//	EX0=1;
//	EA=1;
//}




void main (void)
{
	init_lcd1602();
	init_timer0();
//	init_int0();
	write_string(0,1,"   00:00:00  ");
	while(1)
	{
		if(key1num==0)
		{
//			g=miao%10;
//			s=miao/10; 
//			write_char(10,1,g+0x30);
//			write_char(9,1,s+0x30);
			sprintf(temp,"%.2d",miao);
			write_string(9,1,temp);
			sprintf(temp+3,"%.2d",fen);
			write_string(6,1,temp+3);
			sprintf(temp+6,"%.2d",shi);
			write_string(3,1,temp+6);
			key();
		}
		else
		{
			key();
		}
	}
}



void timer0(void) interrupt 1
{
	count++;
	if(count>=5000)
	{
		count=0;
		miao++;
		if(miao>=60)
		{	
			miao=0;
			fen++;
			if(fen>=60)
			{
				fen=0;
				shi++;
		        if(shi>=24)
				{
					shi=0;
				}
	    	}
	    }
	 }
}



//void  int0(void) interrupt 0
//{
//	 key();
//}

