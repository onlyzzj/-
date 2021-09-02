#include "common.h"
#include "led.h"
#include "key.h"
#include"delay.h"




static  uchar i;
void main (void)
{
	while(1)
	{
//		shumaguan__dt();
//		shumaguan__dtx(temp);
//		key();
		for(i=0;i<60;i++)
		{
			shumaguan__dtx(i); 
			delayms(500);	
		}
	}
}	