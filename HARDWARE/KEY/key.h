#ifndef __KEY_H
#define __KEY_H

#include "sys.h"
#include "Clibrary.h"

//按键
#define KEY1    PBin(0)
#define EC11_B  PAin(0)
#define EC11_A  PAin(1)

//全局变量


extern void KEY_IO_Init(void);     //按键初始化
extern uint8 KEY_SCAN(void);
extern uint8 EC11_scan(void);
extern uint8 LongKey_Scan(void);    //长按键检测

#endif
