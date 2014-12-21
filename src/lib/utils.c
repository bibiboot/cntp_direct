#include "utils.h"

void
print_ts(uint32_t *ts)
{
    printf("+\t%u\t+\t%u\n",*ts, *(ts+1));
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void
print_drtt_packet(void *packet)
{
    print_header(packet);
    print_ts(packet + C_HLEN);
}

void
print_header_net(void *packet)
{
    struct custom_packet_header* pkt;
    pkt = (struct custom_packet_header*)packet;
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("+\t0x%04x\t+\t0x%04x\t+\t0x%04x\t+\t0x%04x\t+\n",
            htons(pkt->next_hop_addr), htons(pkt->dst_addr),
            htons(pkt->src_addr), htons(pkt->dst_port) );
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void
print_ts_net(uint32_t *ts)
{
    printf("+\t0x%08x\t+\t0x%08x\n",htonl(*ts), htonl(*(ts+1)) );
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void
print_drtt_packet_net(void *packet)
{
    print_header_net(packet);
    print_ts_net(packet + C_HLEN);
}

void
print_timestamp(struct timestamp* ts)
{
    printf("sec:%u\tfsec:%u\n", ts->sec, ts->fsec);
}
