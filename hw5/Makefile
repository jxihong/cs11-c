# 
# CS 11: Makefile for assignment 5.
#
 
CC     = gcc
CFLAGS = -g -Wall -Wstrict-prototypes -ansi -pedantic

all: 1dCA_pointer 1dCA_array

1dCA_pointer: 1dCA_pointer.o memcheck.o 
	$(CC) 1dCA_pointer.o memcheck.o -o 1dCA_pointer


1dCA_array: 1dCA_array.o memcheck.o 
	$(CC) 1dCA_array.o memcheck.o -o 1dCA_array

1dCA_pointer.o: 1dCA_pointer.c
	$(CC) $(CFLAGS) -c 1dCA_pointer.c 

1dCA_array.o: 1dCA_array.c
	$(CC) $(CFLAGS) -c 1dCA_array.c 

memcheck.o: memcheck.c memcheck.h
	$(CC) $(CFLAGS) -c memcheck.c

check:
	c_style_check 1dCA_pointer.c 1dCA_array.c

clean:
	rm -f 1dCA_pointer 1dCA_array *.o