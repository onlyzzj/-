#include"delay.h"
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=11;j>0;j--);
}

