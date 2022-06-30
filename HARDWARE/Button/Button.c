/*******************************************************************************
 * Copyright (C), 2022, 羽落叶秋
 * @file    Button.c
 * @brief
 * @details
 * @author  羽落叶秋
 * @version 1.0.0
 * @date    2022年04月14日
 * ----------------------------------------------------------------------------*
 * 修改记录:
 * <日期>     | <版本> | <作者>   | <修改记录>
 * ----------------------------------------------------------------------------*
 * 2022-04-14 | 1.0.0 | 羽落叶秋  | 创建文件并实现功能
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ 头文件包含 =================================*/
#include "Button.h"
#include "display.h"

/*================================= 全局变量 =================================*/
#ifdef BUTTON_INTERRUPT
uint8 Button_EXIT; //按键中断标志，0xAA表示有按键中断事件，其他值无
#endif
BUTTON_ATTRIBUTE user_button[USER_BUTTON_MAX]; //按键定义

/*================================= 私有函数 =================================*/
/**
 * @brief   获取按键状态
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
 * @brief   初始化按键参数
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-04-24
 * @note
 **/
void UserButtonInit(void)
{
    uint8 i; //用于for循环

    for (i = 0; i < USER_BUTTON_MAX; i++)
    {
        //========= 初始化默认参数 =========//
        user_button[i].ID = i;                                    //初始化按键编号
        user_button[i].Button_read = GetButtonValue;              //初始化按键状态
        user_button[i].Button_state = BOUNCE;                     //初始化按键状态，弹起
        user_button[i].Button_event = DEFAULT;                    //初始化按键事件，空
        user_button[i].Debounce_Time = SHAKE_TIME;                //初始化消抖时间
        user_button[i].Double_Click_Time = DOUBLE_C_TIME;         //初始化化双击有效间隔
        user_button[i].Long_Click_Time = LONG_C_TIME;             //初始化长按键有效时间
        user_button[i].Pressed_Logic_Level = DEFAULT_LOGIC_LEVEL; //初始化逻辑电平
        user_button[i].scan_cnt = 0;                              //初始化扫描次数
        user_button[i].click_cnt = 0;                             //初始化单击次数
        user_button[i].EN_EXTI = 0;                               //默认关闭外部中断使能

        //========= 初始化非默认参数 =========//
        if ((i == USER_BUTTON_1) || (i == USER_BUTTON_2))
        {
            user_button[i].EN_EXTI = 0xAA; //开启EC11外部中断使能
        }
    }
}
/**
 * @brief   获取当前按键状态
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-06-06
 * @note
 **/
uint32 GetButtonData(void)
{
    uint8 i;                //用于for循环
    uint32 tButtonData = 0; //按键状态，每一位代表一个按键是否被按下，1：按下 0：弹起

    /* 一次性读取全部按键状态，存在tButtonData中，每1位代表一个按键状态，按键1在最低位 */
    for (i = 0; i < USER_BUTTON_MAX; i++)
    {
        tButtonData |= (((user_button[i].Button_read)(&user_button[i]) ^ user_button[i].Pressed_Logic_Level)
                        << i); //获取按键状态
    }

    return tButtonData;
}

/**
 * @brief   获取当前按键事件
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-05-04
 * @note
 **/
uint32 GetButtonEvent(uint32 button_data)
{
    uint8 i;                 //用于for循环
    uint32 tButtonEvent = 0; //缓存按键事件

    /* 获取按键事件 */
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
        /* 按键事件状态机 */
        switch (user_button[i].Button_state)
        {
        case BOUNCE:                       //弹起状态
            if ((button_data >> i) & 0x01) //按键按下
            {
                if (user_button[i].Button_event == DEFAULT)
                {
                    user_button[i].scan_cnt = 0;
                    user_button[i].click_cnt = 0;
                    user_button[i].Button_event = PENDING; //置按键事件待定
                }
                else if (user_button[i].scan_cnt >= user_button[i].Debounce_Time) //消抖
                {
                    user_button[i].Button_state = PRESS;
                }
            }
            else //消抖失败
            {
                if (user_button[i].click_cnt > 1)
                {
                    user_button[i].click_cnt = 0;
                    user_button[i].Button_event = DOUBLE_CLICK; //连击
                    tButtonEvent |= (1 << i);
                }
                else if (user_button[i].click_cnt == 1)
                {
                    user_button[i].click_cnt = 0;
                    user_button[i].Button_event = SINGLE_CLICK; //单击
                    tButtonEvent |= (1 << i);
                }
                else
                {
                    user_button[i].Button_event = DEFAULT; //无按键
                }
            }
            break;
        case PRESS:                        //按下状态
            if ((button_data >> i) & 0x01) //按键按下
            {
                if (user_button[i].click_cnt > 0)
                {
                    user_button[i].click_cnt = 0;
                    user_button[i].Button_event = DOUBLE_CLICK; //连击
                    user_button[i].Button_state = KEEP_CLICK;   //等待按键弹起
                    tButtonEvent |= (1 << i);
                }
                else if (user_button[i].scan_cnt >= user_button[i].Long_Click_Time)
                {
                    user_button[i].Button_event = LONG_CLICK; //长按键
                    user_button[i].Button_state = KEEP_CLICK; //等待按键弹起
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
        case PRESS_BOUNCE:                 //回弹等待状态
            if ((button_data >> i) & 0x01) //按键按下
            {
                user_button[i].scan_cnt = 0;
                user_button[i].Button_state = BOUNCE;
                user_button[i].Button_event = PENDING; //直接置按键待定，即开始消抖
            }
            else
            {
                if (user_button[i].scan_cnt >= user_button[i].Double_Click_Time)
                {
                    if (user_button[i].click_cnt > 1)
                    {
                        user_button[i].click_cnt = 0;
                        user_button[i].Button_event = DOUBLE_CLICK; //连击
                        tButtonEvent |= (1 << i);
                    }
                    else
                    {
                        user_button[i].click_cnt = 0;
                        user_button[i].Button_event = SINGLE_CLICK; //点击
                        tButtonEvent |= (1 << i);
                    }
                    user_button[i].Button_state = BOUNCE;
                }
            }
            break;
        case KEEP_CLICK:
            if (!((button_data >> i) & 0x01)) //等待按键弹起
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
 * @brief   获取EC11动作
 * @param   [In]
 * @param   [Out]
 * @return  
 * @version 1.0.0
 * @date    2022-06-10
 * @note    
 **/
uint8 GetEC11Data(void)
{
    uint8 tDirection = 0;   //转动方向，0xAA表示正转，0x55表示反转，其他表示无转动

    if (EC11_A_EVENT == SINGLE_CLICK)
    {
        if (EC11_B_EVENT == SINGLE_CLICK) //正转
        {
            tDirection = 0xAA;
        }
        else //反转
        {
            tDirection = 0x55;
        }
    }

    return tDirection;
}

/**
 * @brief   按键任务
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-06-06
 * @note
 **/
void Buttontask(void)
{
    uint8 i;    //用于for循环
    uint8 tEC11Data;    //缓存EC11键值
    
    //========= 按键事件处理 =========//
    if ((KEY_EVENT > PENDING) || (EC11_A_EVENT >PENDING))
    {
        if (g_SetWifi_Cursor.state) //选择或设置状态光标指针才有效
        {
            tEC11Data = GetEC11Data(); //获取EC11状态

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
                  g_SetWifi_Cursor.state = 0x55;    //进入选择状态
                  g_SetWifi_Cursor.position = 0x01; //从1开始
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

    //========= 清除按键事件 =========//
    for (i = 0; i < USER_BUTTON_MAX; i++)
    {
        user_button[i].Button_event = DEFAULT;
    }
}

/*================================= 接口函数 =================================*/
/**
 * @brief   按键初始化
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

    //========= 普通GPIO配置 =========//
    /* 使能对应端口时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE); //使能PA,PB端口时钟

    /* 配置IO口参数 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; // EC11对应PA0和PA1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          //上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      // IO口速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;         // Key对应PB0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;     //上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // IO口速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

#ifdef BUTTON_INTERRUPT
    //========= 外部中断配置 =========//
    /* 使能对应时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //使能复用功能时钟

    /* 配置中断参数 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1); // PA.1
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;                  //配置中断线1
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;         //中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //下降沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;                   //使能中断线
    EXTI_Init(&EXTI_InitStructure);

    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0); // PB.0
    // EXTI_InitStructure.EXTI_Line = EXTI_Line0;                  //配置中断线1
    // EXTI_Init(&EXTI_InitStructure);

    //========= NVIC配置 =========//
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;             //使能PA.1所在的外部中断通道
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //抢占优先级2，
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;        //子优先级2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);

    // NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;             //使能PB.0所在的外部中断通道
    // NVIC_Init(&NVIC_InitStructure);
#endif

    //========= 其他配置 =========//
    /* 初始化自定义参数 */
    UserButtonInit(); //按键参数初始化
}

/**
 * @brief   按键事件处理
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-05-19
 * @note
 **/
void HandleButtonEvent(void)
{
    uint32 tButtonData; //缓存按键键值

    tButtonData = GetButtonData();

    if (GetButtonEvent(tButtonData)) //有按键按下
    {
        Buttontask(); //执行按键任务
    }
}

#ifdef BUTTON_INTERRUPT
// /**
//  * @brief   EXTI0中断服务函数，对应PB0，KEY
//  * @param   [In]
//  * @param   [Out]
//  * @return
//  * @version 1.0.0
//  * @date    2022-05-03
//  * @note
//  **/
// void EXTI0_IRQHandler(void)
// {
//     if (EXTI_GetITStatus(EXTI_Line0) != RESET) //判断某个线上的中断是否发生
//     {

//         EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位
//     }
// }

/**
 * @brief   EXTI1中断服务函数，对应PA1，EC11_A
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2022-05-03
 * @note
 **/
void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) //判断某个线上的中断是否发生
    {
        Button_EXIT = 0xAA;                 //置按键中断事件标志
        EXTI_ClearITPendingBit(EXTI_Line1); //清除LINE1上的中断标志位
    }
}
#endif

/*================================= 文件结尾 =================================*/
