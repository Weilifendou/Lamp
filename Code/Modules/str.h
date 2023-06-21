#ifndef __STR_H
#define __STR_H

#include "config.h"

void IntToStr(s8* str, s32 value);
void FloatToStr(s8* str, double value, u8 precision);
u8 GetStrLen(s8* str);
void AddStr(s8* preStr, s8* subStr);

#endif
