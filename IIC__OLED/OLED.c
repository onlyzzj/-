#include "oled.h"
#include "IIC.h"
#include "bmp.h"
#include "delay.h"





//OLEDд����
void OLED_WrDat(uchar IIC_Data)
{
	Single_WriteIIC(0x78,0x40,IIC_Data);       //0x78��OLED�豸��ַ,0x40��OLED�ϵ����ݼĴ�����ַ
}




//OLEDд����
void OLED_WrCmd(uchar IIC_Command)
{
	Single_WriteIIC(0x78,0x00,IIC_Command);    //0x78��OLED�豸��ַ,0x00��OLED�ϵ�����Ĵ�����ַ
}





//OLED��������    x�ķ�Χ0��127��yΪҳ��Χ0��7
void OLED_Set_Pos(uchar x,uchar y) 
{ 
	OLED_WrCmd(0xb0+y);               //����ҳ��ַ
	OLED_WrCmd(((x&0xf0)>>4)|0x10);   //�����е�ַ�ĸ�4λ
	OLED_WrCmd((x&0x0f)|0x00);        //�����е�ַ�ĵ�4λ
}






//OLED����
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




//OLEDȫ��      0x00:������0ʱϨ��   0xff:ȫ����1ʱ������
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





//OLED��ʼ��
void OLED_Init(void)
{
	delayms(500);                //��ʼ��֮ǰ����ʱ����Ҫ��
	OLED_WrCmd(0xae);            //�ر�OLED��ʾ
	OLED_WrCmd(0x00);            //������ʾʱ����ʼ�е�ַ��4λ
	OLED_WrCmd(0x10);            //������ʾʱ����ʼ�е�ַ��4λ
	OLED_WrCmd(0x40);            //[5:0]������ʾʱ����ʼ�е�ַ,����0~63
	OLED_WrCmd(0x81);            //���öԱȶ�
	OLED_WrCmd(Brightness);      //���õĶԱȶȵ�ֵ��ֵԽ����Ļ��Խ��
	OLED_WrCmd(0xa1);            //���ö���ӳ��,bit0:0,0->0;1,0->127;     0xa0���ҷ��� 0xa1����
	OLED_WrCmd(0xc8);            //����COM���ɨ�跽��                    0xc0���·��� 0xc8����
	OLED_WrCmd(0xa6);            //����������ʾ
	OLED_WrCmd(0xa8);            //��������·��
	OLED_WrCmd(0x3f);            //Ĭ��0X3F(1/64)
	OLED_WrCmd(0xd3);            //������ʾƫ��
	OLED_WrCmd(0x00);            //Ĭ��Ϊ0
	OLED_WrCmd(0xd5);            //����ʱ�ӷ�Ƶ����,��Ƶ��
	OLED_WrCmd(0x80);            //[3:0],��Ƶ����;[7:4],��Ƶ��     ����ʱ��Ϊ100֡/��
	OLED_WrCmd(0xd9);            //����Ԥ�������
	OLED_WrCmd(0xf1);            //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WrCmd(0xda);            //����COMӲ����������
	OLED_WrCmd(0x12);            //[5:4]����
	OLED_WrCmd(0xdb);            //����VCOMH ��ѹ����
	OLED_WrCmd(0x40);            //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	OLED_WrCmd(0x20);            //�����ڴ��ַģʽ
	OLED_WrCmd(0x02);            //[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	OLED_WrCmd(0x8d);            //���õ�ɱ�����/����
	OLED_WrCmd(0x14);            //0x14:������ɱ�  0x10:�رյ�ɱã������������Ϊ0x14
	OLED_WrCmd(0xa4);            //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)(0xa5/0xa4)
	OLED_WrCmd(0xa6);            //0xa6:ȫ������   0xa7:ȫ������
	OLED_WrCmd(0xaf);            //����OLED��ʾ
	OLED_Clear();            		 //OLED����
}




//��������������һ���㣨x,y��
//������x�ķ�Χ0��127��y�ķ�Χ0��63
void OLED_PutPixel(uchar x,uchar y)
{
	uchar temp;
	temp=1<<(y%8); 	
	OLED_WrCmd(0xb0+(y/8));
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x00);
	OLED_WrDat(temp); 	 	
}





//��������������һ��ʵ�ľ���
//���������Ͻ����꣨x1,y1��,���½����꣨x2��y2);����x1��x2�ķ�Χ0��127��y1��y2�ķ�Χ0��63
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





//������������ʾ6*8һ���׼ASCII�ַ���(6Ϊ��ȣ�8Ϊ�߶�)
//��������ʾ�����꣨x,y����x�ķ�Χ0��127��yΪҳ��Χ0��7
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








//������������ʾ8*16һ���׼ASCII�ַ���(8Ϊ��ȣ�16Ϊ�߶�)
//��������ʾ�����꣨x,y����x�ķ�Χ0��127��yΪҳ��Χ0��7
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






//������������ʾ16*16һ����׼����(16Ϊ��ȣ�16Ϊ�߶�)
//��������ʾ�����꣨x,y����x�ķ�Χ0��127��yΪҳ��Χ0��7
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





//������������ʾBMPͼƬ
//������ͼƬ���Ͻ����꣨x1,y1��,���½����꣨x2��y2);����x1��x2�ķ�Χ0��127��y1��y2Ϊҳ�ķ�Χ0��7
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





////������������ʾ6*8һ���׼ASCII�ַ���(6Ϊ��ȣ�8Ϊ�߶�)
////��������ʾ�����꣨x,y����x�ķ�Χ0��127��yΪҳ��Χ0��7
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










////������������ʾ8*16һ���׼ASCII�ַ���(8Ϊ��ȣ�16Ϊ�߶�)
////��������ʾ�����꣨x,y����x�ķ�Χ0��127��yΪҳ��Χ0��7
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
