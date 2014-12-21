#include "globals.h"
#include "recv_ts.h"

/*
 * Create two threads
 * 1. Sniffer thread which replies back as welll as
 *    recv reply and calcukates the drtt and stores it
 *    in global variable.
 * 2. IPC thread which stores the drtt at certain
 *    memory location.
 */

int main(int argc, char *argv[])
{
    struct receiver_arg arg;
    globals.src_node = atoi(argv[1]);
    globals.recv_inf = argv[2];

    arg.dev = globals.recv_inf;
    arg.my_addr = globals.src_node;;
    start_receiver((void*)&arg);

    return 0;
}
