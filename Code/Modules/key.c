#include "key.h"
#include "power.h"
#include "pwm.h"

static u16 Temp;

static u8 PressFlag;
static u8 LongPressDelayer;
static u8 LongPressFlag;
static u8 ShortPressFlag;

static u8 LightType;


void ChangeIntensity(void) {
    switch (LightType) {
        case 1: PWM0_Value += PWM_STEP;
                if (PWM0_Value > PWM_TOTAL) PWM0_Value = PWM_STEP;
                break;
        case 2: PWM1_Value += PWM_STEP;
                if (PWM1_Value > PWM_TOTAL) PWM1_Value = PWM_STEP;
                break;
        case 3: PWM0_Value += PWM_STEP;
                if (PWM0_Value > PWM_TOTAL) PWM0_Value = PWM_STEP;
                PWM1_Value = PWM0_Value;
                break;
        default: break;
    }
    
}

void SwitchType(void) {
    LightType++;
    if (LightType >= 4) {
        LightType = 0;
    }
    switch (LightType) {
        case 0: PWM0_Value = 0;
                PWM1_Value = 0;
                break;
        case 1: if (PWM0_Value == 0) PWM0_Value = PWM_STEP;
                break;
        case 2: if (PWM1_Value == 0) PWM1_Value = PWM_STEP;
                break;
        case 3: if (PWM0_Value == 0) PWM0_Value = PWM_STEP;
                if (PWM1_Value == 0) PWM1_Value = PWM_STEP;
                if (PWM0_Value < PWM1_Value) PWM0_Value = PWM1_Value;
                else PWM1_Value = PWM0_Value;
                break;
        default: break;
    }
}

void Key_Init(void) {
    P5M0 &= ~(0x01 << 5);
    P5M1 &= ~(0x01 << 5);  //PxM0与PxM1共同配置IO状态
    Ext3_Enable();
    PCA_Timer_Init(1000);
}

void DetectKey(Press longPress, Press shortPress)
{
    if (!P55) {
        PressFlag = 1;
    } else {
        PressFlag = 0;
        LongPressFlag = 0;
        LongPressDelayer = 0;
    }
    if (PressFlag) {
        if (!LongPressFlag) {
            if (LongPressDelayer > 20) {
                LongPressFlag = 1;
                ShortPressFlag = 0;
//                Ext3_Enable();
                longPress();
            } else {
                ShortPressFlag = 1;
            }
        }
    } else {
        if (ShortPressFlag) {
            ShortPressFlag = 0;
//            Ext3_Enable();
            shortPress();
        }
    }
}

void Ext3_Enable(void)
{
    INT_CLKO |= (0x01 << 5);  //外部中断3，仅支持下降沿中断
}

void Ext3_Disable(void)
{
    INT_CLKO &= ~(0x01 << 5);  //外部中断3，仅支持下降沿中断
}


void PCA_Timer_Init(u16 hz)
{
    CCAPM2 |= 0x49; //打开CAPPWM模块2的软件定时器中断
    Temp = FOSC / hz / 2; //设置中断频率
    CCAP2L = Temp;
    CCAP2H = Temp >> 8;
    Temp += Temp;
    EA = 1;
    CR = 1;
}

void PCA_Timer_Int(void) interrupt 7
{
    static u16 delayer = 0;
    CCF2 = 0;
    CCAP2L = Temp;
    CCAP2H = Temp >> 8;
    Temp += Temp;
    if (delayer >= 5)  //该数值可以调节长按时间
    {
        delayer = 0;
        if (PressFlag && !LongPressFlag) LongPressDelayer++;
        if (LongPressDelayer > 250) LongPressDelayer = 250;
    }
    DetectKey(ChangeIntensity, SwitchType);
    delayer++;
}

void Ext3_Int(void) interrupt 11
{
    PressFlag = 1;
//    Ext3_Disable();
}

