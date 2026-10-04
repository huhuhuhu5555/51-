#include "reg52.h"

typedef unsigned int u16;
typedef unsigned char u8;

// ===== 硬件引脚定义 =====
sbit BEEP = P2^5;
sbit KEY3 = P3^2;// 对应外部中断0
sbit HC138_A = P2^2;
sbit HC138_B = P2^3;
sbit HC138_C = P2^4;

// ===== 数码管段码表 =====
unsigned char code SegCode[] = 
{
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F
};

// ===== 延时函数 =====
void delay_10us(u16 ten_us)
{
    while(ten_us--);
}

void delay_ms(u16 ms) 
{
    u16 i, j;
    for(i = ms; i > 0; i--)
        for(j = 110; j > 0; j--);
}

// ===== 中断控制变量 =====
bit key_pressed = 0;      // 标记：按键被按下
bit beep_busy = 0;        // 标记：蜂鸣器正在响

// ===== 外部中断0服务函数（极简） =====
void Int0_Routine(void) interrupt 0 
{
    if (beep_busy == 0) 
	{
        key_pressed = 1;   // 只立标记，不等待
    }
}

// ===== 主函数 =====
void main() 
{
    // 中断初始化
    IT0 = 1;
    EX0 = 1;
    EA = 1;

    while(1) 
	{
       
        HC138_A = 1; HC138_B = 1; HC138_C = 1;
        P0 = SegCode[0];
        delay_10us(100);
        P0 = 0x00;

        HC138_A = 0; HC138_B = 1; HC138_C = 1;
        P0 = SegCode[1];
        delay_10us(100);
        P0 = 0x00;

        HC138_A = 1; HC138_B = 0; HC138_C = 1;
        P0 = SegCode[2];
        delay_10us(100);
        P0 = 0x00;

        HC138_A = 0; HC138_B = 0; HC138_C = 1;
        P0 = SegCode[3];
        delay_10us(100);
        P0 = 0x00;

        HC138_A = 1; HC138_B = 1; HC138_C = 0;
        P0 = SegCode[4];
        delay_10us(100);
        P0 = 0x00;

        HC138_A = 0; HC138_B = 1; HC138_C = 0;
        P0 = SegCode[5];
        delay_10us(100);
        P0 = 0x00;

        HC138_A = 1; HC138_B = 0; HC138_C = 0;
        P0 = SegCode[6];
        delay_10us(100);
        P0 = 0x00;

        HC138_A = 0; HC138_B = 0; HC138_C = 0;
        P0 = SegCode[7];
        delay_10us(100);
        P0 = 0x00;
	
        if (key_pressed == 1)
		 {
            key_pressed = 0;
            beep_busy = 1;

            BEEP = 1;           // 蜂鸣器响
            delay_ms(100);      // 持续100ms
            BEEP = 0;           // 关闭蜂鸣器

            beep_busy = 0;
          }
    }
}