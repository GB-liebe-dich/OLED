/*******************************************************************************
 * Copyright (C), 2021, 羽落叶秋
 * @file    CLibrary.h
 * @brief   
 * @details 
 * @author  羽落叶秋
 * @version 1.0.0
 * @date    2021年12月18日
 * @History:
 *      1. Date: 2021-12-18
 *         Author: 羽落叶秋
 *         Modification: 新建
 ******************************************************************************/
#ifndef __CLIBRARY_H
#define __CLIBRARY_H

/*================================ 头文件包含 =================================*/
#include "stm32f10x.h"

/*=============================== 宏定义/重定义 ===============================*/
#define invalid (-1)    /* 无效 */
#define SUCCESS (0)
#define FAIL    (1)

typedef signed char     int8;
typedef unsigned char   uint8;
typedef short           int16;
typedef unsigned short  uint16;
typedef int             int32;
typedef unsigned        uint32;

/*============================= 结构体/联合体定义 =============================*/


/*================================= 全局变量 =================================*/


/*================================= 私有函数 =================================*/
uint8 GetDecDigit(uint32 number);

/*================================= 接口函数 =================================*/
extern uint8 DecToChar(uint32 number, uint8 tlength, uint8 *pDstStr);
extern uint8 Hex2Bcd(uint8 tHex);
extern uint8 Bcd2Hex(uint8 tBcd);
extern int16 FindStrPos(const uint8 *pSrcStr, int16 tSrcLen, const uint8 *pAimStr, int16 tAimLen);
extern uint8 EngMonthGetNum(uint8 *pAimStr, uint8 tlength);
extern uint8 EngWeekGetNum(uint8 *pAimStr, uint8 tlength);

#endif
/*================================= 文件结尾 =================================*/
