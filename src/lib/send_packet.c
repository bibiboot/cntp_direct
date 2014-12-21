#include "send_packet.h"

int
send_packet(int s, struct sockaddr_ll* sk_addr, void *packet, int packet_len)
{
    int ret;
    ret = sendto(s, packet, packet_len, 0,
                 (struct sockaddr*)sk_addr,
                 sizeof(struct sockaddr_ll));
    if (-1 == ret){
        perror("sendto:");
        exit(1);
    }
}
