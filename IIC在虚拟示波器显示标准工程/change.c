#include "change.h"
#include "IIC.h"


//��������ת��Ϊ�ַ�����(�ַ���)
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



//�ϳ�����
int hecheng_data(uchar address)
{
	char H,L;
	H=Single_ReadIIC(address);
	L=Single_ReadIIC(address+1);
	return (H<<8)+L;   //�ϳ�����
}