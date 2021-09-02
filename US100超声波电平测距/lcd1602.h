#ifndef  __lcd1602_h_
#define  __lcd1602_h_
#include "common.h"


#define DATAPORT P0
sbit rs=P3^5;
sbit rw=P3^6;
sbit en=P3^7;

void write_com(uchar com);
void write_data(uchar dat);
void init_lcd1602(void);
void write_char(uchar x,uchar y,char z);
void write_string(uchar x,uchar y,char *z);
void display_distance(ulong number);



#endif