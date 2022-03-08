/*******************************************************************************
 * Copyright (C), 2021, ����Ҷ��
 * @file    display.c
 * @brief
 * @details
 * @author  ����Ҷ��
 * @version 1.0.0
 * @date    2021��12��12��
 * ----------------------------------------------------------------------------*
 * �޸ļ�¼:
 * <����>     | <�汾> | <����>   | <�޸ļ�¼>
 * ----------------------------------------------------------------------------*
 * 2021-12-12 | 1.0.0 | ����Ҷ��  | �����ļ���ʵ�ֹ���
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ ͷ�ļ����� =================================*/
#include "display.h"
#include "gui.h"
#include "oled.h"
#include "test.h"
#include "dht11.h"
#include "rtc.h"
#include "ESP8266.h"

/*================================= ȫ�ֱ��� =================================*/
u8 temperature = 0;
u8 humidity = 0;
u8 wendu[3] = {0};
u8 shidu[3] = {0};

DISPLAY g_Display = {main_interface, 0}; /* ��ʾ���� */
CURSOR g_SetWifi_Cursor;                 /* WiFi�������ý����� */

/*================================= �ӿں��� =================================*/
/**
 * @brief   ��ʾ��������
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2021-12-29
 * @note
 **/
void Dis_PowerOn(void)
{
    uint8 i;
    for (i = 0; i < 5; i++)
    {
        TEST_BMP();
    }
}

/**
 * @brief   ��ʾ������
 * @param   [In]
 * @param   [Out]
 * @return  None
 * @version 1.0.0
 * @date    2021-12-13
 * @note
 **/
void Dis_MainInterface(void)
{
    u8 nian[5] = {0};
    u8 yue[3] = {0};
    u8 ri[3] = {0};
    u8 shi[3] = {0};
    u8 fen[3] = {0};
    u8 miao[3] = {0};

    /* ���� */
    // OLED_Clear(0);

    /* ��ʾͼƬ */
    main_bmp();

    /* ���� */
    DecToChar(calendar.w_year, 4, nian);
    DecToChar(calendar.w_month, 2, yue);
    DecToChar(calendar.w_date, 2, ri);

    GUI_ShowString(0, 8, nian, 8, 1);
    GUI_ShowString(24, 8, "-", 8, 1);
    GUI_ShowString(30, 8, yue, 8, 1);
    GUI_ShowString(42, 8, "-", 8, 1);
    GUI_ShowString(48, 8, ri, 8, 1);

    /* ʱ�� */
    Dis_time();
    /*
    DecToChar(calendar.hour, 2, shi);
    DecToChar(calendar.min, 2, fen);
    DecToChar(calendar.sec, 2, miao);

    // GUI_ShowString(39, 16, ":", 18, 1);
    // GUI_ShowString(77, 16, ":", 18, 1);
    GUI_ShowString(0, 16, shi, 16, 1);
    GUI_ShowString(38, 16, fen, 16, 1);
    GUI_ShowString(50, 40, miao, 16, 1);
    */

    /* �˵� */
    DecToChar(temperature, 2, wendu);
    DecToChar(humidity, 2, shidu);
    GUI_ShowString(105, 18, wendu, 8, 1);
    GUI_ShowString(105, 31, shidu, 8, 1);
    // GUI_ShowCHinese(36, 36, 16, "��", 1);
    // GUI_ShowString(96, 36, "%", 16, 1);

    /* ������ʾ */
    OLED_Display();
}

/**
 * @brief   ��ʾWIFI�û�������������ҳ��
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2021-12-13
 * @note
 **/
void Dis_Wificonfig(void)
{
    uint8 Dis_temp;
    static uint8 s_Cursor_position; /* ���������λ�õı仯 */

    /* ��ʼ����ʾ���� */
    if (g_Display.Interface_State != 0xAA)
    {
        g_Display.Interface_State = 0xAA;

        OLED_Clear(0); /* ���� */

        /* ��ʾ�̶����� */
        GUI_ShowCHinese(0, 0, 16, "���ƣ�", 1);
        GUI_ShowCHinese(0, 16, 16, "���룺", 1);
        GUI_ShowString(0, 32, "T: ", 16, 1);
        GUI_ShowString(0, 48, "Port: ", 16, 1);

        /* ��ʾ�������� */
        GUI_ShowString(40, 0, g_Wifi.ssid, 16, 1);
        GUI_ShowString(40, 16, g_Wifi.password, 16, 1);
        GUI_ShowString(24, 32, g_Wifi.tcp_address, 16, 1);
        GUI_ShowString(48, 48, g_Wifi.tcp_port, 16, 1);
    }

    /* ������ʾ */
    if (g_SetWifi_Cursor.state)
    {
        if (s_Cursor_position != g_SetWifi_Cursor.position)
        {
            Dis_temp = g_Wifi.ssid[s_Cursor_position];
            GUI_ShowString((40 + (s_Cursor_position * 8)), 16, &Dis_temp, 16, 1);
            s_Cursor_position = g_SetWifi_Cursor.position;
        }
        Dis_temp = g_Wifi.ssid[g_SetWifi_Cursor.position];
        GUI_ShowString((40 + (g_SetWifi_Cursor.position * 8)), 16, &Dis_temp, 16, g_SetWifi_Cursor.twinkle);
    }
}

/*================================= ˽�к��� =================================*/

/*================================= �ļ���β =================================*/
