/************************************************************
**FileName: Timer1.c
**Author:   NJM     Version :  V1.0      Date: 2013-7-10
**Chip:         dsPIC33FJ256GP710
**Description:			PWM   
**			  ����Ƶ��FCY=40M 
**			  ʹ���ⲿXT Ӧ����XT_PLL  
**Function List:  
**                 
***********************************************************/



#include"PWM.h"


void Init_PWM()
{
	OC3CONbits.OCM=0B000;				//��ֹ���ģ��
	OC3CONbits.OCTSEL=0;				//��ʱ��2��ʱ��Դ
	OC3R=0;							//ռ�ձ�
	OC3CONbits.OCM=0B110;				//�����������ϱ���PWMģʽ

	OC2CONbits.OCM=0B000;				//��ֹ���ģ��
	OC2CONbits.OCTSEL=0;				//��ʱ��2��ʱ��Դ
	OC2R=0;							//ռ�ձ�
	OC2CONbits.OCM=0B110;				//�����������ϱ���PWMģʽ
	
    T2CONbits.TON=0;					//��ֹ16λ��ʱ��
	T2CONbits.T32=0;					//ѡ��16λ��ʱ��
	T2CONbits.TCS=0;					//ʱ��Դ40MHZ	
	T2CONbits.TSIDL=0;					//�ڿ���ģʽ�¼�������
	T2CONbits.TGATE=0;					//��ֹ�ſص�·
	T2CONbits.TCKPS=0B00;				//Ԥ��Ƶ��Ϊ1
	
	TMR2=0;
	PR2=1333;							//�Ƚ�ֵ				
		
	IPC1bits.T2IP=0B110;					//�ж����ȼ�
	IFS0bits.T2IF=0;					//�жϱ�־λ����
	IEC0bits.T2IE=1;					//�����ж�

//	T2CONbits.TON=1;					//����16λ��ʱ��
}

