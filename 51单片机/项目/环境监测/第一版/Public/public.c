#include "public.h"


void delay_10us(u16 ten_us)//延时10us函数
{
	while(ten_us--);	
}

void delay_ms(u16 ms)//延时1ms
{
	u16 i,j;
	for(i=ms;i>0;i--)
		for(j=110;j>0;j--);
}