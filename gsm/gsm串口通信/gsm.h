#ifndef  __gsm_h_
#define  __gsm_h_

#include "common.h"


void send_chinese(void);
void send_english(void);
void checkenglish_sendenglish(void);
void checkenglish_sendchinese(void);
void checkchinese_sendenglish(void);
void checkchinese_sendchinese(void);
void send_call1(void);
void send_call2(void);
void send_over(void);
void Print_Char(uchar ch);
void Print_Str(uchar *str);
void clearBuff(void);
void led(int i);
void init_gsm(void);


extern uchar code ATE0[];
extern uchar code CREG_CMD[];
extern uchar code SMS_send[];
extern uchar code ATCN[];
extern uchar code CMGF0[];
extern uchar code CMGF1[];
extern uchar code CMGR[];
extern uchar code CMGD[];
extern uchar  aa[];
extern uchar j;


#endif