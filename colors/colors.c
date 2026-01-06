#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "colors.h"

// Exercise 57. (20’) An application represents a color with its red, green, and blue components
// (RGB) using a color object declared as follows:
// struct color {
// unsigned int red;
// unsigned int green;
// unsigned int blue;
// };
// In a source file called colors.c or colors.cc write a C or C++ function declared as
// void string_to_color (struct color *, const char *);
// that assigns a color object from a string consisting of between zero and six hexadecimal characters
// representing three bytes, one for each of the RGB components. For example
// struct color c;
// string_to_color(&c, "A00B20"); /* c.red=160; c.green=11; c.blue=32; */
// When the string has less than six characters, all the other characters are considered to be 0 by
// default. For example:
// string_to_color(&c, "A"); /* c.red=160; c.green=0; c.blue=0; */
// Any character that is not a valid hexadecimal digit (see below) is interpreted as a terminator. The
// above default rule still applies. For example:
// string_to_color(&c, "1x"); /* c.red=16; c.green=0; c.blue=0; */
// string_to_color(&c, "CIAO"); /* c.red=192; c.green=0; c.blue=0; */
// string_to_color(&c, "c1ao"); /* c.red=193; c.green=160; c.blue=0; */
// As usual, you may assume the ASCII encoding for all characters and strings. No characters outside
// of the ASCII set need to be considered.
// Hint: recall that the hexadecimal digits are 0123456789abcdefABCDEF, where the numbers have
// their usual values 0–9 while the alphabetic characters a–f and A–F have values 10–15, respectively.
// Each byte value consists of two hexadecimal characters. As usual, the one on the left is the most
// significant one. Thus "10" is 16 while "01" is 1. In general, the value of an hexadecimal number
// made of two digits xy is 16 × value(x) + value(y). For example, the value of the hexadecimal A1
// is 161, since the value of A is 10, so 16 × 10 + 1 = 161


static char* hex = "0123456789abcdefABCDEF";


int hex_value(char ch)
{
    if(ch>= '0' && ch <= '9')return ch-'0';
    if(ch>='a'&&ch<='f')return ch-'a'+10;
    if(ch>='A'&&ch<='F')return ch - 'A'+10;
    return -1;
}

void string_to_color(struct color* c,const char* str)
{
    int value[6];
    int count = 0;
    while(*str && count<=5 && strchr(hex,*str))
    {
        value[count++] = hex_value(*str);
        str++;
    }
    int diff = 6 - count;
    while(diff)
    {
        value[count++] = hex_value('0');
        diff--;
    }




    c->red = 16*value[0] + value[1];
    c->green = 16*value[2] + value[3];
    c->blue = 16*value[4] + value[5];
    
}