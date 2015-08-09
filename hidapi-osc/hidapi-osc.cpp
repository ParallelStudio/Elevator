#ifdef WIN32
#include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <hidapi/hidapi.h>
#include <oscpack/osc/OscOutboundPacketStream.h>
#include <oscpack/ip/UdpSocket.h>
#include "hidapi-osc.h"

#define OUTPUT_BUFFER_SIZE 1024

int last_state = -1;
char *host;
int port;
int dots = 0;

int main(int argc, char* argv[]){
	hid_device *handle;
	unsigned char resbuf[8];

	if(argc < 3){
		usage();
		return 1;
	}
	host = argv[1];
	port = atoi(argv[2]);

	printf("Opening ONTRAK device...\n");
	handle = hid_open(VENDOR_ID, DEVICE_ID, NULL);
	hid_set_nonblocking(handle, 0);	//blocking mode ftw
	printf("Device opened and set to blocking mode.");

	UdpTransmitSocket transmitSocket( IpEndpointName( host, port ) );

	while(true){
		send_ontrak_command(handle);
		int res = hid_read(handle, resbuf, 8);
		if(res <= 0){
			printf("ERROR reading\n");
		}
		else{
			fprintf(stdout, ".");
			fflush(stdout);
			if(++dots > 80){
				printf("\n");
				dots = 0;
			}
			int state = atoi((const char*)resbuf+1);
			// printf("%d\n", state);
			if(state != last_state){
				last_state = state;
				send_osc(transmitSocket, state);
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

int send_osc(UdpTransmitSocket &transmitSocket, int state){
	printf("\nSending OSC: %d\n", state);
	dots = 0;
	char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
	p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/ontrak" ) 
            << state << osc::EndMessage
        << osc::EndBundle;
    transmitSocket.Send( p.Data(), p.Size() );
	return 0;
}

void usage(){
	printf("Usage: hidapi-osc <host> <port>\n");
}