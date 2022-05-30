/*******************************************************************************
 * Copyright (C), 2022, 羽落叶秋
 * @file    Button.h
 * @brief
 * @details
 * @author  羽落叶秋
 * @version 1.0.0
 * @date    2022年04月14日
 * @History:
 *      1. Date: 2022-04-14
 *         Author: 羽落叶秋
 *         Modification: 新建
 ******************************************************************************/
#ifndef __BUTTON_H
#define __BUTTON_H

/*================================ 头文件包含 =================================*/
#include "Clibrary.h"
#include "sys.h"

/*=============================== 宏定义/重定义 ===============================*/
#define QUERY_MODE 0 //为0表示仅采用定时查询方式，为1表示采用定时+中断方式
#if (QUERY_MODE == 1)
#define BUTTON_TIMING    //按键采用定时查询方式
#define BUTTON_INTERRUPT //按键采用中断查询方式
#else
#define BUTTON_TIMING //按键采用定时查询方式
#endif

#define Scan_interval 0       //扫描间隔
#define SHAKE_TIME 1          //消抖时间
#define DOUBLE_C_TIME 2       //双击有效间隔
#define LONG_C_TIME 3         //长按有效时间
#define DEFAULT_LOGIC_LEVEL 0 //默认逻辑电平
#define KEY PBin(0)
#define EC11_A PAin(1)
#define EC11_B PAin(0)

/*========================== 枚举体/联合体/结构体定义 ==========================*/
/**
 * @brief 按键声明
 * @note  添加或删除按键在这里声明
 **/
typedef enum
{
    USER_BUTTON_0 = 0, //按键1
    USER_BUTTON_1,     //按键2
    USER_BUTTON_2,     //按键3
    USER_BUTTON_MAX
};

/**
 * @brief 按键动作枚举体
 * @note
 **/
typedef enum
{
    BOUNCE = 0,  //弹起
    PRESS,       //按下
    PRESS_BOUNCE //回弹等待状态，等待多连击
} BUTTON_ACTION;

/**
 * @brief 按键动作枚举体
 * @note
 **/
typedef enum
{
    DEFAULT = 0,  //无事件
    PENDING,      //待定
    SINGLE_CLICK, //单点
    DOUBLE_CLICK, //双击
    LONG_CLICK    //长按
} BUTTON_EVENT;

/**
 * @brief 按键功能结构体
 * @note  {attribute：属性；}
 **/
typedef struct _button_attribute
{
    BUTTON_ACTION Button_state;   //按键状态
    BUTTON_EVENT Button_event;    //按键事件
    uint16 Debounce_Time;         //消抖时长
    uint16 Double_Click_Time;     //连击间隔
    uint16 Long_Click_Time;       //长按时长
    uint16 scan_cnt;              //记录扫描时间，按键按下是开始从零计数
    uint8 click_cnt;              //记录单击次数，用于判定单击、连击
    uint8 ID;                     //按键编号
    uint8 Pressed_Logic_Level;    //按键按下的逻辑电平。1：标识按键按下的时候为高电平；0：标识按键按下的时候未低电平
    uint8 (*Button_read)(void *); //读按键引脚电平
} BUTTON_ATTRIBUTE;

/*================================= 全局变量 =================================*/
extern BUTTON_ATTRIBUTE user_button[USER_BUTTON_MAX];

/*================================= 私有函数 =================================*/

/*================================= 接口函数 =================================*/

#endif
/*================================= 文件结尾 =================================*/
