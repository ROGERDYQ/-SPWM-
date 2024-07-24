#ifndef _DS18B20_H_
#define _DS18B20_H_
#include "p33FJ256GP710.h"
#include "Delay.h"

#define BUS_HIGH()        _TRISD5=1
#define BUS_LOW()         _TRISD5=0;DQ=0
#define DQ				_RD5

//复位初始化DS18B20
extern uchar Init_DS18B20();
//DS18B20写数据
extern void Write_DS18B20(uchar data);
//DS18B20读数据
extern uint Read_DS18B20();
//读取温度
extern float GETTEMP_DS18B20();

#endif