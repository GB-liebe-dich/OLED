/*******************************************************************************
 * Copyright (C), 2021, ����Ҷ��
 * @file    CLibrary.c
 * @brief   C�����㷨������
 * @details
 * @author  ����Ҷ��
 * @version 1.0.0
 * @date    2021��12��18��
 * ----------------------------------------------------------------------------*
 * �޸ļ�¼:
 * <����>     | <�汾> | <����>   | <�޸ļ�¼>
 * ----------------------------------------------------------------------------*
 * 2021-12-18 | 1.0.0 | ����Ҷ��  | �����ļ���ʵ�ֹ���
 * 2022-2-4   | 1.0.1 | ����Ҷ��  | DecToChar()�������ӣ�tlength���������������
 * 2022-2-16  | 1.0.2 | ����Ҷ��  | DecToChar()�����޸��������ִ���2λʱ��������
 * 2022-3-3   | 1.0.3 | ����Ҷ��  | ����EngMonthGetNum()��EngWeekGetNum
 * ----------------------------------------------------------------------------*
 ******************************************************************************/

/*================================ ͷ�ļ����� =================================*/
#include "CLibrary.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

/*================================= ȫ�ֱ��� =================================*/

/*================================= ˽�к��� =================================*/
/**
 * @brief   ��ȡʮ������λ��
 * @param   [In]number��ʮ������
 * @param   [Out]
 * @return
 * @version 1.0.0
 * @date    2021-12-22
 * @note
 **/
uint8 GetDecDigit(uint32 number)
{
    /* ����1 */
    return (number ? ((uint8)log10(number) + 1) : 1); //����ǿ������ת��
    // return (number ? (uint8)log10(abs(number))+1 : 1);  //abs()��ȡ����ֵ��������ʱ����

    /* ����2 */
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

/*================================= �ӿں��� =================================*/
/**
 * @brief   ʮ������ת�ַ���
 * @param   [In]number: ʮ������
 * @param   [In]tlength��Ŀ���ַ������ȣ�Ϊ0ʱ�Զ���ȡ���ݳ���
 * @param   [Out]*pAimStr: ת������ַ���
 * @return  tAimStrLen
 * @version 1.1.1
 * @date    2022-2-16
 * @note    ���룺123,0��������0x31,0x32,0x33�����أ�3
 *          ���룺123,4��������0x30,0x31,0x32,0x33�����أ�4
 **/
uint8 DecToChar(uint32 number, uint8 tlength, uint8 *pAimStr)
{
    uint32 tNumber;     //�����ת��number
    uint8 tAimStrLen;   //Ŀ���ַ�������
    uint8 tLen;         //����Ŀ���ַ������ȣ�����ת��

    /* ��ȡĿ���ַ������� */
    if (tlength == 0)
    {
        tAimStrLen = GetDecDigit(number);   //�Զ���ȡʮ������λ��
    }
    else
    {
        tAimStrLen = tlength;               //�Զ���ʮ������λ��
    }
    /* ����ת�� */
    tNumber = number;                       //ȡ��ת������
    tLen = tAimStrLen;                      //ȡĿ���ַ�������
    do{
        tLen--;
        pAimStr[tLen] = ((tNumber % 10) + '0');
        tNumber /= 10;
    }while (tLen);

    /* ����Ŀ���ַ������� */
    return tAimStrLen;
}

/**
 * @brief   ʮ������תBCD��
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
 * @brief   BCD��תʮ������
 * @param   [In]tBcd��BCD��
 * @param   [Out]
 * @return  ת�����ʮ��������
 * @version 1.00
 * @date    2021-10-12
 * @note
 **/
uint8 Bcd2Hex(uint8 tBcd)
{
    return (((tBcd >> 4) * 10) + (tBcd & 0x0F));
}

/**
 * @brief   ��һ���ַ����в����ض��ַ������������ض��ַ�������λ��
 * @param   [In]*pSrcStr�������ҵ�Դ�ַ���
 * @param   [In]tSrcLen��Դ�ַ�������
 * @param   [In]*pAimStr��Ҫ���ҵ�Ŀ���ַ���
 * @param   [In]tAimLen��Ŀ���ַ�������
 * @param   [Out]
 * @return  i���ҵ��ַ������ز�ѯ������λ�ã�
 *          invalid��-1��δ�ҵ�������Чֵ
 * @version 1.0.0
 * @date    2021-12-18
 * @note    ���ַ�����0123456789�����ҵ���567��������5
 *          {[Pos��position����λ�ã��ص�]��[Src��source������Դ������]��[Aim��Ŀ�꣬Ŀ��]��}
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
 * @brief   �����·�Ӣ�ģ���ȡ��Ӧ��ֵ��1-12��
 * @param   [In]*pAimStr���洢Ҫ�Աȵ��ַ���ָ��
 * @param   [In]tlength��Ҫ�Աȵ��ֽ���
 * @param   [Out]��
 * @return  i����Ӧ�·�
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
 * @brief   ��������Ӣ�ģ���ȡ��Ӧ��ֵ��1-7��
 * @param   [In]*pAimStr���洢Ҫ�Աȵ��ַ���ָ��
 * @param   [In]tlength��Ҫ�Աȵ��ֽ���
 * @param   [Out]��
 * @return  i����Ӧ�·�
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

/*================================= �ļ���β =================================*/
