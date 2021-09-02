#ifndef __led_H__
#define __led_H__
#include "common.h"                      
sbit led=P0^6;
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


#endif