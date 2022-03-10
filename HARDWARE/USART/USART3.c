/*******************************************************************************
 * Copyright (C), 2022, ����Ҷ��
 * @file    USART3.c
 * @brief   
 * @details 
 * @author  ����Ҷ��
 * @version 1.0.0
 * @date    2022��02��24��
 * ----------------------------------------------------------------------------*
 * �޸ļ�¼:
 * <����>     | <�汾> | <����>   | <�޸ļ�¼>
 * ----------------------------------------------------------------------------*
 * 2022-02-24 | 1.0.0 | ����Ҷ��  | �����ļ���ʵ�ֹ���
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ ͷ�ļ����� =================================*/
#include "USART3.h"
#include "delay.h"
#include "string.h"

/*================================= ȫ�ֱ��� =================================*/
USART_RX_TypeDef g_USART3_RxData = {0};   //����3��������

/*================================= ˽�к��� =================================*/
/**
 * @brief   ����3�жϴ�����
 * @param   [In]��
 * @param   [Out]��
 * @return  ��
 * @version 1.0.0
 * @date    2022-02-24
 * @note    
**/
void USART3_IRQHandler(void)
{
    uint8 tRxData; //�������ݻ���
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)   //�����ݼĴ����ǿ�
    {
        /* ���жϱ�־ */
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);     //???��Ҫ
        /* �������� */
        tRxData =USART_ReceiveData(USART3);
        /* �������ݽ��� */
        if(g_USART3_RxData.RxLen < USART_RX_MAX)
        {
            g_USART3_RxData.USART_RX_BUF[g_USART3_RxData.RxLen++] = tRxData;

            /* ATָ���ж� */
            switch (tRxData)
            {
            case 0x0D:
                g_USART3_RxData.RX_AT_Flag = 0x55;
                break;
            case 0x0A:
                if(g_USART3_RxData.RX_AT_Flag == 0x55)
                {
                    g_USART3_RxData.RX_AT_Flag = 0xAA;  //���յ�ATָ��
                }
                break;
            default:
                if(g_USART3_RxData.RX_AT_Flag != 0xAA)
                {
                    g_USART3_RxData.RX_AT_Flag = 0x00;
                }
                break;
            }
        }
    }
}

/*================================= �ӿں��� =================================*/
/**
 * @brief   ��ʼ��USART3
 * @param   [In]bound��������
 * @param   [Out]��
 * @return  ��
 * @version 1.0.0
 * @date    2022-02-22
 * @note    
**/
void USART3_Init(uint32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* GPIO ʱ��ʹ�ܣ�����ʱ��ʹ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //GPIOBʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);   //USART3ʱ��ʹ��

    /* ��λ���� */
    USART_DeInit(USART3);

    /* GPIO �˿�ģʽ���� */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;              //USART3_TX��PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);                  //��ʼ��PB10

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;              //USART3_RX��PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);                  //��ʼ��PB11

    /* ���ڲ�����ʼ�� */
    USART_InitStructure.USART_BaudRate = bound;                 //���ò�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;         //����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl 
                            = USART_HardwareFlowControl_None;   //��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ
    USART_Init(USART3, &USART_InitStructure);                       //��ʼ������3
    
    /* ��ʼ�� NVIC */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;      //�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);                         //�ж����ȼ���ʼ��

    /* �����ж� */
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  //�����ж�

    /* ʹ�ܴ��� */
    USART_Cmd(USART3, ENABLE);                      //ʹ�ܴ���
}

/**
 * @brief   ���ڷ�������
 * @param   [In]UARTx��Ҫ�������ݵĴ���
 * @param   [In]pSrcStr��Ҫ���͵�����
 * @param   [In]tSrcLen��Ҫ�������ݵĳ���
 * @param   [Out]��
 * @return  ��
 * @version 1.0.0
 * @date    2022-02-24
 * @note    
**/
void UartxSendData(USART_TypeDef *UARTx, uint8 *pAimStr, uint16 tSrcLen)
{
    uint16 i;
    
    for(i = 0; i < tSrcLen; i++)
    {
        while(USART_GetFlagStatus(UARTx,USART_FLAG_TC) != SET); //�����ڷ��͵�����
        USART_SendData(UARTx, pAimStr[i]);                      //���ڷ�������
    }
    while(USART_GetFlagStatus(UARTx,USART_FLAG_TC) != SET);     //�ȴ����ͽ���
}

/**
 * @brief   ���ڷ����ַ���
 * @param   [In]UARTx��Ҫ�������ݵĴ���
 * @param   [In]pSrcStr��Ҫ���͵�����
 * @param   [Out]��
 * @return  ��
 * @version 1.0.0
 * @date    2022-02-25
 * @note    
**/
void UartxSendStr(USART_TypeDef *UARTx, uint8 *pAimStr)
{
    uint16 i;
    uint16 tDataLen;

    tDataLen = strlen(pAimStr);
    for(i = 0; i < tDataLen; i++)
    {
        while(USART_GetFlagStatus(UARTx,USART_FLAG_TC) != SET); //�����ڷ��͵�����
        USART_SendData(UARTx, pAimStr[i]);                      //���ڷ�������
    }
    while(USART_GetFlagStatus(UARTx,USART_FLAG_TC) != SET);     //�ȴ����ͽ���
}

/**
 * @brief   �ȴ�ATָ���Ӧ
 * @param   [In]pAimStr���ȴ����ص�����
 * @param   [In]pSrcStr���ȴ����ݴ洢��λ��
 * @param   [In]tWaiteTime���ȴ�ʱ�䣬��λ20ms
 * @param   [Out]��
 * @return  0���ȴ��ɹ���1���ȴ�ʧ��
 * @version 1.0.0
 * @date    2022-02-24
 * @note    
**/
uint8 UartxWaitAT(uint8 *pAimStr, uint8 *pSrcStr, uint16 tWaiteTime)
{
    uint16 i;

    for(i = 0; i < tWaiteTime; i += 20)
    {
        delay_ms(20);
        if(strstr(pSrcStr,pAimStr))
        {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief   ����ATָ��ȴ�����
 * @param   [In]
 * @param   [Out]
 * @return  
 * @version 1.0.0
 * @date    2022-02-25
 * @note    
**/
uint8 UartxSendAT(USART_TypeDef* UARTx, uint8 *SendData, uint8 *pAimStr, 
                                       uint8 *pSrcStr, uint16 tWaiteTime)
{
    memset(&g_USART3_RxData.RxLen, 0x00, sizeof(g_USART3_RxData));   //��ṹ��
    UartxSendStr(UARTx, SendData);
    return UartxWaitAT(pAimStr, pSrcStr, tWaiteTime);
}

/*================================= �ļ���β =================================*/
