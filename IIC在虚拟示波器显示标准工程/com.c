#include "com.h"
#include"delay.h"


void Print_Char(uchar ch)//发送单个字符
{
    SBUF=ch; //送入缓冲区
    while(TI!=1); //等待发送完毕
    TI=0; //软件清零
}


void Print_Str(uchar *str)//发送字符串
{
	while(*str!='\0')
    {
        Print_Char(*str);
        delayms(2);
        str++;
    }

}