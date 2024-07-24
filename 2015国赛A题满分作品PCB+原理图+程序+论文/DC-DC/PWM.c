/************************************************************
**FileName: Timer1.c
**Author:   NJM     Version :  V1.0      Date: 2013-7-10
**Chip:         dsPIC33FJ256GP710
**Description:			PWM   
**			  工作频率FCY=40M 
**			  使用外部XT 应定义XT_PLL  
**Function List:  
**                 
***********************************************************/



#include"PWM.h"


void Init_PWM()
{
	OC3CONbits.OCM=0B000;				//禁止输出模块
	OC3CONbits.OCTSEL=0;				//定时器2是时钟源
	OC3R=0;							//占空比
	OC3CONbits.OCM=0B110;				//开启不带故障保护PWM模式

	OC2CONbits.OCM=0B000;				//禁止输出模块
	OC2CONbits.OCTSEL=0;				//定时器2是时钟源
	OC2R=0;							//占空比
	OC2CONbits.OCM=0B110;				//开启不带故障保护PWM模式
	
    T2CONbits.TON=0;					//禁止16位定时器
	T2CONbits.T32=0;					//选择16位定时器
	T2CONbits.TCS=0;					//时钟源40MHZ	
	T2CONbits.TSIDL=0;					//在空闲模式下继续工作
	T2CONbits.TGATE=0;					//禁止门控电路
	T2CONbits.TCKPS=0B00;				//预分频比为1
	
	TMR2=0;
	PR2=1333;							//比较值				
		
	IPC1bits.T2IP=0B110;					//中断优先级
	IFS0bits.T2IF=0;					//中断标志位清零
	IEC0bits.T2IE=1;					//开启中断

//	T2CONbits.TON=1;					//开启16位定时器
}

