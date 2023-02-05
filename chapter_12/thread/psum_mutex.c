#include "csapp.h"
#include <time.h>
#define MAXTHREAD 32

long gsum = 0;
long *psum;
long nelems_per_thread;
sem_t mutex; // Mutex to protect global sum

void *sum_mutex(void *vargp)
{
    long myid = *((long *)vargp);
    long start = myid * nelems_per_thread;
    long end = start + nelems_per_thread;
    long i;

    for (i = start; i < end; i++) {
        sem_wait(&mutex);
        gsum += i;
        sem_post(&mutex);
    }
    return NULL;
}

void *sum_array(void *vargp)
{
    long myid = *((long *)vargp);
    long start = myid * nelems_per_thread;
    long end = start + nelems_per_thread;
    long i;

    psum[myid] = 0;
    for (i = start; i < end; i++) {
        psum[myid] += i;
    }
    return NULL;
}

void *sum_local(void *vargp)
{
    long myid = *((long *)vargp);
    long start = myid * nelems_per_thread;
    long end = start + nelems_per_thread;
    long i, sum = 0;;

    for (i = start; i < end; i++) {
        sum += i;
    }
    psum[myid] = sum;
    return NULL;
}

int main(int argc, char *argv[])
{
    long i, nelems, log_nelems, nthreads, myid[MAXTHREAD];
    pthread_t tid[MAXTHREAD];

    if (argc != 3) {
        printf("Usage: %s <nthreads> <log_nelems>\n", argv[0]);
        return 1;
    }

    nthreads = atoi(argv[1]);
    log_nelems = atoi(argv[2]);
    nelems = (1L << log_nelems);
    nelems_per_thread = nelems / nthreads;
    sem_init(&mutex, 0, 1);

    {
        // Very slow: High synchronization overhead.
        clock_t start;
        start = clock();
        // Create peer threads and wait for them to finish
        for (i = 0; i < nthreads; i++) {
            myid[i] = i;
            pthread_create(&tid[i], NULL, sum_mutex, &myid[i]);
        }
        for (i = 0; i < nthreads; i++) {
            pthread_join(tid[i], NULL);
        }

        if (gsum != (nelems * (nelems - 1)) / 2)
            printf("Error: result=%ld\n", gsum);
        else
            printf("OK: result=%ld time: %fseconds\n", gsum, ((double)(clock() - start)) / CLOCKS_PER_SEC);
    }

    {
        // Fast: less synchronization overhead.
        clock_t start;
        start = clock();
        psum = (long *)malloc(sizeof(long) * nthreads);
        for (i = 0; i < nthreads; i++) {
            myid[i] = i;
            pthread_create(&tid[i], NULL, sum_array, &myid[i]);
        }
        for (i = 0; i < nthreads; i++) {
            pthread_join(tid[i], NULL);
        }
        long ans = 0;
        for (i = 0; i < nthreads; i++) {
            ans += psum[i];
        }
        if (ans != (nelems * (nelems - 1)) / 2)
            printf("Error: result=%ld\n", ans);
        else
            printf("OK: result=%ld time: %fseconds\n", ans, ((double)(clock() - start)) / CLOCKS_PER_SEC);
    }

    {
        // Very Fast: less synchronization overhead and use local variable.
        clock_t start;
        start = clock();
        psum = (long *)malloc(sizeof(long) * nthreads);
        for (i = 0; i < nthreads; i++) {
            myid[i] = i;
            pthread_create(&tid[i], NULL, sum_local, &myid[i]);
        }
        for (i = 0; i < nthreads; i++) {
            pthread_join(tid[i], NULL);
        }
        long ans = 0;
        for (i = 0; i < nthreads; i++) {
            ans += psum[i];
        }
        if (ans != (nelems * (nelems - 1)) / 2)
            printf("Error: result=%ld\n", ans);
        else
            printf("OK: result=%ld time: %fseconds\n", ans, ((double)(clock() - start)) / CLOCKS_PER_SEC);
    }

    return 0;
}
