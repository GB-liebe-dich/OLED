/*******************************************************************************
 * Copyright (C), 2022, 羽落叶秋
 * @file    USART3.h
 * @brief   
 * @details 
 * @author  羽落叶秋
 * @version 1.0.0
 * @date    2022年02月24日
 * @History:
 *      1. Date: 2022-02-24
 *         Author: 羽落叶秋
 *         Modification: 新建
 ******************************************************************************/
#ifndef __USART3_H
#define __USART3_H

/*================================ 头文件包含 =================================*/
#include "Clibrary.h"

/*=============================== 宏定义/重定义 ===============================*/
#define USART_RX_MAX  (300)

/*============================= 结构体/联合体定义 =============================*/
/**
 * @brief 串口接收结构体
 * @note  
**/
typedef struct _usart_rx {
    uint16 RxLen;       //接收数据的长度
    uint8 Rx_Data_Flag; //接收到数据标志，0xAA接收到数据，0x55表示数据处理完成
    uint8 RX_AT_Flag;   //接收到AT命令标志
    uint8 USART_RX_BUF[USART_RX_MAX];//接收到的数据
} USART_RX_TypeDef;


/*================================= 全局变量 =================================*/
extern USART_RX_TypeDef g_USART3_RxData;

/*================================= 私有函数 =================================*/


/*================================= 接口函数 =================================*/
extern void USART3_Init(uint32 bound);
extern void UartxSendData(USART_TypeDef *UARTx, uint8 *pAimStr, uint16 tSrcLen);
extern void UartxSendStr(USART_TypeDef *UARTx, uint8 *pAimStr);
extern uint8 UartxWaitAT(uint8 *pAimStr, uint8 *pSrcStr, uint16 tWaiteTime);
extern uint8 UartxSendAT(USART_TypeDef* UARTx, uint8 *SendData, uint8 *pAimStr, 
                                            uint8 *pSrcStr, uint16 tWaiteTime);

#endif
/*================================= 文件结尾 =================================*/
