#ifndef __KEY_H
#define __KEY_H

#include "sys.h"
#include "Clibrary.h"

//按键
#define KEY1    PBin(0)
#define EC11_B  PAin(0)
#define EC11_A  PAin(1)

//全局变量


void KEY_IO_Init(void);     //按键初始化
uint8 KEY_SCAN(void);
uint8 EC11_scan(void);

#endif
