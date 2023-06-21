#ifndef __DELAY_H
#define __DELAY_H

#include "config.h"

#define MST (FOSC / 10000)
#define UST (FOSC / 10000000)

void delay_us(u16 us);
void delay_ms(u16 ms);

#endif
