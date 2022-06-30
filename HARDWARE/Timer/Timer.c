/*******************************************************************************
 * Copyright (C), 2022, ����Ҷ��
 * @file    Timer.c
 * @brief   
 * @details 
 * @author  ����Ҷ��
 * @version 1.0.0
 * @date    2022��06��30��
 * ----------------------------------------------------------------------------*
 * �޸ļ�¼:
 * <����>     | <�汾> | <����>   | <�޸ļ�¼>
 * ----------------------------------------------------------------------------*
 * 2022-06-30 | 1.0.0 | ����Ҷ��  | �����ļ���ʵ�ֹ���
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ ͷ�ļ����� =================================*/
#include "Timer.h"

/*================================= ȫ�ֱ��� =================================*/


/*================================= ˽�к��� =================================*/


/*================================= �ӿں��� =================================*/
/**
 * @brief   
 * @param   [In]
 * @param   [Out]
 * @return  
 * @version 1.0.0
 * @date    2022-06-30
 * @note    
 **/
void TIM3_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    //========= ��ʱ������ =========//
    /* ʹ�ܶ�ʱ��ʱ�� */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʹ��TIM3ʱ��

    /* ���ö�ʱ������ */
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM_Period;        //�����Զ���װ�ؼĴ������ڵ�ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = BASIC_TIM_Prescaler;  //����ʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //����ʱ�ӷָ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM ���ϼ���
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //��ʼ�� TIM3

    //========= NVIC���� =========//
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           // TIM3 �ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ� 0 ��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //�����ȼ� 3 ��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ ͨ����ʹ��
    NVIC_Init(&NVIC_InitStructure);                           //��ʼ�� NVIC �Ĵ���

    /* �����ж� */
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //ʹ��TIM3��ʱ���ж�
    
    /* ʹ�ܶ�ʱ�� */
    TIM_Cmd(TIM3, ENABLE); //ʹ��TIM3��ʱ��
}

/**
 * @brief   
 * @param   [In]
 * @param   [Out]
 * @return  
 * @version 1.0.0
 * @date    2022-06-30
 * @note    
 **/
void TIM3_IRQHandler(void) // TIM3 �ж�
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //��� TIM3 �����жϷ������
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //��� TIM3 �����жϱ�־
    }
}

/*================================= �ļ���β =================================*/
