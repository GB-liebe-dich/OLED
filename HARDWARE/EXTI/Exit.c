#include "delay.h"
#include "stm32f10x_exti.h"
#include "exit.h"
#include "key.h"
#include "delay.h"
#include "display.h"
#include "ESP8266.h"

uint8 test_cnt = 0;

/* �����ж� */
void EC11_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) //�ж�ĳ�����ϵ��ж��Ƿ���
    {
        delay_ms(10); //����
        if (EC11_scan() == 1)
        {
            if (g_SetWifi_Cursor.state == 1) /* ѡ��״̬ */
            {
                if (g_SetWifi_Cursor.position <= sizeof(g_Wifi.ssid))
                {
                    g_SetWifi_Cursor.position++;
                }
            }
            else if (g_SetWifi_Cursor.state == 2) /* ����״̬ */
            {
                g_Wifi.ssid[g_SetWifi_Cursor.position]++;
            }
        }
        else if (EC11_scan() == 2)
        {
            if ((g_SetWifi_Cursor.state == 1) && (g_SetWifi_Cursor.position > 0)) /* ѡ��״̬ */
            {
                g_SetWifi_Cursor.position--;
            }
            else if (g_SetWifi_Cursor.state == 2) /* ����״̬ */
            {
                g_Wifi.ssid[g_SetWifi_Cursor.position]--;
            }
        }

        EXTI_ClearITPendingBit(EXTI_Line1); //���LINE0�ϵ��жϱ�־λ
    }
}

//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //ʹ�ܸ��ù���ʱ��

    //GPIOE.2 �ж����Լ��жϳ�ʼ������   �½��ش���
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);

    EXTI_InitStructure.EXTI_Line = EXTI_Line1; //KEY2
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;             //ʹ�ܰ���KEY2���ڵ��ⲿ�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;        //�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);
}

//�ⲿ�ж�1�������
void EXTI1_IRQHandler(void)
{
    EC11_IRQHandler();
}
