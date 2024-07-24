/**************************************************************************
**文件名称:   delay.c
**芯片系列:   DSPIC33F
**芯片型号:   p33FJ256GP710
**编译器版本: MPLAB C30 V3.21
**编译器环境: MPLAB IDE V8.30
**
**创建人:     江峰
**创建日期:   2010.8.8
**说明:       小误差延时子程序,系统时钟40MHz 
**************************************************************************/

//------------------------------------------------------------------------//系统时钟40MHz 微秒级延时,固定误差8指令周期
//入口参数 USNums为延时微秒数,当入口参数为0时最大延时周期65536
//------------------------------------------------------------------------
//微秒延时
void DelayUs(unsigned int USNums)
{
    unsigned char i;
    USNums=USNums;
    do
    {        
        i=8;
        while(--i);
    } 
    while(--USNums);  
}

//------------------------------------------------------------------------//系统时钟40MHz 微秒级延时,每毫秒累加误差22指令周期
//入口参数 USNums为延时毫秒数,当入口参数为0时最大延时周期65536
//------------------------------------------------------------------------
//毫秒延时
void DelayMs(unsigned int MSNums)
{       
    do
    {   
         DelayUs(1000);
    }
    while(--MSNums);   
}
