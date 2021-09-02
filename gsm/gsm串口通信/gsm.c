#include "gsm.h"																									   
#include "delay.h"


#define CALL_YOU_TELNUMBER "ATD18326638928;\r\n"//打电话,填入你手机上的手机号码,不是gsm模块上的
#define OVER_YOU_TELNUMBER "ATH\r\n"//挂电话,填入你手机上的手机号码,不是gsm模块上的
#define ACCEPT_YOU_TELNUMBER "ATA\r\n"//接电话,填入你手机上的手机号码,不是gsm模块上的
#define SEND_MESSA_TO_YOUR "at+cmgs=\"18326638928\"\r\n"//填入你手机上的手机号码,不是gsm模块上的
#define SEND_MESSA_CONTENT_english "warning"//发短信内容"warning"
#define SEND_MESSA_CONTENT_chinese "0891683110305005F011000D91688123668329F80008A720002300317535996D95050020002300327A7A8C030020002300336D178863673A"//发短信内容"请输入密码：",前面是gsm模块上的手机号所在地的短信中心号码，后面是接收短信的手机号码
#define MAXCHAR 81


uchar j=0,aa[MAXCHAR];
uchar code ATE0[]="ATE0\r\n";//关闭回显
uchar code ATCN[]="AT+CNMI=2,1\r\n";//短信存入SIM卡
uchar code CREG_CMD[]="AT+CREG?\r\n";//查询网络注册情况
uchar code SMS_send[]="AT+CMGS=47\r\n";//发送短消息的字节数为27
uchar code CMGF0[]="AT+CMGF=0\r\n";//PDU模式
uchar code CMGF1[]="AT+CMGF=1\r\n";//Text模式
uchar code CMGR[]="AT+CMGR=1\r\n";//读取第1条短消息
uchar code CMGD[]="AT+CMGD=1\r\n";//删除第1条短消息


void send_english(void)
{
	clearBuff();
    P0=0XFF;//灯全灭
	Print_Str(CMGF1);//Text模式
    while(strstr(aa,"OK")==NULL);
    led(0x01);//第1个灯灭
	clearBuff();
	Print_Str(SEND_MESSA_TO_YOUR);
	while(strstr(aa,">")==NULL);
    led(0x02);//第2个灯灭
	clearBuff();
	Print_Str(SEND_MESSA_CONTENT_english);//发短信内容"warning"
    Print_Char(0x1A);//发送完上面的完整代码后，需要发送“Ctrl+Z”结束符号,其ASCII码值为26，转换为16进制代码为：1A。
	while(strstr(aa,"OK")==NULL);
    led(0x04);//第3个灯灭
    clearBuff();
}


void send_chinese(void)
{
	clearBuff();
    P0=0XFF;//灯全灭
	Print_Str(CMGF0);//PDU模式
    while(strstr(aa,"OK")==NULL);
    led(0x01);//第1个灯灭
	clearBuff();
	Print_Str(SMS_send);//发送短消息的字节数为27
	while(strstr(aa,">")==NULL);
    led(0x02);//第2个灯灭
	clearBuff();
	Print_Str(SEND_MESSA_CONTENT_chinese);//发短信内容
    Print_Char(0x1A);//发送完上面的完整代码后，需要发送“Ctrl+Z”结束符号,其ASCII码值为26，转换为16进制代码为：1A。
    while(strstr(aa,"OK")==NULL);
	led(0x04);//第3个灯灭
    clearBuff();
}


void checkenglish_sendenglish(void)
{
	clearBuff();
	P0=0XFF;//灯全灭
	while(strstr(aa,"SM")==NULL);
    led(0x01);//第1个灯灭
    clearBuff();
	Print_Str(CMGF1);//Text模式
    while(strstr(aa,"OK")==NULL);
    led(0x02);//第2个灯灭
	clearBuff();
	Print_Str(CMGR);//读取第1条短消息
    while(strstr(aa,"OK")==NULL);
    led(0x04);//第3个灯灭
	send_english();
	Print_Str(CMGD); //删除第1条短消息
	while(strstr(aa,"OK")==NULL);
	led(0x08);//第4个灯灭
	clearBuff();
}


void checkenglish_sendchinese(void)
{
	clearBuff();
	P0=0XFF;//灯全灭
	while(strstr(aa,"SM")==NULL);
    led(0x01);//第1个灯灭
    clearBuff();
	Print_Str(CMGF1);//Text模式
    while(strstr(aa,"OK")==NULL);
    led(0x02);//第2个灯灭
	clearBuff();
	Print_Str(CMGR);//读取第1条短消息
    while(strstr(aa,"OK")==NULL);
    led(0x04);//第3个灯灭
	send_chinese();
	Print_Str(CMGD); //删除第1条短消息
	while(strstr(aa,"OK")==NULL);
	led(0x08);//第4个灯灭
	clearBuff();
}


void checkchinese_sendenglish(void)
{
	clearBuff();
	P0=0XFF;//灯全灭
	while(strstr(aa,"SM")==NULL);
    led(0x01);//第1个灯灭
    clearBuff();
	Print_Str(CMGF0);//PDU模式
    while(strstr(aa,"OK")==NULL);
    led(0x02);//第2个灯灭
	clearBuff();
	Print_Str(CMGR);//读取第1条短消息
    while(strstr(aa,"OK")==NULL);
    led(0x04);//第3个灯灭
	send_chinese();
	Print_Str(CMGD); //删除第1条短消息
	while(strstr(aa,"OK")==NULL);
	led(0x08);//第4个灯灭
	clearBuff();
}


void checkchinese_sendchinese(void)
{
	clearBuff();
	P0=0XFF;//灯全灭
	while(strstr(aa,"SM")==NULL);
    led(0x01);//第1个灯灭
    clearBuff();
	Print_Str(CMGF0);//PDU模式
    while(strstr(aa,"OK")==NULL);
    led(0x02);//第2个灯灭
	clearBuff();
	Print_Str(CMGR);//读取第1条短消息
    while(strstr(aa,"OK")==NULL);
    led(0x04);//第3个灯灭
	send_chinese();
	Print_Str(CMGD); //删除第1条短消息
	while(strstr(aa,"OK")==NULL);
	led(0x08);//第4个灯灭
	clearBuff();
}


void send_call1(void)//打通了
{
    clearBuff();
	P0=0XFF;//灯全灭
    Print_Str(CALL_YOU_TELNUMBER);//打电话
	while(strstr(aa,"OK")==NULL);
	led(0x01);//第1个灯灭
    clearBuff();
	delay(1000);
	Print_Str(OVER_YOU_TELNUMBER);//挂电话
	while(strstr(aa,"OK")==NULL);
	led(0x04);//第3个灯灭
    clearBuff();
}


void send_call2(void)//没打通了
{
    clearBuff();
	P0=0XFF;//灯全灭
    Print_Str(CALL_YOU_TELNUMBER);//打电话
	delay(100);
	led(0x01);//第1个灯灭
    clearBuff();
	delay(500);
	Print_Str(OVER_YOU_TELNUMBER);//挂电话
	while(strstr(aa,"NO CARRIER")==NULL);
	led(0x02);//第2个灯灭
    clearBuff();
}

void send_over(void)
{
    clearBuff();
	P0=0XFF;//灯全灭
	while(strstr(aa,"RING")==NULL);
	led(0x01);//第1个灯灭
    Print_Str(ACCEPT_YOU_TELNUMBER );//接电话
	while(strstr(aa,"OK")==NULL);
	led(0x02);//第2个灯灭
    clearBuff();
	delay(500);
	Print_Str(OVER_YOU_TELNUMBER);//挂电话
	while(strstr(aa,"OK")==NULL);
	led(0x04);//第3个灯灭
    clearBuff();
}


void Print_Char(uchar ch)//发送单个字符
{
    SBUF=ch; //送入缓冲区
    while(TI!=1); //等待发送完毕
    TI=0; //软件清零
}


void Print_Str(uchar *str)//发送字符串
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
    Print_Str(ATE0);//关闭回显
    while(strstr(aa,"OK")==NULL);
    led(0xfe);//灯1
    clearBuff();
	Print_Str(ATCN);//短信存入SIM卡
	while(strstr(aa,"OK")==NULL);
	led(0xfd);//灯2
	clearBuff();
	while(1)
    {
        Print_Str(CREG_CMD);//查询网络注册情况
        while(strstr(aa,"OK")==NULL);
        if(((aa[9]=='0')&&(aa[11]=='1'))||((aa[9]=='0')&&(aa[11]=='5')))
        {
        	led(0xfb);//灯3
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

