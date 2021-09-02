#include<reg52.h>
//#include<12864.h>
#include<intrins.h>
#include "common.h"
sbit DQ = P3^3;
sbit lcd_rs=P3^5;
sbit lcd_rw=P3^6;
sbit lcd_en=P3^7;
sbit lcd_psb=P3^1;                       //数据口define interface
uchar i;
uchar tab[]="现在温度:";
uint temp;                           //温度值 variable of temperature


/*************精确延时函数*****************/
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
此延时函数针对的是12Mhz的晶振
delay(0):延时518us 误差:518-2*256=6
delay(1):延时7us   （原帖写"5us"是错的）
delay(10):延时25us    误差:25-20=5
delay(20):延时45us    误差:45-40=5
delay(100):延时205us 误差:205-200=5
delay(200):延时405us 误差:405-400=5
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
void Init_Ds18b20(void)     //DS18B20初始化send reset and initialization command
{
DQ = 1;                     //DQ复位,不要也可行。
delay(1);                  //稍做延时
DQ = 0;                    //单片机拉低总线
delay(250);                //精确延时，维持至少480us
DQ = 1;                    //释放总线，即拉高了总线
delay(100);                //此处延时有足够,确保能让DS18B20发出存在脉冲。
}

uchar Read_One_Byte()       //读取一个字节的数据read a byte date
                            //读数据时,数据以字节的最低有效位先从总线移出
{
uchar i   = 0;
uchar dat = 0;
for(i=8;i>0;i--)
{
   DQ = 0;                  //将总线拉低，要在1us之后释放总线
                           //单片机要在此下降沿后的15us内读数据才会有效。
   _nop_();                //至少维持了1us,表示读时序开始
   dat >>= 1;               //让从总线上读到的位数据，依次从高位移动到低位。
   DQ = 1;                  //释放总线，此后DS18B20会控制总线,把数据传输到总线上
   delay(1);                 //延时7us,此处参照推荐的读时序图，尽量把控制器采样时间放到读时序后的15us内的最后部分
   if(DQ)                   //控制器进行采样
   {
    dat |= 0x80;            //若总线为1,即DQ为1,那就把dat的最高位置1;若为0,则不进行处理,保持为0
   }        
   delay(10);               //此延时不能少，确保读时序的长度60us。
}
return (dat);
}

void Write_One_Byte(uchar dat)
{
uchar i = 0;
for(i=8;i>0;i--)
{
   DQ = 0;                        //拉低总线
   _nop_();                       //至少维持了1us,表示写时序(包括写0时序或写1时序)开始
   DQ = dat&0x01;                 //从字节的最低位开始传输
                                 //指令dat的最低位赋予给总线,必须在拉低总线后的15us内,
                                 //因为15us后DS18B20会对总线采样。
   delay(10);                     //必须让写时序持续至少60us
   DQ = 1;                        //写完后,必须释放总线,
   dat >>= 1;
   delay(1);
}
}


uint Get_Tmp()                   //获取温度get the temperature
{
float tt;
uchar a,b;
Init_Ds18b20();                //初始化
Write_One_Byte(0xcc);          //忽略ROM指令
Write_One_Byte(0x44);          //温度转换指令
Init_Ds18b20();                 //初始化
Write_One_Byte(0xcc);          //忽略ROM指令
Write_One_Byte(0xbe);          //读暂存器指令
a = Read_One_Byte();           //读取到的第一个字节为温度LSB
b = Read_One_Byte();           //读取到的第一个字节为温度MSB
temp = b;                      //先把高八位有效数据赋于temp
temp <<= 8;                    //把以上8位数据从temp低八位移到高八位
temp = temp|a;                //两字节合成一个整型变量
tt = temp*0.0625;              //得到真实十进制温度值
                                //因为DS18B20可以精确到0.0625度
                                //所以读回数据的最低位代表的是0.0625度
temp = tt*10+0.5;               //放大十倍
                                //这样做的目的将小数点后第一位也转换为可显示数字
                                //同时进行一个四舍五入操作。
return temp;
}


/****************数码码动态显示函数**************/

void Display(uint temp)   //显示程序
{
uchar A1,A2,A3;
A1 = temp/100;    //百位
A2 = temp%100/10;   //十位
A3 = temp%10;    //个位

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
date12864(0xa1);//161号ASCII码
date12864(0xe6);//230号ASCII码
while(1)
{
     Display(Get_Tmp());
   }
}

