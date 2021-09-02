#ifndef __led_H__
#define __led_H__
#include "common.h"                      
sbit led=P0^0;
sbit led1=P0^1;
sbit led2=P0^4;
sbit led3=P0^7;
sbit led4=P0^3;
sbit wei1=P2^7;
sbit wei2=P2^6;
sbit wei3=P2^5;
sbit wei4=P2^4;
#define duanxuan P1
void diyigeliang(void);
void shanshuo1(void);
void shanshuo2(void);
void shanshuo3(void);
void shanshuo4(void);
void liushuideng1(void);
void liushuideng2(void);
void shumaguan__jt(void);
void shumaguan__dt(void);
void shumaguan__dtx(uint num);
void miaobiao(uchar num1,uchar num2);


#endif