#ifndef __KEY_H
#define __KEY_H

#include "config.h"

extern u8 LightType;

typedef void (*Press)(void);

void DetectKey(Press, Press);

void Key_Init(void);
void PCA_Timer_Init(u16 hz);
void Ext3_Enable(void);
void Ext3_Disable(void);


#endif
