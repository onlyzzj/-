#include "com.h"
#include"delay.h"


void Print_Char(uchar ch)//���͵����ַ�
{
    SBUF=ch; //���뻺����
    while(TI!=1); //�ȴ��������
    TI=0; //�������
}


void Print_Str(uchar *str)//�����ַ���
{
	while(*str!='\0')
    {
        Print_Char(*str);
        delayms(2);
        str++;
    }

}