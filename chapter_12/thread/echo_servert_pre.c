#include "csapp.h"
#include "sbuf.h"
#define NTHREADS 4
#define SBUFSIZE 16

sbuf_t sbuf; // Shared buffer of connected descriptors
static int byte_cnt; // Byte counter
static sem_t mutex;

static void init_echo_cnt(void)
{
    sem_init(&mutex, 0, 1);
    byte_cnt = 0;
}

void echo_cnt(int connfd)
{
    int n;
    char buf[MAXLINE];
    rio_t rio;
    static pthread_once_t once = PTHREAD_ONCE_INIT;

    pthread_once(&once, init_echo_cnt);
    rio_readinitb(&rio, connfd);
    while ((n = rio_readlineb(&rio, buf, MAXLINE, true)) != 0) {
        sem_wait(&mutex);
        byte_cnt += n;
        printf("server received %d (%d total) bytes on fd %d\n", n, byte_cnt, connfd);
        sem_post(&mutex);
        rio_writen(connfd, buf, n);
    }
}

void *thread(void *vargp)
{
    pthread_detach(pthread_self()); // Detach self thread from parent thread
    while (1) {
        int connfd = sbuf_remove(&sbuf); // Remove connfd from buffer
        echo_cnt(connfd);
        close(connfd);
    }
}

int main(int argc, char *argv[])
{
    int i, listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        return 1;
    }
    listenfd = open_listenfd(argv[1]);

    sbuf_init(&sbuf, SBUFSIZE);
    for (i = 0; i < NTHREADS; i++)
        pthread_create(&tid, NULL, thread, NULL);

    while (1) {
        clientlen = sizeof(struct sockaddr_storage);
        connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
        sbuf_insert(&sbuf, connfd);
    }
}
