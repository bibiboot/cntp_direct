#include "globals.h"
#include <pcap.h>
#define SNAP_LEN 1518

pcap_t* get_pcap_handle(char *dev);
