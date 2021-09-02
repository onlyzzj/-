#include"key.h"
#include"delay.h"
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
			P0=0xaa;

		
		}	 
	}
}			 