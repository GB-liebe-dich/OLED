#ifndef __EXIT_H
#define __EXIT_H

#include "sys.h"
#include "Clibrary.h"

extern uint8 test_cnt;

//全局变量

void EXTI1_IRQHandler(void);
void EXTIX_Init(void);
void EC11_IRQHandler(void);


#endif
