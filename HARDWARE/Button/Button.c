/*******************************************************************************
 * Copyright (C), 2022, ����Ҷ��
 * @file    Button.c
 * @brief
 * @details
 * @author  ����Ҷ��
 * @version 1.0.0
 * @date    2022��04��14��
 * ----------------------------------------------------------------------------*
 * �޸ļ�¼:
 * <����>     | <�汾> | <����>   | <�޸ļ�¼>
 * ----------------------------------------------------------------------------*
 * 2022-04-14 | 1.0.0 | ����Ҷ��  | �����ļ���ʵ�ֹ���
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ ͷ�ļ����� =================================*/
#include "Button.h"
#include "display.h"

/*================================= ȫ�ֱ��� =================================*/
#ifdef BUTTON_INTERRUPT
uint8 Button_EXIT; //�����жϱ�־��0xAA��ʾ�а����ж��¼�������ֵ��
#endif
BUTTON_ATTRIBUTE user_button[USER_BUTTON_MAX]; //��������

/*================================= ˽�к��� =================================*/
/**
 * @brief   ��ȡ����״̬
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-04-24
 * @note
 **/
static uint8 GetButtonValue(void *arg)
{
    uint8_t value = 0;

    BUTTON_ATTRIBUTE *btn = (BUTTON_ATTRIBUTE *)arg;

    switch (btn->ID)
    {
    case USER_BUTTON_0:
        value = KEY_PIN;
        break;
    case USER_BUTTON_1:
        value = EC11_A_PIN;
        break;
    case USER_BUTTON_2:
        value = EC11_B_PIN;
        break;
    default:
        break;
    }

    return value;
}
/**
 * @brief   ��ʼ����������
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-04-24
 * @note
 **/
void UserButtonInit(void)
{
    uint8 i; //����forѭ��

    for (i = 0; i < USER_BUTTON_MAX; i++)
    {
        //========= ��ʼ��Ĭ�ϲ��� =========//
        user_button[i].ID = i;                                    //��ʼ���������
        user_button[i].Button_read = GetButtonValue;              //��ʼ������״̬
        user_button[i].Button_state = BOUNCE;                     //��ʼ������״̬������
        user_button[i].Button_event = DEFAULT;                    //��ʼ�������¼�����
        user_button[i].Debounce_Time = SHAKE_TIME;                //��ʼ������ʱ��
        user_button[i].Double_Click_Time = DOUBLE_C_TIME;         //��ʼ����˫����Ч���
        user_button[i].Long_Click_Time = LONG_C_TIME;             //��ʼ����������Чʱ��
        user_button[i].Pressed_Logic_Level = DEFAULT_LOGIC_LEVEL; //��ʼ���߼���ƽ
        user_button[i].scan_cnt = 0;                              //��ʼ��ɨ�����
        user_button[i].click_cnt = 0;                             //��ʼ����������
        user_button[i].EN_EXTI = 0;                               //Ĭ�Ϲر��ⲿ�ж�ʹ��

        //========= ��ʼ����Ĭ�ϲ��� =========//
        if ((i == USER_BUTTON_1) || (i == USER_BUTTON_2))
        {
            user_button[i].EN_EXTI = 0xAA; //����EC11�ⲿ�ж�ʹ��
        }
    }
}
/**
 * @brief   ��ȡ��ǰ����״̬
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-06-06
 * @note
 **/
uint32 GetButtonData(void)
{
    uint8 i;                //����forѭ��
    uint32 tButtonData = 0; //����״̬��ÿһλ����һ�������Ƿ񱻰��£�1������ 0������

    /* һ���Զ�ȡȫ������״̬������tButtonData�У�ÿ1λ����һ������״̬������1�����λ */
    for (i = 0; i < USER_BUTTON_MAX; i++)
    {
        tButtonData |= (((user_button[i].Button_read)(&user_button[i]) ^ user_button[i].Pressed_Logic_Level)
                        << i); //��ȡ����״̬
    }

    return tButtonData;
}

/**
 * @brief   ��ȡ��ǰ�����¼�
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-05-04
 * @note
 **/
uint32 GetButtonEvent(uint32 button_data)
{
    uint8 i;                 //����forѭ��
    uint32 tButtonEvent = 0; //���水���¼�

    /* ��ȡ�����¼� */
    for (i = 0; i < USER_BUTTON_MAX; i++)
    {
        if (user_button[i].Button_event == PENDING)
        {
            user_button[i].scan_cnt++;
            if (user_button[i].scan_cnt >= ((1 << (sizeof(user_button[i].scan_cnt) * 8)) - 1))
            {
                user_button[i].scan_cnt = user_button[i].Long_Click_Time;
            }
        }
        /* �����¼�״̬�� */
        switch (user_button[i].Button_state)
        {
        case BOUNCE:                       //����״̬
            if ((button_data >> i) & 0x01) //��������
            {
                if (user_button[i].Button_event == DEFAULT)
                {
                    user_button[i].scan_cnt = 0;
                    user_button[i].click_cnt = 0;
                    user_button[i].Button_event = PENDING; //�ð����¼�����
                }
                else if (user_button[i].scan_cnt >= user_button[i].Debounce_Time) //����
                {
                    user_button[i].Button_state = PRESS;
                }
            }
            else //����ʧ��
            {
                if (user_button[i].click_cnt > 1)
                {
                    user_button[i].click_cnt = 0;
                    user_button[i].Button_event = DOUBLE_CLICK; //����
                    tButtonEvent |= (1 << i);
                }
                else if (user_button[i].click_cnt == 1)
                {
                    user_button[i].click_cnt = 0;
                    user_button[i].Button_event = SINGLE_CLICK; //����
                    tButtonEvent |= (1 << i);
                }
                else
                {
                    user_button[i].Button_event = DEFAULT; //�ް���
                }
            }
            break;
        case PRESS:                        //����״̬
            if ((button_data >> i) & 0x01) //��������
            {
                if (user_button[i].click_cnt > 0)
                {
                    user_button[i].click_cnt = 0;
                    user_button[i].Button_event = DOUBLE_CLICK; //����
                    user_button[i].Button_state = KEEP_CLICK;   //�ȴ���������
                    tButtonEvent |= (1 << i);
                }
                else if (user_button[i].scan_cnt >= user_button[i].Long_Click_Time)
                {
                    user_button[i].Button_event = LONG_CLICK; //������
                    user_button[i].Button_state = KEEP_CLICK; //�ȴ���������
                    tButtonEvent |= (1 << i);
                }
            }
            else
            {
                user_button[i].scan_cnt = 0;
                user_button[i].click_cnt++;
                user_button[i].Button_state = PRESS_BOUNCE;
            }
            break;
        case PRESS_BOUNCE:                 //�ص��ȴ�״̬
            if ((button_data >> i) & 0x01) //��������
            {
                user_button[i].scan_cnt = 0;
                user_button[i].Button_state = BOUNCE;
                user_button[i].Button_event = PENDING; //ֱ���ð�������������ʼ����
            }
            else
            {
                if (user_button[i].scan_cnt >= user_button[i].Double_Click_Time)
                {
                    if (user_button[i].click_cnt > 1)
                    {
                        user_button[i].click_cnt = 0;
                        user_button[i].Button_event = DOUBLE_CLICK; //����
                        tButtonEvent |= (1 << i);
                    }
                    else
                    {
                        user_button[i].click_cnt = 0;
                        user_button[i].Button_event = SINGLE_CLICK; //���
                        tButtonEvent |= (1 << i);
                    }
                    user_button[i].Button_state = BOUNCE;
                }
            }
            break;
        case KEEP_CLICK:
            if (!((button_data >> i) & 0x01)) //�ȴ���������
            {
                user_button[i].Button_state = BOUNCE;
            }
        default:
            break;
        }
    }

    return tButtonEvent;
}
/**
 * @brief   ��ȡEC11����
 * @param   [In]
 * @param   [Out]
 * @return  
 * @version 1.0.0
 * @date    2022-06-10
 * @note    
 **/
uint8 GetEC11Data(void)
{
    uint8 tDirection = 0;   //ת������0xAA��ʾ��ת��0x55��ʾ��ת��������ʾ��ת��

    if (EC11_A_EVENT == SINGLE_CLICK)
    {
        if (EC11_B_EVENT == SINGLE_CLICK) //��ת
        {
            tDirection = 0xAA;
        }
        else //��ת
        {
            tDirection = 0x55;
        }
    }

    return tDirection;
}

/**
 * @brief   ��������
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-06-06
 * @note
 **/
void Buttontask(void)
{
    uint8 i;    //����forѭ��
    uint8 tEC11Data;    //����EC11��ֵ
    
    //========= �����¼����� =========//
    if ((KEY_EVENT > PENDING) || (EC11_A_EVENT >PENDING))
    {
        if (g_SetWifi_Cursor.state) //ѡ�������״̬���ָ�����Ч
        {
            tEC11Data = GetEC11Data(); //��ȡEC11״̬

            if (tEC11Data)
            {
                (tEC11Data == 0xAA) ? g_SetWifi_Cursor.position++
                                    : g_SetWifi_Cursor.position--;
            }
        }

        switch (g_Display.Now_interface)
        {
          case main_interface:
          {
              if (KEY_EVENT == LONG_CLICK)
              {
                  g_Display.Now_interface = menu_interface;
                  g_SetWifi_Cursor.state = 0x55;    //����ѡ��״̬
                  g_SetWifi_Cursor.position = 0x01; //��1��ʼ
              }
              break;
          }break;
          case menu_interface:
          {
              if (KEY_EVENT == SINGLE_CLICK)
              {
                  g_Display.Now_interface += g_SetWifi_Cursor.position;
                  g_SetWifi_Cursor.position = 0;
              }
              if (g_SetWifi_Cursor.position >= Max_interface)
              {
                  g_SetWifi_Cursor.position = 0x01;
              }
          }break;
          case WiFiSet_interface:
          {
              
          }break;
          case Update_interface:
          {
              
          }break;
          default:
          {
              
          }break;
        }
    }

    //========= ��������¼� =========//
    for (i = 0; i < USER_BUTTON_MAX; i++)
    {
        user_button[i].Button_event = DEFAULT;
    }
}

/*================================= �ӿں��� =================================*/
/**
 * @brief   ������ʼ��
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-05-03
 * @note
 **/
void Button_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    //========= ��ͨGPIO���� =========//
    /* ʹ�ܶ�Ӧ�˿�ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); //ʹ��PA,PB�˿�ʱ��

    /* ����IO�ڲ��� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // EC11��ӦPA0��PA1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      // IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;         // Key��ӦPB0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

#ifdef BUTTON_INTERRUPT
    //========= �ⲿ�ж����� =========//
    /* ʹ�ܶ�Ӧʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //ʹ�ܸ��ù���ʱ��

    /* �����жϲ��� */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1); // PA.1
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;                  //�����ж���1
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;         //�ж�ģʽ
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //�½��ش���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                   //ʹ���ж���
    EXTI_Init(&EXTI_InitStructure);

    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0); // PB.0
    // EXTI_InitStructure.EXTI_Line = EXTI_Line0;                  //�����ж���1
    // EXTI_Init(&EXTI_InitStructure);

    //========= NVIC���� =========//
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;             //ʹ��PA.1���ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;        //�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);

    // NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;             //ʹ��PB.0���ڵ��ⲿ�ж�ͨ��
    // NVIC_Init(&NVIC_InitStructure);
#endif

    //========= �������� =========//
    /* ��ʼ���Զ������ */
    UserButtonInit(); //����������ʼ��
}

/**
 * @brief   �����¼�����
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-05-19
 * @note
 **/
void HandleButtonEvent(void)
{
    uint32 tButtonData; //���水����ֵ

    tButtonData = GetButtonData();

    if (GetButtonEvent(tButtonData)) //�а�������
    {
        Buttontask(); //ִ�а�������
    }
}

#ifdef BUTTON_INTERRUPT
// /**
//  * @brief   EXTI0�жϷ���������ӦPB0��KEY
//  * @param   [In]
//  * @param   [Out]
//  * @return
//  * @version 1.0.0
//  * @date    2022-05-03
//  * @note
//  **/
// void EXTI0_IRQHandler(void)
// {
//     if (EXTI_GetITStatus(EXTI_Line0) != RESET) //�ж�ĳ�����ϵ��ж��Ƿ���
//     {

//         EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ
//     }
// }

/**
 * @brief   EXTI1�жϷ���������ӦPA1��EC11_A
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-05-03
 * @note
 **/
void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) //�ж�ĳ�����ϵ��ж��Ƿ���
    {
        Button_EXIT = 0xAA;                 //�ð����ж��¼���־
        EXTI_ClearITPendingBit(EXTI_Line1); //���LINE1�ϵ��жϱ�־λ
    }
}
#endif

/*================================= �ļ���β =================================*/
