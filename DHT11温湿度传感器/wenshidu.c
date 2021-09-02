#include "wenshidu.h"
#include "delay.h"



uchar comdata=0,flag,temp,RH_data_H_temp,RH_data_L_temp,T_data_H_temp,T_data_L_temp,check_data,check_data_temp,RH_data_H,RH_data_L,T_data_H,T_data_L;




void com(void)
{
	uchar i;
	for(i=0;i<8;i++)	   
	{
		//ÿһbit���ݶ���50us�͵�ƽʱ϶��ʼ
		flag=2;	
		while((!P2_0)&&flag++);//P2_0=1��flag������0ʱ�˳���ѭ��
		delay10us();
		delay10us();
		delay10us();
		temp=0;      //�ߵ�ƽ����26~28us��ʾ���ݡ�0��
		if(P2_0)
		{
			temp=1;    //�ߵ�ƽ����70us��ʾ���ݡ�1��
		}
		flag=2;
		while((P2_0)&&flag++);//P2_0=0��flag������0ʱ�˳���ѭ��	  
		if(flag==1)
		{
			break;//��ʱ������forѭ��	
		}
		comdata<<=1;
		comdata|=temp;  
	}
}




//ʪ���������ݣ�RH_data_H
//ʪ��С�����ݣ�RH_data_L
//�¶��������ݣ�T_data_H
//�¶�С�����ݣ�T_data_L
//У��ͣ�check_data
void wenshidu(void)
{
	//������������������18ms(��ʼ�ź�)����֤DHT11�ܼ�⵽��ʼ�ź�
	P2_0=0;
	delayms(20);
	//�������Ϳ�ʼ�źŽ�������ʱ�ȴ�20~40us�󣬶�ȡDHT11����Ӧ�ź�
	P2_0=1;
	delay10us();
	delay10us();
	delay10us();
	delay10us();
	//�������Ϳ�ʼ�źŽ�����,�����л�������ģʽ����������ߵ�ƽ���ɣ�������������������
	P2_0=1; 
	//DHT11�ӵ������Ŀ�ʼ�źź󣬵ȴ�������ʼ�źŽ�����Ȼ����80us�͵�ƽ��Ӧ�ź�    	
	if(!P2_0)	
	{
		//�жϴӻ�����80us�ĵ͵�ƽ��Ӧ�ź��Ƿ����	
		flag=2; 
		while((!P2_0)&&flag++);//P2_0=1��flag������0ʱ�˳���ѭ��
		//DHT11������Ӧ�źź��ٰ���������80us��׼����������
		flag=2;
		while((P2_0)&&flag++);//P2_0=0��flag������0ʱ�˳���ѭ��	 	
		//���ݷ���				
		com();
		RH_data_H_temp=comdata;
		com();
		RH_data_L_temp=comdata;
		com();
		T_data_H_temp=comdata;
		com();
		T_data_L_temp=comdata;
		com();
		check_data=comdata;
		P2_0=1;//DHT11��������50us,��������������������߽������״̬
		check_data_temp=(RH_data_H_temp+RH_data_L_temp+T_data_H_temp+T_data_L_temp);//����У�� 
		if(check_data==check_data_temp)
		{
			RH_data_H=RH_data_H_temp;
			RH_data_L=RH_data_L_temp;
			T_data_H=T_data_H_temp;
			T_data_L=T_data_L_temp;
		}
	}
}