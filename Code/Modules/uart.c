#include "uart.h"
#include "str.h"
#include "pwm.h"

u8 FunctionCode;

void UART1_Init(u32 brt)
{
    u32 temp = 0;
    P3M0 &= ~(0x03 << 0);
    P3M1 &= ~(0x03 << 0);  //PxM0与PxM1共同配置IO状态
    SCON |= (0x05 << 4);  //常用0x40，基本不用修改
    SCON &= ~(0x01 << 7);
    TMOD &= ~(0x07 << 4);  //设置定时器为定时模式
    AUXR |= (0x01 << 6);  //将定时器1作为串口发生器
    temp = FOSC / brt / 4;
    temp = 65536ul - temp;
    TL1 = temp;
    TH1 = temp >> 8;
    IPH |= (0x01 << 4);
    PS = 1;
    ES = 1;
    EA = 1;
    TR1 = 1;
}

void UART1_SendByte(u8 dat)
{
    SBUF = dat;
    while(!TI);
    TI = 0;
}

void URAT1_PrintText(u8* str)
{
    for(; *str != 0; str++)
        UART1_SendByte(*str);
}


void UART1_Int(void) interrupt 4
{
    static u8 cnt = 0;
    if(RI)
    {
        RI = 0;
        switch(cnt){
            case 0: if(SBUF == 0x55) cnt++;
                    break;
            case 1: if(SBUF == 0xaa) cnt++;
                    else cnt = 0;
                    break;
            case 2: FunctionCode = SBUF; cnt++;
                    break;
            case 3: PWM0_Value = SBUF; cnt++;
                    break;
            case 4: PWM1_Value = SBUF; cnt = 0;
                    break;
            default: cnt = 0;
                    break;
        }
    }
}

void SendData(void) {
    
}

