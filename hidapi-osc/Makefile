
CC=g++
CFLAGS=-Wall -lhidapi-libusb -fPIC

all: test

test: test.o
	$(CC) $(CFLAGS) test.o -o test	

test.o: test.c
	$(CC) -c $(CFLAGS) test.c

clean: 
	rm *.o test
