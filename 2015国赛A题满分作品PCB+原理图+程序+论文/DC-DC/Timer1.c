/************************************************************
**FileName: Timer1.c
**Author:   NJM     Version :  V1.0      Date: 2013-7-10
**Chip:         dsPIC33FJ256GP710
**Description:			��ʱ��1    
**			  ����Ƶ��FCY=40M 
**			  ʹ���ⲿXT Ӧ����XT_PLL  
**Function List:  
**                 
***********************************************************/
/*-----------------------------------------------------------
		��ʱʱ�䣺256*15625*1/40000000=0.1s
  -----------------------------------------------------------*/
#include"Timer1.h"
void Timer1()
{
	
	T1CONbits.TON=0;		//��ֹ16λ��ʱ��	
	T1CONbits.TGATE=0;		//��ֹ�ſ�ʱ���ۼ�	
	T1CONbits.TCKPS=0b11;	//Ԥ��Ƶ��256
    
    T1CONbits.TSIDL=0;		//�ڿ���ģʽ�¶�ʱ����������//
	T1CONbits.TCS=0;		//�ڲ�ʱ��40MHZ
	T1CONbits.TSYNC=0;		//��ͬ���ⲿʱ��
	
	TMR1=0;					//ʱ������15625
	PR1=15625;

	IPC0bits.T1IP=0B010;		//�ж����ȼ�1
	IFS0bits.T1IF=0;		
	IEC0bits.T1IE=1;
	
	T1CONbits.TON=1;  		//����16λ��ʱ��

}
/*void __attribute__((__interrupt__, __shadow__)) _T1Interrupt(void)
{
    	IFS0bits.T1IF=0;
}*/