#include "delay.h"
#include "us100.h"
#include "lcd1602.h"






void main(void)
{
	ulong num;
	init_lcd1602();
	while(1)
	{
		num=Dianping_distance();
		display_distance(num);
		delayms(500);
	}
}



