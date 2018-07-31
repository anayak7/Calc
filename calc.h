#ifndef CALC_H_
#define CALC_H_

long int fromString(char *input, char base, int isneg);

long int expcalc(int base, int pow);

void reverse(char *bits);

int toString(long int num, char outputbase, char *output);

int twosComp(char *answer);

#endif
