/*******************************************************************************
 * Copyright (C), 2021, 羽落叶秋
 * @file    display.h
 * @brief   
 * @details 
 * @author  羽落叶秋
 * @version 1.0.0
 * @date    2021年12月12日
 * @History:
 *      1. Date: 2021-12-12
 *         Author: 羽落叶秋
 *         Modification: 新建
 ******************************************************************************/
#ifndef __DISPLAY_H
#define __DISPLAY_H

/*================================ 头文件包含 =================================*/
#include "Clibrary.h"

/*=============================== 宏定义/重定义 ===============================*/


/*============================= 结构体/联合体定义 =============================*/
/**
 * @brief 显示界面枚举体，用来表示当前界面
 * @note  
**/
typedef enum _interface {
    main_interface = 0, //主界面
    menu_interface,     //菜单界面
    WiFiSet_interface,  //WiFi设置界面
    Update_interface    //更新参数界面
} INTERFACE;

/**
 * @brief 界面属性结构体
 * @note  
**/
typedef struct _display {
    INTERFACE Now_interface;    /* 当前显示界面 */
    uint8 Interface_State;      /*当前界面状态，0xAA：界面已初始化完成，其他：界面未初始化 */
} DISPLAY;

/**
 * @brief 光标显示及动作相关变量结构体
 * @note  
**/
typedef struct _cursor {
    uint8 state;    /* 选择状态，0：隐藏，1：选择，2：设置 */
    uint8 position;   /* 光标目前所在位置 */
    uint8 twinkle;   /* 光标闪烁标志 */
} CURSOR;

/*================================= 全局变量 =================================*/
extern DISPLAY g_Display;   /* 显示界面 */
extern CURSOR g_SetWifi_Cursor;    /* WiFi参数设置界面光标 */
extern u8 temperature;
extern u8 humidity;

/*================================= 接口函数 =================================*/
void Dis_PowerOn(void); /* 开机动画 */
void Dis_MainInterface(void);   /* 显示主界面 */
void Dis_Wificonfig(void);  /* 显示WIFI用户名和密码配置页面 */

/*================================= 私有函数 =================================*/


#endif
/*================================= 文件结尾 =================================*/
