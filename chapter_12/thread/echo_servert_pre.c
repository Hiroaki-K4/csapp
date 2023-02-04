#include "csapp.h"
#include "sbuf.h"
#define NTHREADS 4
#define SBUFSIZE 16

void *thread(void *vargp)
{
    pthread_detach(pthread_self()); // Detach self thread from parent thread
    while (1) {
        int connfd = sbuf_remove(&sbuf); // Remove connfd from buffer
        echo_cnt(connfd);
        close(connfd);
    }
}

// void echo_cnt(int connfd)
// {
//     int n;
//     char buf[MAXLINE];
//     rio_t rio;
//     static pthread_once_t once = PTHREAD_ONCE_INIT;

//     pthread_once()
// }

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

    // sbuf_init(&sbuf, SBUFSIZE);
    // for (i = 0; i < NTHREADS; i++)
    //     pthread_create(&tid, NULL, thread, NULL);

    // while (1) {
    //     clientlen = sizeof(struct sockaddr_storage);
    //     connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
    //     sbuf_insert(&sbuf, connfd);
    // }
}
