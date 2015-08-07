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

int main(int argc, char* argv[]){
	hid_device *handle;
	unsigned char resbuf[8];

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
	unsigned char buf[8];
	memset(buf, 0, 8);
	buf[0] = 0x01;	//first byte is 1, which says incoming data is ascii
	buf[1] = 'P';
	buf[2] = 'I';	//PI command reads both PA and PB in one go, with ascii response
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