#include "lcd9648.h"
#include "font.h"

void lcd9648_spi_write_byte(u8 dat)//
{
    u8 i;
    for(i=0;i<8;i++)
    {
        if((dat & 0x80) != 0)
        SDA = 1;
        else
        SDA = 0;

        dat <<= 1;//左移一位
        SCL = 0;//拉低
        SCL = 1;//时钟线拉高，从机开始读取SDA线上的数据

    }

}

void lcd9648_write_cmd(u8 cmd)//写命令
{
    CS = 0;//片选拉低
    RS = 0;//等于0时是写命令,等于1时是写数据
    lcd9648_spi_write_byte(cmd);
    CS = 1;//片选拉高
}

void lcd9648_write_dat(u8 dat)//写数据
{
    CS = 0;
    RS = 1;
    lcd9648_spi_write_byte(dat);
    CS = 1;
}

void lcd9648_init(void)//初始化
{
    //硬件复位
    RST = 1;
    delay_ms(10);
    RST = 0;
    delay_ms(10);
    RST = 1;
    delay_ms(10);

    lcd9648_write_cmd(0xE2);//软件系统复位
    lcd9648_write_cmd(0xC8);//COM方向（上下）
    lcd9648_write_cmd(0xA0);//SEG方向（左右）
    lcd9648_write_cmd(0x2F);//电源控制；升压+稳压+跟随全开（不开屏不亮）
    lcd9648_write_cmd(0x26);//VLCD电阻比（粗略调节对比度）
    lcd9648_write_cmd(0x81);//电子音量（对比度细调）
    lcd9648_write_cmd(0x10);//同上
    lcd9648_write_cmd(0xAF);//开显示
    lcd9648_write_cmd(0x40);//起始行=0
}