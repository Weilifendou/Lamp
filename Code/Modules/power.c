#include "power.h"
#include "delay.h"


void SavePower(void) {
    PCON |= 0x02; //控制其进入掉电模式
}

void ADC_Init(void)
{
    P5M0 &= ~(0x01 << 4);
    P5M1 |= (0x01 << 4);
    P_SW2 |= (0x01 << 7);
    ADCTIM = 0x3f;  //设置ADC转换时间
    P_SW2 &= ~(0x01 << 7);
    ADCCFG = 0x1f; //设置ADC为系统时钟/2/16
    ADCCFG |= (0x01 << 5); //设置ADC值为右对齐
    ADC_CONTR = 0x04; //打开ADC电源，并选择P5.4端口
}

void ADC_ClosePower(void)
{
    ADC_CONTR &= ~(0x01 << 7);
}

void ADC_OpenPower(void)
{
    ADC_CONTR |= (0x01 << 7);
    delay_ms(5);  //打开ADC电源需要等待几个毫秒使其电平稳定
}

u16 ADC_GetValue(void)
{
    u16 temp = 0;
    u16 overtime = 0;
    ADC_OpenPower();
    ADC_CONTR |= (0x01 << 6);
    delay_us(3);
    while(!(ADC_CONTR & 0x20) && ++overtime); //等待ADC转换结束，并加入超时监测
    ADC_ClosePower();
    ADC_CONTR &= ~(0x01 << 5); //清除ADC转换结束标志
    temp = ADC_RES;
    temp <<= 8;
    temp |= ADC_RESL;
    return temp;
}
    