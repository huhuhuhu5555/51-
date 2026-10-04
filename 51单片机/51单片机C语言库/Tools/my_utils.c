// my_utils.c
#include "my_utils.h"

// 两个延时函数
void delay_10us(u16 ten_us) {
    while(ten_us--);
}

void delay_ms(u16 ms) {
    u16 i, j;
    for(i = ms; i > 0; i--)
        for(j = 110; j > 0; j--);
}

// 数码管段码表0~1
unsigned char code SegCode[] = {
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
    0x7F, 0x6F
};
//如果在你的代码工程中，没有全部引用这里面的文件，keil4会报警告