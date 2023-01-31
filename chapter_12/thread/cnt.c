// Warning: This code is buggy example.
#include "csapp.h"

volatile long cnt = 0;
sem_t mutex;

void *thread(void *vargp)
{
    long i, niters = *((long *)vargp);
    for (i = 0; i < niters; i++) {
        sem_wait(&mutex);
        cnt++;
        sem_post(&mutex);
    }
    return NULL;
}

int main(int argc, char **argv)
{
    long niters;
    pthread_t tid1, tid2;

    if (argc != 2) {
        printf("usage: %s <niters>\n", argv[0]);
        return 1;
    }
    niters = atoi(argv[1]);
    sem_init(&mutex, 0, 1);

    pthread_create(&tid1, NULL, thread, &niters);
    pthread_create(&tid2, NULL, thread, &niters);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    if (cnt != (2 * niters))
        printf("Boom! cnt=%ld\n", cnt);
    else
        printf("OK cnt=%ld\n", cnt);
    return 0;
}
