#include "gsm.h"																									   
#include "delay.h"


#define CALL_YOU_TELNUMBER "ATD18326638928;\r\n"//��绰,�������ֻ��ϵ��ֻ�����,����gsmģ���ϵ�
#define OVER_YOU_TELNUMBER "ATH\r\n"//�ҵ绰,�������ֻ��ϵ��ֻ�����,����gsmģ���ϵ�
#define ACCEPT_YOU_TELNUMBER "ATA\r\n"//�ӵ绰,�������ֻ��ϵ��ֻ�����,����gsmģ���ϵ�
#define SEND_MESSA_TO_YOUR "at+cmgs=\"18326638928\"\r\n"//�������ֻ��ϵ��ֻ�����,����gsmģ���ϵ�
#define SEND_MESSA_CONTENT_english "warning"//����������"warning"
#define SEND_MESSA_CONTENT_chinese "0891683110305005F011000D91688123668329F80008A720002300317535996D95050020002300327A7A8C030020002300336D178863673A"//����������"���������룺",ǰ����gsmģ���ϵ��ֻ������ڵصĶ������ĺ��룬�����ǽ��ն��ŵ��ֻ�����
#define MAXCHAR 81


uchar j=0,aa[MAXCHAR];
uchar code ATE0[]="ATE0\r\n";//�رջ���
uchar code ATCN[]="AT+CNMI=2,1\r\n";//���Ŵ���SIM��
uchar code CREG_CMD[]="AT+CREG?\r\n";//��ѯ����ע�����
uchar code SMS_send[]="AT+CMGS=47\r\n";//���Ͷ���Ϣ���ֽ���Ϊ27
uchar code CMGF0[]="AT+CMGF=0\r\n";//PDUģʽ
uchar code CMGF1[]="AT+CMGF=1\r\n";//Textģʽ
uchar code CMGR[]="AT+CMGR=1\r\n";//��ȡ��1������Ϣ
uchar code CMGD[]="AT+CMGD=1\r\n";//ɾ����1������Ϣ


void send_english(void)
{
	clearBuff();
    P0=0XFF;//��ȫ��
	Print_Str(CMGF1);//Textģʽ
    while(strstr(aa,"OK")==NULL);
    led(0x01);//��1������
	clearBuff();
	Print_Str(SEND_MESSA_TO_YOUR);
	while(strstr(aa,">")==NULL);
    led(0x02);//��2������
	clearBuff();
	Print_Str(SEND_MESSA_CONTENT_english);//����������"warning"
    Print_Char(0x1A);//����������������������Ҫ���͡�Ctrl+Z����������,��ASCII��ֵΪ26��ת��Ϊ16���ƴ���Ϊ��1A��
	while(strstr(aa,"OK")==NULL);
    led(0x04);//��3������
    clearBuff();
}


void send_chinese(void)
{
	clearBuff();
    P0=0XFF;//��ȫ��
	Print_Str(CMGF0);//PDUģʽ
    while(strstr(aa,"OK")==NULL);
    led(0x01);//��1������
	clearBuff();
	Print_Str(SMS_send);//���Ͷ���Ϣ���ֽ���Ϊ27
	while(strstr(aa,">")==NULL);
    led(0x02);//��2������
	clearBuff();
	Print_Str(SEND_MESSA_CONTENT_chinese);//����������
    Print_Char(0x1A);//����������������������Ҫ���͡�Ctrl+Z����������,��ASCII��ֵΪ26��ת��Ϊ16���ƴ���Ϊ��1A��
    while(strstr(aa,"OK")==NULL);
	led(0x04);//��3������
    clearBuff();
}


void checkenglish_sendenglish(void)
{
	clearBuff();
	P0=0XFF;//��ȫ��
	while(strstr(aa,"SM")==NULL);
    led(0x01);//��1������
    clearBuff();
	Print_Str(CMGF1);//Textģʽ
    while(strstr(aa,"OK")==NULL);
    led(0x02);//��2������
	clearBuff();
	Print_Str(CMGR);//��ȡ��1������Ϣ
    while(strstr(aa,"OK")==NULL);
    led(0x04);//��3������
	send_english();
	Print_Str(CMGD); //ɾ����1������Ϣ
	while(strstr(aa,"OK")==NULL);
	led(0x08);//��4������
	clearBuff();
}


void checkenglish_sendchinese(void)
{
	clearBuff();
	P0=0XFF;//��ȫ��
	while(strstr(aa,"SM")==NULL);
    led(0x01);//��1������
    clearBuff();
	Print_Str(CMGF1);//Textģʽ
    while(strstr(aa,"OK")==NULL);
    led(0x02);//��2������
	clearBuff();
	Print_Str(CMGR);//��ȡ��1������Ϣ
    while(strstr(aa,"OK")==NULL);
    led(0x04);//��3������
	send_chinese();
	Print_Str(CMGD); //ɾ����1������Ϣ
	while(strstr(aa,"OK")==NULL);
	led(0x08);//��4������
	clearBuff();
}


void checkchinese_sendenglish(void)
{
	clearBuff();
	P0=0XFF;//��ȫ��
	while(strstr(aa,"SM")==NULL);
    led(0x01);//��1������
    clearBuff();
	Print_Str(CMGF0);//PDUģʽ
    while(strstr(aa,"OK")==NULL);
    led(0x02);//��2������
	clearBuff();
	Print_Str(CMGR);//��ȡ��1������Ϣ
    while(strstr(aa,"OK")==NULL);
    led(0x04);//��3������
	send_chinese();
	Print_Str(CMGD); //ɾ����1������Ϣ
	while(strstr(aa,"OK")==NULL);
	led(0x08);//��4������
	clearBuff();
}


void checkchinese_sendchinese(void)
{
	clearBuff();
	P0=0XFF;//��ȫ��
	while(strstr(aa,"SM")==NULL);
    led(0x01);//��1������
    clearBuff();
	Print_Str(CMGF0);//PDUģʽ
    while(strstr(aa,"OK")==NULL);
    led(0x02);//��2������
	clearBuff();
	Print_Str(CMGR);//��ȡ��1������Ϣ
    while(strstr(aa,"OK")==NULL);
    led(0x04);//��3������
	send_chinese();
	Print_Str(CMGD); //ɾ����1������Ϣ
	while(strstr(aa,"OK")==NULL);
	led(0x08);//��4������
	clearBuff();
}


void send_call1(void)//��ͨ��
{
    clearBuff();
	P0=0XFF;//��ȫ��
    Print_Str(CALL_YOU_TELNUMBER);//��绰
	while(strstr(aa,"OK")==NULL);
	led(0x01);//��1������
    clearBuff();
	delay(1000);
	Print_Str(OVER_YOU_TELNUMBER);//�ҵ绰
	while(strstr(aa,"OK")==NULL);
	led(0x04);//��3������
    clearBuff();
}


void send_call2(void)//û��ͨ��
{
    clearBuff();
	P0=0XFF;//��ȫ��
    Print_Str(CALL_YOU_TELNUMBER);//��绰
	delay(100);
	led(0x01);//��1������
    clearBuff();
	delay(500);
	Print_Str(OVER_YOU_TELNUMBER);//�ҵ绰
	while(strstr(aa,"NO CARRIER")==NULL);
	led(0x02);//��2������
    clearBuff();
}

void send_over(void)
{
    clearBuff();
	P0=0XFF;//��ȫ��
	while(strstr(aa,"RING")==NULL);
	led(0x01);//��1������
    Print_Str(ACCEPT_YOU_TELNUMBER );//�ӵ绰
	while(strstr(aa,"OK")==NULL);
	led(0x02);//��2������
    clearBuff();
	delay(500);
	Print_Str(OVER_YOU_TELNUMBER);//�ҵ绰
	while(strstr(aa,"OK")==NULL);
	led(0x04);//��3������
    clearBuff();
}


void Print_Char(uchar ch)//���͵����ַ�
{
    SBUF=ch; //���뻺����
    while(TI!=1); //�ȴ��������
    TI=0; //�������
}


void Print_Str(uchar *str)//�����ַ���
{
	while(*str!='\0')
    {
        Print_Char(*str);
        delay(2);
        str++;
    }

}


void clearBuff(void)
{
    for(j=0;j<MAXCHAR;j++)
    {
        aa[j]=0x00;
    }
    j=0;
}


void led(int i)
{
//    P0 |= i;
//    delay(20);
//    P0 &= ~i;
//    delay(20);
//    P0 |= i;
//    delay(20);
//    P0 &= ~i;
	P0=i;
}


void init_gsm(void)
{
	clearBuff();
    Print_Str(ATE0);//�رջ���
    while(strstr(aa,"OK")==NULL);
    led(0xfe);//��1
    clearBuff();
	Print_Str(ATCN);//���Ŵ���SIM��
	while(strstr(aa,"OK")==NULL);
	led(0xfd);//��2
	clearBuff();
	while(1)
    {
        Print_Str(CREG_CMD);//��ѯ����ע�����
        while(strstr(aa,"OK")==NULL);
        if(((aa[9]=='0')&&(aa[11]=='1'))||((aa[9]=='0')&&(aa[11]=='5')))
        {
        	led(0xfb);//��3
			clearBuff();
            break;
        }
        else
        {
            led(0xf7);//4
            clearBuff();
        }
    }
}

