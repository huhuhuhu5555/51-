#include "reg52.h"
#define LED_PORT P2

sbit  LED1 = LED_PORT^0;
sbit  LED2 = LED_PORT^1;
sbit  LED3 = LED_PORT^2;
sbit  LED4 = LED_PORT^3;
sbit  LED5 = LED_PORT^4;
sbit  LED6 = LED_PORT^5;
sbit  LED7 = LED_PORT^6;
sbit  LED8 = LED_PORT^7;
 
typedef unsigned int u16;
typedef unsigned char u8;
 
void delay_ms(u16 ms)
{
	u16 i,j;
	for(i=ms;i>0;i--)
	{
		for(j=110;j>0;j--);
	}
}

void main()
{
	while(1)
	{
		LED1=0;
		delay_ms(30);
  		LED_PORT=0xFF;
		delay_ms(30);
		LED2=0;
		delay_ms(30);
  		LED_PORT=0xFF;
		delay_ms(30);
		LED3=0;
		delay_ms(30);
  		LED_PORT=0xFF;
		delay_ms(30);
		LED4=0;
		delay_ms(30);
  		LED_PORT=0xFF;
		delay_ms(30);
		LED5=0;
		delay_ms(30);
  		LED_PORT=0xFF;
		delay_ms(30);
		LED6=0;
		delay_ms(30);
  		LED_PORT=0xFF;
		delay_ms(30);
		LED7=0;
		delay_ms(30);
  		LED_PORT=0xFF;
		delay_ms(30);
		LED8=0;
		delay_ms(30);
  		LED_PORT=0xFF;
		delay_ms(30);


	}
	
}
