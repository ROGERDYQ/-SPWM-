/**************************************
**
**FileName: LCD12864.h
**
**Author:  PZY    Version: V3.21   Date:  2012-10-15
**
**Description:  LCD������ʾ
**
**Function List:
**
***************************************/


#ifndef  _LCD12864_H_
#define  _LCD12864_H_

#include "Delay.h"
#include "p33FJ256GP710.h"

/******IO�˿ڶ���******/
#define  CS    _LATA2
#define  SID   _LATA3
#define  CLK   _LATA4
#define  PSB   _LATA5

/******LCD�˿�����******/
#define SET_IO  TRISA&=~((1<<2)|(1<<3)|(1<<4)|(1<<5))

/******��λ������******/
extern void sendbyte(unsigned char byte);

/******д��������******/
extern void writ_com(unsigned int com);

/******д����**********/
extern void writ_Date(unsigned char Date);

/******����***********/
extern void Clear_lcd();

/******LCD��ʼ��******/
extern void InitLCD();

/******�ַ�����ʾ*****/
extern void DISPLAY_stri(unsigned char x, unsigned char y, unsigned char *p);

/******��ֵ��ʾ**(Ԥ��ʾ��ֵ��ʵ��λ������ʾλ����С����λ�ã�*/
extern void DISPLAY_num(long num,unsigned char w,unsigned char ds,unsigned char point);

/********��ʾ����*************/

extern unsigned int *ADC_deal_I(unsigned  int Value);
extern unsigned int *ADC_deal_U(unsigned  int Value);
extern unsigned int *ADC_deal_I_1(unsigned  int Value);

#endif






 



 
