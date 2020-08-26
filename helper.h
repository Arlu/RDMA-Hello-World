/*
 * Helper functions.
 *
 * Author: Arie
 */

#ifndef HELPER_H
#define HELPER_H

struct RemoteMR {
    uint64_t remote_addr;
    uint32_t rkey;
};

int post_recv(int size);
int post_send(int size);
int post_send_read(struct RemoteMR remote_mr, int size);
int post_send_write(struct RemoteMR remote_mr, int size);
int wait_completions(int wr_id);

#endif //HELPER_H
