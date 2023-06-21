#include "power.h"
#include "delay.h"


void SavePower(void) {
    PCON |= 0x02; //������������ģʽ
}

void ADC_Init(void)
{
    P5M0 &= ~(0x01 << 4);
    P5M1 |= (0x01 << 4);
    P_SW2 |= (0x01 << 7);
    ADCTIM = 0x3f;  //����ADCת��ʱ��
    P_SW2 &= ~(0x01 << 7);
    ADCCFG = 0x1f; //����ADCΪϵͳʱ��/2/16
    ADCCFG |= (0x01 << 5); //����ADCֵΪ�Ҷ���
    ADC_CONTR = 0x04; //��ADC��Դ����ѡ��P5.4�˿�
}

void ADC_ClosePower(void)
{
    ADC_CONTR &= ~(0x01 << 7);
}

void ADC_OpenPower(void)
{
    ADC_CONTR |= (0x01 << 7);
    delay_ms(5);  //��ADC��Դ��Ҫ�ȴ���������ʹ���ƽ�ȶ�
}

u16 ADC_GetValue(void)
{
    u16 temp = 0;
    u16 overtime = 0;
    ADC_OpenPower();
    ADC_CONTR |= (0x01 << 6);
    delay_us(3);
    while(!(ADC_CONTR & 0x20) && ++overtime); //�ȴ�ADCת�������������볬ʱ���
    ADC_ClosePower();
    ADC_CONTR &= ~(0x01 << 5); //���ADCת��������־
    temp = ADC_RES;
    temp <<= 8;
    temp |= ADC_RESL;
    return temp;
}
    