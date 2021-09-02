#include "change.h"
#include "IIC.h"


//整数类型转化为字符类型(字符串)
void change(uchar *s,int temp)
{
	if(temp<0)
	{
		temp=-temp;
		*s='-';
	}
	else
	{
		*s=' ';
	}
	*++s =temp/100+0x30;
	temp=temp%100;
	*++s =temp/10+0x30;
	temp=temp%10;
	*++s =temp+0x30; 	
}



//合成数据
int hecheng_data(uchar address)
{
	char H,L;
	H=Single_ReadIIC(address);
	L=Single_ReadIIC(address+1);
	return (H<<8)+L;   //合成数据
}