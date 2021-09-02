#include "oled.h"
#include "delay.h"
#include "bmp.h"  




void main(void)
{
	OLED_Init();
	while(1)
	{
//		OLED_PutPixel(127,3);
//		OLED_Rectangle(1,58,126,60);
//		OLED_F6x8Str(122,2,"\\");
		OLED_F8x16Str(120,2,"000000");
//		OLED_F16x16Ch(112,2,2);
//		OLED_BMP(0,0,127,7,BMP2);
//		OLED_D6x8Str(122,2,"\\");
//		OLED_D8x16Str(120,2,"000000");
	}
}
