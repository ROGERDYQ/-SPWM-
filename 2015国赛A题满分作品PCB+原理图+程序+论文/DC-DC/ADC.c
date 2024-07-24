/************************************************************
**FileName: ADC.c
**Author:   NJM     Version :  V1.0      Date: 2013-7-16
**Chip:         dsPIC33FJ256GP710
**Description:		  ADC    
**			  ����Ƶ��FCY=40M 
**			  ʹ���ⲿXT Ӧ����XT_PLL  
**Function List:  
**                 
***********************************************************/
#include "ADC.h"
#include "Delay.h"

void Init_ADC()
{


     _TRISB0=1;								//�˿����Ŷ���
	_TRISB1=1;
	_TRISB2=1;
	_TRISB3=1;
	_TRISB4=1;
	_TRISA9=1;
	_TRISA10=1;
	AD1CON1bits.ADON=0;						//��ֹADC
	AD1CON1bits.AD12B=0;					//ѡ��10λģʽ
	AD1CON2bits.VCFG=0B011;					//ѡ��ο���ѹ����λ
	AD1CON3bits.ADCS=0X02;					//ѡ��ģ��ת��ʱ��
	AD1CON3bits.ADRC=0;						//ѡ���ڲ�ʱ��
	AD1PCFGL=0XFFF0;						//ѡ��AN0������Ϊģ������
	AD1CON2bits.CHPS=0B00;					//ʹ�õ�ͨ��ΪCH0
	AD1CON1bits.SIMSAM=0;					//��˳�����ε����������ͨ����ÿ��ͨ��
	AD1CSSL=0X000F;							//��AN0����ɨ��
	AD1CON1bits.SAMP=0;						//�ֶ�����
	AD1CON1bits.FORM=0B00;					//�������Ĵ洢��ʽ�����ʽΪ����
	AD1CON4=0X0004;							//��ÿ��ģ���������16�ֵĻ�����
	AD1CON1bits.ADON=1;						//����ADC
}

unsigned int ADC(unsigned int input)
{
	static unsigned int AD=0;
	AD1CHS0=input;
	AD1CON1bits.SAMP=1;						//�յ�����
	DelayUs(1);								//��ʱ�ȴ�
	AD1CON1bits.SAMP=0;						//��ʼװ��
	while(!AD1CON1bits.DONE);				
	AD=ADC1BUF0;							//ȡֵ
	return AD;
}

unsigned int filter(unsigned int ANx)
{
	unsigned int sum,AD_value,i;
	for(i=0;i<30;i++)
	{
	sum=ADC(ANx)+sum;
	}
	AD_value=sum/30;
	sum=0;
	return AD_value;
}
