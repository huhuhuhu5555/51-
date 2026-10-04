#include "reg52.h"//头文件
#include "intrins.h"//头文件
typedef unsigned char u8;//定义字符类型
typedef unsigned int u16;//定义字符类型
u8 dat = 0;
sbit DQ = P3^7;//温度传感器端口

void delay_ten_us(u16 us)//延时函数10us 【改1】参数u8改成u16
{
    while(us--);
}

void delay_ten_ms(u16 ms)
{
    while(ms--)
    {
        delay_ten_us(100);//约1ms
    }
}

void uart_send(u8 dat)//串口
{
    TI = 0;
    SBUF = dat;
    while(!TI);
    TI = 0;
}

u8 ds_check(void)//检测温度传感器，返回1=检测到
{
    u8 wait = 0;

    DQ = 1;
    delay_ten_us(1);
    DQ = 0;
    delay_ten_us(75);//【改2】拉低52改成75，够750us
    DQ = 1;
    
    wait = 0;
    while(DQ && wait <200)//等DQ变低
    {
        wait ++;
        delay_ten_us(1);
    }
    if(DQ == 1) return 0;//没等到变低，没检测到

    wait = 0;
    while((!DQ) && wait <200)//【改3】再等DQ变高，让应答结束
    {
        wait ++;
        delay_ten_us(1);
    }

    return 1;//检测到
}

//读字节
u8 ReadByte(void)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        dat >>= 1;
        DQ = 0;
        _nop_();_nop_();//延时2us
        DQ = 1;
        _nop_();_nop_();_nop_();_nop_();//延时4us
        if(DQ == 1)
        {
            dat |=0x80;
        }
        delay_ten_us(5);
    }
    return dat;
}

//写字节
void WriteByte(u8 dat)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        DQ = 0;
        if(dat & 0x01)//写1时
        {
            _nop_();_nop_();
            DQ = 1;
            delay_ten_us(6);
        }
        else//写0时
        {
            delay_ten_us(6);
            DQ = 1;
            _nop_();_nop_();
        }
        dat >>= 1;
    }
}

//读温度，返回整数摄氏度
u8 ds_read_temp(void)
{
    u8 low;
    u8 high;
    u16 raw;

    ds_check();
    WriteByte(0xCC);//跳过ROM
    WriteByte(0x44);//启动转换
    delay_ten_ms(800);//等转换完成

    ds_check();
    WriteByte(0xCC);
    WriteByte(0xBE);//读暂存器
    low  = ReadByte();//第1字节
    high = ReadByte();//第2字节

    raw = high;
    raw = raw << 8;
    raw = raw | low;

    return raw >> 4;
}

void main()//主程序
{
    u8 t;

    TMOD = 0x20;
    TR1 = 1;
    TH1 = 0xFD;
    TL1 = 0xFD;
    PCON &= 0x7F;
    SCON = 0x50;

    delay_ten_ms(100);
    while(1)
    {
        t = ds_read_temp();

        uart_send(t / 10 + '0');
        uart_send(t % 10 + '0');
        uart_send('\n');

        delay_ten_ms(1000);
    }
}
