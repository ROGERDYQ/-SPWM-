/**************************************
**
**FileName: LCD12864.h
**
**Author:  PZY    Version: V3.21   Date:  2012-10-15
**
**Description:  LCD串行显示
**
**Function List:
**
***************************************/


#ifndef  _LCD12864_H_
#define  _LCD12864_H_

#include "Delay.h"
#include "p33FJ256GP710.h"

/******IO端口定义******/
#define  CS    _LATA2
#define  SID   _LATA3
#define  CLK   _LATA4
#define  PSB   _LATA5

/******LCD端口设置******/
#define SET_IO  TRISA&=~((1<<2)|(1<<3)|(1<<4)|(1<<5))

/******按位送数据******/
extern void sendbyte(unsigned char byte);

/******写控制命令******/
extern void writ_com(unsigned int com);

/******写数据**********/
extern void writ_Date(unsigned char Date);

/******清屏***********/
extern void Clear_lcd();

/******LCD初始化******/
extern void InitLCD();

/******字符串显示*****/
extern void DISPLAY_stri(unsigned char x, unsigned char y, unsigned char *p);

/******数值显示**(预显示数值，实际位数，显示位数，小数点位置）*/
extern void DISPLAY_num(long num,unsigned char w,unsigned char ds,unsigned char point);

/********显示函数*************/

extern unsigned int *ADC_deal_I(unsigned  int Value);
extern unsigned int *ADC_deal_U(unsigned  int Value);
extern unsigned int *ADC_deal_I_1(unsigned  int Value);

#endif






 



 
