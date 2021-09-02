#include"common.h"
#include"delay.h"
#include <intrins.h>


void main(void)
{
	P0=0xfe;
	while(1)
	{

		P0=_crol_(P0,1);
		delayms(20);
	}
}