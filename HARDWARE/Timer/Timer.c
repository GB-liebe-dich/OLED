/*******************************************************************************
 * Copyright (C), 2022, 羽落叶秋
 * @file    Timer.c
 * @brief   
 * @details 
 * @author  羽落叶秋
 * @version 1.0.0
 * @date    2022年06月30日
 * ----------------------------------------------------------------------------*
 * 修改记录:
 * <日期>     | <版本> | <作者>   | <修改记录>
 * ----------------------------------------------------------------------------*
 * 2022-06-30 | 1.0.0 | 羽落叶秋  | 创建文件并实现功能
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ 头文件包含 =================================*/
#include "Timer.h"

/*================================= 全局变量 =================================*/


/*================================= 私有函数 =================================*/


/*================================= 接口函数 =================================*/
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

    //========= 定时器配置 =========//
    /* 使能定时器时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //使能TIM3时钟

    /* 配置定时器参数 */
    TIM_TimeBaseStructure.TIM_Period = BASIC_TIM_Period;        //设置自动重装载寄存器周期的值
    TIM_TimeBaseStructure.TIM_Prescaler = BASIC_TIM_Prescaler;  //设置时钟频率除数的预分频值
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // TIM 向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //初始化 TIM3

    //========= NVIC配置 =========//
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           // TIM3 中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级 0 级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级 3 级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           // IRQ 通道被使能
    NVIC_Init(&NVIC_InitStructure);                           //初始化 NVIC 寄存器

    /* 开启中断 */
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //使能TIM3定时器中断
    
    /* 使能定时器 */
    TIM_Cmd(TIM3, ENABLE); //使能TIM3定时器
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
void TIM3_IRQHandler(void) // TIM3 中断
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查 TIM3 更新中断发生与否
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除 TIM3 更新中断标志
    }
}

/*================================= 文件结尾 =================================*/
