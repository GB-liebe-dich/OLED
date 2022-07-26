#include "stdio.h"
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "gui.h"
#include "test.h"
#include "Clibrary.h"
#include "dht11.h"
#include "display.h"
#include "rtc.h"
#include "USART3.h"
#include "ESP8266.h"
#include "Button.h"
#include "Timer.h"

u8 delayi;
u8 t = 0;
u8 t1 = 0;

/*  //������
uint32 Temp;
uint32 TTemp;
uint8 test[4] = {0};
*/

int main(void)
{
    uint8 tTemp[20];
    uint8 tLen;

    /* ��ʼ�� */
    delay_init();                                   //��ʱ������ʼ��
    OLED_Init();                                    //��ʼ��OLED
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    RTC_Init();                                     // RTC��ʼ��
    DHT11_Init();
    USART3_Init(115200); //��ʼ������3
    TIM3_Init();
    Button_Init();
    OLED_Clear(0);       //������ȫ�ڣ�

    /* �������� */
    Dis_PowerOn(); //��������
    OLED_Clear(0);
    DHT11_Read_Data(&temperature, &humidity);
    Dis_MainInterface(); //��ʾ�����棬�ȴ�wifi����
		OLED_Display();
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

/*  //������
    UartxSendStr(USART3, "test start");
*/
    while (1)
    {
        /* 10ms�¼� */
        if (BasicTimeFlg.ms_ten == 0xAA)
        {
            BasicTimeFlg.ms_ten = 0x00;

            /*  //������
            Temp = GetButtonData();
            
            if(Temp != TTemp)
            {
                TTemp = Temp;

                uLongToByte(Temp, test, 0xAA);
                tLen = HexToAsc(test, 4, tTemp);
                UartxSendData(USART3, tTemp, tLen);
            }
            */

            HandleButtonEvent(); //�����¼�����
        }
        /* 100ms�¼� */
        if (BasicTimeFlg.ms_hundred == 0xAA)
        {
            BasicTimeFlg.ms_hundred = 0x00;

            //========= ��ʾ���� =========//
            /* ��ʼ���������� */
            switch (g_Display.Now_interface)
            {
            case main_interface:
                Dis_MainInterface();
                break;
            case menu_interface:
                Dis_MenuInterFace();
                break;
            case WiFiSet_interface:
                Dis_Wificonfig();
                break;
            case Update_interface:
                break;
            default:
                break;
            }
            /* ������ʾ */
            OLED_Display();
        }
        /* 1���¼� */
        if (BasicTimeFlg.S_one == 0xAA)
        {
            BasicTimeFlg.S_one = 0x00;

            RTC_Get();                                //����ʱ��
            DHT11_Read_Data(&temperature, &humidity); //��ȡ��ʪ��

           if (g_8266State.Timing != 0xAA) //Уʱ
           {
               if (SUCCESS == ESP8266_GetTime())
               {
                   g_8266State.Timing = 0xAA;
               }
           }
        }

        __WFI(); //����˯��ģʽ���ȴ��ж�
    }

    // if (t % 1 == 0)
    // {
    //     if (g_SetWifi_Cursor.state)
    //     {
    //         if (g_SetWifi_Cursor.state == 1) /* ѡ��״̬ */
    //         {
    //             g_SetWifi_Cursor.twinkle = 0;
    //         }
    //         else /* ����״̬ */
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
    //         g_SetWifi_Cursor.state = 2; /* ��������״̬ */
    //     }
    //     else if (!g_SetWifi_Cursor.state)
    //     {
    //         g_SetWifi_Cursor.state = 1; /* ����ѡ��״̬ */
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
