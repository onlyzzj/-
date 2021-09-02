#include "common.h"
#include "lcd1602.h"
#include "IIC.h"
#include "change.h"


//��ʼ��MPU6050
void init_MPU6050(void)
{
	Single_WriteIIC(PWR_MGMT_1,0x00);//�������״̬
	Single_WriteIIC(SMPLRT_DIV,0x07);
	Single_WriteIIC(CONFIG,0x06);
	Single_WriteIIC(GYRO_CONFIG,0x18);
	Single_WriteIIC(ACCEL_CONFIG,0x01);
}


void main()
{ 			
	init_lcd1602();//Һ����ʼ��
	init_MPU6050();//��ʼ��MPU6050
	while(1)
	{
		display(2,0,hecheng_data(ACCEL_XOUT_H));//��ʾX����ٶ�
		display(7,0,hecheng_data(ACCEL_YOUT_H));//��ʾY����ٶ�
		display(12,0,hecheng_data(ACCEL_ZOUT_H));//��ʾZ����ٶ�
		display(2,1,hecheng_data(GYRO_XOUT_H));//��ʾX����ٶ�
		display(7,1,hecheng_data(GYRO_YOUT_H));//��ʾY����ٶ�
		display(12,1,hecheng_data(GYRO_ZOUT_H));//��ʾZ����ٶ�
	}
}