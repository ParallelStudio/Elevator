#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <hidapi/hidapi.h>
#include "hidapi-osc.h"

int last_state = 0;
char *host;
int port;

int main(int argc, char* argv[]){
	hid_device *handle;
	unsigned char resbuf[8];

	if(argc < 3){
		usage();
		return 1;
	}
	host = argv[1];
	port = atoi(argv[2]);

	handle = hid_open(VENDOR_ID, DEVICE_ID, NULL);
	hid_set_nonblocking(handle, 0);	//blocking mode ftw

	while(true){
		send_ontrak_command(handle);
		int res = hid_read(handle, resbuf, 8);
		if(res <= 0){
			printf("ERROR reading");
		}
		else{
			printf("Data: ");
			int state = atoi((const char*)resbuf+1);
			printf("%d\n", state);
			if(state != last_state){
				last_state = state;
				send_osc(state);
			}
		}
		usleep(POLL_SLEEP_MS * 1000);
	}
}

int send_ontrak_command(hid_device *handle){
	unsigned char buf[] = { 0x01, 'P', 'I', 0, 0, 0, 0, 0 };
	int res = hid_write(handle, buf, 8);
	if(res < 0) {
		printf("Unable to write()!\n");
	}
	return res;
}

int send_osc(int state){
	printf("Sending OSC: %d\n", state);
	return 0;
}

void usage(){
	printf("Usage: hidapi-osc <host> <port>\n");
}