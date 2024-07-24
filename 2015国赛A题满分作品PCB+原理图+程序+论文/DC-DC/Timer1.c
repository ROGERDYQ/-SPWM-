/************************************************************
**FileName: Timer1.c
**Author:   NJM     Version :  V1.0      Date: 2013-7-10
**Chip:         dsPIC33FJ256GP710
**Description:			定时器1    
**			  工作频率FCY=40M 
**			  使用外部XT 应定义XT_PLL  
**Function List:  
**                 
***********************************************************/
/*-----------------------------------------------------------
		定时时间：256*15625*1/40000000=0.1s
  -----------------------------------------------------------*/
#include"Timer1.h"
void Timer1()
{
	
	T1CONbits.TON=0;		//禁止16位定时器	
	T1CONbits.TGATE=0;		//禁止门控时间累加	
	T1CONbits.TCKPS=0b11;	//预分频比256
    
    T1CONbits.TSIDL=0;		//在空闲模式下定时器继续工作//
	T1CONbits.TCS=0;		//内部时钟40MHZ
	T1CONbits.TSYNC=0;		//不同步外部时钟
	
	TMR1=0;					//时钟周期15625
	PR1=15625;

	IPC0bits.T1IP=0B010;		//中断优先级1
	IFS0bits.T1IF=0;		
	IEC0bits.T1IE=1;
	
	T1CONbits.TON=1;  		//启动16位定时器

}
/*void __attribute__((__interrupt__, __shadow__)) _T1Interrupt(void)
{
    	IFS0bits.T1IF=0;
}*/