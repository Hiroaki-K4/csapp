#ifndef CSAPP_H
# define CSAPP_H

#include <stddef.h>
#include <unistd.h>

#define MAXLINE 8192
#define RIO_BUFSIZE 8192

// Persistent state for the robust I/O (rio) package
typedef struct {
    int rio_fd;
    int rio_cnt;
    char *rio_bufptr;
    char rio_buf[RIO_BUFSIZE];
} rio_t;

int open_clientfd(char *hostname, char *port);
int open_listenfd(char *port);

#endif
