#include "pwm.h"

u8 PWM0_Value;
u8 PWM1_Value;

void PWM_Init(void)
{
    P3M0 &= ~(0x03 << 2);
    P3M1 &= ~(0x03 << 2); //PxM0��PxM1��ͬ����IO״̬
    CMOD &= ~(0x03 << 1);
    CMOD |= (0x01 << 3); //����Ϊϵͳʱ�ӱ��ʣ��൱�ڵ���PWMƵ��
    CCAPM0 |= (0x01 << 1); //����PCAģ��0���PWM
    CCAPM0 |= (0x01 << 6); //����PCAģ��0���PWM
    CCAPM1 |= (0x01 << 1); //����PCAģ��1���PWM
    CCAPM1 |= (0x01 << 6); //����PCAģ��1���PWM
    PCA_PWM0 &= ~(0x01 << 1); //����PWM0Ϊ8λPWM��ʹ��0x20���ã�0x00ʹ��
    PCA_PWM1 &= ~(0x01 << 1);
    CR = 1;  //����PCA������
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