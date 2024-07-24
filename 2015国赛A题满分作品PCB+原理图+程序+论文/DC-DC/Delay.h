/**************************************************************************
**文件名称:   delay.h
**芯片系列:   DSPIC33F
**芯片型号:   p33FJ256GP710
**编译器版本: MPLAB C30 V3.21
**编译器环境: MPLAB IDE V8.30
**
**创建人:     江峰
**创建日期:   2010.8.8
**说明:       小误差延时子程序,系统时钟40MHz 
**************************************************************************/

#ifndef _Delay_H_
#define _Delay_H_
//微秒延时
extern void DelayUs(unsigned int USNums);

//毫秒延时
extern void DelayMs(unsigned int MSNums);
#endif


