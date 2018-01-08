#include <pthread.h>
#include <stdio.h>
#include "./include/mysemaphore.h"
#include <stdlib.h>
#include <unistd.h>

#define N 100
#define M 1000

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

sem_t critsec;
volatile int *data[M];
volatile int *data_cpy[M];


void *test_func(void *d)
{
    (void)d;
    while(1)
    {
        sem_wait(&critsec);
        volatile int x = 0;
        for(unsigned i = 0; i < M ; ++i)
        {
            x += *(data[i]);
            data_cpy[i] = data[i];
            data[i] = NULL;
        }
        for(unsigned i = 0; i < M; ++i)
            data[i] = data_cpy[i];
        sem_post(&critsec);    
        int msec = (int)rand()%500 + 200;
        usleep(msec*1000);
    }

    return NULL;
}

int main()
{
    srand(time(NULL));

    sem_init(&critsec, 1);

    pthread_t pthr[N];

    for(int i = 0; i < M; ++i)
        data[i] = malloc(sizeof(int));

    for(int i = 0; i < N; ++i)
        if(pthread_create(&pthr[i], NULL, test_func, NULL) != 0)
            handle_error("pthread_create");

    for(int i = 0; i < N; ++i)
        if(pthread_join(pthr[i], NULL) != 0)
            handle_error("pthread_join");

    return 0;
}