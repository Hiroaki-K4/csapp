#include "csapp.h"

void echo(int connfd)
{
    ssize_t n;
    char buf[MAXLINE];
    rio_t rio;

    rio_readinitb(&rio, connfd);
    while ((n = rio_readlineb(&rio, buf, MAXLINE, true)) != 0) {
        if (n == -1) {
            fprintf(stderr, "rio_readlineb error");
        }
        printf("Server received %d bytes\n", (int)n);
        printf("Received message: %s\n", buf);
    }
}

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return (1);
    }
    listenfd = open_listenfd(argv[1]);
    printf("listenfd: %d\n", listenfd);
    if (listenfd == -1) {
        fprintf(stderr, "open_listenfd error\n");
        return (1);
    }
    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
        getnameinfo((SA *)&clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        echo(connfd);
        close(connfd);
    }
    return (0);
}
