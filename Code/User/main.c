#include "delay.h"
#include "uart.h"
#include "str.h"
#include "pwm.h"
#include "key.h"
#include "power.h"
#include "timer.h"

/**********************ʵ��֤��***************************

���˿�����Ϊ׼���������ʱ��ͨ��N��MOS��AO3400
�������أ��˿ڴ����Բ����������裬�����Ҫ��������Ҫ500K���ϵĵ��衣

���˿�����Ϊ���������ʱ��ͨ��N��MOS��AO3400
�������أ��˿ڴ�Ҳ���Բ����������裬�����Ҫ������Ӧ����10K���ϵĵ��衣
***********************************************************/

/**********************ʵ��֤��***************************
C��������Ҫʹ�õ��ַ�����Ҫ�������ȣ�����Ҫ�ı�Ŀ���ֱ�Ӷ���ָ�롣

/************************������********************************/

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



