#ifndef __KEY_H
#define __KEY_H

#include "sys.h"
#include "Clibrary.h"

//����
#define KEY1    PBin(0)
#define EC11_B  PAin(0)
#define EC11_A  PAin(1)

//ȫ�ֱ���


extern void KEY_IO_Init(void);     //������ʼ��
extern uint8 KEY_SCAN(void);
extern uint8 EC11_scan(void);
extern uint8 LongKey_Scan(void);    //���������

#endif
