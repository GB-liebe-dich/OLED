/*******************************************************************************
 * Copyright (C), 2022, 羽落叶秋
 * @file    ESP8266.c
 * @brief
 * @details
 * @author  羽落叶秋
 * @version 1.0.0
 * @date    2022年02月20日
 * ----------------------------------------------------------------------------*
 * 修改记录:
 * <日期>     | <版本> | <作者>   | <修改记录>
 * ----------------------------------------------------------------------------*
 * 2022-02-20 | 1.0.0 | 羽落叶秋  | 创建文件并实现功能
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ 头文件包含 =================================*/
#include "ESP8266.h"
#include "USART3.h"
#include "rtc.h"
#include "string.h"
#include "delay.h"
#include "CLibrary.h"

/*================================= 全局变量 =================================*/
WIFI_CONFIG g_Wifi = {/* wifi配置 */
                      .ssid = WIFI_SSID,
                      .password = WIFI_PASSWORD,
                      .tcp_address = WIFI_TCPIP,
                      .tcp_port = WIFI_TCPPORT};

ESP8266_STATE g_8266State = {0};

/*================================= 私有函数 =================================*/

/*================================= 接口函数 =================================*/
/**
 * @brief   ESP8266复位
 * @param   [In]无
 * @param   [Out]无
 * @return  无
 * @version 1.0.0
 * @date    2022-02-25
 * @note
 **/
uint8 ESP8266_RST(void)
{
    /* AT */
    if (UartxSendAT(USART3, AT_TEST, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* 关回显 */
    if (UartxSendAT(USART3, AT_ATE0, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* RST */
    if (UartxSendAT(USART3, AT_RST, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    return 0;
}

/**
 * @brief   查询ESP8266是否已连接wifi
 * @param   [In]无
 * @param   [Out]无
 * @return
 * @version 1.0.0
 * @date    2022-03-04
 * @note    成功：+CWJAP_DEF:"test","ec:41:18:b5:d4:73",11,-15,0
 *          失败：No AP
 **/
uint8 ESP8266_QueryWifi(void)
{
    /* AT */
    if (UartxSendAT(USART3, AT_TEST, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* 查wifi */
    if (UartxSendAT(USART3, AT_CWJAP, g_Wifi.ssid, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }

    return 0;
}

/**
 * @brief   ESP8266连接wifi
 * @param   [In]无
 * @param   [Out]无
 * @return  无
 * @version 1.0.0
 * @date    2022-02-25
 * @note
 **/
uint8 ESP8266_ConnectWifi(void)
{
    uint8 t_SetWifi[50];

    /* 准备参数 */
    AT_SETWIFI(t_SetWifi); // wifi参数

    /* AT */
    if (UartxSendAT(USART3, AT_TEST, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* 设置WIFI */
    if (UartxSendAT(USART3, t_SetWifi, WIFI_GETIP, g_USART3_RxData.USART_RX_BUF, 8000))
    {
        return 1;
    }

    return 0;
}

/**
 * @brief   获取当前时间
 * @param   [In]无
 * @param   [Out]无
 * @return  无
 * @version 1.0.0
 * @date    2022-02-25
 * @note    +CIPSNTPTIME:Thu Jan 01 00:00:00 1970
 **/
uint8 ESP8266_GetTime(void)
{
    uint8 i;
    int8 tPos;
    uint8 tTime[30] = {0}; //时间
    _calendar_obj tClock;  //时钟结构体

    /* AT */
    if (UartxSendAT(USART3, AT_TEST, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* 设置时区 */
    if (UartxSendAT(USART3, AT_SNTP, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    delay_ms(1000);
    /* 获取时间 */
    for (i = 0; i < 8; i++) //连续校时8次，若还不成功则在主循环中继续校时
    {
        if (SUCCESS == UartxSendAT(USART3, AT_GETTIME, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
        {
            if (!strstr(g_USART3_RxData.USART_RX_BUF, (uint8 *)"1970")) // 1970表示未校时成功
            {
                /* 设置系统时间 */
                tPos = FindStrPos(g_USART3_RxData.USART_RX_BUF,
                                  g_USART3_RxData.RxLen,
                                  (uint8 *)"+CIPSNTPTIME:",
                                  sizeof("+CIPSNTPTIME:") - 1);
                if (invalid != tPos)
                {
                    memcpy(tTime, &g_USART3_RxData.USART_RX_BUF[tPos + 13], 24);

                    tClock.w_year = (((tTime[20] & 0x0F) * 1000) 
                                    + ((tTime[21] & 0x0F) * 100) 
                                    + ((tTime[22] & 0x0F) * 10) 
                                    + (tTime[23] & 0x0F));                          //年
                    tClock.w_month = EngMonthGetNum(&tTime[4], 3);                  //月
                    tClock.w_date = ((tTime[8] & 0x0F) * 10) + (tTime[9] & 0x0F);   //日
                    tClock.week = EngWeekGetNum(&tTime[0], 3);                      //周
                    tClock.hour = ((tTime[11] & 0x0F) * 10) + (tTime[12] & 0x0F);   //时
                    tClock.min = ((tTime[14] & 0x0F) * 10) + (tTime[15] & 0x0F);    //分
                    tClock.sec = ((tTime[17] & 0x0F) * 10) + (tTime[18] & 0x0F);    //秒
                    /* 存时间到RTC计数器 */
                    RTC_Set(tClock.w_year, tClock.w_month, tClock.w_date, tClock.hour, tClock.min, tClock.sec);

                    return 0;
                }
            }
        }
        else
        {
            return 1;
        }

        delay_ms(1000);
    }

    return 1;
}

/**
 * @brief   获取当前天气
 * @param   [In]无
 * @param   [Out]无
 * @return  无
 * @version 1.0.0
 * @date    2022-02-25
 * @note
 **/
uint8 ESP8266_Weather(void)
{
    uint8 tPos;
    uint8 tweather[10];
    uint8 t_SetTcp[50];

    /* 准备参数 */
    AT_SETTCP(t_SetTcp); // TCP参数

    /* AT */
    if (UartxSendAT(USART3, AT_TEST, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* 设置TCP */
    if (UartxSendAT(USART3, t_SetTcp, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* 设置透传 */
    if (UartxSendAT(USART3, AT_CIPMODE, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* 开启发送 */
    if (UartxSendAT(USART3, AT_CIPSEND, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* 获取天气 */
    if (UartxSendAT(USART3, GET_WEATHER, (uint8 *)"code", g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    if (invalid != FindStrPos(g_USART3_RxData.USART_RX_BUF, g_USART3_RxData.RxLen, (uint8 *)"code", sizeof("code") - 1))
    {
        tPos = FindStrPos(g_USART3_RxData.USART_RX_BUF, g_USART3_RxData.RxLen, (uint8 *)"code", sizeof("code") - 1);
        if (g_USART3_RxData.USART_RX_BUF[tPos + 8] == 0x22) // 0x22 即 "
        {
            g_8266State.weather = (g_USART3_RxData.USART_RX_BUF[tPos + 7] & 0x0F);
        }
        else
        {
            g_8266State.weather = ((g_USART3_RxData.USART_RX_BUF[tPos + 7] & 0x0F) * 10) + (g_USART3_RxData.USART_RX_BUF[tPos + 8] & 0x0F);
        }
    }
    delay_ms(100);
    /* 退出透传并关闭TCP连接 */
    if (UartxSendAT(USART3, AT_ENDSEND, (uint8 *)"CLOSED", g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    delay_ms(500);

    return 0;
}

/**
 * @brief   ESP8266中断事件
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-03-05
 * @note
 **/
void ESP8266_Event(void)
{
    ;
}

/*================================= 文件结尾 =================================*/
