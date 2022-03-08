/*******************************************************************************
 * Copyright (C), 2021, 羽落叶秋
 * @file    CLibrary.c
 * @brief   C语言算法函数库
 * @details
 * @author  羽落叶秋
 * @version 1.0.0
 * @date    2021年12月18日
 * ----------------------------------------------------------------------------*
 * 修改记录:
 * <日期>     | <版本> | <作者>   | <修改记录>
 * ----------------------------------------------------------------------------*
 * 2021-12-18 | 1.0.0 | 羽落叶秋  | 创建文件并实现功能
 * 2022-2-4   | 1.0.1 | 羽落叶秋  | DecToChar()函数增加：tlength变量及其相关描述
 * 2022-2-16  | 1.0.2 | 羽落叶秋  | DecToChar()函数修复输入数字大于2位时出错问题
 * 2022-3-3   | 1.0.3 | 羽落叶秋  | 新增EngMonthGetNum()和EngWeekGetNum
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ 头文件包含 =================================*/
#include "CLibrary.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

/*================================= 全局变量 =================================*/

/*================================= 私有函数 =================================*/
/**
 * @brief   获取十进制数位数
 * @param   [In]number：十进制数
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2021-12-22
 * @note
 **/
uint8 GetDecDigit(uint32 number)
{
    /* 方法1 */
    return (number ? ((uint8)log10(number) + 1) : 1); //必须强制类型转换
    // return (number ? (uint8)log10(abs(number))+1 : 1);  //abs()：取绝对值，处理负数时可用

    /* 方法2 */
    // uint8 tDigit=0;
    // if(number==0)
    //     return 1;
    // while(number)
    // {
    //     tDigit++;
    //     number /= 10;
    // }
    // return tDigit;
}

/*================================= 接口函数 =================================*/
/**
 * @brief   十进制数转字符串
 * @param   [In]number: 十进制数
 * @param   [In]tlength：目标字符串长度，为0时自动获取数据长度
 * @param   [Out]*pAimStr: 转化后的字符串
 * @return  tAimStrLen
 * @version 1.1.1
 * @date    2022-2-16
 * @note    传入：123,0；传出：0x31,0x32,0x33；返回：3
 *          传入：123,4；传出：0x30,0x31,0x32,0x33；返回：4
 **/
uint8 DecToChar(uint32 number, uint8 tlength, uint8 *pAimStr)
{
    uint32 tNumber;     //缓存待转换number
    uint8 tAimStrLen;   //目标字符串长度
    uint8 tLen;         //缓存目标字符串长度，用于转换

    /* 获取目标字符串长度 */
    if (tlength == 0)
    {
        tAimStrLen = GetDecDigit(number);   //自动获取十进制数位数
    }
    else
    {
        tAimStrLen = tlength;               //自定义十进制数位数
    }
    /* 数据转换 */
    tNumber = number;                       //取待转换数字
    tLen = tAimStrLen;                      //取目标字符串长度
    do{
        tLen--;
        pAimStr[tLen] = ((tNumber % 10) + '0');
        tNumber /= 10;
    }while (tLen);

    /* 返回目标字符串长度 */
    return tAimStrLen;
}

/**
 * @brief   十六进制转BCD码
 * @param   [In]
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2021-12-22
 * @note
 **/
uint8 Hex2Bcd(uint8 tHex)
{
    return (((tHex / 10) << 4) | (tHex % 10));
}

/**
 * @brief   BCD码转十六进制
 * @param   [In]tBcd：BCD码
 * @param   [Out]
 * @return  转换后的十六进制数
 * @version 1.00
 * @date    2021-10-12
 * @note
 **/
uint8 Bcd2Hex(uint8 tBcd)
{
    return (((tBcd >> 4) * 10) + (tBcd & 0x0F));
}

/**
 * @brief   在一个字符串中查找特定字符串，并返回特定字符串的首位置
 * @param   [In]*pSrcStr：被查找的源字符串
 * @param   [In]tSrcLen：源字符串长度
 * @param   [In]*pAimStr：要查找的目标字符串
 * @param   [In]tAimLen：目标字符串长度
 * @param   [Out]
 * @return  i：找到字符串返回查询到的首位置；
 *          invalid：-1，未找到返回无效值
 * @version 1.0.0
 * @date    2021-12-18
 * @note    从字符串“0123456789”中找到“567”，返回5
 *          {[Pos（position）：位置，地点]；[Src（source）：来源，出处]；[Aim：目标，目的]；}
 **/
int16 FindStrPos(const uint8 *pSrcStr, int16 tSrcLen, const uint8 *pAimStr, int16 tAimLen)
{
    int16 i;
    int16 tlen = tSrcLen - tAimLen + 1;

    for (i = 0; i < tlen; i++)
    {
        if (memcmp(pSrcStr + i, pAimStr, tAimLen) == 0)
        {
            return i;
        }
    }
    return invalid;
}

/**
 * @brief   输入月份英文，获取对应数值（1-12）
 * @param   [In]*pAimStr：存储要对比的字符的指针
 * @param   [In]tlength：要对比的字节数
 * @param   [Out]无
 * @return  i：对应月份
 * @version 1.0.0
 * @date    2022-03-03
 * @note    
**/
uint8 EngMonthGetNum(uint8 *pAimStr, uint8 tlength)
{
    uint8 i;
    uint8 mouth = 0;
    uint8 *mouths[12]={"January","February","March","April","May","June","July",
                       "August","September","October","November","December"};
    for(i = 0; i < 12; i++)
    {
        mouth++;
        if(!memcmp(mouths[i], pAimStr, tlength))
        {
            return mouth;
        }
    }

    return 0;
}

/**
 * @brief   输入星期英文，获取对应数值（1-7）
 * @param   [In]*pAimStr：存储要对比的字符的指针
 * @param   [In]tlength：要对比的字节数
 * @param   [Out]无
 * @return  i：对应月份
 * @version 1.0.0
 * @date    2022-03-03
 * @note    
**/
uint8 EngWeekGetNum(uint8 *pAimStr, uint8 tlength)
{
    uint8 i;
    uint8 week;
    uint8 weeks[7][10]={"monday","tuesday","wednesday","thursday","friday",
                        "saturday","sunday"};
    for(i = 0; i < 7; i++)
    {
        week++;
        if(!memcmp(weeks[i], pAimStr, tlength))
        {
            return week;
        }
    }

    return 0;
}

/*================================= 文件结尾 =================================*/
