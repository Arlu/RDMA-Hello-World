/*
 * Configures.
 *
 * Author: Arie
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <infiniband/verbs.h>

#define PORT 8080
#define PORT_STR "8080"

#define IB_PORT 1
#define MTU IBV_MTU_4096
#define COUNT 1000
#define WC_BATCH 100
#define BUFFER_SIZE 1024

enum {
    RECV_WRID = 1,
    SEND_WRID = 2,
    READ_WRID = 4,
    WRITE_WRID = 8,
};

#endif //CONFIG_H
