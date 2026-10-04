// my_utils.h
#ifndef __MY_UTILS_H__
#define __MY_UTILS_H__

#include "reg52.h"      // 因为延时和段码都用到了51的寄存器

typedef unsigned int u16;
typedef unsigned char u8;

// 1. 声明延时函数（告诉外部，我有这两个函数）
void delay_10us(u16 ten_us);
void delay_ms(u16 ms);

// 2. 声明段码表（告诉外部，我有这个数组）
extern unsigned char code SegCode[];

#endif