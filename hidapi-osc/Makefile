
CC=g++
OSCPACK=./oscpack_1_1_0/
CFLAGS=-Wall -lhidapi-libusb -loscpack -lstdc++ -fPIC
SRC=$(wildcard '*.c')

all: test hidapi-osc

test: test.o
	$(CC) $(CFLAGS) test.o -o test	

hidapi-osc: hidapi-osc.o
	$(CC) $(CFLAGS) hidapi-osc.o -o hidapi-osc

test.o: test.c
	$(CC) -c $(CFLAGS) test.c

hidapi-osc.o: hidapi-osc.cpp hidapi-osc.h
	$(CC) -c -x c++ $(CFLAGS) hidapi-osc.cpp

clean: 
	rm *.o test
