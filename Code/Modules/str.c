#include "str.h"

void IntToStr(s8* str, s32 value)        //整型数值转换为字符串函数
{
    long integer = 0;
    long compare = 1; 
    if(value < 0){
        value = -value;
        *str++ = '-';
    }
    integer = (long) value;
    do{
        compare *= 10;
    }while(compare <= integer);
    do{                                         
        compare /= 10;
        *str++ = integer / compare % 10 + '0';
    }while(compare > 1);
    *str = 0;
}

void FloatToStr(s8* str, double value, u8 precision)       //浮点型数值转换为字符串函数
{
    long integer = 0;
    long compare = 1;
    long decimalPower = 1;  
    double decimal = 0;
    if(value < 0){
        value = -value;
        *str++ = '-';
    }
    integer = (long) value;
    decimal = value - integer;
    do{
        compare *= 10;
    }while(compare <= integer);
    do{
        compare /= 10;
        *str++ = integer / compare % 10 + '0';
    }while(compare > 1);
    if(precision > 0){
        *str++ = '.';
        while(precision){
            precision--;
            decimalPower *= 10;
            *str++ = (long) (decimal * decimalPower) % 10 + '0';
        }
        *str = 0;
    } else *str = 0;
}

u8 GetStrLen(s8* str)
{
    u8 i = 0;
    for (i = 0; str[i] != 0; i++);
    return i;
    
}

void AddStr(s8* preStr, s8* subStr)
{
    u8 i = 0;
    u8 temp = GetStrLen(preStr);
    for (i = 0; subStr[i] != 0; i++) {
        preStr[temp + i] = subStr[i];
    }
    preStr[temp + i] = 0;
}

