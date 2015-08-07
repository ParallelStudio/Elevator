#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <hidapi/hidapi.h>

#define VENDOR_ID 0xa07
#define DEVICE_ID 0xd0

int main(int argc, char* argv[]){
	hid_device *handle;
	unsigned char buf[8];
	unsigned char resbuf[8];
	int res;

	handle = hid_open(VENDOR_ID, DEVICE_ID, NULL);
	hid_set_nonblocking(handle, 1);

	buf[0] = 0x01;	//first byte is 1, which says incoming data is ascii
	buf[1] = 'P';
	buf[2] = 'I';	//PI command reads both PA and PB in one go, with ascii response
	buf[3] = 0x00;
	buf[4] = 0x00;
	buf[5] = 0x00;
	buf[6] = 0x00;
	buf[7] = 0x00;

	while(true){
		res = hid_write(handle, buf, 8);
		if(res < 0) {
			printf("Unable to write()!\n");
		}

		res = 0;
		while(res == 0) {	//busy wait until data ready (which sucks, but works)
			res = hid_read(handle, resbuf, 8);
			if(res == 0) {
				//printf("waiting...\n");
			} else if(res < 0) {
				printf("Unable to read()\n");
			}
			usleep(15*1000);
		}

		printf("Data: ");
		printf("%s\n", resbuf+1);
	}
}
