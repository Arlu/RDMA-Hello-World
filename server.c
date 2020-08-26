/*
 * Server
 *
 * Author: Arie
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <infiniband/verbs.h>

#include "config.h"
#include "setup_ib.h"
#include "helper.h"

void chat()
{
    struct RemoteMR remote_mr;

    // Get Hello World via send and receive request:
    post_recv(BUFFER_SIZE);
    wait_completions(RECV_WRID);

    printf(ib_res.buf);

    // Get remote address and rkey:
    post_recv(sizeof(struct RemoteMR));
    wait_completions(RECV_WRID);
    memcpy(&remote_mr, ib_res.buf, sizeof(struct RemoteMR));

    // Get Hello World via RDMA Read:
    post_recv(1); // Wait to the client for read ready:
    wait_completions(RECV_WRID);
    post_send_read(remote_mr, BUFFER_SIZE);
    wait_completions(READ_WRID);

    printf(ib_res.buf);

    // Send remote address and rkey:
    remote_mr.remote_addr = (uint64_t)ib_res.buf;
    remote_mr.rkey = ib_res.mr->rkey;
    memcpy(ib_res.buf, &remote_mr, sizeof(struct RemoteMR));
    post_send(sizeof(struct RemoteMR));
    wait_completions(SEND_WRID);

    // Wait to the client for Send Hello World via RDMA Write:
    post_recv(1);
    wait_completions(RECV_WRID);

    printf(ib_res.buf);
}

int main(int argc, char *argv[])
{
    server_name = NULL;

    if (setup_ib())
    {
        perror("Failed to setup IB.");
    }

    chat();

    close_ib_connection();

    return 0;
}