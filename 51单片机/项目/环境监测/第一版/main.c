#include "lcd9648.h"

#include "lcd9648.h"

// 测试用：把整屏点亮
void lcd9648_all_on(void)
{
    u8 page;
    u8 col;

    lcd9648_init();                     // 先初始化（复位 + 9 条配置）

    for(page = 0; page < 9; page++)     // 逐页：0~8
    {
        lcd9648_write_cmd(0xB0 | page); // 设页地址
        lcd9648_write_cmd(0x30);        // 设列地址高 4 位 = 0
        lcd9648_write_cmd(0x00);        // 设列地址低 4 位 = 0

        for(col = 0; col < 96; col++)   // 逐列：0~95
        {
            lcd9648_write_dat(0xFF);    // 写 0xFF：这一列的 8 个点全亮
        }
    }
}

void main(void)
{
    lcd9648_all_on();

    while(1)
    {
    }
}
