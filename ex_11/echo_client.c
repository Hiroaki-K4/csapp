#include "csapp.h"

int main(int argc, char *argv[])
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        return (1);
    }
    host = argv[1];
    port = argv[2];

    clientfd = open_clientfd(host, port);
    if (clientfd == -1) {
        fprintf(stderr, "clientfd is -1\n");
        return (1);
    }
    printf("clientfd: %d\n", clientfd);
    rio_readinitb(&rio, clientfd);

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        // Write the string received in standard input to clientfd.
        if (rio_writen(clientfd, buf, strlen(buf)) == -1) {
            fprintf(stderr, "rio_writen error\n");
            return (-1);
        }
        rio_readlineb(&rio, buf, MAXLINE, false);
        fputs(buf, stdout);
    }
    close(clientfd);
    return (0);
}
