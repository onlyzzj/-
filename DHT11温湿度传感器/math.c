#include "math.h"


//��������ת��Ϊʮ������
uchar math(uchar a)
{
	uchar num=0,i;
	uint j=1;
	for(i=0;i<8;i++)
	{
		num+=(a&0x01)*j;
		a>>=1;
		j*=2;
	}
	return num;
}


