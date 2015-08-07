
#define POLL_SLEEP_MS 25
#define VENDOR_ID 0xa07
#define DEVICE_ID 0xd0

int send_ontrak_command(hid_device *handle);
int send_osc(int state);