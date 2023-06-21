#ifndef __POWER_H
#define __POWER_H

#include "config.h"

void ADC_Init(void);
void ADC_ClosePower(void);
void ADC_OpenPower(void);
u16 ADC_GetValue(void);
void SavePower(void);

#endif
