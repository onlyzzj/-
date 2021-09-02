#include "common.h"
#include "lcd1602.h"
#include "IIC.h"
#include "change.h"


//初始化MPU6050
void init_MPU6050(void)
{
	Single_WriteIIC(PWR_MGMT_1,0x00);//解除休眠状态
	Single_WriteIIC(SMPLRT_DIV,0x07);
	Single_WriteIIC(CONFIG,0x06);
	Single_WriteIIC(GYRO_CONFIG,0x18);
	Single_WriteIIC(ACCEL_CONFIG,0x01);
}


void main()
{ 			
	init_lcd1602();//液晶初始化
	init_MPU6050();//初始化MPU6050
	while(1)
	{
		display(2,0,hecheng_data(ACCEL_XOUT_H));//显示X轴加速度
		display(7,0,hecheng_data(ACCEL_YOUT_H));//显示Y轴加速度
		display(12,0,hecheng_data(ACCEL_ZOUT_H));//显示Z轴加速度
		display(2,1,hecheng_data(GYRO_XOUT_H));//显示X轴角速度
		display(7,1,hecheng_data(GYRO_YOUT_H));//显示Y轴角速度
		display(12,1,hecheng_data(GYRO_ZOUT_H));//显示Z轴角速度
	}
}