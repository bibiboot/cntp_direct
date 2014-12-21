#include "recv_ts.h"
#include "filter.h"
#include "packet_print.h"

/*
 * Print the payload
 */
void cntp_packet_handler( struct timestamp recv_kern,
                          unsigned char *packet, int packet_len )
{
    recv_packet_print(packet, packet_len);
    get_offset(packet, packet_len, recv_kern);
}

void*
start_receiver(void *argument)
{
    struct msghdr msg;
    struct iovec entry;
    struct control control;

    unsigned char *packet;
    int recv_sock_fd;
    struct sockaddr_in from_addr;
    struct receiver_arg *arg = (struct receiver_arg*)argument;

    setup_receiver(arg, &recv_sock_fd, &packet, globals.config.packet_len,
		  &msg, &entry, &control, &from_addr);

    int err_packet;
    int num_bytes_read;
    struct timeval recv_usr;
    struct timestamp recv_kern;
    while(1)
    {
        num_bytes_read = recv_rawpacket_ts(recv_sock_fd, &msg, 0, &err_packet, &recv_kern);
        if (num_bytes_read < 0){
            printf("Error receiving\n");
            exit(1);
        } else if(err_packet){
	    printf("An error packet. Exiting.\n");
	    exit(1);
	}

	gettimeofday(&recv_usr, 0);

	if (is_cntp(packet)){
            cntp_packet_handler( recv_kern, packet, num_bytes_read );
        } else {
            /* Drop the packet */
        }
   }
}
