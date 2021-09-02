#include "common.h"
#include "lcd12864.h"
#include "key.h"
#include "delay.h"
#include <stdio.h>

uint count=0;

void init_timer0(void)
{
	TMOD=0x02;
	TH0=56;
	TL0=56;
	EA=1;
	ET0=1;
	TR0=1;
}



void main (void)
{
	init_lcd12864();
  	init_timer0(); 
	while(1)
	{
	    if(key4num==0)
		{
			if(key1num==0)
			{
				if(flag1==0)
				{
					write_com(0x01);
					write_string(0,1,"0000年00月00日  ");
					write_string(0,2,"  00时00分00秒  ");
				}
				sprintf(temp,"%02d",miao);
				write_string(5,2,temp);
				sprintf(temp+3,"%02d",fen);
				write_string(3,2,temp+3);
				sprintf(temp+6,"%02d",shi);
				write_string(1,2,temp+6);
				sprintf(temp+9,"%04d",nian);
				write_string(0,1,temp+9);
				sprintf(temp+12,"%02d",yue);
				write_string(3,1,temp+12);
				sprintf(temp+15,"%02d",ri);
				write_string(5,1,temp+15);
				key();
			}
			if(key1num!=0)
			{
				key();
			}
		}
		if(key4num==1)
		{	
			if(key1num==0)
			{
				if(flag==0)
				{
					write_com(0x01);
					write_string(0,1,"  00  00  00    ");
					write_string(0,2,"  00  00  00    ");
				}
				sprintf(temp+21,"%02d",xfen);
				write_string(3,2,temp+21);
				sprintf(temp+24,"%02d",xshi);
				write_string(1,2,temp+24);
				sprintf(temp+33,"%02d",x);
				write_string(5,1,temp+33);
				sprintf(temp+30,"%02d",y);
				write_string(3,1,temp+30);
				sprintf(temp+27,"%02d",z);
				write_string(1,1,temp+27);
				sprintf(temp+18,"%02d",xmiao);
				write_string(5,2,temp+18);
				key();
			}
			if(key1num!=0)
			{
				key();
			}
		}
		if(shi==xshi&&fen==xfen&&miao==xmiao)
		{
			jiao=0;
		}
		if(shi==xshi+z&&fen==xfen+y&&miao==xmiao+x)
		{
			jiao=1;
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
					ri++;
					if((nian%400==0)||(nian%4==0&&nian%100!=0))
				       {
					   		if(yue==2) xri=29;
					   }
					   else
					   {
					   	    if(yue==2) xri=28;
					   }
					   if(yue==1||yue==3||yue==5||yue==7||yue==8||yue==10||yue==12) xri=31;
					   if(yue==4||yue==6||yue==9||yue==11) xri=30;
					   if(ri>xri)
					   {
							ri=1;
							yue++;
							if(yue>12)
							{
								yue=1;
								nian++;
							}
					   }
				}
	    	}
	    }
	 }
}

