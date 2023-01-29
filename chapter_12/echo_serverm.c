#include "csapp.h"

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }

    listenfd = open_listenfd(argv[1]);

    FD_ZERO(&read_set);

    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = accept(listenfd, (SA *) &clientaddr, &clientlen);
        if (fork() == 0) {
            close(listenfd);
            echo(connfd);
            close(connfd);
            exit(0);
        }
        close(connfd);
    }

    return 0;
}
