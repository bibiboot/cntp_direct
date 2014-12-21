#pragma once

#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <sys/time.h>
#include <unistd.h>

#include "config.h"
#include "color.h"
#include "uthash.h"
#include "logger.h"

#define TIMESTAMP_LEN 8
#define C_HLEN        68

#define CNTP_PORT     3

//#define BROADCAST_ADDR 0xFFFF
#define BROADCAST_ADDR 0x0FF00
#define IDENTIFIER     0x0FF00
#define ROUTER_IP      3

#define SECONDS      1000000000
#define MILLISECONDS 1000000
#define MICROSECONDS 1000
#define NANOSECONDS  1

#define EXTRACT_64BITS(p) \
                ((u_int64_t)((u_int64_t)*((const u_int8_t *)(p) + 0) << 56 | \
                                                             (u_int64_t)*((const u_int8_t *)(p) + 1) << 48 | \
                                                             (u_int64_t)*((const u_int8_t *)(p) + 2) << 40 | \
                                                             (u_int64_t)*((const u_int8_t *)(p) + 3) << 32 | \
                                                             (u_int64_t)*((const u_int8_t *)(p) + 4) << 24 | \
                                                             (u_int64_t)*((const u_int8_t *)(p) + 5) << 16 | \
                                                             (u_int64_t)*((const u_int8_t *)(p) + 6) << 8 | \
                                                             (u_int64_t)*((const u_int8_t *)(p) + 7)))


typedef uint16_t addr_t;
typedef uint16_t port_t;

/*
 * Not used
 */
typedef struct hashl {
    int key;
    char value[100];
    UT_hash_handle hh;
} dict_node;

struct custom_packet_header{
    addr_t identifier;     /* Custom protocol identifier */
    addr_t next_hop_addr;
    addr_t dst_addr;
    addr_t src_addr;
    port_t dst_port;
    char padding[58];      /* Padding for large length   */
};

struct timestamp{
    uint32_t sec;
    uint32_t fsec;
};

struct globals {
    struct config config;
    dict_node *hashl;     /* Not used        */
    pthread_t recv_th;    /* Receiver thread */
    pthread_t ipc_th;     /* IPC thread      */
    char *drtt;           /* DRTT            */
    int src_node;         /* Source node     */
    int dest_node;        /* Destination node*/
    char *sender_inf;     /* Send interface  */
    char *recv_inf;     /* Send interface  */
};

extern struct globals globals;
