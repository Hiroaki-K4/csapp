#include "csapp.h"

typedef struct { // represents a pool of connected descriptors
    int maxfd; // Largest descripriptor in read_set
    fd_set read_set; // Set of all active descriptors
    fd_set ready_set; // Subset of descriptors ready for reading
    int nready; // Number of ready descriptors from select
    int maxi; // Highwater index into client array
    int clientfd[FD_SETSIZE]; // Set of active descriptors
    rio_t clientrio[FD_SETSIZE]; // Set of active read buffers
} pool;

void init_pool(int listenfd, pool *p)
{
    // Initially, there are no connected descriptors
    int i;
    p->maxi = -1;
    for (i = 0; i < FD_SETSIZE; i++)
        p->clientfd[i] = -1;
    
    // Initially, listenfd is only member of select read set
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool *p)
{
    int i;
    p->nready--;
    for (i = 0; i < FD_SETSIZE; i++) { // Find an available slot
        if (p->clientfd[i] < 0) {
            // Add connected descriptor to the pool
            p->clientfd[i] = connfd;
            rio_readinitb(&p->clientrio[i], connfd);

            // Add the descriptor to descriptor set
            FD_SET(connfd, &p->read_set);

            // Update max descriptor and pool highwater mark
            if (connfd > p->maxfd)
                p->maxfd = connfd;
            if (i > p->maxi)
                p->maxi = i;
            break;
        }
    }
    if (i == FD_SETSIZE) // Couldn't find an empty slot
        printf("add_client error: Too many clients\n");
}

int byte_cnt = 0; // Counts total bytes received by server

void check_clients(pool *p)
{
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for (i = 0; (i <= p->maxi) && (p->nready > 0); i++) {
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        // If the descriptor is ready, echo a text line from it
        if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set))) {
            p->nready--;
            if ((n = rio_readlineb(&rio, buf, MAXLINE, true)) != 0) {
                byte_cnt += n;
                printf("Server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
                rio_writen(connfd, buf, n);
            }
            else { // EOF detected, remove descriptor from pool
                close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    listenfd = open_listenfd(argv[1]);
    init_pool(listenfd, &pool);

    while (1) {
        // Wait for listening/connected descriptors to become ready
        pool.ready_set = pool.read_set;
        printf("before select\n");
        pool.nready = select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);
        printf("nready: %d\n", pool.nready);

        // If listening descriptor ready, add new client to pool
        if (FD_ISSET(listenfd, &pool.ready_set)) {
            clientlen = sizeof(struct sockaddr_storage);
            connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
            printf("connfd: %d\n", connfd);
            add_client(connfd, &pool);
            printf("add_client finish\n");
        }

        // Echo a text line from each ready connected descriptor
        check_clients(&pool);
        printf("check_clients finish\n");
    }

    return 0;
}
