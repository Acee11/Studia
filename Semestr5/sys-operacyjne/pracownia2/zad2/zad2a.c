#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "./include/mysemaphore.h"

#define think() usleep(1000*((int)rand()%500 + 300))
#define eat() usleep(1000*((int)rand()%500 + 300))

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define NUM_PHIL 5
#define PRINT_TO_STDOUT 0

sem_t forks[NUM_PHIL];
pthread_t phil[NUM_PHIL];

unsigned deadlock_check;
bool terminate = false;

void sigint_handler(int signum)
{
    (void)signum;
    terminate = true;
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
        #if PRINT_TO_STDOUT
        printf("Philosopher %d finished eating\n", i);
        #endif
        put_forks(i);

        ++deadlock_check;
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

    // aktywne czekanie uzyte jest celowo by wykryc deadlocka
    while(!terminate)
    {
        unsigned old_dl_check = deadlock_check;
        sleep(2);
        if (deadlock_check == old_dl_check)
        {
            fprintf(stderr, "Possible deadlock");
            break;
        }
    }

    for(int i = 0; i < NUM_PHIL; ++i)
        if(pthread_cancel(phil[i]) != 0)
            handle_error("pthread_cancel");
    
    for(int i = 0; i < NUM_PHIL; ++i)
        pthread_join(phil[i], NULL);

    return 0;
}