#include"key.h"
#include"delay.h"
#include  "led.h"

char temp=0;
bit flag_key1=0;


void key(void)
{
	if(key1==0)
	{
		delayms(10);
		if(key1==0)
		{
			jiao=0;
			while(!key1);
			jiao=1;
			led1=0; 
			TR0=~TR0;
			flag_key1=~flag_key1;



		
		}	 
	}
	if (key2==0)
	{
		delayms(10);
		if(key2==0)
		{
			jiao=0;
			while(!key2);
			jiao=1;
			led2=0;
			fen=0;
			miao=0;

		}
	}
	if(flag_key1==1)
	{	
		if(key3==0)
		{
			delayms(10);
			if(key3==0)
			{
				jiao=0;
				while(!key3);
				jiao=1;
				led3=0;	  
				miao++;
				if(miao>=60)
				{	
					miao=0;
					fen++;
					if(fen>=60)
					{
						fen=0;
					}
				}
			}
		}
	}	
	if(flag_key1==1)
	{	
		if(key4==0)
		{
			delayms(10);
			if(key4==0)
			{
				jiao=0;
				while(!key4);
				jiao=1;
				led4=0;	  
				miao--;
				if(miao<0)
				{	
					miao=59;
					fen--;
					if(fen<0)
					{
						fen=59;
					}
				}
			}
		}
	}	
}			 