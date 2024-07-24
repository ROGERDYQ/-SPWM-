/************************************************************
**FileName: ADC.h
**Author:   NJM     Version :  V1.0      Date: 2013-7-10
**Chip:         dsPIC33FJ256GP710
**Description:			ADC    
**			  工作频率FCY=40M 
**			  使用外部XT 应定义XT_PLL  
**Function List:  
**                 
***********************************************************/
#ifndef _ADC_H_
#define _ADC_H_
#include"p33FJ256GP710.h"

extern void Init_ADC();
extern unsigned int ADC(unsigned int input);
extern unsigned int filter(unsigned int ANx);

#endif
