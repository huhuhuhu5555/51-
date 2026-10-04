#include "lcd1602.h"

void lcd1602_write_cmd(u8 cmd)//写命令
{
    LCD1602_RS = 0;//选择命令
    LCD1602_RW = 0;//写模式
    LCD1602_E = 0;//
    LCD1602_DATAPORT = cmd;
    delay_ms(1);//等数据稳定
    LCD1602_E = 1;//拉高
    delay_ms(1);//延时1ms
    LCD1602_E = 0;//拉低
}

void lcd1602_write_data(u8 dat)//写数据
{
    LCD1602_RS = 1;
    LCD1602_RW = 0;
    LCD1602_E = 0;
    LCD1602_DATAPORT = dat;
    delay_ms(1);
    LCD1602_E = 1;
    delay_ms(1);
    LCD1602_E = 0;
}

void lcd1602_init(void)//初始化
{
    delay_ms(20);//上电等待稳定
    lcd1602_write_cmd(0x38);//8位总线，2行，5X8点阵
    lcd1602_write_cmd(0x0C);//开显示，无光标，不闪烁
    lcd1602_write_cmd(0x06);//写入后光标右移，屏幕不动
    lcd1602_write_cmd(0x01);//清屏，等1.64ms
}

void lcd1602_clear(void)//清屏函数
{
    lcd1602_write_cmd(0x01);//清屏
}

void lcd1602_set_cursor(u8 x,u8 y)//光标
{
    u8 addr;
    if(y == 0)
    {
        addr = 0x80 + x;
    }
    else
    {
        addr = 0x80 + 0x40 + x;
    }    
    lcd1602_write_cmd(addr);
}

void lcd1602_show_string(u8 x, u8 y, u8 *str)
{
    u8 i;
    lcd1602_set_cursor(x,y);
    for(i = 0; str[i] != '\0'; i++)// ← 思路②：从第 0 个开始挨个来
    {
        lcd1602_write_data(str[i]);// ← 思路②：把第 i 个字符写出去
    }
}

void lcd1602_show_char(u8 x,u8 y,u8 ch)//写一个字符
{
    lcd1602_set_cursor(x,y);
    lcd1602_write_data(ch);
}

void lcd1602_show_num(u8 x, u8 y,u16 num)
{
    lcd1602_set_cursor(x,y);
    lcd1602_write_data(num / 10 + '0'); 
    lcd1602_write_data(num % 10 + '0');
}

