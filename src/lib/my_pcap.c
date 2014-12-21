#include "my_pcap.h"

pcap_t*
get_pcap_handle(char* dev)
{
	char errbuf[PCAP_ERRBUF_SIZE];		
    pcap_t* handle;
    handle = pcap_open_live(dev, SNAP_LEN, 1, 1000, errbuf);
	if (handle == NULL)
	{
		fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
		exit(EXIT_FAILURE);
	}
    return handle;
}
