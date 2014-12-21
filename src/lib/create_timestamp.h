#include "globals.h"
#include <sys/time.h>
#define FIRST_TS(pkt) (struct timestamp*)((pkt) + CUSTOM_HEADER_SZ)
#define NEXT_TS(ts) ((ts)+ 1)
#define IS_TS_ZERO(ts) ((ts->sec == 0) && (ts->fsec == 0))
void create_timestamp(struct timestamp*);
void cal_time_diff(struct timestamp*, struct timestamp*, void* payload);
