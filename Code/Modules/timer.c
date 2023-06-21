#include "timer.h"
#include "pwm.h"
#include "power.h"


u32 TimeStamp;

void Timer0_Init(u16 us) {
    u16 temp = 0;
    temp = FOSC / us / 12;
    temp = 65536ul - temp;
    TL0 = temp;
    TH0 = temp >> 8;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
}

void Timer0_Int(void) interrupt 1 {
    static u16 delayer = 0;
    static u8 savePowerDelayer = 0;
    if (delayer >= 1000) {
        delayer = 0;
        TimeStamp++;
        if (PWM0_Value == 0 && PWM1_Value == 0) {
            savePowerDelayer++;
            if (savePowerDelayer >= 3) {
                savePowerDelayer = 0;
                SavePower();
            }
        } else savePowerDelayer = 0;
    }
    delayer++;
}