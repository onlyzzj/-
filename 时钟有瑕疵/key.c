#include"key.h"
#include"delay.h"
#include "lcd1602.h"
#include <stdio.h>

uchar xri;
uchar key1num=0;
uchar key4num=0;
uchar flag=-1;
uchar temp[40];
int miao=56,fen=59,shi=6,nian=19,yue=12,ri=22;
int xmiao=0,xfen=0,xshi=0;
int x=0,y=0,z=0;



void key(void)
{
	if(key1==0)//调节时间功能键
	{
		delayms(10);//消抖
		if(key1==0)
		{
//			jiao=0;
			while(!key1);//等待松手
			jiao=1;
			key1num++;
			if(key1num>=7)
				key1num=0;
			if(key4num==0)
			{
				switch(key1num)
				{
					case 0: TR0=1; write_com(0x0c); break;
					case 1: TR0=0; write_com(0x0f); write_com(0x80+0x4b); break;
					case 2: write_com(0x80+0x48); break;			
				 	case 3: write_com(0x80+0x45); break;
					case 4: write_com(0x80+0x05); break;			
				 	case 5: write_com(0x80+0x08); break;
					case 6: write_com(0x80+0x0b); break;
				}
			}
			if(key4num==1)
			{
				switch(key1num)
				{
					case 0: TR0=1; write_com(0x0c); break;
					case 1: write_com(0x0f); write_com(0x80+0x4b); break;
					case 2: write_com(0x80+0x48); break;			
				 	case 3: write_com(0x80+0x45); break;
					case 4: write_com(0x80+0x05); break;			
				 	case 5: write_com(0x80+0x08); break;
					case 6: write_com(0x80+0x0b); break;
				}
			}
		}	 
	}
	if(key4==0)//调节闹钟功能键
	{
		delayms(10);//消抖
		if(key4==0)
		{
//			jiao=0;
			while(!key4);//等待松手
			jiao=1;
			key4num++;
			if(key4num>1)
				key4num=0;
		}	 
	}
	if (key2==0)//时间加
	{
		delayms(10);//消抖
		if(key2==0)
		{
//			jiao=0;
			while(!key2);//等待松手
			jiao=1;
			if(key4num==0)
			{
				switch (key1num)
				{
					case 1:miao++;
						   if (miao>=60) 
						   miao=0; 
						   sprintf(temp,"%02d",miao);
					       write_string(10,1,temp);
						   write_com(0x80+0x4b);
						   break;
					case 2:fen++;
						   if (fen>=60) 
						   fen=0; 					   
						   sprintf(temp+3,"%02d",fen);
						   write_string(7,1,temp+3);
						   write_com(0x80+0x48);
						   break;
					case 3:shi++;
						   if (shi>=24) 
						   shi=0; 					  
						   sprintf(temp+6,"%02d",shi);
						   write_string(4,1,temp+6);
						   write_com(0x80+0x45);
						   break;
	            	case 4:nian++;
						   sprintf(temp+9,"%04d",nian);
						   write_string(2,0,temp+9);
						   write_com(0x80+0x05);
						   break;
					case 5:yue++;
						   if (yue>12) 
						   yue=1;
					       sprintf(temp+12,"%02d",yue);
						   write_string(7,0,temp+12);
						   write_com(0x80+0x08);
						   break;
					case 6:if((nian%400==0)||(nian%4==0&&nian%100!=0))
					       {
						   		if(yue==2) xri=29;
						   }
						   else
						   {
						   	    if(yue==2) xri=28;
						   }
						   if(yue==1||yue==3||yue==5||yue==7||yue==8||yue==10||yue==12) xri=31;
						   if(yue==4||yue==6||yue==9||yue==11) xri=30;	 
						   ri++;	
						   if (ri>xri) 
						   ri=1; 					  
				           sprintf(temp+15,"%02d",ri);
				           write_string(10,0,temp+15);
						   write_com(0x80+0x0b);
						   break;		
		 	    }
			}
			if(key4num==1)
			{
	        	switch (key1num)
				{
					case 1:xmiao++;
						   if (xmiao>=60) 
						   xmiao=0; 
						   sprintf(temp+18,"%02d",xmiao);
					       write_string(10,1,temp+18);
						   write_com(0x80+0x4b);
						   break;
					case 2:xfen++;
						   if (xfen>=60) 
						   xfen=0; 					   
						   sprintf(temp+21,"%02d",xfen);
						   write_string(7,1,temp+21);
						   write_com(0x80+0x48);
						   break;
					case 3:xshi++;
						   if (xshi>=24) 
						   xshi=0; 					  
						   sprintf(temp+24,"%02d",xshi);
						   write_string(4,1,temp+24);
						   write_com(0x80+0x45);
						   break;
	            	case 4:z++;
						   if(z>=24)
						   z=0;
						   sprintf(temp+27,"%02d",z);
						   write_string(4,0,temp+27);
						   write_com(0x80+0x05);
						   break;
					case 5:y++;
						   if (y>=60) 
						   y=0;
					       sprintf(temp+30,"%02d",y);
						   write_string(7,0,temp+30);
						   write_com(0x80+0x08);
						   break;
					case 6:x++;	
						   if (x>=60) 
						   x=0; 					  
				           sprintf(temp+33,"%02d",x);
				           write_string(10,0,temp+33);
						   write_com(0x80+0x0b);
						   break;		
		 	    }
			}	
		 }
	}
	if(key3==0)//时间减
	{
		delayms(10);//消抖
		if(key3==0)
		{
//			jiao=0;
			while(!key3);//等待松手
			jiao=1;
			if(key4num==0)
			{
				switch (key1num)
				{
					case 1:miao--;
						   if (miao<0) 
						   miao=59; 
						   sprintf(temp,"%02d",miao);
					       write_string(10,1,temp);
						   write_com(0x80+0x4b);
						   break;
					case 2:fen--;
						   if (fen<0) 
						   fen=59; 					   
						   sprintf(temp+3,"%02d",fen);
						   write_string(7,1,temp+3);
						   write_com(0x80+0x48);
						   break;
					case 3:shi--;
						   if (shi<0) 
						   shi=23; 					  
						   sprintf(temp+6,"%02d",shi);
						   write_string(4,1,temp+6);
						   write_com(0x80+0x45);
						   break;
				    case 4:nian--;
						   sprintf(temp+9,"%04d",nian);
						   write_string(2,0,temp+9);
						   write_com(0x80+0x05);
						   break;
					case 5:yue--;
						   if (yue<1) 
						   yue=12; 					   
					       sprintf(temp+12,"%02d",yue);
						   write_string(7,0,temp+12);
						   write_com(0x80+0x08);
						   break;
					case 6:if((nian%400==0)||(nian%4==0&&nian%100!=0))
					       {
						   		if(yue==2) xri=29;
						   }
						   else
						   {
						   	    if(yue==2) xri=28;
						   }
						   if(yue==1||yue==3||yue==5||yue==7||yue==8||yue==10||yue==12) xri=31;
						   if(yue==4||yue==6||yue==9||yue==11) xri=30;
						   ri--;
						   if (ri<1) 
						   ri=xri; 					  
				           sprintf(temp+15,"%02d",ri);
				           write_string(10,0,temp+15);
						   write_com(0x80+0x0b);
						   break;		
			    }
			}
			if(key4num==1)
			{
				switch (key1num)
				{
					case 1:xmiao--;
						   if (xmiao<0) 
						   xmiao=59; 
						   sprintf(temp+18,"%02d",xmiao);
					       write_string(10,1,temp+18);
						   write_com(0x80+0x4b);
						   break;
					case 2:xfen--;
						   if (xfen<0) 
						   xfen=59; 					   
						   sprintf(temp+21,"%02d",xfen);
						   write_string(7,1,temp+21);
						   write_com(0x80+0x48);
						   break;
					case 3:xshi--;
						   if (xshi<0) 
						   xshi=23; 					  
						   sprintf(temp+24,"%02d",xshi);
						   write_string(4,1,temp+24);
						   write_com(0x80+0x45);
						   break;
	            	case 4:z--;
						   if(z<0)
						   z=23;
						   sprintf(temp+27,"%02d",z);
						   write_string(4,0,temp+27);
						   write_com(0x80+0x05);
						   break;
					case 5:y--;
						   if (y<0) 
						   y=59;
					       sprintf(temp+30,"%02d",y);
						   write_string(7,0,temp+30);
						   write_com(0x80+0x08);
						   break;
					case 6:x--;	
						   if (x<0) 
						   x=59; 					  
				           sprintf(temp+33,"%02d",x);
				           write_string(10,0,temp+33);
						   write_com(0x80+0x0b);
						   break;		
		 	    }
			}
		}
	}
	if(key4num!=0)
		flag++;
	else
		flag=-1;		
}		






		 