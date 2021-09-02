#ifndef  __key_h_
#define  __key_h_
#include "common.h"
sbit key1=P2^0;
sbit key2=P2^2;
sbit key3=P2^1;
sbit key4=P2^3;
sbit jiao=P3^4;
void key(void);
extern char temp;
extern char miao,fen;




#endif