#include<reg52.h>
//#include<12864.h>
#include<intrins.h>
#include "common.h"
sbit DQ = P3^3;
sbit lcd_rs=P3^5;
sbit lcd_rw=P3^6;
sbit lcd_en=P3^7;
sbit lcd_psb=P3^1;                       //���ݿ�define interface
uchar i;
uchar tab[]="�����¶�:";
uint temp;                           //�¶�ֵ variable of temperature


/*************��ȷ��ʱ����*****************/
void delay(unsigned char i) 
{
while(--i); 
}
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

/******************************************
����ʱ������Ե���12Mhz�ľ���
delay(0):��ʱ518us ���:518-2*256=6
delay(1):��ʱ7us   ��ԭ��д"5us"�Ǵ�ģ�
delay(10):��ʱ25us    ���:25-20=5
delay(20):��ʱ45us    ���:45-40=5
delay(100):��ʱ205us ���:205-200=5
delay(200):��ʱ405us ���:405-400=5
*******************************************/

/*****************DS18B20******************/
void com12864(uchar cmd)
{
	lcd_rs=0;
	lcd_rw=0;
	lcd_en=0;
	P0=cmd;
	delayms(5);
	lcd_en=1;
	delayms(5);
	lcd_en=0;
}
void date12864(uchar dat)
{
	lcd_rs=1;
	lcd_rw=0;
	lcd_en=0;
	P0=dat;
	delayms(5);
	lcd_en=1;
	delayms(5);
	lcd_en=0;
}
//void lcd_pos(uchar x,uchar y)
//{
//	uchar pos;
//	if(x==0)
//	{
//		y=0x80;
//	}
//	else if(x==1)
//	{
//		y=0x90;
//	}
//	else if(x==2)
//	{
//		y=0x88;
//	}
//	else if(x==3)
//	{
//		y=0x98;
//	}
//	pos=x+y;
//	com12864(pos);
//}
void init12864()
{
	lcd_psb=1;
	com12864(0x30);
	delayms(5);
	com12864(0x0c);
	delayms(5);
	com12864(0x01);
	delayms(5);
}
void Init_Ds18b20(void)     //DS18B20��ʼ��send reset and initialization command
{
DQ = 1;                     //DQ��λ,��ҪҲ���С�
delay(1);                  //������ʱ
DQ = 0;                    //��Ƭ����������
delay(250);                //��ȷ��ʱ��ά������480us
DQ = 1;                    //�ͷ����ߣ�������������
delay(100);                //�˴���ʱ���㹻,ȷ������DS18B20�����������塣
}

uchar Read_One_Byte()       //��ȡһ���ֽڵ�����read a byte date
                            //������ʱ,�������ֽڵ������Чλ�ȴ������Ƴ�
{
uchar i   = 0;
uchar dat = 0;
for(i=8;i>0;i--)
{
   DQ = 0;                  //���������ͣ�Ҫ��1us֮���ͷ�����
                           //��Ƭ��Ҫ�ڴ��½��غ��15us�ڶ����ݲŻ���Ч��
   _nop_();                //����ά����1us,��ʾ��ʱ��ʼ
   dat >>= 1;               //�ô������϶�����λ���ݣ����δӸ�λ�ƶ�����λ��
   DQ = 1;                  //�ͷ����ߣ��˺�DS18B20���������,�����ݴ��䵽������
   delay(1);                 //��ʱ7us,�˴������Ƽ��Ķ�ʱ��ͼ�������ѿ���������ʱ��ŵ���ʱ����15us�ڵ���󲿷�
   if(DQ)                   //���������в���
   {
    dat |= 0x80;            //������Ϊ1,��DQΪ1,�ǾͰ�dat�����λ��1;��Ϊ0,�򲻽��д���,����Ϊ0
   }        
   delay(10);               //����ʱ�����٣�ȷ����ʱ��ĳ���60us��
}
return (dat);
}

void Write_One_Byte(uchar dat)
{
uchar i = 0;
for(i=8;i>0;i--)
{
   DQ = 0;                        //��������
   _nop_();                       //����ά����1us,��ʾдʱ��(����д0ʱ���д1ʱ��)��ʼ
   DQ = dat&0x01;                 //���ֽڵ����λ��ʼ����
                                 //ָ��dat�����λ���������,�������������ߺ��15us��,
                                 //��Ϊ15us��DS18B20������߲�����
   delay(10);                     //������дʱ���������60us
   DQ = 1;                        //д���,�����ͷ�����,
   dat >>= 1;
   delay(1);
}
}


uint Get_Tmp()                   //��ȡ�¶�get the temperature
{
float tt;
uchar a,b;
Init_Ds18b20();                //��ʼ��
Write_One_Byte(0xcc);          //����ROMָ��
Write_One_Byte(0x44);          //�¶�ת��ָ��
Init_Ds18b20();                 //��ʼ��
Write_One_Byte(0xcc);          //����ROMָ��
Write_One_Byte(0xbe);          //���ݴ���ָ��
a = Read_One_Byte();           //��ȡ���ĵ�һ���ֽ�Ϊ�¶�LSB
b = Read_One_Byte();           //��ȡ���ĵ�һ���ֽ�Ϊ�¶�MSB
temp = b;                      //�ȰѸ߰�λ��Ч���ݸ���temp
temp <<= 8;                    //������8λ���ݴ�temp�Ͱ�λ�Ƶ��߰�λ
temp = temp|a;                //���ֽںϳ�һ�����ͱ���
tt = temp*0.0625;              //�õ���ʵʮ�����¶�ֵ
                                //��ΪDS18B20���Ծ�ȷ��0.0625��
                                //���Զ������ݵ����λ�������0.0625��
temp = tt*10+0.5;               //�Ŵ�ʮ��
                                //��������Ŀ�Ľ�С������һλҲת��Ϊ����ʾ����
                                //ͬʱ����һ���������������
return temp;
}


/****************�����붯̬��ʾ����**************/

void Display(uint temp)   //��ʾ����
{
uchar A1,A2,A3;
A1 = temp/100;    //��λ
A2 = temp%100/10;   //ʮλ
A3 = temp%10;    //��λ

com12864(0x80+5);
date12864(0x30+A1);
date12864(0x30+A2);
date12864('.');
date12864(0x30+A3);

}


void main()
{
init12864();
com12864(0x80);
for(i=0;i<9;i++)
{
	date12864(tab[i]);
}
com12864(0x80+7);
date12864(0xa1);//161��ASCII��
date12864(0xe6);//230��ASCII��
while(1)
{
     Display(Get_Tmp());
   }
}

