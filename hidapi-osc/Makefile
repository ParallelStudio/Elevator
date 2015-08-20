
CC=g++
OSCPACK=./oscpack_1_1_0/
CFLAGS=-Wall -lhidapi-libusb -lstdc++ -fPIC
SRC=$(wildcard '*.c')

default: winderz

all: test hidapi-osc

test: test.o
	$(CC) $(CFLAGS) test.o -o test	

hidapi-osc: hidapi-osc.o
	$(CC) $(CFLAGS) hidapi-osc.o -o hidapi-osc

test.o: test.c
	$(CC) -c $(CFLAGS) test.c

hidapi-osc.o: hidapi-osc.cpp hidapi-osc.h
	$(CC) -c -x c++ $(CFLAGS) hidapi-osc.cpp

winderz: hidapi-osc.cpp hidapi-osc.h
	g++ -I.\oscpack_1_1_0 -I.\hidapi-0.7.0\hidapi \
		oscpack_1_1_0\osc\OscTypes.cpp oscpack_1_1_0\osc\OscOutboundPacketStream.cpp \
		oscpack_1_1_0\ip\win32\NetworkingUtils.cpp oscpack_1_1_0\ip\win32\UdpSocket.cpp \
		oscpack_1_1_0\ip\IpEndpointName.cpp \
		hidapi-0.7.0\windows\hid.c \
		hidapi-osc.cpp \
		-Wall -Wextra -I. -lws2_32 -lwinmm \
		-lsetupapi \
		-o hidapi-osc.exe

clean: 
	rm *.o test hidapi-osc.exe
