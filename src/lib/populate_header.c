#include "populate_header.h"

int
populate_header(addr_t next_hop_addr, addr_t dst_addr,
                addr_t src_addr, port_t dst_port,
                unsigned char **packet)
{
    struct custom_packet_header* hdr;
    hdr = (struct custom_packet_header*)*packet;
    hdr->identifier = IDENTIFIER;
    hdr->next_hop_addr = htons(next_hop_addr);
    hdr->dst_addr = htons(dst_addr);
    hdr->src_addr = htons(src_addr);
    hdr->dst_port = htons(dst_port);
}
