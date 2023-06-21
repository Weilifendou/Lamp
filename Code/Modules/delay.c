#include "delay.h"

void delay_us(u16 us)
{
	u16 i;
	do{
		i = UST;
		while(--i);
	}while(--us);
}

void delay_ms(u16 ms)
{
	u16 i;
	do{
		i = MST;
		while(--i);
	}while(--ms);
}

