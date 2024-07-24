/************************************************************
**FileName: InitCPU.c
**Author:   ZJC     Version :  V1.0      Date: 2011-8-10
**Chip:         dsPIC33FJ256GP710
**Description:配置位设置和初始化CPU    
**			  工作频率FCY=40M 
**			  使用外部XT 应定义XT_PLL  
**Function List:  
**                 
***********************************************************/
#include"InitCPU.h"
//使用外部XT 须定义XT_PLL   
#define XT_PLL

#ifdef XT_PLL
//////////////////////////////////////////////使用外部XT定义//////////////////////////////////////////////////////////////////////
/**************************** Register FBS (0xf80000)    引导段程序设置****************************/

_FBS( RBS_NO_RAM &  BSS_NO_FLASH&BWRP_WRPROTECT_OFF );

/************************ Register FSS (0xf80002)          安全段程序设置*********************** */

 _FSS(   RSS_NO_RAM    &   SWRP_WRPROTECT_OFF    & SSS_NO_FLASH    );

/************************* Register FGS (0xf80004)      通用段程序设置************************ */

_FGS( GSS_OFF & GCP_OFF&GWRP_OFF );

/*********************** Register FOSCSEL (0xf80006)  振荡源  和双速时钟启动**********************/

 _FOSCSEL(  FNOSC_PRIPLL  &IESO_ON);

/*************************** Register FOSC (0xf80008)    时钟配置**************************/

 _FOSC( FCKSM_CSDCMD &OSCIOFNC_OFF &  POSCMD_NONE& POSCMD_XT );

/****************************Register FWDT (0xf8000a)  看门狗 ****************************/

 _FWDT( FWDTEN_OFF & WINDIS_OFF );

/****************************Register FPOR (0xf8000c)           PWM 模块  ****************************/

_FPOR(  FPWRT_PWR1 );
//CPU初始化
void InitCPU()
{
//设置工作频率  Fcy=Fosc/2; Fosc=Fin*M/(N1*N2)=8*40/2/2=80MHz
//时钟源: 带PLL主振荡器XT
//工作频率Fcy=40M
//
/*OSCCON： 振荡器控制寄存器
       bit 14-12 COSC<2:0>：当前振荡器选择位 （只读） 
       bit 10-8 NOSC<2:0>：新振荡器选择位 
       bit 7 CLKLOCK：时钟锁定使能位
       bit 5 LOCK： PLL锁定状态位（只读）
       bit 3 CF：时钟故障检测位（由应用程序读 /清零）
       bit 1 LPOSCEN：  辅助 （LP）振荡器使能位
       bit 0 OSWEN：  振荡器切换使能位  
*/


//CLKDIV：时钟分频比寄存器
    CLKDIV=0x0000;					

// PLLFBD：PLL 反馈倍频比寄存器

   PLLFBD = 38;

/*OSCTUN：FRC 振荡器调节寄存器
      bit 15-6 未实现：读为0
      bit 5-0 TUN<5:0>：FRC振荡器调节位
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

//////////////////////////////////////////////使用内部RC定义//////////////////////////////////////////////////////////////////////
#else
/**************************** Register FBS (0xf80000)    引导段程序设置********************************/

_FBS( RBS_NO_RAM &  BSS_NO_FLASH&BWRP_WRPROTECT_OFF );

/************************ Register FSS (0xf80002)          安全段程序设置************************** */

 _FSS(   RSS_NO_RAM    &   SWRP_WRPROTECT_OFF    & SSS_NO_FLASH    );


//************************* Register FGS (0xf80004)      通用段程序设置******************************** */

_FGS( GSS_OFF & GCP_OFF&GWRP_OFF );


/*********************** Register FOSCSEL (0xf80006)  振荡源  和双速时钟启动**********************/

 _FOSCSEL(  FNOSC_FRCPLL  &IESO_ON);


/*************************** Register FOSC (0xf80008)    时钟配置**************************/

 _FOSC( FCKSM_CSDCMD &OSCIOFNC_OFF &  POSCMD_NONE );

/****************************Register FWDT (0xf8000a)  看门狗 ****************************/

 _FWDT( FWDTEN_ON & WINDIS_OFF );

/****************************Register FPOR (0xf8000c)           PWM 模块  ****************************/

_FPOR(  FPWRT_PWR1 );

void InitCPU()
{
//设置工作频率  Fcy=Fosc/2; Fosc=Fin*M/(N1*N2)=8*40/2/2=80MHz
//时钟源: 带PLL主振荡器XT
//工作频率Fcy=40M
//
//OSCCON： 振荡器控制寄存器


//CLKDIV：时钟分频比寄存器
   CLKDIV=0x0000;

// PLLFBD：PLL 反馈倍频比寄存器
   PLLFBD = 38;

//OSCTUN：FRC 振荡器调节寄存器
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
