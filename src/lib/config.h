#pragma once

#define CONFIG_INIT { \
    .ipc_sleep_time = 60*1, \
    .packet_len = 1024, \
    .rtt = 2 ,}

struct config {
    uint16_t rtt;
    uint16_t ipc_sleep_time;
    uint16_t packet_len;
};
