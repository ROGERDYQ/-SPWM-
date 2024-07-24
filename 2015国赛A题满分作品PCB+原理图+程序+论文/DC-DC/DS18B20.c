#include "DS18B20.h"
#include "Delay.h"
//复位初始化DS18B20
uchar Init_DS18B20()
{
	uchar temp=1;
	BUS_HIGH();
	DelayUs(2);
	while(temp)
	{
		BUS_LOW(); 
		DelayUs(550);
		//释放总线15~60us
		BUS_HIGH();                  
		DelayUs(40); 
		if(DQ==1)	temp=1;
		else	temp=0;	 
		DelayUs(160);
	}
}
//DS18B20写数据
void Write_DS18B20(uchar data)
{
	uchar i;
	BUS_HIGH();
	DelayUs(2);
	for(i=0;i<8;i++)
	{
		//拉低总线>1us
		BUS_LOW();                 
		DelayUs(2);
		DQ=data&0x01;
		data>>=1;
		DelayUs(70);
		BUS_HIGH();
		DelayUs(2);
	}
}
//DS18B20读数据
uint Read_DS18B20()
{
	uint data,i;
	BUS_HIGH();
	DelayUs(1);
	for(i=0;i<8;i++)
	{
		data>>=1;
		//拉低总线>1us
		BUS_LOW();		
		DelayUs(6);
		BUS_HIGH();
		DelayUs(5);	
		if(DQ)	data|=0x80;
		DelayUs(50);
	}
	return data;
}
//读取温度
float GETTEMP_DS18B20()
{
	uint temp1,temp2,C;
	float T;
	Init_DS18B20();
	Write_DS18B20(0XCC);//跳过ROM
	Write_DS18B20(0X44);//温度转换
    DelayMs(50);
    Init_DS18B20();
	Write_DS18B20(0XCC);
	Write_DS18B20(0XBE);
	temp1=Read_DS18B20();
	temp2=Read_DS18B20();
	T=(temp2*256+temp1)*6.25;
    return(T);
}