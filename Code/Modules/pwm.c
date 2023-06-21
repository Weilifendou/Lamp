#include "pwm.h"

u8 PWM0_Value;
u8 PWM1_Value;

void PWM_Init(void)
{
    P3M0 &= ~(0x03 << 2);
    P3M1 &= ~(0x03 << 2); //PxM0与PxM1共同配置IO状态
    CMOD &= ~(0x03 << 1);
    CMOD |= (0x01 << 3); //设置为系统时钟倍率，相当于调节PWM频率
    CCAPM0 |= (0x01 << 1); //设置PCA模块0输出PWM
    CCAPM0 |= (0x01 << 6); //设置PCA模块0输出PWM
    CCAPM1 |= (0x01 << 1); //设置PCA模块1输出PWM
    CCAPM1 |= (0x01 << 6); //设置PCA模块1输出PWM
    PCA_PWM0 &= ~(0x01 << 1); //设置PWM0为8位PWM并使能0x20禁用，0x00使能
    PCA_PWM1 &= ~(0x01 << 1);
    CR = 1;  //启动PCA计数器
}

void PWM_SetDuty(u8 order, u8 duty)
{
    if (order == 0)
    {
        if (duty == 0xff) {
            PCA_PWM0 |= (0x01 << 1);
            CCAP0H = duty;
        } else {
            PCA_PWM0 &= ~(0x01 << 1);
            CCAP0H = duty;
        }
    }
    else if (order == 1)
    {
        if (duty == 0xff) {
            PCA_PWM1 |= (0x01 << 1);
            CCAP1H = duty;
        } else {
            PCA_PWM1 &= ~(0x01 << 1);
            CCAP1H = duty;
        }
    }
    else if (order == 2)
    {
        if (duty == 0xff) {
            PCA_PWM2 |= (0x01 << 1);
            CCAP2H = duty;
        } else {
            PCA_PWM2 &= ~(0x01 << 1);
            CCAP2H = duty;
        }
    }
}