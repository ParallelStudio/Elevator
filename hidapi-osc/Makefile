
CC=g++
CFLAGS=-Wall -lhidapi-libusb -fPIC
SRC=$(wildcard '*.c')

all: test hidapi-osc

test: test.o
	$(CC) $(CFLAGS) test.o -o test	

hidapi-osc: hidapi-osc.o
	$(CC) $(CFLAGS) hidapi-osc.o -o hidapi-osc

test.o: test.c
	$(CC) -c $(CFLAGS) test.c

hidapi-osc.o: hidapi-osc.c hidapi-osc.h
	$(CC) -c $(CFLAGS) hidapi-osc.c

clean: 
	rm *.o test
