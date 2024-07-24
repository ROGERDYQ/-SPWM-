/*******************************************
**
**FileName:LCD12864.c
**
**Author:  PZY  Version: V3.21  Date: 2012-10-15
**
**Description:  LCD12864������ʾ
**
**Function List:
                 1.MCU��LCD�����ֽڣ����д��ͣ�
                 2.д��������
                 3.д����
                 4.���LCD����
                 5.����LCD
                 6.����������ʾ��ʽ

*******************************************/

#include "LCD12864.h"

unsigned char Data_U[7]={'0','0','.','0','0','0','\0'};
unsigned char Data_I[7]={'0','0','0','.','0','0','\0'};
unsigned char Data_I_1[7]={'0','.','0','0','0','0','\0'};
unsigned char num[12]={'0','1','2','3','4','5','6','7','8','9','\0'};

/******��λ���ֽ�******/

void sendbyte(unsigned char byte)
{
  unsigned char i,bw;
  for(i=0;i<8;i++)
      {
        bw=0x80;
        if(bw&byte)
        SID=1;
        else SID=0;
        byte=byte<<1;
        CLK=1;
        DelayUs(1);
        CLK=0;
        DelayUs(1);
       }
 }


/******д��������******/
void writ_com(unsigned int com) 
{
    CS=1;
    DelayUs(1);

    /**���͵�һ�ֽ�**/
    sendbyte(0xf8);  

    /**���͵ڶ��ֽ�*���͸�4λ**/          
    sendbyte(com&0xf0);  

    /**���͵����ֽ�*���͵�4λ**/    
    sendbyte((com<<4)&0xf0);
    DelayUs(5);
    CS=0;
}




/******д����**********/
void writ_Data(unsigned char Data)
{
   CS=1;
   
   /**���͵�һ�ֽ�*RW=0 RS=0**/
   sendbyte(0xfa);  

   /**���͵ڶ��ֽ�****/                  
   sendbyte(Data&0xf0);

   /***���͵����ֽ�***/
   sendbyte((Data<<4)&0xf0);
   DelayUs(2);
   CS=0; 
}


/***���LCD��ʾ����***/
void Clear_lcd()
 {
   writ_com(0x01);
   DelayMs(1);
 }



/***��ʼ��LCD********/
void InitLCD()
{
  SET_IO ;
  DelayMs(1);
  PSB=0;

  /**�����趨**/
  writ_com(0x30);
  DelayUs(50);

  /**8λ����**/
  writ_com(0x30);
  DelayMs(30);
  writ_com(0x30);
  DelayUs(100);
  DelayUs(100);

  /**��������ʾ���ر��α꼰�α�λ��**/
  writ_com(0x0c);
  DelayUs(100);

  /**����***/
  writ_com(0x01);
  DelayUs(100); 

/**���뷽ʽ**/ 
  writ_com(0x06);       
   DelayUs(50);  

}



/******��ʾ�ַ���**����ֻ����������****/
void DISPLAY_stri(unsigned char x ,unsigned char y , unsigned char *p)
{ 
  
  switch(y)
  {
    case 0 :  writ_com(0x80+x);break;
    case 1 :  writ_com(0x90+x);break;
    case 2 :  writ_com(0x88+x);break;
    case 3 :  writ_com(0x98+x);break;

    default:break;
  }
  while(*p>0)
  {    
      writ_Data(*p);
      p++;
  
       
  }
  
}  
unsigned int *ADC_deal_I(unsigned  int Value)//������ʾ 000.00 MA
{
	Data_I[0]=num[Value/10000];
	Data_I[1]=num[Value%10000/1000];
	Data_I[2]=num[Value%1000/100];
	Data_I[4]=num[Value%100/10];
	Data_I[5]=num[Value%10];
	return (Data_I); 
}
unsigned int *ADC_deal_I_1(unsigned  int Value)//����ʾ  0.0000A
{
	Data_I_1[0]=num[Value/10000];
	Data_I_1[2]=num[Value%10000/1000];
	Data_I_1[3]=num[Value%1000/100];
	Data_I_1[4]=' ';
	Data_I_1[5]=' ';
	return (Data_I_1); 
}

unsigned int *ADC_deal_U(unsigned  int Value)//��ѹ��ʾ  00.000V
{
	Data_U[0]=num[Value/10000];
	Data_U[1]=num[Value%10000/1000];
	Data_U[3]=num[Value%1000/100];
	Data_U[4]=num[Value%100/10];
	Data_U[5]=num[Value%10];
	return (Data_U); 
}


void Display(unsigned char x, unsigned char y, unsigned char *p)
{
   unsigned char L;
   L = 0x80;

   while (*p>0)
   {
        
        writ_com(L+x);
        writ_Data(*p);
        p++;
        DelayMs(10);
        writ_Data(*p);
        DelayMs(10);
        p++;
        L++;
   
        if ((L>0x87) && (y == 1))
        {
             L = 0x90;
             y = 2;
        }
        
        if ((L>0x97) && (y == 2))
        {
             L = 0x88;
             y =3;
        }
    
        if ((L>0x8F) && (y == 3))
        {
             L = 0x98;
             y = 4;
        }
        
        if ((L>0x9F) && (y == 4))
        {
             break;
        }

   }

}   
        


 /**��ֵ����ʾ��ֵ ��ʵ��λ������ʾλ����С����λ��**/
/*void DISPLAY_num(long num,unsigned char w,unsigned char ds,unsigned char point )
{
	long m=1;
	unsigned char i;
	unsigned char  buff[8];


	for(i=0;i<(w-1);i++)
	{
		m=m*10; 
	}


	for(i=0;i<ds;i++)
	{
		buff[i]=num/m;
		num=num%m;
		m=m/10;


		writ_Date(buff[i]+0x30);


		if(i==point-1)
        {
             writ_Date(0x2e);

        }
	}
}


//ͼƬ��ʾ//
void DisplayCGRAM(unsigned char x,unsigned char y)
{
  switch (y)
   { 
     case 1: writ_com(0x80+x);break;
     case 2: writ_com(0x90+x);break;
     case 3: writ_com(0x88+x);break;
     case 4: writ_com(0x98+x);break;
     default:break;

   };

    writ_Data(00);
    writ_Data(00);

}
  


//��ʾ����//

void Displayupdata()
{
  unsigned char num;
  Clear_lcd();
  num=(sizeof(SendSeg)/sizeof(SendSeg[0]));

  if(0+(set/4)*4<num)
    Display_String(1,1,SendSeg[0+(set/4)*4]);
  else
    Display_String(1,1,"");
  if(1+(set/4)*4<num)
    Display_String(1,2,SendSeg[1+(set/4)*4]);
  else
    Display_String(1,2,"");
  if(2+(set/4)*4<num)
    Display_String(1,3,SendSeg[2+(set/4)*4]);
  else
    Display_String(1,3,"");
  if(3+(set/4)*4<num)
    Display_String(1,4,SendSeg[3+(set/4)*4]);
  else
    Display_String(1,4,"");

    DisplayCGRAM(0,set%4+1);

}*/