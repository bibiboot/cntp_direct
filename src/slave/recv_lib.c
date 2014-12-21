#include "recv_lib.h"

void
setup_receiver(struct receiver_arg* arg, int* s, unsigned char** payload,
			   int payload_len, struct msghdr* msg, struct iovec* entry,
			   struct control* control, struct sockaddr_in* from_addr)
{
    arg->inf_index = inf_to_index(arg->dev);
    arg->send_sfd = create_sending_socket(arg->dev, &(arg->sk));

    *payload = (char *)malloc(payload_len);
	if (NULL == payload){
		printf("malloc failed\n");
		exit(1);
	}
    memset(*payload, 0, payload_len);

    *s = create_recv_rawsocket_ts(arg->dev);
    set_promisc(arg->dev, *s);
    setup_raw_msghdr(msg,
                 entry,
                 control,
                 *payload,
                 payload_len,
                 from_addr);
}
