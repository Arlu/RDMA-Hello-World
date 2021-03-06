/*
 * Setup InfiniBand.
 *
 * Author: Arie
 */

#ifndef SETUP_IB_H
#define SETUP_IB_H

#include <infiniband/verbs.h>

struct IBRes {
    struct ibv_context *ctx;
    struct ibv_pd *pd;
    struct ibv_mr *mr;
    struct ibv_cq *cq;
    struct ibv_qp *qp;
    struct ibv_port_attr port_info;

    void *buf;
    size_t size;
};

struct IBDest {
    int lid;
    int qpn;
    int psn;
};

extern struct IBRes ib_res;
extern char *server_name;

extern struct IBDest local_dest;
extern struct IBDest remote_dest;

int setup_ib();
void close_ib_connection();

#endif //SETUP_IB_H
