/*
 * Client
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

#define MSG_SEND_RECV "Hello World via send and receive!\n"
#define MSG_READ "Hello World via RDMA Read!\n"
#define MSG_WRITE "Hello World via RDMA Write!\n"

void chat()
{
    struct RemoteMR remote_mr = {
            .remote_addr = (uint64_t)ib_res.buf,
            .rkey = ib_res.mr->rkey
    };

    // Send Hello World via send and receive request:
    memcpy(ib_res.buf, MSG_SEND_RECV, sizeof(MSG_SEND_RECV));
    post_send(BUFFER_SIZE);
    wait_completions(SEND_WRID);

    // Send remote address and rkey:
    memcpy(ib_res.buf, &remote_mr, sizeof(struct RemoteMR));
    post_send(sizeof(struct RemoteMR));
    wait_completions(SEND_WRID);

    // Send Hello World via RDMA Read:
    memcpy(ib_res.buf, MSG_READ, sizeof(MSG_READ));
    post_send(1); // Notify the server for read.
    wait_completions(SEND_WRID);

    // Get remote address and rkey:
    post_recv(sizeof(struct RemoteMR));
    wait_completions(RECV_WRID);
    memcpy(&remote_mr, ib_res.buf, sizeof(struct RemoteMR));

    // Send Hello World via RDMA Write:
    memcpy(ib_res.buf, MSG_WRITE, sizeof(MSG_WRITE));
    post_send_write(remote_mr, BUFFER_SIZE);
    wait_completions(WRITE_WRID);

    post_send(1); // Notify the server for continue.
    wait_completions(SEND_WRID);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("It must get hostname!\n");
        exit(EXIT_FAILURE);
    }

    server_name = strdup(argv[1]);

    if (setup_ib())
    {
        perror("Failed to setup IB.");
    }

    chat();

    close_ib_connection();

    return 0;
}

