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

#define BIG_DATA                0xAA                    //大端数据
#define SMALL_DATA              0x55                    //小端数据

typedef signed char     int8;
typedef unsigned char   uint8;
typedef short           int16;
typedef unsigned short  uint16;
typedef int             int32;
typedef unsigned        uint32;

/*============================= 结构体/联合体定义 =============================*/
//------------------------------------------------------//
//类型定义
//四字节结构体类型定义
//------------------------------------------------------//
typedef union
{
	u8  Data[4];
	u32 val;
	struct
	{
		u8 byte0;
	    u8 byte1;
		u8 byte2;
		u8 byte3;
	}St;
	struct
	{
		u16 val_L;
		u16 val_H;
	}St1;
}U32STR_Def;											//4个字节 结构体定义

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
extern uint16 HexToAsc(u8 *pHEX, u16 lenHEX, char *pASC);
extern uint16 HexToStr(u8 *pHEX, u16 lenHEX, char *pASC);
extern void uLongToByte(u32 uData, u8 *Byte, u8 DataType);

#endif
/*================================= 文件结尾 =================================*/
