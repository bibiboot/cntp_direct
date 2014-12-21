#include "globals.h"
#include "ipc_client.h"

void start()
{
    //pthread_create(&globals.master_th, 0, &send_cntp_packet, NULL);
    pthread_create(&globals.ipc_th, 0, start_ipc_client, NULL);

    //pthread_join(globals.master_th, NULL);
    //pthread_join(globals.ipc_th, NULL);
}

int main(int argc, char *argv[])
{
    globals.src_node  = atoi(argv[1]);
    globals.dest_node = atoi(argv[2]);

    globals.sender_inf = argv[3];

    start();
    sleep(10);

    send_cntp_packet();
    return 0;
}
