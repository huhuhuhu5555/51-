#include "reg52.h"
typedef unsigned char u8;
typedef unsigned int u16; 
		
sbit KEY3 = P3^2;

void delay_ten_us(u16 ten_us)
{
    while(ten_us--);
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
	{	delay_ten_us(10000);
		if(KEY3==0)
		{
    		TI = 0;          // ① 清发送完成标志
    		SBUF = 'A';      // ② 写 SBUF，硬件自动开始发
    		while(!TI);      // ③ 等它发完
    		TI = 0;          // ④ 手动清标志（硬件不会自动清）
			while(KEY3==0);
		}
	 }
  }
  
}

