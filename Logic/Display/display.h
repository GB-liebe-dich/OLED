/*******************************************************************************
 * Copyright (C), 2021, ����Ҷ��
 * @file    display.h
 * @brief   
 * @details 
 * @author  ����Ҷ��
 * @version 1.0.0
 * @date    2021��12��12��
 * @History:
 *      1. Date: 2021-12-12
 *         Author: ����Ҷ��
 *         Modification: �½�
 ******************************************************************************/
#ifndef __DISPLAY_H
#define __DISPLAY_H

/*================================ ͷ�ļ����� =================================*/
#include "Clibrary.h"

/*=============================== �궨��/�ض��� ===============================*/


/*============================= �ṹ��/�����嶨�� =============================*/
/**
 * @brief ��ʾ����ö���壬������ʾ��ǰ����
 * @note  
**/
typedef enum _interface {
    main_interface = 0, //������
    menu_interface,     //�˵�����
    WiFiSet_interface,  //WiFi���ý���
    Update_interface    //���²�������
} INTERFACE;

/**
 * @brief �������Խṹ��
 * @note  
**/
typedef struct _display {
    INTERFACE Now_interface;    /* ��ǰ��ʾ���� */
    uint8 Interface_State;      /*��ǰ����״̬��0xAA�������ѳ�ʼ����ɣ�����������δ��ʼ�� */
} DISPLAY;

/**
 * @brief �����ʾ��������ر����ṹ��
 * @note  
**/
typedef struct _cursor {
    uint8 state;    /* ѡ��״̬��0�����أ�1��ѡ��2������ */
    uint8 position;   /* ���Ŀǰ����λ�� */
    uint8 twinkle;   /* �����˸��־ */
} CURSOR;

/*================================= ȫ�ֱ��� =================================*/
extern DISPLAY g_Display;   /* ��ʾ���� */
extern CURSOR g_SetWifi_Cursor;    /* WiFi�������ý����� */
extern u8 temperature;
extern u8 humidity;

/*================================= �ӿں��� =================================*/
void Dis_PowerOn(void); /* �������� */
void Dis_MainInterface(void);   /* ��ʾ������ */
void Dis_Wificonfig(void);  /* ��ʾWIFI�û�������������ҳ�� */

/*================================= ˽�к��� =================================*/


#endif
/*================================= �ļ���β =================================*/
