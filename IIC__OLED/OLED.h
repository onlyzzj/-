#ifndef  __oled_h_
#define  __oled_h_
#include "common.h"  


#define	Brightness	0xCF //设置的对比度的值，值越大屏幕就越亮



void OLED_WrDat(uchar IIC_Data);
void OLED_WrCmd(uchar IIC_Command);
void OLED_Set_Pos(uchar x,uchar y);
void OLED_Clear(void);
void OLED_Fill(uchar bmp_dat);
void OLED_Init(void);
void OLED_PutPixel(uchar x,uchar y);
void OLED_Rectangle(uchar x1,uchar y1,uchar x2,uchar y2);
void OLED_F6x8Str(uchar x,uchar y,uchar ch[]);
void OLED_F8x16Str(uchar x,uchar y,uchar ch[]);
void OLED_F16x16Ch(uchar x,uchar y,uchar c);
void OLED_BMP(uchar x1,uchar y1,uchar x2,uchar y2,uchar BMP[]);
//void OLED_D6x8Str(uchar x,uchar y,uchar ch[]);
//void OLED_D8x16Str(uchar x,uchar y,uchar ch[]);
	


#endif