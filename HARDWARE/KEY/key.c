#include "key.h"
#include "delay.h"

void KEY_IO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA, ENABLE); //使能PB,PA端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //继电器输出 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1; //继电器输出 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //IO口速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8 KEY_SCAN(void)
{
    uint8 res = 0;
    if (!KEY1)
    {
        delay_ms(10);
        if (!KEY1)
        {
            while (!KEY1)
                ; //卡死
            res = 1;
        }
    }
    return res;
}
/**
 * @brief      获取EC11正反转信息
 * @param[In]  
 * @param[Out] 
 * @return     
 * @version    
 * @date       
 * @note       
**/
uint8 EC11_scan(void)
{
    uint8 ScanResult = 0;

    if(EC11_A == 0)
    {
        if(EC11_B)
            ScanResult = 1;
        else
            ScanResult = 2;
    }
    return ScanResult;
}

/**
 * @brief   长按键检测
 * @param   [In]
 * @param   [Out]
 * @return  
 * @version 1.0.0
 * @date    2022-03-10
 * @note    
**/
uint8 LongKey_Scan(void)
{
    static uint8 LongKey_Time = 0;

    if(KEY_SCAN())
    {
        LongKey_Time++;
    }
    else
    {
        LongKey_Time = 0;
    }

    if(LongKey_Time >= 3)
    {
        return 0;
    }

    return 1;
}


