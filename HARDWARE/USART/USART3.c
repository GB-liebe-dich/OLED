/*******************************************************************************
 * Copyright (C), 2022, 羽落叶秋
 * @file    USART3.c
 * @brief   
 * @details 
 * @author  羽落叶秋
 * @version 1.0.0
 * @date    2022年02月24日
 * ----------------------------------------------------------------------------*
 * 修改记录:
 * <日期>     | <版本> | <作者>   | <修改记录>
 * ----------------------------------------------------------------------------*
 * 2022-02-24 | 1.0.0 | 羽落叶秋  | 创建文件并实现功能
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ 头文件包含 =================================*/
#include "USART3.h"
#include "delay.h"
#include "string.h"

/*================================= 全局变量 =================================*/
USART_RX_TypeDef g_USART3_RxData = {0};   //串口3接收数据

/*================================= 私有函数 =================================*/
/**
 * @brief   串口3中断处理函数
 * @param   [In]无
 * @param   [Out]无
 * @return  无
 * @version 1.0.0
 * @date    2022-02-24
 * @note    
**/
void USART3_IRQHandler(void)
{
    uint8 tRxData; //接收数据缓存
    if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)   //读数据寄存器非空
    {
        /* 清中断标志 */
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);     //???必要
        /* 缓存数据 */
        tRxData =USART_ReceiveData(USART3);
        /* 正常数据接收 */
        if(g_USART3_RxData.RxLen < USART_RX_MAX)
        {
            g_USART3_RxData.USART_RX_BUF[g_USART3_RxData.RxLen++] = tRxData;

            /* AT指令判断 */
            switch (tRxData)
            {
            case 0x0D:
                g_USART3_RxData.RX_AT_Flag = 0x55;
                break;
            case 0x0A:
                if(g_USART3_RxData.RX_AT_Flag == 0x55)
                {
                    g_USART3_RxData.RX_AT_Flag = 0xAA;  //接收到AT指令
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

/*================================= 接口函数 =================================*/
/**
 * @brief   初始化USART3
 * @param   [In]bound：波特率
 * @param   [Out]无
 * @return  无
 * @version 1.0.0
 * @date    2022-02-22
 * @note    
**/
void USART3_Init(uint32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* GPIO 时钟使能，串口时钟使能 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //GPIOB时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);   //USART3时钟使能

    /* 复位串口 */
    USART_DeInit(USART3);

    /* GPIO 端口模式设置 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;              //USART3_TX，PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         //复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);                  //初始化PB10

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;              //USART3_RX，PB11
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   //浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);                  //初始化PB11

    /* 串口参数初始化 */
    USART_InitStructure.USART_BaudRate = bound;                 //设置波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //8位数据格式
    USART_InitStructure.USART_StopBits = USART_StopBits_1;      //一个停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;         //无奇偶校验位
    USART_InitStructure.USART_HardwareFlowControl 
                            = USART_HardwareFlowControl_None;   //无硬件数据流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式
    USART_Init(USART3, &USART_InitStructure);                       //初始化串口3
    
    /* 初始化 NVIC */
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;      //子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;         //IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);                         //中断优先级初始化

    /* 开启中断 */
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  //开启中断

    /* 使能串口 */
    USART_Cmd(USART3, ENABLE);                      //使能串口
}

/**
 * @brief   串口发送数据
 * @param   [In]UARTx：要发送数据的串口
 * @param   [In]pSrcStr：要发送的数据
 * @param   [In]tSrcLen：要发送数据的长度
 * @param   [Out]无
 * @return  无
 * @version 1.0.0
 * @date    2022-02-24
 * @note    
**/
void UartxSendData(USART_TypeDef *UARTx, uint8 *pAimStr, uint16 tSrcLen)
{
    uint16 i;
    
    for(i = 0; i < tSrcLen; i++)
    {
        while(USART_GetFlagStatus(UARTx,USART_FLAG_TC) != SET); //无正在发送的数据
        USART_SendData(UARTx, pAimStr[i]);                      //串口发送数据
    }
    while(USART_GetFlagStatus(UARTx,USART_FLAG_TC) != SET);     //等待发送结束
}

/**
 * @brief   串口发送字符串
 * @param   [In]UARTx：要发送数据的串口
 * @param   [In]pSrcStr：要发送的数据
 * @param   [Out]无
 * @return  无
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
        while(USART_GetFlagStatus(UARTx,USART_FLAG_TC) != SET); //无正在发送的数据
        USART_SendData(UARTx, pAimStr[i]);                      //串口发送数据
    }
    while(USART_GetFlagStatus(UARTx,USART_FLAG_TC) != SET);     //等待发送结束
}

/**
 * @brief   等待AT指令回应
 * @param   [In]pAimStr：等待返回的数据
 * @param   [In]pSrcStr：等待数据存储的位置
 * @param   [In]tWaiteTime：等待时间，单位20ms
 * @param   [Out]无
 * @return  0：等待成功，1：等待失败
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
 * @brief   发送AT指令并等待返回
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
    memset(&g_USART3_RxData.RxLen, 0x00, sizeof(g_USART3_RxData));   //清结构体
    UartxSendStr(UARTx, SendData);
    return UartxWaitAT(pAimStr, pSrcStr, tWaiteTime);
}

/*================================= 文件结尾 =================================*/
