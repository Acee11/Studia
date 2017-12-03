#include <stdio.h>
#include <pthread.h>
#include <mysemaphore.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#define think() usleep(1000*((int)rand()%500 + 300))
#define eat() usleep(1000*((int)rand()%500 + 300))

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define NUM_PHIL 5

sem_t forks[NUM_PHIL];
pthread_t phil[NUM_PHIL];

void sigint_handler(int signum)
{
    (void)signum;
    for(int i = 0; i < NUM_PHIL; ++i)
        if(pthread_cancel(phil[i]) != 0)
            handle_error("pthread_cancel");
}

void take_forks(int i)
{
    if(i%2)
    {
        sem_wait(&forks[i]);
        sem_wait(&forks[(i+1)%NUM_PHIL]);
    }
    else
    {
        sem_wait(&forks[(i+1)%NUM_PHIL]);
        sem_wait(&forks[i]);
    }
}

void put_forks(int i)
{
    if(i%2)
    {
        sem_post(&forks[(i+1)%NUM_PHIL]);
        sem_post(&forks[i]);
    }
    else
    {
        sem_post(&forks[i]);        
        sem_post(&forks[(i+1)%NUM_PHIL]);
    }
}

void *philosopher(void *data)
{
    int i = *(int*)data;
    while(1)
    {
        think();
        take_forks(i);
        eat();
        printf("Philosopher %d finished eating\n", i);
        put_forks(i);
    }
}

int main()
{
    struct sigaction new_action;
    memset(&new_action, 0, sizeof(struct sigaction));
    if(sigemptyset(&new_action.sa_mask) == -1)
        handle_error("sigemptyset");
    new_action.sa_handler = sigint_handler;

    if(sigaction(SIGINT, &new_action, NULL) == -1)
        handle_error("sigaction");

    int data[NUM_PHIL];
    for(int i = 0; i < NUM_PHIL; ++i)
        sem_init(&forks[i], 1);
    for(int i = 0; i < NUM_PHIL; ++i)
    {
        data[i] = i;
        if(pthread_create(&phil[i], NULL, philosopher, &data[i]) != 0)
            handle_error("pthread_create");
    }

    for(int i = 0; i < NUM_PHIL; ++i)
        pthread_join(phil[i], NULL);

    return 0;
}