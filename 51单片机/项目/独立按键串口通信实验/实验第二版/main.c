#include "reg52.h"
typedef unsigned char u8;
typedef unsigned int u16; 
		
sbit KEY3 = P3^2;
u8 count = 0;

void delay_ten_us(u16 ten_us)
{
    while(ten_us--);
}

void uart_send(u8 dat)
{
	TI = 0;
    SBUF = dat; 
    while(!TI);      
    TI = 0;	
}

void main()
{
  KEY3=1;
  TMOD=0x20;
  TH1=0xFD;
  TL1=0xFD;
  SCON=0x50;
  PCON &=0x7F;
  TR1=1;
  while(1)
  {
  	if(KEY3 == 0)
	{	delay_ten_us(5000);
		if(KEY3==0)
		{	
			count ++;
			uart_send(count / 10 + '0');
			uart_send(count % 10 + '0');
			uart_send('\n');
			while(KEY3==0);
		}
	 }
  }
  
}

