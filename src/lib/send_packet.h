#include "globals.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/if_packet.h>
int send_packet(int, struct sockaddr_ll*, void*, int); 
