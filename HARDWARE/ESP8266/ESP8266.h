/*******************************************************************************
 * Copyright (C), 2022, 羽落叶秋
 * @file    ESP8266.h
 * @brief   
 * @details 
 * @author  羽落叶秋
 * @version 1.0.0
 * @date    2022年02月20日
 * @History:
 *      1. Date: 2022-02-20
 *         Author: 羽落叶秋
 *         Modification: 新建
 ******************************************************************************/
#ifndef __ESP8266_H
#define __ESP8266_H

/*================================ 头文件包含 =================================*/
#include "Clibrary.h"
#include "stdio.h"

/*=============================== 宏定义/重定义 ===============================*/
/* wifi参数 */
#define MAX_USER        (20)         //WiFi用户名最大值
#define MAX_PASSWORD    (20)        //WiFi密码最大值
#define WIFI_SSID       "Hellow world"      //WIFI名称
#define WIFI_PASSWORD   "gaobinying123.." //wifi密码
#define WIFI_TCPIP      (uint8 *)"api.seniverse.com"    //TCPip
#define WIFI_TCPPORT    (uint8 *)"80"                   //TCP端口
/* ESP8266CMD */
#define AT_TEST     (uint8 *)"AT\r\n"                //测试连接
#define AT_ATE0     (uint8 *)"ATE0\r\n"              //关回显
#define AT_RST      (uint8 *)"AT+RST\r\n"            //复位
#define AT_CWMOD    (uint8 *)"AT+CWMODE_DEF=1\r\n"   //设置Sta模式
#define AT_SNTP     (uint8 *)"AT+CIPSNTPCFG=1,8\r\n" //设置时区
#define AT_GETTIME  (uint8 *)"AT+CIPSNTPTIME?\r\n"   //获取时间
#define AT_CIPMODE  (uint8 *)"AT+CIPMODE=1\r\n"      //设置透传模式
#define AT_CIPSEND  (uint8 *)"AT+CIPSEND\r\n"        //开始发送
#define AT_ENDSEND  (uint8 *)"+++"                   //退出透传
#define AT_CIPCLOSE (uint8 *)"AT+CIPCLOSE\r\n"       //关闭TCP连接
#define AT_CWJAP    (uint8 *)"AT+CWJAP_DEF?\r\n"     //查询连接的wifi
/* ESP8266状态 */
#define WIFI_CONNECTED  (uint8 *)"WIFI CONNECTED\r\n"   //wifi连接成功
#define WIFI_DISCONNECT (uint8 *)"WIFI DISCONNECT\r\n"  //wifi断开连接
#define WIFI_GETIP      (uint8 *)"WIFI GOT IP\r\n"      //wifi入网成功
#define ESP8266_READY   (uint8 *)"ready\r\n"            //重启成功
#define AT_OK           (uint8 *)"OK\r\n"               //OK
#define AT_SETWIFI(buf) snprintf(buf,sizeof(buf),\
                        "AT+CWJAP=\"%s\",\"%s\"\r\n",\
                        (uint8 *)WIFI_SSID,(uint8 *)WIFI_PASSWORD)  //设置wifi
#define AT_SETTCP(buf)  snprintf(buf,sizeof(buf),\
                        "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",\
                        WIFI_TCPIP,WIFI_TCPPORT)                    //设置TCP
/* ESP8266DATA */
#define GET_WEATHER (uint8*)"GET https://api.seniverse.com/v3/weather/\
now.json?key=S-D_y3mouaI7Do0p5&location=ip\
&language=zh-Hans&unit=c\r\n"   //获取天气信息
/*============================= 结构体/联合体定义 =============================*/
/**
 * @brief WiFi相关参数结构体
 * @note  
**/
typedef struct _wifi_config {
    uint8 ssid[MAX_USER + 1];           /* WiFi名称 */
    uint8 password[MAX_PASSWORD + 1];   /* wifi密码 */
    uint8 *tcp_address;                 /* tcp地址 */
    uint8 *tcp_port;                    /* tcp端口 */
} WIFI_CONFIG;

/**
 * @brief ESP8266状态结构体
 * @note  
**/
typedef struct _esp8266state {
    uint8 wifi_online;  //wifi在线标志，0xAA：在线，0x55：离线
    uint8 tcp_online;   //tcp在线标志，0xAA：在线，0x55：离线
    uint8 Timing;       //校时标志，0xAA表示校时成功
    uint8 weather;      //天气，心知天气代码
} ESP8266_STATE;

/*================================= 全局变量 =================================*/
extern WIFI_CONFIG g_Wifi;          //wifi配置
extern ESP8266_STATE g_8266State;   //ESP8266状态

/*================================= 私有函数 =================================*/


/*================================= 接口函数 =================================*/
extern uint8 ESP8266_RST(void);
extern uint8 ESP8266_QueryWifi(void);
extern uint8 ESP8266_ConnectWifi(void);
extern uint8 ESP8266_GetTime(void);
extern uint8 ESP8266_Weather(void);
extern void ESP8266_Event(void);

#endif
/*================================= 文件结尾 =================================*/
