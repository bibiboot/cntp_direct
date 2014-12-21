#include "create_timestamp.h"

void
create_timestamp(struct timestamp* ts)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    ts->sec = tv.tv_sec;
    ts->fsec = tv.tv_usec;
}

void
cal_time_diff(struct timestamp* dst,
              struct timestamp* local_rx,
              void* payload)
{
    struct timestamp *local_tx, *remote_rx, *remote_tx;
    local_tx = (struct timestamp*)(payload + C_HLEN);
    remote_rx = local_tx + 1;
    remote_tx = local_tx + 2;

    printf("calculating time diff\n");
    printf("local tx: %u.%u\n", local_tx->sec, local_tx->fsec);
    printf("remot rx: %u.%u\n", remote_rx->sec, remote_rx->fsec);
    printf("remot tx: %u.%u\n", remote_tx->sec, remote_tx->fsec);
    printf("local rx: %u.%u\n", local_rx->sec, local_rx->fsec);

    dst->sec = (local_rx->sec - local_tx->sec) //total delay
               - (remote_tx->sec - remote_rx->sec); //remote processing
    dst->fsec = (local_rx->fsec - local_tx->fsec)
                - (remote_tx->fsec - remote_rx->fsec);

    printf("time diff: %u.%u\n", dst->sec, dst->fsec);
}
