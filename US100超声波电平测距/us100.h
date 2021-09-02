#ifndef  __us100_h_
#define  __us100_h_
#include "common.h"


sbit Trig_Pin = P2^4;
sbit Echo_Pin = P2^5;



void init_timer1(void);
ulong Dianping_distance(void);


#endif