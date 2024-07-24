#include "p33FJ256GP710.h"
#include<math.h>
#include "Delay.h"
#include "InitCPU.h"
#include "LCD12864.h"
#include "ADC.h"
#include "KEY.h"
#include "PWM.h"
#include "DS18B20.h" 
#define uint unsigned int 
#define uchar unsigned char
#define ulint unsigned long int 

#define KeyPort PORTE
/*********��������***********/
unsigned char KEY_Receive =0;			//����ɨ�����洢
unsigned int cls=0;					//����ָʾ
unsigned char switchover =0;			//����
unsigned int Duty_one =0,Duty_two=0;	//ռ�ձȼĴ���
unsigned int I_Set_One =15000;	//1ģ���2ģ���趨����ֵ�����⣩
unsigned int count =0,start=0,start1=0;   //
unsigned char test =0;					//�����Ӽ��Ĵ�����test =1�ӣ�test=2����
unsigned char BUCK=0,BOOST=0;					//�ɼ�100�α�־λ
/********************״̬��־λ************************/
unsigned  char Menu =1;								//���˵���־λ
unsigned char Menu_A =0;							//һ���˵�A��״̬A��
unsigned char Menu_B =0;
unsigned char Menu_C =0;				//һ���˵�B��״̬B��
unsigned char Cursor =1;							//���״̬��־λ
unsigned char stateA =0;							//A״̬��־λ����������ģʽ���ǹ���������
unsigned char stateB =0;							//B״̬��־λ
unsigned char stateC =0;

float RE_Ui=0,RE_Uo=0,RE_Ii=0,RE_Io=0;
float RE_Ui_all=0,RE_Uo_all=0,RE_Ii_all=0,RE_Io_all=0;
float Ui_ave=0,Uo_ave=0,Ii_ave=0,Io_ave=0;
float Ui=0,Uo=0,Ii=0,Io=0;
float GETTEMP;
float POWER_factor=0;

unsigned char KeyScan();
void main()
{/*****��ʼ��*****/
	InitCPU();	
	InitLCD();
	Init_ADC();
	Init_PWM();	
	Init_DS18B20();
	_TRISF2=0;//���������
	_TRISD1=0;
	_TRISD2=0;
	Clear_lcd();
	DelayMs(10);
    DISPLAY_stri(0 ,0 , "ģʽѡ��: ");
    DISPLAY_stri(0,1,"->1.���ģ��");	
    DISPLAY_stri(0,2,"  2.�ŵ�ģ��");	
    DISPLAY_stri(0,3,"  3.�Զ�ģ��");
	writ_com(0x0F);	
	writ_com(0x90);	
	while(1)
	{     
     	KEY_Receive=KeyScan();
		switch ( KEY_Receive )
		{
			case 1: 		//��������ƶ���+��
			{			
					test =1;				//�����Ĵ�������
					if(Menu==1)
					{	test=0;
						Cursor ++;
						Cursor=Cursor>=4?1:Cursor;	
						if( Cursor ==1 )
						{ 
                          DISPLAY_stri(0 ,1 , "->1.���ģ��");	
                          DISPLAY_stri(0 ,2 , "  2.�ŵ�ģ��");
                          DISPLAY_stri(0 ,3 , "  3.�Զ�ģ��"); 
						  writ_com(0x90);		//�����ʾ�ڵ�һ��
						}	
						if( Cursor ==2 )
						{DISPLAY_stri(0 ,1 , "  1.���ģ��");	
                         DISPLAY_stri(0 ,2 , "->2.�ŵ�ģ��");
                         DISPLAY_stri(0 ,3 , "  3.�Զ�ģ��");
						 writ_com(0x88);		//�����ʾ�ڵڶ���
						}	
                       if( Cursor ==3 )
						{DISPLAY_stri(0 ,1 , "  1.���ģ��");	
                         DISPLAY_stri(0 ,2 , "  2.�ŵ�ģ��");
                         DISPLAY_stri(0 ,3 , "->3.�Զ�ģ��");
                         writ_com(0x98);//�����ʾ�ڵڶ���
					     }  
					}
					break;	
			}
			case 2:
			{
				//�˵���꣬��ʾ2��
					test =2;			 	//�����Ĵ�������
					if( Menu ==1)
					{  	test=0;
						Cursor --;
						Cursor=Cursor==0?3:Cursor;	
						if( Cursor ==1 )
						{
						 DISPLAY_stri(0 ,1 , "->1.���ģ��");
                         DISPLAY_stri(0 ,2 , "  2.�ŵ�ģ��");
                         DISPLAY_stri(0 ,3 , "  3.�Զ�ģ��");
						 writ_com(0x90);		//�����ʾ�ڵ�һ��
						}	
						if( Cursor ==2 )
						{   
							 DISPLAY_stri(0 ,1 , "  1.���ģ��");
                             DISPLAY_stri(0 ,2 , "->2.�ŵ�ģ��");
                             DISPLAY_stri(0 ,3 , "  3.�Զ�ģ��"); 
							 writ_com(0x88);		//�����ʾ�ڵڶ���
						}	
                      if( Cursor ==3 )
						{     DISPLAY_stri(0 ,1 , "  1.���ģ��");
                              DISPLAY_stri(0 ,2 , "  2.�ŵ�ģ��");
                              DISPLAY_stri(0 ,3 , "->3.�Զ�ģ��"); 
							  writ_com(0x98);		//�����ʾ�ڵڶ���////////////////
						}																	
					}
					break;			
			}
			case 3:		//(ȷ������������״̬(ִ��״̬)
			{    
					switchover =~switchover;
					cls=1;									
					if( ( Menu * Cursor ) ==1 )  //BUCKģʽ
					{	
						_TRISD1=0;
						_TRISD2=0;					
						Menu_A =1;
						Menu_B =0;
						Menu_C =0;
						Menu =0;

						stateA=1;
						stateB=0;
						stateC=0;
						OC3CONbits.OCM=0B110;
						OC2CONbits.OCM=0B110;
						Duty_one=10; 			//PWM����one����BUCK����PWM������two�ض�
						Duty_two=0;

						T2CONbits.TON=1;
						writ_com(0x0C);			//�ر��α���α�λ��
				 		Clear_lcd();
					}
					if(  ( Menu * Cursor ) ==2 )//BOOSTģʽ
					{
						_TRISD2=0;
						_TRISD1=0;
						Menu_A =0;
						Menu_B =1;
						Menu_C =0;
						Menu =0;
				
						stateA=0;
						stateB=1;
						stateC=0;
						OC3CONbits.OCM=0B110;
						OC2CONbits.OCM=0B110;
						Duty_one=0; 			////PWM����two����BUCK����PWM������one�ض�
						Duty_two=10;

						T2CONbits.TON=1;
						writ_com(0x0C);			//�ر��α���α�λ��
				 		Clear_lcd();
					}	
                   	if( ( Menu * Cursor ) ==3 )//�Զ�ģʽ
					{
						_TRISD2=0;
						_TRISD1=0;
						Menu_A =0;
						Menu_B =0;
						Menu_C =1;
						Menu =0;

						stateA=0;
						stateB=0;
						stateC=1;
						OC3CONbits.OCM=0B000;
						OC2CONbits.OCM=0B000;
						BUCK=0;
						BOOST=0;
						Duty_one=0; 			//PWM���ã��տ�ʼ��BUCK
						Duty_two=0;

						T2CONbits.TON=0;
						writ_com(0x0C);			//�ر��α���α�λ��
				 		Clear_lcd();
					}
					break;				
			}
			case 4:
			{
					if( Menu_A ==1 )	
					{					
						Menu_A =0;
						Menu_B =0;
						Menu_C =0;
						Menu =1;
						Cursor =1;
						stateA=0;
						stateB=0;
						stateC=0;
						start=0;
						OC3RS=0;	
						OC2RS=0;
						OC3CONbits.OCM=0B000;
						OC2CONbits.OCM=0B000;
						_LATD2=0;
						_LATD1=0;
						_LATF2=0;
						T2CONbits.TON=0;
						I_Set_One=15000;
						Clear_lcd();
						DelayMs(10);
					    DISPLAY_stri(0 ,0 , "ģʽѡ��: ");
						DISPLAY_stri(0 ,1 , "->1.���ģ��");	
						DISPLAY_stri(0 ,2 , "  2.�ŵ�ģ��");
                        DISPLAY_stri(0 ,3 , "  3.�Զ�ģ��");	
						writ_com(0x90);
						writ_com(0x0F);					
					}
					if( Menu_B ==1 )
					{					
						Menu_A =0;
						Menu_B =0;
						Menu_C =0;
						Menu =1;
						Cursor =1;
						stateA=0;
						stateB=0;
						stateC=0;
						OC3RS=0;
						OC2RS=0;
						start1=0;
						OC3CONbits.OCM=0B000;
						OC2CONbits.OCM=0B000;
						_LATD2=0;
						_LATD1=0;
						T2CONbits.TON=0;
						Clear_lcd();
						DelayMs(10);
				        DISPLAY_stri(0 ,0 , "ģʽѡ��: ");
						DISPLAY_stri(0 ,1 , "->1.���ģ��");	
						DISPLAY_stri(0 ,2 , "  2.�ŵ�ģ��");
                        DISPLAY_stri(0 ,3 , "  3.�Զ�ģ��");	
						writ_com(0x90);
						writ_com(0x0F);
					}
                  	if( Menu_C ==1 )
					{					
                        Menu_A =0;
						Menu_B =0;
						Menu_C =0;
						Menu=1;
						Cursor=1;
						stateA=0;
						stateB=0;
						stateC=0;
						OC3RS=0;
						OC2RS=0;
						_LATD2=0;
						_LATD1=0;
						OC3CONbits.OCM=0B000;
						OC2CONbits.OCM=0B000;
						T2CONbits.TON=0;
						Clear_lcd();
						DelayMs(10);
  					    DISPLAY_stri(0 ,0 , "ģʽѡ��: ");
						DISPLAY_stri(0 ,1 , "->1.���ģ��");	
						DISPLAY_stri(0 ,2 , "  2.�ŵ�ģ��");
                        DISPLAY_stri(0 ,3 , "  3.�Զ�ģ��");	
						writ_com(0x90);
						writ_com(0x0F);
					}
					break;				
			}
			default :break;
		}
		switch (stateA)//���ģʽ
		{
			case 1:	//�ɼ���ѹ����
					RE_Ui=filter(0);	
					RE_Ii=filter(1);
					RE_Uo=filter(2);
					RE_Io=filter(3);
					Ui=(RE_Ui/1.023)*38.74;
					Ii=((RE_Ii/1023)*2980-2082)*10000/418;
					Uo=(RE_Uo/1.023)*25.33;		
					Io=((RE_Io/1023)*2980-2063)*10000/417;
					
				//	POWER_factor=Ui
					start++;	
				
					I_Set_One=test==1?I_Set_One+1000:I_Set_One;
					I_Set_One=test==2?I_Set_One-1000:I_Set_One;
					I_Set_One=I_Set_One>20000?10000:I_Set_One;
					I_Set_One=I_Set_One<10000?20000:I_Set_One;
					test=0;	
					if(Io>=I_Set_One)
					{
					Duty_one=Duty_one<=10?700:Duty_one-1;
					}
					else
					{
					Duty_one=Duty_one>=1300?700:Duty_one+1;
					}
				
					if(Uo>=24000)		//��ѹ����
					{
						DelayMs(2000);
						if(Uo>=24000)
						{
						_LATF2=1;
						T2CONbits.TON=0;
						OC3CONbits.OCM=0B000;
						OC2CONbits.OCM=0B000;
						_LATD2=0;
						_LATD1=0;
						}
					}
					if(switchover)		//��ҳ��ʾ
					{
					if(cls==1)
					{
					Clear_lcd();
					DelayMs(10);
					}
					cls=0;
					DISPLAY_stri(0,0,"����Ui��");
					DISPLAY_stri(4,0,ADC_deal_U(Ui));
					DISPLAY_stri(0,1,"����Ii��");
					DISPLAY_stri(4,1,ADC_deal_I_1(Ii));
					DISPLAY_stri(0,2,"���Uo��");
					DISPLAY_stri(4,2,ADC_deal_U(Uo));
					DISPLAY_stri(0,3,"���Io��");
					if(start==50)
					{start=0;
					GETTEMP=GETTEMP_DS18B20();
					DISPLAY_stri(4,3,ADC_deal_I_1(Io));
					}
					}
					if(!switchover)
					{
					if(cls==1)
					{
					Clear_lcd();
					DelayMs(10);
					}
					cls=0;
					DISPLAY_stri(0,1,"I_set �� ");
					DISPLAY_stri(4,1,ADC_deal_I_1(I_Set_One));
					DISPLAY_stri(0,0,"T��  ");
					DISPLAY_stri(4,0,ADC_deal_U(GETTEMP*100));
					DISPLAY_stri(0,2,"I_fact��");
					if(start==50)
					{
					start=0;
					GETTEMP=GETTEMP_DS18B20();
					DISPLAY_stri(4,2,ADC_deal_I_1(Io));
					}
					}
					stateA=1;		
					break;
 			default :break;
		} 

		switch (stateB)//�ŵ�ģʽ
		{
			case 1:	//�ɼ���ѹ����
					RE_Ui=filter(0);	
					RE_Ii=filter(1);
					RE_Uo=filter(2);
					RE_Io=filter(3);
					Ui=(RE_Ui/1.023)*38.74;
					Ii=(2082-(RE_Ii/1023)*2980)*10000/418;
					Uo=(RE_Uo/1.023)*25.33;		
					Io=(2079-(RE_Io/1023)*2980)*10000/417;
				//	GETTEMP=GETTEMP_DS18B20();		
					if(Ui>=30000)		//��ѹ
					{
					Duty_two=Duty_two<10?700:Duty_two-1;
					}
					else
					{
					Duty_two=Duty_two>1300?700:Duty_two+1;
					}
					start1++;	
					DISPLAY_stri(0,0,"����Ui��");
					if(start1==50)
					{
					start1=0;
					DISPLAY_stri(4,0,ADC_deal_U(Ui));
					}
					DISPLAY_stri(0,1,"����Ii��");
					DISPLAY_stri(4,1,ADC_deal_I_1(Ii));
					DISPLAY_stri(0,2,"���Uo��");
					DISPLAY_stri(4,2,ADC_deal_U(Uo));
					DISPLAY_stri(0,3,"���Io��");
					DISPLAY_stri(4,3,ADC_deal_I_1(Io));
					stateB=1;		
					break;
 			default :break;
		} 
             
		switch (stateC)//�Զ�ģʽ
		{
			case 1:	
					RE_Ui=filter(0);	
					RE_Uo=filter(2);
					Ui=(RE_Ui/1.023)*38.74;
					Uo=(RE_Uo/1.023)*25.33;		
					
					if((Ui>30300)&(BUCK!=1))		//BUCKģʽ  ����30.3	ѡ��BUCK״̬
					{
					BUCK=1;
					BOOST=0;
					OC3CONbits.OCM=0B110;  //BUCK��
					OC2CONbits.OCM=0B000;	//BOOST��
					Duty_one=10;
					T2CONbits.TON=1;	
					}
					if((Ui<29700)&(BOOST!=1))		//BOOSTģʽ  С��29.7	ѡ��BOOST״̬
					{
					BUCK=0;
					BOOST=1;
					OC3CONbits.OCM=0B000;  //BUCK��
					OC2CONbits.OCM=0B110;	//BOOST��
					Duty_two=10;
					T2CONbits.TON=1;	
					}
					if(BUCK==1)
					{
						if(Ui>=30000)		//��ѹ
						{
						Duty_one=Duty_one>1300?10:Duty_one+1;
						}
						else
						{
						Duty_one--; 
						if(Duty_one==4)
						{
							//Duty_one=0;
							//Duty_two=6;
							T2CONbits.TON=0;
							OC3CONbits.OCM=0B000;  //BUCK��
							OC2CONbits.OCM=0B110;	//BOOST��
							Duty_one=0;
							Duty_two=6;
							T2CONbits.TON=1;
							BOOST=1;
							BUCK=0;
						}	
						}	
					}
					if(BOOST==1)
					{
						if(Ui>=30000)		//��ѹ
						{
						Duty_two--;
						if(Duty_two==4)
						{
							T2CONbits.TON=0;
							Duty_two=0;
							Duty_one=6;
							OC3CONbits.OCM=0B110;  //BUCK��
							OC2CONbits.OCM=0B000;	//BOOST��
							T2CONbits.TON=1;
							BOOST=0;
							BUCK=1;
						}	
						
						}
						else
						{
						Duty_two=Duty_two>1300?10:Duty_two+1;
						}	
					}
					DISPLAY_stri(0,0,"����Ui��");
					DISPLAY_stri(4,0,ADC_deal_U(Ui));
					DISPLAY_stri(0,2,"���Uo��");
					DISPLAY_stri(4,2,ADC_deal_U(Uo));

					stateC=1;		
					break;
 			default :break;	
		} 
    			            
    }

	
}
unsigned char KeyScan()
{
	TRISE=0X0F;		//����883��4,5,6,7
 	unsigned char keyvalue;
	if(KeyPort!=0X0F)
   	{
   	 	DelayMs(5);
		if(KeyPort!=0X0F)
	   {
	    	keyvalue=KeyPort;
	    	while(KeyPort!=0X0F);
			switch(keyvalue)
			{
		 		case 0x0E:return 1;break;
		 		case 0x0D:return 2;break;
		 		case 0x0B:return 3;break;
		 		case 0x07:return 4;break;
		 	/*	case 0xEF:return 5;break;
		 		case 0xDF:return 6;break;
		 		case 0xBF:return 7;break;
		 		case 0x7F:return 8;break;
			*/
		 		default:return 0;break;
			}
	  }
   }
   return 0;
}



void __attribute__((__interrupt__,__shadow__)) _T2Interrupt(void)
{
	if(	IFS0bits.T2IF ==1 )
	{
		OC3RS =Duty_one;
		OC2RS =Duty_two;
		IFS0bits.T2IF=0;
	}
} 
