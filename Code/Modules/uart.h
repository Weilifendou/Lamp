#ifndef __UART_H
#define __UART_H

#include "config.h"

#define	COM_RX1_LENGTH	32
#define	COM_TX1_LENGTH	32

void UART1_Init(u32 brt);
void UART1_SendByte(u8 dat);
void URAT1_PrintText(u8* str);

void SendData(void);

#endif
