#ifndef FORMAT_H_
#define FORMAT_H_

int toInt(char *num, char type);

void reverse(char *bits);

int expcalc(int base, int pow);

typedef union Number Number;

static void get_float_digit( float x, char * digit, int * pow10, float * remainder );

static void append( char * s, char c );

void floatToASCII( float x, char * output );

void intToDecASCII(int input, char *answer);

#endif