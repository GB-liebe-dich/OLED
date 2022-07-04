/*******************************************************************************
 * Copyright (C), 2022, ����Ҷ��
 * @file    Button.h
 * @brief
 * @details
 * @author  ����Ҷ��
 * @version 1.0.0
 * @date    2022��04��14��
 * @History:
 *      1. Date: 2022-04-14
 *         Author: ����Ҷ��
 *         Modification: �½�
 ******************************************************************************/
#ifndef __BUTTON_H
#define __BUTTON_H

/*================================ ͷ�ļ����� =================================*/
#include "Clibrary.h"
#include "sys.h"

/*=============================== �궨��/�ض��� ===============================*/
#define QUERY_MODE 0 //Ϊ0��ʾ�����ö�ʱ��ѯ��ʽ��Ϊ1��ʾ���ö�ʱ+�жϷ�ʽ
#if (QUERY_MODE == 1)
#define BUTTON_TIMING    //�������ö�ʱ��ѯ��ʽ
#define BUTTON_INTERRUPT //���������жϲ�ѯ��ʽ
#else
#define BUTTON_TIMING //�������ö�ʱ��ѯ��ʽ
#endif

#define Scan_interval 0       //ɨ��������λms
#define SHAKE_TIME 1          //����ʱ��
#define DOUBLE_C_TIME 50      //˫����Ч���
#define LONG_C_TIME 200       //������Чʱ��
#define DEFAULT_LOGIC_LEVEL 1 //Ĭ���߼���ƽ
#define KEY_PIN PBin(0)
#define EC11_A_PIN PAin(1)
#define EC11_B_PIN PAin(0)

#define KEY_EVENT    (user_button[0].Button_event)
#define EC11_A_EVENT (user_button[1].Button_event)
#define EC11_B_EVENT (user_button[2].Button_event)

/*========================== ö����/������/�ṹ�嶨�� ==========================*/
/**
 * @brief ��������
 * @note  ��ӻ�ɾ����������������
 **/
enum
{
    USER_BUTTON_0 = 0, //����1
    USER_BUTTON_1,     //����2
    USER_BUTTON_2,     //����3
    USER_BUTTON_MAX
};

/**
 * @brief ��������ö����
 * @note
 **/
typedef enum
{
    BOUNCE = 0,  //����
    PRESS,       //����
    KEEP_CLICK,  //���±���
    PRESS_BOUNCE //�ص��ȴ�״̬���ȴ�������
} BUTTON_ACTION;

/**
 * @brief ��������ö����
 * @note
 **/
typedef enum
{
    DEFAULT = 0,  //���¼�
    PENDING,      //����
    SINGLE_CLICK, //����
    DOUBLE_CLICK, //˫��
    LONG_CLICK    //����
} BUTTON_EVENT;

/**
 * @brief �������ܽṹ��
 * @note  {attribute�����ԣ�}
 **/
typedef struct _button_attribute
{
    uint8 (*Button_read)(void *); //���������ŵ�ƽ
    BUTTON_ACTION Button_state;   //����״̬
    BUTTON_EVENT Button_event;    //�����¼�
    uint16 Debounce_Time;         //����ʱ��
    uint16 Double_Click_Time;     //�������
    uint16 Long_Click_Time;       //����ʱ��
    uint16 scan_cnt;              //��¼ɨ��ʱ�䣬���������ǿ�ʼ�������
    uint8 click_cnt;              //��¼���������������ж�����������
    uint8 ID;                     //�������
    uint8 Pressed_Logic_Level;    //�������µ��߼���ƽ��1����ʶ�������µ�ʱ��Ϊ�ߵ�ƽ��0����ʶ�������µ�ʱ��δ�͵�ƽ
    uint8 EN_EXTI;                //�ⲿ�ж�ʹ��λ��0xAAΪʹ���ⲿ�жϣ�����ֵΪʧ��
} BUTTON_ATTRIBUTE;

/*================================= ȫ�ֱ��� =================================*/
extern BUTTON_ATTRIBUTE user_button[USER_BUTTON_MAX];

/*================================= ˽�к��� =================================*/
static uint8 GetButtonValue(void *arg);
void UserButtonInit(void);
uint32 GetButtonData(void);
uint32 GetButtonEvent(uint32 button_data);
void Buttontask(void);

/*================================= �ӿں��� =================================*/
extern void Button_Init(void);
extern void HandleButtonEvent(void);

#endif
/*================================= �ļ���β =================================*/
