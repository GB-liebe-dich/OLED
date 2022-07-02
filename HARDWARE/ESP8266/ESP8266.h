/*******************************************************************************
 * Copyright (C), 2022, ����Ҷ��
 * @file    ESP8266.h
 * @brief   
 * @details 
 * @author  ����Ҷ��
 * @version 1.0.0
 * @date    2022��02��20��
 * @History:
 *      1. Date: 2022-02-20
 *         Author: ����Ҷ��
 *         Modification: �½�
 ******************************************************************************/
#ifndef __ESP8266_H
#define __ESP8266_H

/*================================ ͷ�ļ����� =================================*/
#include "Clibrary.h"
#include "stdio.h"

/*=============================== �궨��/�ض��� ===============================*/
/* wifi���� */
#define MAX_USER        (20)         //WiFi�û������ֵ
#define MAX_PASSWORD    (20)        //WiFi�������ֵ
#define WIFI_SSID       "Hellow world"      //WIFI����
#define WIFI_PASSWORD   "gaobinying123.." //wifi����
#define WIFI_TCPIP      (uint8 *)"api.seniverse.com"    //TCPip
#define WIFI_TCPPORT    (uint8 *)"80"                   //TCP�˿�
/* ESP8266CMD */
#define AT_TEST     (uint8 *)"AT\r\n"                //��������
#define AT_ATE0     (uint8 *)"ATE0\r\n"              //�ػ���
#define AT_RST      (uint8 *)"AT+RST\r\n"            //��λ
#define AT_CWMOD    (uint8 *)"AT+CWMODE_DEF=1\r\n"   //����Staģʽ
#define AT_SNTP     (uint8 *)"AT+CIPSNTPCFG=1,8\r\n" //����ʱ��
#define AT_GETTIME  (uint8 *)"AT+CIPSNTPTIME?\r\n"   //��ȡʱ��
#define AT_CIPMODE  (uint8 *)"AT+CIPMODE=1\r\n"      //����͸��ģʽ
#define AT_CIPSEND  (uint8 *)"AT+CIPSEND\r\n"        //��ʼ����
#define AT_ENDSEND  (uint8 *)"+++"                   //�˳�͸��
#define AT_CIPCLOSE (uint8 *)"AT+CIPCLOSE\r\n"       //�ر�TCP����
#define AT_CWJAP    (uint8 *)"AT+CWJAP_DEF?\r\n"     //��ѯ���ӵ�wifi
/* ESP8266״̬ */
#define WIFI_CONNECTED  (uint8 *)"WIFI CONNECTED\r\n"   //wifi���ӳɹ�
#define WIFI_DISCONNECT (uint8 *)"WIFI DISCONNECT\r\n"  //wifi�Ͽ�����
#define WIFI_GETIP      (uint8 *)"WIFI GOT IP\r\n"      //wifi�����ɹ�
#define ESP8266_READY   (uint8 *)"ready\r\n"            //�����ɹ�
#define AT_OK           (uint8 *)"OK\r\n"               //OK
#define AT_SETWIFI(buf) snprintf(buf,sizeof(buf),\
                        "AT+CWJAP=\"%s\",\"%s\"\r\n",\
                        (uint8 *)WIFI_SSID,(uint8 *)WIFI_PASSWORD)  //����wifi
#define AT_SETTCP(buf)  snprintf(buf,sizeof(buf),\
                        "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",\
                        WIFI_TCPIP,WIFI_TCPPORT)                    //����TCP
/* ESP8266DATA */
#define GET_WEATHER (uint8*)"GET https://api.seniverse.com/v3/weather/\
now.json?key=S-D_y3mouaI7Do0p5&location=ip\
&language=zh-Hans&unit=c\r\n"   //��ȡ������Ϣ
/*============================= �ṹ��/�����嶨�� =============================*/
/**
 * @brief WiFi��ز����ṹ��
 * @note  
**/
typedef struct _wifi_config {
    uint8 ssid[MAX_USER + 1];           /* WiFi���� */
    uint8 password[MAX_PASSWORD + 1];   /* wifi���� */
    uint8 *tcp_address;                 /* tcp��ַ */
    uint8 *tcp_port;                    /* tcp�˿� */
} WIFI_CONFIG;

/**
 * @brief ESP8266״̬�ṹ��
 * @note  
**/
typedef struct _esp8266state {
    uint8 wifi_online;  //wifi���߱�־��0xAA�����ߣ�0x55������
    uint8 tcp_online;   //tcp���߱�־��0xAA�����ߣ�0x55������
    uint8 Timing;       //Уʱ��־��0xAA��ʾУʱ�ɹ�
    uint8 weather;      //��������֪��������
} ESP8266_STATE;

/*================================= ȫ�ֱ��� =================================*/
extern WIFI_CONFIG g_Wifi;          //wifi����
extern ESP8266_STATE g_8266State;   //ESP8266״̬

/*================================= ˽�к��� =================================*/


/*================================= �ӿں��� =================================*/
extern uint8 ESP8266_RST(void);
extern uint8 ESP8266_QueryWifi(void);
extern uint8 ESP8266_ConnectWifi(void);
extern uint8 ESP8266_GetTime(void);
extern uint8 ESP8266_Weather(void);
extern void ESP8266_Event(void);

#endif
/*================================= �ļ���β =================================*/
