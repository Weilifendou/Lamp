#ifndef __PWM_H
#define __PWM_H

#include "config.h"


#define PWM_TOTAL 0xFA
#define PWM_STEP_NUMBER 5
#define PWM_STEP (PWM_TOTAL / PWM_STEP_NUMBER)

extern u8 PWM0_Value;
extern u8 PWM1_Value;

void PWM_Init(void);
void PWM_SetDuty(u8 order, u8 duty);

#endif
