/************************************************************
**FileName: InitCPU.c
**Author:   ZJC     Version :  V1.0      Date: 2011-8-10
**Chip:         dsPIC33FJ256GP710
**Description:����λ���úͳ�ʼ��CPU    
**			  ����Ƶ��FCY=40M 
**			  ʹ���ⲿXT Ӧ����XT_PLL  
**Function List:  
**                 
***********************************************************/
#include"InitCPU.h"
//ʹ���ⲿXT �붨��XT_PLL   
#define XT_PLL

#ifdef XT_PLL
//////////////////////////////////////////////ʹ���ⲿXT����//////////////////////////////////////////////////////////////////////
/**************************** Register FBS (0xf80000)    �����γ�������****************************/

_FBS( RBS_NO_RAM &  BSS_NO_FLASH&BWRP_WRPROTECT_OFF );

/************************ Register FSS (0xf80002)          ��ȫ�γ�������*********************** */

 _FSS(   RSS_NO_RAM    &   SWRP_WRPROTECT_OFF    & SSS_NO_FLASH    );

/************************* Register FGS (0xf80004)      ͨ�öγ�������************************ */

_FGS( GSS_OFF & GCP_OFF&GWRP_OFF );

/*********************** Register FOSCSEL (0xf80006)  ��Դ  ��˫��ʱ������**********************/

 _FOSCSEL(  FNOSC_PRIPLL  &IESO_ON);

/*************************** Register FOSC (0xf80008)    ʱ������**************************/

 _FOSC( FCKSM_CSDCMD &OSCIOFNC_OFF &  POSCMD_NONE& POSCMD_XT );

/****************************Register FWDT (0xf8000a)  ���Ź� ****************************/

 _FWDT( FWDTEN_OFF & WINDIS_OFF );

/****************************Register FPOR (0xf8000c)           PWM ģ��  ****************************/

_FPOR(  FPWRT_PWR1 );
//CPU��ʼ��
void InitCPU()
{
//���ù���Ƶ��  Fcy=Fosc/2; Fosc=Fin*M/(N1*N2)=8*40/2/2=80MHz
//ʱ��Դ: ��PLL������XT
//����Ƶ��Fcy=40M
//
/*OSCCON�� �������ƼĴ���
       bit 14-12 COSC<2:0>����ǰ����ѡ��λ ��ֻ���� 
       bit 10-8 NOSC<2:0>��������ѡ��λ 
       bit 7 CLKLOCK��ʱ������ʹ��λ
       bit 5 LOCK�� PLL����״̬λ��ֻ����
       bit 3 CF��ʱ�ӹ��ϼ��λ����Ӧ�ó���� /���㣩
       bit 1 LPOSCEN��  ���� ��LP������ʹ��λ
       bit 0 OSWEN��  �����л�ʹ��λ  
*/


//CLKDIV��ʱ�ӷ�Ƶ�ȼĴ���
    CLKDIV=0x0000;					

// PLLFBD��PLL ������Ƶ�ȼĴ���

   PLLFBD = 38;

/*OSCTUN��FRC �������ڼĴ���
      bit 15-6 δʵ�֣���Ϊ0
      bit 5-0 TUN<5:0>��FRC��������λ
*/
	// Wait for Clock switch to occur
	while (OSCCONbits.COSC != 0b011);		
	/* Wait for PLL to lock */
	while(OSCCONbits.LOCK!=1) {};
	AD1PCFGH=0xFFFF;
	AD1PCFGL=0xFFFF;
	AD2PCFGL=0xFFFF;
	TRISA = 0xFFFF;
	TRISB = 0xFFFF;
	TRISC = 0xFFFF;
	TRISD = 0xFFFF;
	TRISF = 0xFFFF;
 
}

//////////////////////////////////////////////ʹ���ڲ�RC����//////////////////////////////////////////////////////////////////////
#else
/**************************** Register FBS (0xf80000)    �����γ�������********************************/

_FBS( RBS_NO_RAM &  BSS_NO_FLASH&BWRP_WRPROTECT_OFF );

/************************ Register FSS (0xf80002)          ��ȫ�γ�������************************** */

 _FSS(   RSS_NO_RAM    &   SWRP_WRPROTECT_OFF    & SSS_NO_FLASH    );


//************************* Register FGS (0xf80004)      ͨ�öγ�������******************************** */

_FGS( GSS_OFF & GCP_OFF&GWRP_OFF );


/*********************** Register FOSCSEL (0xf80006)  ��Դ  ��˫��ʱ������**********************/

 _FOSCSEL(  FNOSC_FRCPLL  &IESO_ON);


/*************************** Register FOSC (0xf80008)    ʱ������**************************/

 _FOSC( FCKSM_CSDCMD &OSCIOFNC_OFF &  POSCMD_NONE );

/****************************Register FWDT (0xf8000a)  ���Ź� ****************************/

 _FWDT( FWDTEN_ON & WINDIS_OFF );

/****************************Register FPOR (0xf8000c)           PWM ģ��  ****************************/

_FPOR(  FPWRT_PWR1 );

void InitCPU()
{
//���ù���Ƶ��  Fcy=Fosc/2; Fosc=Fin*M/(N1*N2)=8*40/2/2=80MHz
//ʱ��Դ: ��PLL������XT
//����Ƶ��Fcy=40M
//
//OSCCON�� �������ƼĴ���


//CLKDIV��ʱ�ӷ�Ƶ�ȼĴ���
   CLKDIV=0x0000;

// PLLFBD��PLL ������Ƶ�ȼĴ���
   PLLFBD = 38;

//OSCTUN��FRC �������ڼĴ���
	OSCTUN=9;
    AD1PCFGH=0xFFFF;
    AD1PCFGL=0xFFFF;
    AD2PCFGL=0xFFFF;
    TRISA = 0xFFFF;
    TRISB = 0xFFFF;
    TRISC = 0xFFFF;
    TRISD = 0xFFFF;
    TRISF = 0xFFFF;
 
}

#endif
