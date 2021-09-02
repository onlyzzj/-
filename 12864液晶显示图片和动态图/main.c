#include "common.h"
#include "lcd12864.h"
#include "delay.h"
#include "bmp.h"


void main (void)
{
	init_lcd12864();
	while(1)
	{
		display_bmp(table1);
		delayms(500);
		display_bmp(table2);
		delayms(500);
		display_bmp(table3);
		delayms(500);
		display_bmp(table4);
		delayms(500);
		display_bmp(table5);
		delayms(500);
//		delayms(5000); 
//		clear_bmp_RAM();//Çå³ýRAMÇø 
	}
}



