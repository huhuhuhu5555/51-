#include "reg52.h"
typedef unsigned int u16;
typedef unsigned char u8;

// 新增：蜂鸣器引脚定义
sbit BEEP = P2^5;
sbit KEY3 = P3^2;
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

void delay_ms(u16 ms)
{
	u16 i, j;
	for (i = ms; i > 0; i--)
		for (j = 110; j > 0; j--);
}
 
// 新增：外部中断0服务函数（P3.2按键按下时触发）
void Int0_Routine(void) interrupt 0
{
	
	// 判断按键是否真的按下（P3.2为低电平）
	if (KEY3 == 0)
	{
		BEEP = 1;			// 蜂鸣器响（如果是高电平驱动）
				            // 响100ms
		BEEP = 0;			// 蜂鸣器关闭
		
		// 等待按键释放（防止重复触发）
		while (KEY3 == 0);
	}
}

void main()
{
	// 新增：外部中断0初始化配置
	IT0 = 1;	// 设置外部中断0为下降沿触发（按键按下瞬间触发）
	EX0 = 1;	// 开启外部中断0
	EA = 1;		// 开启总中断
	
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
