CC = gcc

CFLAGS = -g -Wall

COMPILE = $(CC) $(CFLAGS)

all: calc format

calc: calc.c
        $(COMPILE) -o calc calc.c

format: format.c
        $(COMPILE) -o format format.c

clean:
        rm -rf *.o calc
        rm -rf *.o format       
                        