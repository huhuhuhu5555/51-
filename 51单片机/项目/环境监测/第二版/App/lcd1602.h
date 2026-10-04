#ifndef _lcd1602_H
#define _lcd1602_H

#include "public.h"

// ---- 引脚定义 ----
sbit LCD1602_RS = P2^6;          // 数据/命令选择
sbit LCD1602_RW = P2^5;          // 读写选择
sbit LCD1602_E  = P2^7;          // 使能
#define LCD1602_DATAPORT P0      // 8 位数据口 = P0 整口

// ---- 函数声明 ----
void lcd1602_write_cmd(u8 cmd);
void lcd1602_write_data(u8 dat);
void lcd1602_init(void);
void lcd1602_clear(void);
void lcd1602_show_char(u8 x, u8 y, u8 ch);
void lcd1602_set_cursor(u8 x, u8 y);
void lcd1602_show_string(u8 x, u8 y, u8 *str);
void lcd1602_show_num(u8 x, u8 y, u16 num);

#endif
