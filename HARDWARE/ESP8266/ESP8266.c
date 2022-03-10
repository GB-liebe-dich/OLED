/*******************************************************************************
 * Copyright (C), 2022, ����Ҷ��
 * @file    ESP8266.c
 * @brief
 * @details
 * @author  ����Ҷ��
 * @version 1.0.0
 * @date    2022��02��20��
 * ----------------------------------------------------------------------------*
 * �޸ļ�¼:
 * <����>     | <�汾> | <����>   | <�޸ļ�¼>
 * ----------------------------------------------------------------------------*
 * 2022-02-20 | 1.0.0 | ����Ҷ��  | �����ļ���ʵ�ֹ���
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ ͷ�ļ����� =================================*/
#include "ESP8266.h"
#include "USART3.h"
#include "rtc.h"
#include "string.h"
#include "delay.h"
#include "CLibrary.h"

/*================================= ȫ�ֱ��� =================================*/
WIFI_CONFIG g_Wifi = {/* wifi���� */
                      .ssid = WIFI_SSID,
                      .password = WIFI_PASSWORD,
                      .tcp_address = WIFI_TCPIP,
                      .tcp_port = WIFI_TCPPORT};

ESP8266_STATE g_8266State = {0};

/*================================= ˽�к��� =================================*/

/*================================= �ӿں��� =================================*/
/**
 * @brief   ESP8266��λ
 * @param   [In]��
 * @param   [Out]��
 * @return  ��
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
    /* �ػ��� */
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
 * @brief   ��ѯESP8266�Ƿ�������wifi
 * @param   [In]��
 * @param   [Out]��
 * @return
 * @version 1.0.0
 * @date    2022-03-04
 * @note    �ɹ���+CWJAP_DEF:"test","ec:41:18:b5:d4:73",11,-15,0
 *          ʧ�ܣ�No AP
 **/
uint8 ESP8266_QueryWifi(void)
{
    /* AT */
    if (UartxSendAT(USART3, AT_TEST, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* ��wifi */
    if (UartxSendAT(USART3, AT_CWJAP, g_Wifi.ssid, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }

    return 0;
}

/**
 * @brief   ESP8266����wifi
 * @param   [In]��
 * @param   [Out]��
 * @return  ��
 * @version 1.0.0
 * @date    2022-02-25
 * @note
 **/
uint8 ESP8266_ConnectWifi(void)
{
    uint8 t_SetWifi[50];

    /* ׼������ */
    AT_SETWIFI(t_SetWifi); // wifi����

    /* AT */
    if (UartxSendAT(USART3, AT_TEST, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* ����WIFI */
    if (UartxSendAT(USART3, t_SetWifi, WIFI_GETIP, g_USART3_RxData.USART_RX_BUF, 8000))
    {
        return 1;
    }

    return 0;
}

/**
 * @brief   ��ȡ��ǰʱ��
 * @param   [In]��
 * @param   [Out]��
 * @return  ��
 * @version 1.0.0
 * @date    2022-02-25
 * @note    +CIPSNTPTIME:Thu Jan 01 00:00:00 1970
 **/
uint8 ESP8266_GetTime(void)
{
    uint8 i;
    int8 tPos;
    uint8 tTime[30] = {0}; //ʱ��
    _calendar_obj tClock;  //ʱ�ӽṹ��

    /* AT */
    if (UartxSendAT(USART3, AT_TEST, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* ����ʱ�� */
    if (UartxSendAT(USART3, AT_SNTP, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    delay_ms(1000);
    /* ��ȡʱ�� */
    for (i = 0; i < 8; i++) //����Уʱ8�Σ��������ɹ�������ѭ���м���Уʱ
    {
        if (SUCCESS == UartxSendAT(USART3, AT_GETTIME, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
        {
            if (!strstr(g_USART3_RxData.USART_RX_BUF, (uint8 *)"1970")) // 1970��ʾδУʱ�ɹ�
            {
                /* ����ϵͳʱ�� */
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
                                    + (tTime[23] & 0x0F));                          //��
                    tClock.w_month = EngMonthGetNum(&tTime[4], 3);                  //��
                    tClock.w_date = ((tTime[8] & 0x0F) * 10) + (tTime[9] & 0x0F);   //��
                    tClock.week = EngWeekGetNum(&tTime[0], 3);                      //��
                    tClock.hour = ((tTime[11] & 0x0F) * 10) + (tTime[12] & 0x0F);   //ʱ
                    tClock.min = ((tTime[14] & 0x0F) * 10) + (tTime[15] & 0x0F);    //��
                    tClock.sec = ((tTime[17] & 0x0F) * 10) + (tTime[18] & 0x0F);    //��
                    /* ��ʱ�䵽RTC������ */
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
 * @brief   ��ȡ��ǰ����
 * @param   [In]��
 * @param   [Out]��
 * @return  ��
 * @version 1.0.0
 * @date    2022-02-25
 * @note
 **/
uint8 ESP8266_Weather(void)
{
    uint8 tPos;
    uint8 tweather[10];
    uint8 t_SetTcp[50];

    /* ׼������ */
    AT_SETTCP(t_SetTcp); // TCP����

    /* AT */
    if (UartxSendAT(USART3, AT_TEST, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* ����TCP */
    if (UartxSendAT(USART3, t_SetTcp, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* ����͸�� */
    if (UartxSendAT(USART3, AT_CIPMODE, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* �������� */
    if (UartxSendAT(USART3, AT_CIPSEND, AT_OK, g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    /* ��ȡ���� */
    if (UartxSendAT(USART3, GET_WEATHER, (uint8 *)"code", g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    if (invalid != FindStrPos(g_USART3_RxData.USART_RX_BUF, g_USART3_RxData.RxLen, (uint8 *)"code", sizeof("code") - 1))
    {
        tPos = FindStrPos(g_USART3_RxData.USART_RX_BUF, g_USART3_RxData.RxLen, (uint8 *)"code", sizeof("code") - 1);
        if (g_USART3_RxData.USART_RX_BUF[tPos + 8] == 0x22) // 0x22 �� "
        {
            g_8266State.weather = (g_USART3_RxData.USART_RX_BUF[tPos + 7] & 0x0F);
        }
        else
        {
            g_8266State.weather = ((g_USART3_RxData.USART_RX_BUF[tPos + 7] & 0x0F) * 10) + (g_USART3_RxData.USART_RX_BUF[tPos + 8] & 0x0F);
        }
    }
    delay_ms(100);
    /* �˳�͸�����ر�TCP���� */
    if (UartxSendAT(USART3, AT_ENDSEND, (uint8 *)"CLOSED", g_USART3_RxData.USART_RX_BUF, 3000))
    {
        return 1;
    }
    delay_ms(500);

    return 0;
}

/**
 * @brief   ESP8266�ж��¼�
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

/*================================= �ļ���β =================================*/
