#include "stdio.h"
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "gui.h"
#include "test.h"
#include "Clibrary.h"
#include "dht11.h"
#include "key.h"
#include "exit.h"
#include "display.h"
#include "rtc.h"
#include "USART3.h"
#include "ESP8266.h"

u8 delayi;
u8 t = 0;
u8 t1 = 0;
uint8 key_cnt = 0;
uint8 key_cnt_char[3] = {0};
uint8 test_cnt_char[3] = {0};

int main(void)
{
    /* 初始化 */
    delay_init();                                   //延时函数初始化
    OLED_Init();                                    //初始化OLED
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    RTC_Init();                                     // RTC初始化
    DHT11_Init();
    KEY_IO_Init();
    USART3_Init(115200);                            //初始化串口3
    EXTIX_Init();
    OLED_Clear(0); //清屏（全黑）

    /* 开机任务 */
    // Dis_PowerOn();  //开机动画
    OLED_Clear(0);
    DHT11_Read_Data(&temperature, &humidity);
    Dis_MainInterface(); //显示主界面，等待wifi连接
    for (delayi = 0; delayi < 5; delayi++)
    {
        delay_ms(1500);
        if (!ESP8266_QueryWifi())
        {
            g_8266State.wifi_online = 0xAA;
            ESP8266_Weather();
            if (SUCCESS == ESP8266_GetTime())
            {
                g_8266State.Timing = 0xAA;
            }
            break;
        }
    }

    while (1)
    {
        if (t1 != calendar.sec) //秒事件
        {
            t1 = calendar.sec;
            if (g_8266State.Timing != 0xAA) //校时
            {
                if (SUCCESS == ESP8266_GetTime())
                {
                    g_8266State.Timing = 0xAA;
                }
            }
            Dis_MainInterface();
        }
        if (t % 30 == 0)
        {
            DHT11_Read_Data(&temperature, &humidity);
        }

        delay_ms(100);
        t++;
        /*
        if(t%20==0)
        {
            DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值
            DecToChar(temperature, wendu);
            DecToChar(humidity, shidu);
            GUI_ShowString(40,16,wendu,16,1);
            GUI_ShowString(40,32,shidu,16,1);
            GUI_ShowCHinese(56,16,16,"℃",1);
            GUI_ShowCHinese(56,32,16,"％",1);
        }
        if(KEY_SCAN())	key_cnt++;
        if(key_cnt >= 10)	key_cnt = 0;
        DecToChar(key_cnt, key_cnt_char);
        GUI_ShowString(80,16,key_cnt_char,16,0);

        DecToChar(test_cnt, test_cnt_char);
        GUI_ShowString(80,32,test_cnt_char,16,0);
        */

        // if (t % 1 == 0)
        // {
        //     if (g_SetWifi_Cursor.state)
        //     {
        //         if (g_SetWifi_Cursor.state == 1) /* 选择状态 */
        //         {
        //             g_SetWifi_Cursor.twinkle = 0;
        //         }
        //         else /* 设置状态 */
        //         {
        //             if (t % 3 == 0)
        //             {
        //                 g_SetWifi_Cursor.twinkle = !g_SetWifi_Cursor.twinkle;
        //             }
        //         }
        //     }
        //     Dis_Wificonfig();
        // }
        // if (KEY_SCAN())
        // {
        //     if (g_SetWifi_Cursor.state == 1)
        //     {
        //         g_SetWifi_Cursor.state = 2; /* 进入设置状态 */
        //     }
        //     else if (!g_SetWifi_Cursor.state)
        //     {
        //         g_SetWifi_Cursor.state = 1; /* 进入选择状态 */
        //     }
        //     else
        //     {
        //         g_SetWifi_Cursor.position = 0;
        //         g_SetWifi_Cursor.state = 0;
        //         g_Display.Interface_State = 0;
        //     }
        // }

        // delay_ms(100);
        // t++;
    }
}
