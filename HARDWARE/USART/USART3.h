/*******************************************************************************
 * Copyright (C), 2022, ����Ҷ��
 * @file    USART3.h
 * @brief   
 * @details 
 * @author  ����Ҷ��
 * @version 1.0.0
 * @date    2022��02��24��
 * @History:
 *      1. Date: 2022-02-24
 *         Author: ����Ҷ��
 *         Modification: �½�
 ******************************************************************************/
#ifndef __USART3_H
#define __USART3_H

/*================================ ͷ�ļ����� =================================*/
#include "Clibrary.h"

/*=============================== �궨��/�ض��� ===============================*/
#define USART_RX_MAX  (300)

/*============================= �ṹ��/�����嶨�� =============================*/
/**
 * @brief ���ڽ��սṹ��
 * @note  
**/
typedef struct _usart_rx {
    uint16 RxLen;       //�������ݵĳ���
    uint8 Rx_Data_Flag; //���յ����ݱ�־��0xAA���յ����ݣ�0x55��ʾ���ݴ������
    uint8 RX_AT_Flag;   //���յ�AT�����־
    uint8 USART_RX_BUF[USART_RX_MAX];//���յ�������
} USART_RX_TypeDef;


/*================================= ȫ�ֱ��� =================================*/
extern USART_RX_TypeDef g_USART3_RxData;

/*================================= ˽�к��� =================================*/


/*================================= �ӿں��� =================================*/
extern void USART3_Init(uint32 bound);
extern void UartxSendData(USART_TypeDef *UARTx, uint8 *pAimStr, uint16 tSrcLen);
extern void UartxSendStr(USART_TypeDef *UARTx, uint8 *pAimStr);
extern uint8 UartxWaitAT(uint8 *pAimStr, uint8 *pSrcStr, uint16 tWaiteTime);
extern uint8 UartxSendAT(USART_TypeDef* UARTx, uint8 *SendData, uint8 *pAimStr, 
                                            uint8 *pSrcStr, uint16 tWaiteTime);

#endif
/*================================= �ļ���β =================================*/
