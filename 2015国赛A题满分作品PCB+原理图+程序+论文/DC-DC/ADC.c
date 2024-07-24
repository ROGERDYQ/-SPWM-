/************************************************************
**FileName: ADC.c
**Author:   NJM     Version :  V1.0      Date: 2013-7-16
**Chip:         dsPIC33FJ256GP710
**Description:		  ADC    
**			  工作频率FCY=40M 
**			  使用外部XT 应定义XT_PLL  
**Function List:  
**                 
***********************************************************/
#include "ADC.h"
#include "Delay.h"

void Init_ADC()
{


     _TRISB0=1;								//端口引脚定义
	_TRISB1=1;
	_TRISB2=1;
	_TRISB3=1;
	_TRISB4=1;
	_TRISA9=1;
	_TRISA10=1;
	AD1CON1bits.ADON=0;						//禁止ADC
	AD1CON1bits.AD12B=0;					//选择10位模式
	AD1CON2bits.VCFG=0B011;					//选择参考电压配置位
	AD1CON3bits.ADCS=0X02;					//选择模拟转换时钟
	AD1CON3bits.ADRC=0;						//选择内部时钟
	AD1PCFGL=0XFFF0;						//选择AN0引脚作为模拟输入
	AD1CON2bits.CHPS=0B00;					//使用的通道为CH0
	AD1CON1bits.SIMSAM=0;					//按顺序依次单独采样多个通道中每个通道
	AD1CSSL=0X000F;							//对AN0进行扫描
	AD1CON1bits.SAMP=0;						//手动采样
	AD1CON1bits.FORM=0B00;					//缓冲区的存储方式输出格式为整数
	AD1CON4=0X0004;							//给每个模拟输入分配16字的缓冲区
	AD1CON1bits.ADON=1;						//开启ADC
}

unsigned int ADC(unsigned int input)
{
	static unsigned int AD=0;
	AD1CHS0=input;
	AD1CON1bits.SAMP=1;						//收到采样
	DelayUs(1);								//延时等待
	AD1CON1bits.SAMP=0;						//开始装换
	while(!AD1CON1bits.DONE);				
	AD=ADC1BUF0;							//取值
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
