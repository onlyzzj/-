#ifndef  __lcd12864_h_
#define  __lcd12864_h_
#include "common.h"
#define DATAPORT P0


sbit rs=P3^5;
sbit rw=P3^6;
sbit en=P3^7;
sbit PSB=P3^1;
//sbit beiguang=P3^7;


void write_com(uchar com);
void write_data(uchar dat);
void init_lcd12864(void);
void display_bmp(uchar *address);
void clear_bmp_RAM();



#endif