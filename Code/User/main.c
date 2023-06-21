#include "delay.h"
#include "uart.h"
#include "str.h"
#include "pwm.h"
#include "key.h"
#include "power.h"
#include "timer.h"

/**********************实验证明***************************

将端口设置为准输入输出口时，通过N型MOS管AO3400
驱动负载，端口处可以不接下拉电阻，如果非要下拉，须要500K以上的电阻。

将端口设置为推挽输出口时，通过N型MOS管AO3400
驱动负载，端口处也可以不接下拉电阻，如果非要下拉，应该在10K以上的电阻。
***********************************************************/

/**********************实验证明***************************
C语言中需要使用的字符串需要声明长度，不需要改变的可以直接定义指针。

/************************主函数********************************/

u8 Debug;

void main (void)
{
    s8 text[20] = {0};
    UART1_Init(115200);
    Timer0_Init(1000);
    PWM_Init();
    Key_Init();
    ADC_Init();
    Debug = 1;
    while (1)
    {
        SendData();
        PWM_SetDuty(0, 0xff - PWM0_Value);
        PWM_SetDuty(1, 0xff - PWM1_Value);
        if (Debug) {
            IntToStr(text, PWM0_Value);
            AddStr(text, "\t");
            IntToStr(text+GetStrLen(text), PWM1_Value);
            AddStr(text, "\t");
            IntToStr(text+GetStrLen(text), TimeStamp);
            AddStr(text, "\t");
            FloatToStr(text+GetStrLen(text), ADC_GetValue()*4.142/513, 2);
            AddStr(text, "V");
            URAT1_PrintText(text);
        }
        WDT_CONTR |= 0x10;
        delay_ms(200);
    }
}



