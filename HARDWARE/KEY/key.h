#ifndef __KEY_H
#define __KEY_H

#include "sys.h"
#include "Clibrary.h"

//����
#define KEY1    PBin(0)
#define EC11_B  PAin(0)
#define EC11_A  PAin(1)

//ȫ�ֱ���


void KEY_IO_Init(void);     //������ʼ��
uint8 KEY_SCAN(void);
uint8 EC11_scan(void);

#endif
