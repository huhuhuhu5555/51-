#include "reg52.h"

typedef unsigned int u16;	//对系统默认数据类型进行重定义
typedef unsigned char u8;


sbit HC138_A = P2^2;
sbit HC138_B = P2^3;
sbit HC138_C = P2^4;

unsigned char code SegCode[] = 
{
    0x3F, // 数字 0
    0x06, // 数字 1
    0x5B, // 数字 2
    0x4F, // 数字 3
    0x66, // 数字 4
    0x6D, // 数字 5
    0x7D, // 数字 6
    0x07, // 数字 7
    0x7F, // 数字 8
    0x6F  // 数字 9
};

void delay_10us(u16 ten_us)
{
	while(ten_us--);
}

void main()
{	
	while(1)
	{
		HC138_A = 1;
		HC138_B = 1;
		HC138_C = 1;
		P0 = SegCode[0];
		delay_10us(100);
		P0 = 0x00;
		
		HC138_A = 0;
		HC138_B = 1;
		HC138_C = 1;
		P0 = SegCode[1];
		delay_10us(100);
		P0 = 0x00;
	
		HC138_A = 1;
		HC138_B = 0;
		HC138_C = 1;
		P0 = SegCode[2];
		delay_10us(100);
		P0 = 0x00;

		HC138_A = 0;
		HC138_B = 0;
		HC138_C = 1;
		P0 = SegCode[3];
		delay_10us(100);
		P0 = 0x00;

		HC138_A = 1;
		HC138_B = 1;
		HC138_C = 0;
		P0 = SegCode[4];
		delay_10us(100);
		P0 = 0x00;

		HC138_A = 0;
		HC138_B = 1;
		HC138_C = 0;
		P0 = SegCode[5];
		delay_10us(100);
		P0 = 0x00;

		HC138_A = 1;
		HC138_B = 0;
		HC138_C = 0;
		P0 = SegCode[6];
		delay_10us(100);
		P0 = 0x00;

		HC138_A = 0;
		HC138_B = 0;
		HC138_C = 0;
		P0 = SegCode[7];
		delay_10us(100);
		P0 = 0x00;
		//HC138_A是A0，最小位；HC138_C是A2是最大位，读的时候从小往大读


	}	
}


