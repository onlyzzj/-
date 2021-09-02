#include"key.h"
#include"delay.h"


char temp=2;
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
//			P0=0xaa;
			temp ++;
			if(temp>=60)
				temp=0; 

		
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
			temp--;
			if(temp<0)
				temp=59;

		}
	}
	if(key3==0)
	{
		delayms(10);
		if(key3==0)
		{
			jiao=0;
			while(!key3);
			jiao=1;
			temp=0;

		}
	}
}			 