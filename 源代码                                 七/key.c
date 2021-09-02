#include"key.h"
#include"delay.h"
#include  "led.h"
#include "lcd1602.h"
#include <stdio.h>


uchar key1num=0;
uchar temp[16];
int miao=56,fen=59,shi=23;



void key(void)
{
	if(key1==0)//调节时间功能键
	{
		delayms(10);//消抖
		if(key1==0)
		{
			jiao=0;
			while(!key1);//等待松手
			jiao=1;
			key1num++;
			if(key1num>=4)
				key1num=0;
			switch(key1num)
			{
				case 0: TR0=1; write_com(0x0c); break;
				case 1: TR0=0; write_com(0x0f); write_com(0x80+0x4a); break;
				case 2: write_com(0x80+0x47); break;			
			 	case 3: write_com(0x80+0x44); break;
			}
		}	 
	}
	if (key2==0)//时间加
	{
		delayms(10);//消抖
		if(key2==0)
		{
			jiao=0;
			while(!key2);//等待松手
			jiao=1;
			switch (key1num)
			{
				case 1:miao++;
					   if (miao>=60) 
					   miao=0; 
					   sprintf(temp,"%.2d",miao);
				       write_string(9,1,temp);
					   sprintf(temp+3,"%.2d",fen);
					   write_string(6,1,temp+3);
					   sprintf(temp+6,"%.2d",shi);
					   write_string(3,1,temp+6);
					   write_com(0x80+0x4a);
					   break;
				case 2:fen++;
					   if (fen>=60) 
					   fen=0; 					   
					   sprintf(temp,"%.2d",miao);
				       write_string(9,1,temp);
					   sprintf(temp+3,"%.2d",fen);
					   write_string(6,1,temp+3);
					   sprintf(temp+6,"%.2d",shi);
					   write_string(3,1,temp+6);
					   write_com(0x80+0x47);
					   break;
				case 3:shi++;
					   if (shi>=24) 
					   shi=0; 					  
					   sprintf(temp,"%.2d",miao);
				       write_string(9,1,temp);
					   sprintf(temp+3,"%.2d",fen);
					   write_string(6,1,temp+3);
					   sprintf(temp+6,"%.2d",shi);
					   write_string(3,1,temp+6);
					   write_com(0x80+0x44);
					   break;	
	 	    }
         }
	}
	if(key3==0)//时间减
	{
		delayms(10);//消抖
		if(key3==0)
		{
			jiao=0;
			while(!key3);//等待松手
			jiao=1;
			switch (key1num)
			{
				case 1:miao--;
					   if (miao<0) 
					   miao=59; 
					   sprintf(temp,"%.2d",miao);
				       write_string(9,1,temp);
					   sprintf(temp+3,"%.2d",fen);
					   write_string(6,1,temp+3);
					   sprintf(temp+6,"%.2d",shi);
					   write_string(3,1,temp+6);
					   write_com(0x80+0x4a);
					   break;
				case 2:fen--;
					   if (fen<0) 
					   fen=59; 					   
					   sprintf(temp,"%.2d",miao);
				       write_string(9,1,temp);
					   sprintf(temp+3,"%.2d",fen);
					   write_string(6,1,temp+3);
					   sprintf(temp+6,"%.2d",shi);
					   write_string(3,1,temp+6);
					   write_com(0x80+0x47);
					   break;
				case 3:shi--;
					   if (shi<0) 
					   shi=23; 					  
					   sprintf(temp,"%.2d",miao);
				       write_string(9,1,temp);
					   sprintf(temp+3,"%.2d",fen);
					   write_string(6,1,temp+3);
					   sprintf(temp+6,"%.2d",shi);
					   write_string(3,1,temp+6);
					   write_com(0x80+0x44);
					   break;
		    }	
		}
	}		
	if(key4==0)
	{
		delayms(10);//消抖
		if(key4==0)
		{
			jiao=0;
			while(!key4);//等待松手
			jiao=1;
		}
	}
}			 