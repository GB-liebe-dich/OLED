//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RCT6,正点原子MiniSTM32开发板,主频72MHZ，晶振12MHZ
//QDtech-OLED液晶驱动 for STM32
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtft.com
//淘宝网站：http://qdtech.taobao.com
//wiki技术网站：http://www.lcdwiki.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:lcdwiki01@gmail.com    support@lcdwiki.com    goodtft@163.com
//技术支持QQ:3002773612  3002778157
//技术交流QQ群:324828016
//创建日期:2018/8/27
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2018-2028
//All rights reserved
/****************************************************************************************************
//=========================================电源接线================================================//
// OLED模块               STM32单片机
//   VCC         接       DC 5V/3.3V      //OLED屏电源正
//   GND         接          GND          //OLED屏电源地
//=======================================液晶屏数据线接线==========================================//
//本模块默认数据总线类型为4线制SPI
// OLED模块               STM32单片机
//   D1          接          PB15        //OLED屏SPI写信号
//=======================================液晶屏控制线接线==========================================//
// OLED模块               STM32单片机
//   CS          接          PB11        //OLED屏片选控制信号
//   RES         接          PB12        //OLED屏复位控制信号
//   DC          接          PB10        //OLED屏数据/命令选择控制信号
//   D0          接          PB13        //OLED屏SPI时钟信号
//=========================================触摸屏接线=========================================//
//本模块不带触摸功能，所以不需要触摸屏接线
****************************************************************************************************/	
/***************************************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
****************************************************************************************************/
//////////////////////////////////////////////////////////////////////////////////	 
//
//存储图片数据，图片大小为128*64像素
//逐行式，顺向（高位在前）
//
/////////////////////////////////////////////////////////////////////////////////

#ifndef __BMP_H
#define __BMP_H

/* 24*24 */
unsigned char bmp_qing[] = 
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0x18,0x00,0x0C,0x18,0x30,0x0E,
    0x00,0x70,0x07,0x7E,0xE0,0x02,0xE7,0x40,0x01,0x81,0x80,0x03,0x00,0xC0,0x03,0x00,
    0xC0,0x3A,0x00,0x5C,0x3A,0x00,0x5C,0x03,0x00,0xC0,0x03,0x00,0xC0,0x01,0x81,0x80,
    0x02,0xE7,0x40,0x07,0x7E,0xE0,0x0E,0x00,0x70,0x0C,0x18,0x30,0x00,0x18,0x00,0x00,
    0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
unsigned char bmp_yin[] = 
{
    0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x01,0x86,0x18,0x01,
    0xC0,0x38,0x00,0xDF,0xB0,0x00,0x3F,0xC0,0x0F,0xF0,0xE0,0x3F,0xF0,0x60,0x70,0x38,
    0x7E,0x60,0x1C,0x3E,0xC0,0x0D,0xE0,0xC0,0x0F,0xE0,0xC0,0x07,0xF0,0xC0,0x00,0x30,
    0xC0,0x00,0x18,0xC0,0x00,0x18,0xE0,0x00,0x18,0x70,0x00,0x30,0x3C,0x00,0x70,0x1F,
    0xFF,0xE0,0x07,0xFF,0x80,0x00,0x00,0x00
};
unsigned char bmp_yu[] = 
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0x80,0x00,0x79,0xC0,0x00,0xE0,0x60,0x0F,
    0xC0,0x30,0x0D,0x80,0x30,0x08,0x00,0x10,0x3C,0x00,0x1C,0x70,0x00,0x0E,0xC0,0x00,
    0x03,0xC0,0x00,0x03,0x80,0x00,0x01,0xC0,0x00,0x03,0xE0,0x00,0x07,0x7F,0xFF,0xFE,
    0x1F,0xFF,0xF8,0x01,0x8C,0x60,0x03,0x9C,0x60,0x03,0x18,0xC0,0x07,0x39,0xC0,0x06,
    0x31,0x80,0x00,0x00,0x00,0x00,0x00,0x00
};
unsigned char bmp_lei[] = 
{
    0x00,0x00,0x00,0x00,0x7E,0x00,0x00,0xFF,0x00,0x01,0xC3,0x80,0x01,0x81,0x80,0x1F,
    0x81,0xF8,0x3F,0x00,0xFC,0x70,0x00,0x0E,0x60,0x00,0x06,0x60,0x00,0x06,0x60,0x00,
    0x06,0x60,0x00,0x06,0x70,0x00,0x0E,0x38,0x3E,0x1C,0x1F,0xBD,0xF8,0x0F,0xBD,0xF0,
    0x00,0x78,0x00,0x03,0x7E,0x60,0x07,0x1C,0xE0,0x07,0x18,0xE0,0x06,0x30,0xC0,0x00,
    0x30,0x00,0x00,0x20,0x00,0x00,0x40,0x00
};
unsigned char bmp_xue[] = 
{
    0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x06,0x00,0x00,0x1E,0xC0,0x00,0x5F,0xB0,0x02,
    0x6F,0x30,0x03,0x66,0x2E,0x01,0xE6,0x3C,0x00,0xF6,0x78,0x03,0xFF,0xDE,0x00,0x0F,
    0x00,0x03,0x1F,0x8E,0x03,0xFE,0xFE,0x00,0xE6,0x78,0x03,0xE6,0x3E,0x0B,0x67,0x36,
    0x08,0x4F,0xB0,0x6B,0x5E,0xD0,0x3E,0x16,0xC0,0x3E,0x06,0x00,0x7F,0x00,0x00,0x08,
    0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00
};

unsigned char bmp_clear[] = 
{
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
/* 16*16 */
unsigned char bmp_wifi[] = 
{
    0x00,0x00,0x00,0x00,0x03,0xC0,0x1F,0xF8,0x38,0x1C,0x63,0xC6,0x0F,0xF0,0x18,0x18,
    0x03,0xC0,0x06,0x60,0x01,0x80,0x03,0xC0,0x03,0xC0,0x01,0x80,0x00,0x00,0x00,0x00
};

unsigned char bmp_wifi1[] = 
{
    0x00,0x00,0x00,0x00,0x33,0xC0,0x1F,0xF8,0x2C,0x1C,0x66,0xC6,0x0B,0x70,0x19,0x98,
    0x02,0xC0,0x06,0x60,0x01,0xB0,0x03,0xD8,0x03,0xCC,0x01,0x80,0x00,0x00,0x00,0x00
};

unsigned char bmp_dianchi[] = 
{
    0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFC,0xFF,0xFC,0xC0,0x0C,0xDB,0x6F,0xDB,0x6F,
    0xDB,0x6F,0xDB,0x6F,0xC0,0x0C,0xFF,0xFC,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00
};

/* 10*10 */
unsigned char bmp_wendu[] = 
{
    0x0C,0x00,0x1E,0x00,0x16,0x00,0x1E,0x00,0x16,0x00,0x3F,0x00,0x7D,0x80,0x79,0x80,
    0x3F,0x00,0x1E,0x00
};

unsigned char bmp_shidu[] = 
{
    0x0C,0x00,0x0C,0x00,0x1E,0x00,0x1E,0x00,0x3F,0x00,0x7F,0x80,0x7F,0x80,0x7F,0x80,
    0x3F,0x00,0x1E,0x00
};

/* 8*8 */
unsigned char bmp_c[] = 
{
    0xC0,0xCE,0x33,0x20,0x20,0x20,0x33,0x0C
};
unsigned char bmp_bfh[] = 
{
    0x00,0x66,0x6C,0x18,0x18,0x36,0x66,0x00
};

/* 数字0-9,20*28 */
unsigned char bmp_num[12][84] = 
{
    0x01,0xF8,0x00,0x07,0xFE,0x00,0x0F,0x1F,0x00,0x1F,0x1F,0x80,0x3E,0x0F,0xC0,0x3E,
0x0F,0xC0,0x7E,0x0F,0xE0,0x7E,0x0F,0xE0,0xFE,0x07,0xE0,0xFE,0x07,0xF0,0xFE,0x07,
0xF0,0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFE,0x07,0xF0,
0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFF,0x07,0xE0,0x7F,
0x07,0xE0,0x7F,0x07,0xC0,0x3F,0x0F,0xC0,0x1F,0x8F,0x80,0x0F,0xFF,0x00,0x07,0xFE,
0x00,0x01,0xF8,0x00,/*"C:\Users\Administrator\Desktop\111\数字-0@2x.bmp",0*/
    0x00,0x1C,0x00,0x00,0x3E,0x00,0x01,0xFE,0x00,0x07,0xFE,0x00,0x1F,0xFE,0x00,0x0F,
0xFE,0x00,0x01,0xFE,0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,0xFC,
0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,
0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,
0xFC,0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,0xFC,0x00,0x01,0xFF,0x80,0x0F,0xFF,
0x80,0x0F,0xF8,0x00,/*"C:\Users\Administrator\Desktop\111\数字-1@2x.bmp",0*/
    0x00,0x60,0x00,0x07,0xFE,0x00,0x1F,0xFF,0x80,0x3C,0x1F,0xC0,0x78,0x0F,0xE0,0xF8,
0x07,0xE0,0xF8,0x07,0xF0,0x70,0x07,0xF0,0x70,0x07,0xF0,0x30,0x07,0xF0,0x00,0x0F,
0xF0,0x00,0x0F,0xF0,0x00,0x0F,0xF0,0x00,0x1F,0xE0,0x00,0x1F,0xE0,0x00,0x3F,0xC0,
0x00,0x7F,0xC0,0x00,0x7F,0x80,0x00,0xFF,0x00,0x01,0xFC,0x00,0x07,0xF8,0x00,0x0F,
0xF0,0x00,0x1F,0xC0,0x00,0x3F,0x03,0x80,0x7C,0x07,0xC0,0xF0,0x07,0xE0,0x7F,0xFF,
0xE0,0x1F,0xFF,0x80,/*"C:\Users\Administrator\Desktop\111\数字-2@2x.bmp",0*/
    0x03,0xFE,0x00,0x1F,0xFF,0x80,0x3E,0x1F,0xC0,0x7C,0x0F,0xE0,0xF8,0x07,0xF0,0xF8,
0x07,0xF0,0x70,0x07,0xF0,0x70,0x07,0xF0,0x30,0x07,0xF0,0x00,0x07,0xF0,0x00,0x0F,
0xF0,0x00,0x0F,0xE0,0x00,0x1F,0xC0,0x00,0x7F,0x80,0x03,0xFE,0x00,0x03,0xFF,0x00,
0x00,0x7F,0x80,0x00,0x1F,0xC0,0x00,0x0F,0xE0,0x00,0x0F,0xE0,0x00,0x0F,0xF0,0x00,
0x0F,0xF0,0x00,0x0F,0xE0,0x00,0x0F,0xE0,0x00,0x3F,0xC0,0x0F,0xFF,0x80,0x07,0xFF,
0x00,0x00,0x60,0x00,/*"C:\Users\Administrator\Desktop\111\3.BMP",0*/
    0x00,0xF0,0x00,0x00,0xFE,0x00,0x01,0xFE,0x00,0x01,0xFE,0x00,0x01,0xFC,0x00,0x03,
0xFC,0x00,0x03,0xF8,0x00,0x07,0xF8,0x00,0x07,0xF8,0x20,0x0F,0xF0,0x60,0x0F,0xF0,
0x60,0x0F,0xE0,0x60,0x1F,0xE0,0xE0,0x1F,0xC0,0xC0,0x3F,0xC0,0xC0,0x3F,0x80,0xC0,
0x7F,0x81,0xC0,0x7F,0x01,0x9C,0xFE,0x01,0xBE,0x7F,0xFF,0xFE,0x0F,0xFF,0xFE,0x00,
0x03,0x80,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x03,0x00,0x00,0x07,
0x00,0x00,0x06,0x00,/*"C:\Users\Administrator\Desktop\111\4.BMP",0*/
    0x0F,0x80,0x00,0x0F,0xE1,0xC0,0x1F,0xE3,0xC0,0x1F,0xFF,0xE0,0x1F,0xFF,0xE0,0x3F,
0xF8,0x00,0x3F,0x80,0x00,0x7F,0x80,0x00,0x7F,0x00,0x00,0x7F,0x00,0x00,0x7F,0x00,
0x00,0xFE,0xFE,0x00,0xFF,0xFF,0x80,0xFF,0xFF,0xC0,0xFF,0xFF,0xC0,0xF8,0x1F,0xE0,
0x00,0x0F,0xE0,0x00,0x0F,0xF0,0x00,0x07,0xF0,0x00,0x07,0xF0,0x00,0x0F,0xF0,0x00,
0x0F,0xF0,0x00,0x0F,0xE0,0x00,0x1F,0xE0,0x1C,0x3F,0xC0,0x1F,0xFF,0x80,0x0F,0xFF,
0x00,0x01,0xF8,0x00,/*"C:\Users\Administrator\Desktop\111\5.BMP",0*/
    0x00,0x0E,0x00,0x00,0x1E,0x00,0x00,0x3C,0x00,0x00,0xF8,0x00,0x01,0xF0,0x00,0x03,
0xE0,0x00,0x07,0xC0,0x00,0x0F,0xC0,0x00,0x1F,0x80,0x00,0x3F,0x80,0x00,0x3F,0x1C,
0x00,0x7F,0x7F,0x00,0x7F,0xFF,0x80,0xFF,0xFF,0xC0,0xFF,0xFF,0xE0,0xFF,0x0F,0xE0,
0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFE,
0x07,0xE0,0xFE,0x0F,0xE0,0x7E,0x0F,0xE0,0x7F,0x0F,0xC0,0x3F,0x1F,0x80,0x1F,0xFF,
0x00,0x07,0xFC,0x00,/*"C:\Users\Administrator\Desktop\111\6.BMP",0*/
    0x20,0x00,0x00,0x7F,0xFF,0xE0,0xFF,0xFF,0xF0,0x7F,0xFF,0xF0,0x00,0x07,0xF0,0x00,
0x0F,0xF0,0x00,0x0F,0xE0,0x00,0x1F,0xE0,0x00,0x1F,0xC0,0x00,0x3F,0xC0,0x00,0x3F,
0xC0,0x00,0x3F,0x80,0x00,0x7F,0x80,0x00,0x7F,0x80,0x00,0xFF,0x00,0x00,0xFF,0x00,
0x00,0xFE,0x00,0x01,0xFE,0x00,0x01,0xFE,0x00,0x03,0xFC,0x00,0x03,0xFC,0x00,0x03,
0xFC,0x00,0x07,0xF8,0x00,0x07,0xF8,0x00,0x07,0xF8,0x00,0x0F,0xF0,0x00,0x07,0xF0,
0x00,0x03,0xF0,0x00,/*"C:\Users\Administrator\Desktop\111\7.BMP",0*/
    0x00,0x60,0x00,0x07,0xFE,0x00,0x1F,0xFF,0x00,0x3F,0xFF,0x80,0x3F,0x03,0xC0,0x7E,
0x00,0x60,0x7E,0x00,0x00,0x7E,0x00,0x00,0x7F,0x00,0xC0,0x7F,0x81,0xC0,0x7F,0xE7,
0x80,0x3F,0xFF,0x00,0x1F,0xFE,0x00,0x1F,0xFF,0x00,0x0F,0xFF,0x80,0x1F,0xFF,0xC0,
0x3F,0xFF,0xE0,0x7F,0x3F,0xE0,0x7F,0x1F,0xF0,0xFE,0x0F,0xF0,0xFE,0x07,0xF0,0xFE,
0x07,0xF0,0xFE,0x07,0xF0,0x7E,0x07,0xF0,0x7F,0x07,0xE0,0x3F,0x0F,0xE0,0x1F,0xFF,
0x80,0x07,0xFE,0x00,/*"C:\Users\Administrator\Desktop\111\8.BMP",0*/
    0x03,0xFC,0x00,0x0F,0xFF,0x00,0x1F,0xFF,0xC0,0x3F,0xFF,0xE0,0x7F,0xC0,0xE0,0x7F,
0x80,0x30,0xFF,0x00,0x10,0xFF,0x00,0x00,0xFE,0x03,0xE0,0xFE,0x07,0xF0,0xFE,0x07,
0xF0,0xFE,0x07,0xF0,0xFE,0x07,0xF0,0xFE,0x0F,0xE0,0xFE,0x0F,0xE0,0xFF,0x0F,0xE0,
0x7F,0x0F,0xE0,0x7F,0xFF,0xE0,0x3F,0xFF,0xC0,0x1F,0xFF,0xC0,0x0F,0xDF,0xC0,0x00,
0x1F,0xC0,0x00,0x3F,0xC0,0x00,0x3F,0x80,0x00,0x3F,0x80,0x00,0x3F,0x80,0x00,0x3F,
0x80,0x00,0x1F,0x80,/*"C:\Users\Administrator\Desktop\111\9.BMP",0*/
    0x00,0x00,0x00,0x00,0x00,0xF0,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xF0,0xF0,0xF0,0xF0,0xF0,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\111\m.BMP",0*/
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\111\m.BMP",0*/
};

//////////////////////////////////////////////////////////////////////////////////	 
//
//存储图片数据，图片大小为51*32像素
//逐行式，顺向（高位在前）
//
/////////////////////////////////////////////////////////////////////////////////
unsigned char BMP5[] =
{
	0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x00,0x00,0x00,0x00,0x00,
	0x0E,0x00,0x00,0x00,0x00,0x01,0x80,0x0E,0x00,0x20,0x00,0x00,0x01,0xC0,0x00,0x00,
	0x70,0x00,0x00,0x00,0xC0,0x00,0x00,0xE0,0x00,0x00,0x00,0xE0,0x3F,0x81,0xC0,0x00,
	0x00,0x00,0x61,0xFF,0xF0,0x80,0x00,0x00,0x00,0x03,0xC0,0xF8,0x00,0x00,0x00,0x00,
	0x07,0x00,0x1C,0x00,0x00,0x00,0x00,0x1E,0x00,0x0F,0x00,0x00,0x00,0x7C,0x1C,0x00,
	0x03,0x1F,0x80,0x00,0x7C,0x1C,0x07,0xFF,0x1F,0x80,0x00,0x7C,0x1C,0x1F,0xFF,0x9F,
	0x80,0x00,0x00,0x1C,0x7C,0x03,0xF8,0x00,0x00,0x00,0x0F,0xF0,0x00,0x7C,0x00,0x00,
	0x03,0xFF,0x00,0x00,0x0F,0xE0,0x00,0x0F,0xF2,0x00,0x00,0x07,0xFE,0x00,0x1F,0x80,
	0x00,0x00,0x00,0x7F,0x80,0x3C,0x00,0x00,0x00,0x00,0x03,0x80,0x7C,0x00,0x00,0x00,
	0x00,0x03,0xC0,0x70,0x00,0x00,0x00,0x00,0x01,0xC0,0x70,0x00,0x00,0x00,0x00,0x01,
	0xC0,0x78,0x00,0x00,0x00,0x00,0x01,0xC0,0x7C,0x00,0x00,0x00,0x00,0x03,0xC0,0x3C,
	0x00,0x00,0x00,0x00,0x07,0x80,0x3E,0x00,0x00,0x00,0x00,0x3F,0x80,0x0F,0xE1,0xC0,
	0x00,0x1F,0xFC,0x00,0x03,0xFF,0xFC,0x03,0xFF,0xF0,0x00,0x00,0xFF,0xFF,0xFF,0xFF,
	0x00,0x00,0x00,0x00,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x01,0xFC,0x00,0x00,0x00,
};

unsigned char bili_Logo_0[512] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x00,0x70,0x00,0x00,0x00,0x00,0x07,0xE0,0x00,0xF8,0x00,0x00,0x00,0x00,0x07,0xF0,0x01,0xFC,0x00,0x00,
0x00,0x00,0x03,0xF0,0x03,0xF8,0x00,0x00,0x00,0x00,0x03,0xF0,0x07,0xF0,0x00,0x00,0x00,0x00,0x03,0xF8,0x0F,0xF0,0x00,0x00,0x00,0x00,0x01,0xFC,0x1F,0xE0,0x00,0x00,
0x00,0x00,0x07,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,
0x00,0x07,0x00,0x00,0x00,0x01,0xF8,0x00,0x00,0x0F,0x3F,0xFF,0xFF,0xFE,0x7C,0x00,0x00,0x0F,0x7F,0xFF,0xFF,0xFF,0x7C,0x00,0x00,0x0F,0x70,0x00,0x00,0x03,0xBC,0x00,
0x00,0x0F,0x60,0x00,0x00,0x03,0xBC,0x00,0x00,0x1F,0x60,0x38,0x06,0x03,0xBE,0x00,0x00,0x1F,0x60,0x78,0x0F,0x03,0xBE,0x00,0x00,0x1F,0x61,0xF8,0x0F,0xC3,0xBE,0x00,
0x00,0x1F,0x67,0xF0,0x0F,0xF1,0xBE,0x00,0x00,0x1F,0x6F,0xE0,0x03,0xFD,0xBE,0x00,0x00,0x1E,0x6F,0xC0,0x01,0xFD,0xBE,0x00,0x00,0x1E,0xE7,0x00,0x00,0xF9,0x9E,0x00,
0x00,0x1E,0xE0,0x00,0x00,0x39,0x9E,0x00,0x00,0x1E,0xE0,0x00,0x08,0x01,0x9E,0x00,0x00,0x1E,0xE0,0x19,0x9C,0x01,0x9E,0x00,0x00,0x1E,0xE0,0x1F,0xF8,0x01,0x9E,0x00,
0x00,0x1E,0xE0,0x0F,0xF8,0x01,0x9E,0x00,0x00,0x1E,0xE0,0x0E,0x70,0x03,0xBE,0x00,0x00,0x1E,0xE0,0x00,0x00,0x03,0xBE,0x00,0x00,0x1E,0xE0,0x00,0x00,0x03,0xBE,0x00,
0x00,0x1E,0xF0,0x00,0x00,0x03,0xBE,0x00,0x00,0x1E,0xF0,0x00,0x00,0x03,0xBC,0x00,0x00,0x0F,0x7F,0xFF,0xFF,0xFF,0x3C,0x00,0x00,0x0F,0x7F,0xFF,0xFF,0xFF,0x3C,0x00,
0x00,0x0F,0x80,0x3F,0xF8,0x00,0x7C,0x00,0x00,0x0F,0x80,0x00,0x00,0x03,0x7C,0x00,0x00,0x07,0xF8,0x3F,0xFF,0x87,0xF8,0x00,0x00,0x07,0xFC,0x7F,0xFF,0x87,0xF8,0x00,
0x00,0x03,0xFC,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,
0x00,0x00,0x7F,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\bilibili_weather_clock-master\取模软件\小电视动画1\1.bmp",0*/
};
unsigned char bili_Logo_1[512] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xC0,0x00,0xF0,0x00,0x00,
0x00,0x00,0x07,0xE0,0x01,0xF8,0x00,0x00,0x00,0x00,0x0F,0xE0,0x03,0xF8,0x00,0x00,0x00,0x00,0x0F,0xF0,0x07,0xF8,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xF0,0x00,0x00,
0x00,0x00,0x07,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x1E,0x00,0x00,0x00,0x00,0xF8,0xFF,0xFF,0xEF,0x00,0x00,
0x00,0x01,0xF7,0xFF,0xFF,0xF7,0x80,0x00,0x00,0x03,0xCF,0x80,0x0F,0xFB,0xE0,0x00,0x00,0x0F,0xBC,0x00,0x00,0x7D,0xF0,0x00,0x00,0x1E,0x78,0x30,0x00,0x1E,0xF0,0x00,
0x00,0x1E,0xE0,0xF8,0x0F,0x07,0x78,0x00,0x00,0x3D,0xC3,0xF8,0x1F,0xC3,0x38,0x00,0x00,0x3D,0x8F,0xF0,0x0F,0xF3,0xB8,0x00,0x00,0x3D,0x9F,0xC0,0x07,0xFB,0xB8,0x00,
0x00,0x3D,0x9F,0x80,0x03,0xFB,0xBC,0x00,0x00,0x7D,0x9E,0x00,0x00,0xFB,0xBC,0x00,0x00,0x7D,0x8C,0x00,0x08,0x77,0xBC,0x00,0x00,0x7D,0x80,0x31,0x9C,0x07,0xBC,0x00,
0x00,0x7D,0x80,0x3F,0xF8,0x07,0xBC,0x00,0x00,0x7D,0x80,0x1F,0xF8,0x07,0xBC,0x00,0x00,0x7D,0x80,0x0E,0x60,0x07,0x7E,0x00,0x00,0x7D,0x80,0x00,0x00,0x07,0x7E,0x00,
0x00,0x7D,0xC0,0x00,0x00,0x07,0x7E,0x00,0x00,0x7D,0xC0,0x00,0x00,0x07,0x7E,0x00,0x00,0x7D,0xC0,0x00,0x00,0x07,0x7C,0x00,0x00,0x7D,0xC0,0x00,0x00,0x07,0x7C,0x00,
0x00,0x7D,0xC1,0xFF,0xFE,0x07,0x7C,0x00,0x00,0x7D,0xFF,0xFF,0xFF,0xFF,0x7C,0x00,0x00,0x3E,0xFF,0xFF,0xFF,0xFE,0x7C,0x00,0x00,0x3E,0xE0,0x00,0x00,0x1E,0x7C,0x00,
0x00,0x3F,0x00,0xFF,0xFF,0x80,0xF8,0x00,0x00,0x3F,0x00,0xFF,0xFF,0x80,0xF8,0x00,0x00,0x1F,0x31,0xFF,0xFF,0xCE,0xF8,0x00,0x00,0x1F,0xF1,0xFF,0xFF,0xCF,0xF8,0x00,
0x00,0x0F,0xF9,0xE0,0x07,0xDF,0xF0,0x00,0x00,0x0F,0xFB,0xE0,0x03,0xFF,0xF0,0x00,0x00,0x07,0xBF,0xC0,0x03,0xFF,0xE0,0x00,0x00,0x00,0x3F,0xC0,0x01,0xFE,0x00,0x00,
0x00,0x00,0x1F,0x80,0x00,0xFC,0x00,0x00,0x00,0x00,0x0F,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xC0,0x00,0x00,
0x00,0x00,0x07,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x7F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\bilibili_weather_clock-master\取模软件\小电视动画1\2.bmp",0*/
};
unsigned char bili_Logo_2[512] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xC0,0x00,0xE0,0x00,0x00,0x00,0x00,0x07,0xE0,0x01,0xF0,0x00,0x00,
0x00,0x00,0x07,0xE0,0x03,0xF8,0x00,0x00,0x00,0x00,0x07,0xF0,0x07,0xF0,0x00,0x00,0x00,0x00,0x03,0xF8,0x07,0xF0,0x00,0x00,0x00,0x00,0x03,0xFC,0x0F,0xE0,0x00,0x00,
0x00,0x00,0x03,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x03,0xF8,0x00,0x00,0x0F,0xF0,0x00,
0x00,0x0F,0xE7,0xFF,0xFF,0xC3,0xF8,0x00,0x00,0x1F,0x9F,0xFF,0xFF,0xFC,0xF8,0x00,0x00,0x1E,0x7F,0xC0,0x03,0xFF,0x38,0x00,0x00,0x1E,0xE0,0x00,0x00,0x0F,0xBC,0x00,
0x00,0x1D,0xC0,0x78,0x1F,0x81,0xBC,0x00,0x00,0x1D,0xC1,0xFC,0x1F,0xE1,0xBC,0x00,0x00,0x3D,0xCF,0xF8,0x0F,0xF9,0xBE,0x00,0x00,0x3D,0xDF,0xF0,0x03,0xF9,0xBE,0x00,
0x00,0x3D,0xDF,0xC0,0x00,0xF9,0xBE,0x00,0x00,0x3D,0xCF,0x00,0x00,0x39,0xBE,0x00,0x00,0x3D,0xC0,0x00,0x00,0x01,0xBE,0x00,0x00,0x3D,0xC0,0x00,0x00,0x01,0xBE,0x00,
0x00,0x3D,0xC0,0x39,0x9C,0x01,0xBE,0x00,0x00,0x3D,0xC0,0x3F,0xFC,0x01,0xBE,0x00,0x00,0x3D,0xC0,0x1F,0xF8,0x03,0xBE,0x00,0x00,0x3D,0xC0,0x04,0x60,0x03,0xBE,0x00,
0x00,0x3D,0xC0,0x00,0x00,0x03,0xBE,0x00,0x00,0x3D,0xC0,0x00,0x00,0x03,0xBE,0x00,0x00,0x3D,0xC0,0x00,0x00,0x03,0xBE,0x00,0x00,0x3E,0xC0,0x00,0x00,0x03,0xBE,0x00,
0x00,0x3E,0xE1,0xFF,0xFF,0xE3,0xBC,0x00,0x00,0x3E,0xFF,0xFF,0xFF,0xFF,0xBC,0x00,0x00,0x1E,0xFF,0xC0,0x03,0xFF,0x7C,0x00,0x00,0x1E,0x00,0x03,0xF8,0x00,0x7C,0x00,
0x00,0x1F,0x00,0x3F,0xFF,0x07,0x7C,0x00,0x00,0x1F,0xF8,0x7F,0xFF,0x8F,0xF8,0x00,0x00,0x0F,0xF8,0x7F,0xFF,0xCF,0xF8,0x00,0x00,0x0F,0xFF,0xFC,0x1F,0xDF,0xF0,0x00,
0x00,0x02,0x3F,0xE0,0x03,0xFF,0xE0,0x00,0x00,0x00,0x1F,0xE0,0x03,0xFC,0x00,0x00,0x00,0x00,0x0F,0xC0,0x01,0xF8,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x60,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0xC0,0x00,0x00,
0x00,0x00,0x01,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x01,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\bilibili_weather_clock-master\取模软件\小电视动画1\3.bmp",0*/

};
unsigned char bili_Logo_3[512] = {

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x60,0x00,0x00,0x00,0x00,0x07,0xC0,0x01,0xF0,0x00,0x00,
0x00,0x00,0x0F,0xE0,0x03,0xF8,0x00,0x00,0x00,0x00,0x07,0xE0,0x07,0xF0,0x00,0x00,0x00,0x00,0x07,0xE0,0x0F,0xF0,0x00,0x00,0x00,0x00,0x07,0xF0,0x0F,0xE0,0x00,0x00,
0x00,0x00,0x03,0xF8,0x3F,0xC0,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,
0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x0F,0x80,0x00,0x00,0x03,0xF0,0x00,0x00,0x1E,0x7F,0xFF,0xFF,0xFC,0xF8,0x00,0x00,0x1E,0xFF,0xFF,0xFF,0xFE,0xF8,0x00,
0x00,0x1E,0xE0,0x00,0x00,0x06,0x78,0x00,0x00,0x1E,0xC0,0x00,0x00,0x07,0x78,0x00,0x00,0x3E,0xC0,0x60,0x0C,0x07,0x78,0x00,0x00,0x3E,0xC0,0xF0,0x1E,0x07,0x7C,0x00,
0x00,0x3E,0xC3,0xF8,0x1F,0x87,0x7C,0x00,0x00,0x3E,0xCF,0xF0,0x1F,0xE7,0x7C,0x00,0x00,0x3E,0xDF,0xC0,0x07,0xFB,0x7C,0x00,0x00,0x3C,0xDF,0x80,0x03,0xFB,0x3C,0x00,
0x00,0x3C,0xCE,0x00,0x01,0xF3,0x3E,0x00,0x00,0x3C,0xC0,0x00,0x00,0x77,0x3E,0x00,0x00,0x3C,0xC0,0x00,0x10,0x03,0x3E,0x00,0x00,0x3C,0xC0,0x33,0x38,0x07,0x3C,0x00,
0x00,0x3C,0xC0,0x3F,0xF8,0x03,0x3C,0x00,0x00,0x3C,0xC0,0x1F,0xF0,0x07,0x3C,0x00,0x00,0x3C,0xC0,0x1C,0xE0,0x07,0x3C,0x00,0x00,0x3E,0xC0,0x00,0x00,0x07,0x7C,0x00,
0x00,0x3E,0xC0,0x00,0x00,0x07,0x7C,0x00,0x00,0x3E,0xC0,0x00,0x00,0x07,0x7C,0x00,0x00,0x3E,0xE0,0x00,0x00,0x07,0x78,0x00,0x00,0x1E,0xEF,0xFF,0xFF,0xFF,0x78,0x00,
0x00,0x1E,0xFF,0xFF,0xFF,0xFE,0x78,0x00,0x00,0x1E,0x00,0x07,0x00,0x00,0xF8,0x00,0x00,0x1F,0x00,0x00,0x00,0x07,0xF8,0x00,0x00,0x0F,0xF0,0x7F,0xFF,0x0F,0xF0,0x00,
0x00,0x0F,0xF8,0xFF,0xFF,0x0F,0xF0,0x00,0x00,0x07,0xF8,0xFF,0xFF,0x9F,0xC0,0x00,0x00,0x01,0xFD,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x3F,0xF3,0x61,0xFC,0x00,0x00,
0x00,0x00,0x1F,0xC0,0x00,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF8,0x00,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0xC0,0x00,0x00,
0x00,0x00,0x07,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x7F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\bilibili_weather_clock-master\取模软件\小电视动画1\4.bmp",0*/
};
unsigned char bili_Logo_4[512] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x03,0xE0,0x07,0x80,0x00,0x00,0x00,0x00,0x03,0xF0,0x0F,0xC0,0x00,0x00,0x00,0x00,0x07,0xF0,0x0F,0xC0,0x00,0x00,0x00,0x00,0x07,0xF0,0x0F,0xC0,0x00,0x00,
0x00,0x00,0x03,0xF0,0x1F,0xC0,0x00,0x00,0x00,0x00,0x03,0xF8,0x1F,0xC0,0x00,0x00,0x00,0x00,0x03,0xF8,0x1F,0xC0,0x00,0x00,0x00,0x00,0x03,0xF8,0x1F,0xBC,0x00,0x00,
0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,
0x00,0x1F,0x00,0x00,0x00,0x00,0x78,0x00,0x00,0x1E,0x7F,0xFF,0xFF,0xFF,0x78,0x00,0x00,0x1E,0xFF,0xFF,0xFF,0xFF,0x78,0x00,0x00,0x1E,0xC0,0x00,0x00,0x03,0xB8,0x00,
0x00,0x3E,0xC0,0x00,0x00,0x03,0xB8,0x00,0x00,0x3E,0xC0,0x10,0x00,0x03,0xB8,0x00,0x00,0x3E,0xC0,0x78,0x0F,0x03,0xBC,0x00,0x00,0x3E,0xC1,0xF8,0x1F,0xC1,0xBC,0x00,
0x00,0x3E,0xC7,0xF8,0x1F,0xF1,0xBC,0x00,0x00,0x3E,0xDF,0xF0,0x07,0xF9,0xBC,0x00,0x00,0x3E,0xDF,0xE0,0x03,0xFD,0xBC,0x00,0x00,0x3E,0xDF,0x80,0x00,0xF9,0xBC,0x00,
0x00,0x3E,0xCC,0x00,0x00,0x71,0xBC,0x00,0x00,0x3E,0xC0,0x00,0x00,0x01,0xBC,0x00,0x00,0x3E,0xC0,0x10,0x18,0x01,0xBC,0x00,0x00,0x3E,0xC0,0x3B,0xB8,0x01,0xBC,0x00,
0x00,0x3E,0xC0,0x1F,0xF8,0x03,0xBC,0x00,0x00,0x3E,0xC0,0x0F,0xF0,0x03,0xBC,0x00,0x00,0x3E,0xC0,0x04,0x60,0x03,0xBC,0x00,0x00,0x3E,0xE0,0x00,0x00,0x03,0xBC,0x00,
0x00,0x3E,0xE0,0x00,0x00,0x03,0xBC,0x00,0x00,0x3E,0xE0,0x00,0x00,0x03,0xBC,0x00,0x00,0x1E,0xFF,0x7F,0xFF,0xFF,0x7C,0x00,0x00,0x1F,0x7F,0xFF,0xFF,0xFF,0x7C,0x00,
0x00,0x1F,0x3F,0xFF,0xFF,0xFC,0x78,0x00,0x00,0x1F,0xE0,0x00,0x00,0x07,0xF8,0x00,0x00,0x0F,0xF8,0x3F,0xFF,0x07,0xF8,0x00,0x00,0x0F,0xF8,0x7F,0xFF,0x8F,0xF0,0x00,
0x00,0x03,0xF8,0xFF,0xFF,0x8F,0xC0,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x3F,0xF0,0x03,0xFE,0x00,0x00,0x00,0x00,0x1F,0xF0,0x00,0xFC,0x00,0x00,
0x00,0x00,0x07,0xC0,0x00,0x30,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0x80,0x00,
0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x03,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\bilibili_weather_clock-master\取模软件\小电视动画1\5.bmp",0*/
};
unsigned char bili_Logo_5[512] = {

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x18,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x7E,0x00,0x03,0xF0,0x00,0x00,0x00,0x00,0xFF,0x00,0x07,0xF8,0x00,0x00,0x00,0x00,0xFF,0x80,0x0F,0xF8,0x00,0x00,
0x00,0x00,0x7F,0xC0,0x1F,0xF0,0x00,0x00,0x00,0x00,0x3F,0xE3,0xFF,0xE0,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,
0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x7F,0x00,0x00,0x00,0x01,0xFC,0x00,0x00,0xFC,0xFF,0xFF,0xFF,0xFE,0x7F,0x00,
0x01,0xF3,0xF0,0x00,0x00,0x3F,0x9F,0x80,0x03,0xEF,0x80,0x00,0x00,0x03,0xE7,0xC0,0x07,0xDE,0x03,0xE0,0x0F,0x00,0xF3,0xE0,0x0F,0xB8,0x3F,0xF0,0x1F,0xF8,0x79,0xF0,
0x1F,0x70,0xFF,0xF0,0x1F,0xFC,0x1C,0xF8,0x1E,0x60,0xFF,0xE0,0x1F,0xFE,0x0C,0xF8,0x3E,0xE0,0xFF,0xC0,0x07,0xFE,0x0E,0x7C,0x3C,0xC0,0x70,0x00,0x00,0x1C,0x06,0x7C,
0x3C,0xC0,0x00,0x00,0x00,0x00,0x06,0x7C,0x3C,0xC0,0x00,0x63,0x38,0x00,0x06,0x7C,0x3E,0x60,0x00,0x7F,0xF8,0x00,0x0C,0x7C,0x1E,0x60,0x00,0x7F,0xF0,0x00,0x0C,0xF8,
0x1F,0x30,0x00,0x1C,0xC0,0x00,0x18,0xF8,0x1F,0xB8,0x00,0x00,0x00,0x00,0x39,0xF0,0x0F,0xDE,0x00,0x00,0x00,0x00,0xF7,0xE0,0x07,0xE7,0x80,0x00,0x00,0x07,0xCF,0xC0,
0x03,0xFB,0xFF,0xFF,0xFF,0xFF,0x3F,0x80,0x03,0xFC,0x67,0xFF,0xFF,0xF8,0xFF,0x00,0x00,0xFF,0x80,0x00,0x00,0x07,0xFE,0x00,0x00,0x7F,0xE0,0x00,0xFF,0x0F,0xF8,0x00,
0x00,0x1F,0xF0,0xFF,0xFF,0x0F,0xE0,0x00,0x00,0x07,0xF9,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0x80,0x00,
0x00,0x07,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x07,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\bilibili_weather_clock-master\取模软件\小电视动画1\6.bmp",0*/
};
unsigned char bili_Logo_6[512] = {
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00,0xE0,0x00,0x00,0x00,0x00,0x7E,0x00,0x03,0xF0,0x00,0x00,
0x00,0x00,0xFF,0x00,0x07,0xF8,0x00,0x00,0x00,0x00,0x7F,0x80,0x0F,0xF8,0x00,0x00,0x00,0x00,0x3F,0xE0,0x1F,0xF0,0x00,0x00,0x00,0x00,0x1F,0xFF,0xFF,0xE0,0x00,0x00,
0x00,0x01,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0xF8,0x00,0x00,0x7B,0xFF,0xFF,0xFF,0xFF,0x7E,0x00,
0x01,0xF7,0xFF,0xFF,0xFF,0xFF,0xDF,0x80,0x03,0xEF,0xC0,0x00,0x00,0x07,0xEF,0xC0,0x07,0xDE,0x03,0xE0,0x0F,0x80,0xF3,0xE0,0x0F,0x38,0x7F,0xF0,0x1F,0xFC,0x39,0xF0,
0x1F,0x70,0xFF,0xF0,0x1F,0xFE,0x1C,0xF8,0x3E,0xE0,0xFF,0xE0,0x0F,0xFE,0x0E,0x7C,0x3C,0xC0,0x70,0x00,0x00,0x1C,0x06,0x7C,0x3C,0xC0,0x00,0x00,0x00,0x00,0x06,0x7C,
0x3C,0xC0,0x00,0x77,0x38,0x00,0x06,0x7C,0x3E,0x60,0x00,0x7F,0xF8,0x00,0x0C,0xF8,0x1F,0x30,0x00,0x3D,0xE0,0x00,0x1C,0xF8,0x1F,0xB8,0x00,0x00,0x00,0x00,0x3B,0xF0,
0x0F,0xCF,0x00,0x00,0x00,0x01,0xF7,0xE0,0x07,0xE7,0xFF,0xFF,0xFF,0xFF,0xEF,0xC0,0x03,0xFC,0xFF,0xFF,0xFF,0xFF,0xDF,0x80,0x01,0xFF,0x00,0x00,0x00,0x00,0x3E,0x00,
0x00,0x7F,0xE0,0x03,0xFF,0x0F,0xF8,0x00,0x00,0x1F,0xF0,0xFF,0xFF,0x1F,0xE0,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0x80,0x00,
0x00,0x03,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x0F,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*"C:\Users\Administrator\Desktop\bilibili_weather_clock-master\取模软件\小电视动画1\7.bmp",0*/
};

#endif


