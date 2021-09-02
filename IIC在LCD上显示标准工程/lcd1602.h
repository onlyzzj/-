#ifndef  __lcd1602_h_
#define  __lcd1602_h_
#include "common.h"

#define DATAPORT P0//LCD1602数据端口
sbit rs=P3^5;//LCD1602命令端口
sbit rw=P3^6;//LCD1602命令端口
sbit en=P3^7;//LCD1602命令端口

void write_com(uchar com);
void write_data(uchar dat);
void init_lcd1602(void);
void write_string(uchar x,uchar y,char *z);
void display(uchar x,uchar y,int value);



#endif