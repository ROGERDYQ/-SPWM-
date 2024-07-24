#ifndef _DS18B20_H_
#define _DS18B20_H_
#include "p33FJ256GP710.h"
#include "Delay.h"

#define BUS_HIGH()        _TRISD5=1
#define BUS_LOW()         _TRISD5=0;DQ=0
#define DQ				_RD5

//��λ��ʼ��DS18B20
extern uchar Init_DS18B20();
//DS18B20д����
extern void Write_DS18B20(uchar data);
//DS18B20������
extern uint Read_DS18B20();
//��ȡ�¶�
extern float GETTEMP_DS18B20();

#endif