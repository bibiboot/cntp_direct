#include "send_cntp_packet.h"

/*
 * Append the DRTT to the payload
 * and send packet. The kernel will
 * attach the timestamp along the way.
 */
void
send_cntp_packet()
{
    unsigned char *pkt = malloc(C_HLEN + TIMESTAMP_LEN);
    memset(pkt, 0, C_HLEN + TIMESTAMP_LEN);

    struct sockaddr_ll sk;
    int send_sock_fd = create_sending_socket(globals.sender_inf, &sk);

    populate_header(globals.dest_node, globals.dest_node,
                    globals.src_node, CNTP_PORT, &pkt);

    struct timestamp *drtt_st = (struct timestamp *)(pkt + C_HLEN);
    drtt_st->sec = 0;
    drtt_st->fsec = atoi(globals.drtt);

    send_packet(send_sock_fd, &sk, pkt, C_HLEN + TIMESTAMP_LEN);

    print_drtt_packet_net(pkt);
    print_timestamp((struct timestamp*)(pkt + C_HLEN));
}
