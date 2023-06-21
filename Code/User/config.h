#ifndef __CONFIG_H
#define __CONFIG_H

/*********************************************************/

//#define FOSC 22118400L	//定义主时钟
//#define FOSC 12000000L	//定义主时钟
#define FOSC 11059200L	//定义主时钟
//#define FOSC 5529600L	//定义主时钟
//#define FOSC 24000000L	//定义主时钟

//#define STC8Hxx		//STC8H系列
#define STC8Gxx		//STC8G系列

/*********************************************************/

#include "stc8xxxx.h"

#define EnableSystemInterrupt (EA = 1)
#define DisableSystemInterrupt (EA = 0)

#endif
