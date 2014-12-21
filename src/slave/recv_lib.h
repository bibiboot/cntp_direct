#include "globals.h"
#include "my_rawsocket_ts.h"
#include "utils.h"
#include "my_socket.h"
#include "create_timestamp.h"

struct receiver_arg
{
    char* dev;             /* device name */
    addr_t my_addr;
    int inf_index;
    int send_sfd;          /* sender file descriptor */
    struct sockaddr_ll sk;
};

void setup_receiver(struct receiver_arg*, int*, unsigned char**, int, struct msghdr*,
		    struct iovec*, struct control*, struct sockaddr_in*);
