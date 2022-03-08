#include "delay.h"
#include "stm32f10x_exti.h"
#include "exit.h"
#include "key.h"
#include "delay.h"
#include "display.h"
#include "ESP8266.h"

uint8 test_cnt = 0;

/* 按键中断 */
void EC11_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) //判断某个线上的中断是否发生
    {
        delay_ms(10); //消抖
        if (EC11_scan() == 1)
        {
            if (g_SetWifi_Cursor.state == 1) /* 选择状态 */
            {
                if (g_SetWifi_Cursor.position <= sizeof(g_Wifi.ssid))
                {
                    g_SetWifi_Cursor.position++;
                }
            }
            else if (g_SetWifi_Cursor.state == 2) /* 设置状态 */
            {
                g_Wifi.ssid[g_SetWifi_Cursor.position]++;
            }
        }
        else if (EC11_scan() == 2)
        {
            if ((g_SetWifi_Cursor.state == 1) && (g_SetWifi_Cursor.position > 0)) /* 选择状态 */
            {
                g_SetWifi_Cursor.position--;
            }
            else if (g_SetWifi_Cursor.state == 2) /* 设置状态 */
            {
                g_Wifi.ssid[g_SetWifi_Cursor.position]--;
            }
        }

        EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE0上的中断标志位
    }
}

//外部中断0服务程序
void EXTIX_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //使能复用功能时钟

    //GPIOE.2 中断线以及中断初始化配置   下降沿触发
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);

    EXTI_InitStructure.EXTI_Line = EXTI_Line1; //KEY2
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;             //使能按键KEY2所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //抢占优先级2，
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;        //子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);
}

//外部中断1服务程序
void EXTI1_IRQHandler(void)
{
    EC11_IRQHandler();
}
