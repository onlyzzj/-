#include "oled.h"
#include "IIC.h"
#include "bmp.h"
#include "delay.h"





//OLED写数据
void OLED_WrDat(uchar IIC_Data)
{
	Single_WriteIIC(0x78,0x40,IIC_Data);       //0x78是OLED设备地址,0x40是OLED上的数据寄存器地址
}




//OLED写命令
void OLED_WrCmd(uchar IIC_Command)
{
	Single_WriteIIC(0x78,0x00,IIC_Command);    //0x78是OLED设备地址,0x00是OLED上的命令寄存器地址
}





//OLED设置坐标    x的范围0～127，y为页范围0～7
void OLED_Set_Pos(uchar x,uchar y) 
{ 
	OLED_WrCmd(0xb0+y);               //设置页地址
	OLED_WrCmd(((x&0xf0)>>4)|0x10);   //设置列地址的高4位
	OLED_WrCmd((x&0x0f)|0x00);        //设置列地址的低4位
}






//OLED清屏
void OLED_Clear(void)
{
	uchar x,y;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x00);
		OLED_WrCmd(0x10);
		for(x=0;x<128;x++)
		OLED_WrDat(0x00);
	}
}




//OLED全屏      0x00:清屏（0时熄灭）   0xff:全亮（1时点亮）
void OLED_Fill(uchar bmp_dat) 
{
	uchar x,y;
	for(y=0;y<8;y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x00);
		OLED_WrCmd(0x10);
		for(x=0;x<128;x++)
		OLED_WrDat(bmp_dat);
	}
}





//OLED初始化
void OLED_Init(void)
{
	delayms(500);                //初始化之前的延时很重要！
	OLED_WrCmd(0xae);            //关闭OLED显示
	OLED_WrCmd(0x00);            //设置显示时的起始列地址低4位
	OLED_WrCmd(0x10);            //设置显示时的起始列地址高4位
	OLED_WrCmd(0x40);            //[5:0]设置显示时的起始行地址,行数0~63
	OLED_WrCmd(0x81);            //设置对比度
	OLED_WrCmd(Brightness);      //设置的对比度的值，值越大屏幕就越亮
	OLED_WrCmd(0xa1);            //设置段重映射,bit0:0,0->0;1,0->127;     0xa0左右反置 0xa1正常
	OLED_WrCmd(0xc8);            //设置COM输出扫描方向                    0xc0上下反置 0xc8正常
	OLED_WrCmd(0xa6);            //设置正常显示
	OLED_WrCmd(0xa8);            //设置驱动路数
	OLED_WrCmd(0x3f);            //默认0X3F(1/64)
	OLED_WrCmd(0xd3);            //设置显示偏移
	OLED_WrCmd(0x00);            //默认为0
	OLED_WrCmd(0xd5);            //设置时钟分频因子,震荡频率
	OLED_WrCmd(0x80);            //[3:0],分频因子;[7:4],震荡频率     设置时钟为100帧/秒
	OLED_WrCmd(0xd9);            //设置预充电周期
	OLED_WrCmd(0xf1);            //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WrCmd(0xda);            //设置COM硬件引脚配置
	OLED_WrCmd(0x12);            //[5:4]配置
	OLED_WrCmd(0xdb);            //设置VCOMH 电压倍率
	OLED_WrCmd(0x40);            //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	OLED_WrCmd(0x20);            //设置内存地址模式
	OLED_WrCmd(0x02);            //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
	OLED_WrCmd(0x8d);            //设置电荷泵启用/禁用
	OLED_WrCmd(0x14);            //0x14:开启电荷泵  0x10:关闭电荷泵，这个必须设置为0x14
	OLED_WrCmd(0xa4);            //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)(0xa5/0xa4)
	OLED_WrCmd(0xa6);            //0xa6:全屏正显   0xa7:全屏反显
	OLED_WrCmd(0xaf);            //开启OLED显示
	OLED_Clear();            		 //OLED清屏
}




//功能描述：绘制一个点（x,y）
//参数：x的范围0～127，y的范围0～63
void OLED_PutPixel(uchar x,uchar y)
{
	uchar temp;
	temp=1<<(y%8); 	
	OLED_WrCmd(0xb0+(y/8));
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x00);
	OLED_WrDat(temp); 	 	
}





//功能描述：绘制一个实心矩形
//参数：左上角坐标（x1,y1）,右下角坐标（x2，y2);其中x1、x2的范围0～127，y1、y2的范围0～63
void OLED_Rectangle(uchar x1,uchar y1,uchar x2,uchar y2)
{
	uchar i,j; 
	if(y1/8==y2/8)
	{
		for(i=x1;i<=x2;i++)
		{
			OLED_Set_Pos(i,y1/8);
			OLED_WrDat((0xff<<(y1%8))&(0xff>>7-y2%8)); 			
		}
	}
	else
	{
		for(i=x1;i<=x2;i++)
		{
			OLED_Set_Pos(i,y1/8);
			OLED_WrDat(0xff<<(y1%8)); 			
		}
		for(j=(y1/8)+1;j<y2/8;j++)
			for(i=x1;i<=x2;i++)
			{
				OLED_Set_Pos(i,j);
				OLED_WrDat(0xff);
			}
		for(i=x1;i<=x2;i++)
		{
			OLED_Set_Pos(i,y2/8);
			OLED_WrDat(0xff>>7-y2%8); 			
		}
	}
}  





//功能描述：显示6*8一组标准ASCII字符串(6为宽度，8为高度)
//参数：显示的坐标（x,y），x的范围0～127，y为页范围0～7
void OLED_F6x8Str(uchar x,uchar y,uchar ch[])
{
	uchar c=0,i=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-32;
		if(x>122)
		{
			x=0;
			y++;
		}
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		{
			OLED_WrDat(F6x8[c][i]);
		}
		x+=6;
		j++;
	}
}








//功能描述：显示8*16一组标准ASCII字符串(8为宽度，16为高度)
//参数：显示的坐标（x,y），x的范围0～127，y为页范围0～7
void OLED_F8x16Str(uchar x,uchar y,uchar ch[])
{
	uchar c=0,i=0,j=0;
	while(ch[j]!='\0')
	{
		c=ch[j]-32;
		if(x>120)
		{
			x=0;
			y++;
		}
		OLED_Set_Pos(x,y);
		for(i=0;i<8;i++)
		{
			OLED_WrDat(F8x16[c][i]);
		}
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		{
			OLED_WrDat(F8x16[c][i+8]);
		}
		x+=8;
		j++;
	}
}






//功能描述：显示16*16一个标准汉字(16为宽度，16为高度)
//参数：显示的坐标（x,y），x的范围0～127，y为页范围0～7
void OLED_F16x16Ch(uchar x,uchar y,uchar c)
{
	uchar i=0;
	if(x>112)
	{
		x=0;
		y++;
	}
	OLED_Set_Pos(x,y);
	for(i=0;i<16;i++)
	{
		OLED_WrDat(F16x16[c][i]);
	}
	OLED_Set_Pos(x,y+1);
	for(i=0;i<16;i++)
	{
		OLED_WrDat(F16x16[c][i+16]);
	} 	  	
}





//功能描述：显示BMP图片
//参数：图片左上角坐标（x1,y1）,右下角坐标（x2，y2);其中x1、x2的范围0～127，y1、y2为页的范围0～7
void OLED_BMP(uchar x1,uchar y1,uchar x2,uchar y2,uchar BMP[])
{
	uint j=0;
	uchar x,y;
	for(y=y1;y<=y2;y++)
	{
		OLED_Set_Pos(x1,y);
    for(x=x1;x<=x2;x++)
	  {      
			OLED_WrDat(BMP[j++]);
	  }
	}
}





////功能描述：显示6*8一组标准ASCII字符串(6为宽度，8为高度)
////参数：显示的坐标（x,y），x的范围0～127，y为页范围0～7
//void OLED_D6x8Str(uchar x,uchar y,uchar ch[])
//{
//	uchar c=0,i=0,j=0;
//	while(ch[j]!='\0')
//	{
//		c=ch[j]-32;
//		if(x>122)
//		{
//			x=0;
//			y++;
//		}
//		OLED_Set_Pos(x,y);
//		for(i=0;i<6;i++)
//		{
//			OLED_WrDat(D6x8[c*6+i]);
//		}
//		x+=6;
//		j++;
//	}
//}










////功能描述：显示8*16一组标准ASCII字符串(8为宽度，16为高度)
////参数：显示的坐标（x,y），x的范围0～127，y为页范围0～7
//void OLED_D8x16Str(uchar x,uchar y,uchar ch[])
//{
//	uchar c=0,i=0,j=0;
//	while(ch[j]!='\0')
//	{
//		c =ch[j]-32;
//		if(x>120)
//		{
//			x=0;
//			y++;
//		}
//		OLED_Set_Pos(x,y);
//		for(i=0;i<8;i++)
//		{
//			OLED_WrDat(D8x16[c*16+i]);
//		}
//		OLED_Set_Pos(x,y+1);
//		for(i=0;i<8;i++)
//		{
//			OLED_WrDat(D8x16[c*16+i+8]);
//		}
//		x+=8;
//		j++;
//	}
//}
