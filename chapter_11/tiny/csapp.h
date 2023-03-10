#ifndef CSAPP_H
# define CSAPP_H

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXLINE 8192
#define MAXBUF 8192
#define RIO_BUFSIZE 8192
#define LISTENQ  1024  // Second argument to listen(). Maximum queue length of pending connections for sockfd.

// Simplifies calls to bind(), connect(), and accept()
typedef struct sockaddr SA;

// Persistent state for the robust I/O (rio) package
typedef struct {
    int rio_fd;                 // Descriptor for this internal buf
    int rio_cnt;                // Unread bytes in internal buf
    char *rio_bufptr;           // Next unread byte in internal buf
    char rio_buf[RIO_BUFSIZE];  // Internal buffer
} rio_t;

extern char **environ;

void rio_readinitb(rio_t *rp, int fd);
ssize_t rio_writen(int fd, void *usrbuf, size_t n);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen, bool ignore_new_line);
int open_clientfd(char *hostname, char *port);
int open_listenfd(char *port);
void echo(int connfd);

#endif
