#ifndef __CONFIG_H
#define __CONFIG_H

/*********************************************************/

//#define FOSC 22118400L	//������ʱ��
//#define FOSC 12000000L	//������ʱ��
#define FOSC 11059200L	//������ʱ��
//#define FOSC 5529600L	//������ʱ��
//#define FOSC 24000000L	//������ʱ��

//#define STC8Hxx		//STC8Hϵ��
#define STC8Gxx		//STC8Gϵ��

/*********************************************************/

#include "stc8xxxx.h"

#define EnableSystemInterrupt (EA = 1)
#define DisableSystemInterrupt (EA = 0)

#endif
