#include "KEY.h"
#include"Delay.h"
/*------------------------------------------------
°´¼üÉ¨Ãèº¯Êý£¬·µ»ØÉ¨Ãè¼üÖµ
------------------------------------------------*/
#define KeyPort PORTE
unsigned char KeyScan(void)
{
	TRISE=0X0F;
 	unsigned char keyvalue;
	if(KeyPort!=0x0F)
   	{
   	 	DelayMs(10);
		if(KeyPort!=0x0F)
	   {
	    	keyvalue=KeyPort;
	    	while(KeyPort!=0x0F);
			switch(keyvalue)
			{
		 		case 0x0E:return 1;break;
		 		case 0x0D:return 2;break;
		 		case 0x0B:return 3;break;
		 		case 0x07:return 4;break;
		 	/*	case 0xEF:return 5;break;
		 		case 0xDF:return 6;break;
		 		case 0xBF:return 7;break;
		 		case 0x7F:return 8;break;*/
		 		default:return 0;break;
			}
	  }
   }
   return 0;
}
