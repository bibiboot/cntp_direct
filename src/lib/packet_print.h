#include "globals.h"

void print_packet(unsigned char *,int);

void recv_packet_print(unsigned char *packet, int packet_len);

unsigned long get_offset(unsigned char *packet, int packet_len, struct timestamp recv_kern);
