#include "lcd1602.h"
#include "wenshidu.h"
#include "math.h"
#include "delay.h"

uchar shidu_shi,shidu_ge,shidu_xs1,shidu_xs2,wendu_shi,wendu_ge,wendu_xs1,wendu_xs2;


void main(void)
{
	init_lcd1602();
	write_string(0,0,"shidu:");
	write_string(0,1,"wendu:");
	while(1)
	{
		wenshidu();
		shidu_shi=0x30+math(RH_data_H)/10;   //或shidu_shi=0x30+RH_data_H/10
		shidu_ge=0x30+math(RH_data_H)%10;    //或shidu_ge=0x30+RH_data_H%10
		shidu_xs1=0x30+math(RH_data_L)/10;   //或shidu_xs1=0x30+RH_data_L/10
		shidu_xs2=0x30+math(RH_data_L)%10;   //或shidu_xs2=0x30+RH_data_L%10
		wendu_shi=0x30+math(T_data_H)/10;    //或wendu_shi=0x30+T_data_H/10
		wendu_ge=0x30+math(T_data_H)%10;     //或wendu_ge=0x30+T_data_H%10
		wendu_xs1=0x30+math(T_data_L)/10;    //或wendu_xs1=0x30+T_data_L/10
		wendu_xs2=0x30+math(T_data_L)%10;    //或wendu_xs2=0x30+T_data_L%10
		write_char(6,0,shidu_shi);
		write_char(7,0,shidu_ge);
		write_string(8,0,".");
		write_char(9,0,shidu_xs1);
		write_char(10,0,shidu_xs2);
		write_char(6,1,wendu_shi);
		write_char(7,1,wendu_ge);
		write_string(8,1,".");
		write_char(9,1,wendu_xs1);
		write_char(10,1,wendu_xs2);
		delayms(500);
	}
}
	


