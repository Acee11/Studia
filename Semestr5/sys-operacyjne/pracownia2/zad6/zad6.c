#include <pthread.h>
#include <stdio.h>
#include "./include/mysemaphore.h"
#include <stdlib.h>
#include <unistd.h>

#define PRINT_TO_STDOUT 0

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE);} while (0)

#define smoke() usleep(1000*((int)rand()%500 + 300))

#define TOBACCO 1
#define MATCHES 2
#define PAPER 4   

pthread_t agent_thread;
pthread_t tobacco_watcher_thread, paper_watcher_thread, matches_watcher_thread;
pthread_t smoker_thread[3];

sem_t smoke, tobacco, paper, matches;
sem_t watcher_critsec;
sem_t tobacco_wakeup, paper_wakeup, matches_wakeup;

int items;

void *agent(void *data)
{
    (void)data;
    while(1)
    {
        sem_wait(&smoke);
        int x = rand()%3;
        if(x == 0)
        {
            sem_post(&tobacco);
            sem_post(&paper);
        }

        if(x == 1)
        {
            sem_post(&tobacco);
            sem_post(&matches);
        }

        if(x == 2)
        {
            sem_post(&paper);
            sem_post(&matches);
        }
    }
}

void *tobacco_watcher(void *data)
{
    (void)data;
    while(1)
    {
        sem_wait(&tobacco);

        sem_wait(&watcher_critsec);

        items |= TOBACCO;
        if(items & PAPER)
            sem_post(&matches_wakeup);
        else if(items & MATCHES)
            sem_post(&paper_wakeup);

        sem_post(&watcher_critsec);
    }

    return NULL;
}

void *paper_watcher(void *data)
{
    (void)data;
    while(1)
    {
        sem_wait(&paper);
        
        sem_wait(&watcher_critsec);

        items |= PAPER;
        if(items & TOBACCO)
            sem_post(&matches_wakeup);
        else if(items & MATCHES)
            sem_post(&tobacco_wakeup);

        sem_post(&watcher_critsec);

    }
    return NULL;
}

void *matches_watcher(void *data)
{
    (void)data;
    while(1)
    {
        sem_wait(&matches);
        sem_wait(&watcher_critsec);

        items |= MATCHES;
        if(items & TOBACCO)
            sem_post(&paper_wakeup);
        else if(items & PAPER)
            sem_post(&tobacco_wakeup);
        sem_post(&watcher_critsec);
    }

    return NULL;
}

void *smoker(void *data)
{
    int item_owned = *((int*)data);
    while(1)
    {
        if(item_owned == MATCHES)
        {
            sem_wait(&matches_wakeup);
            assert(
                (items & TOBACCO)
                && (items & PAPER)
                && !(items & MATCHES)
            );
        }
        else if(item_owned == TOBACCO)
        {
            sem_wait(&tobacco_wakeup);
            assert(
                !(items & TOBACCO) 
                && (items & PAPER) 
                && (items & MATCHES)
            );
        }
        else
        {
            sem_wait(&paper_wakeup);
            assert(
                (items & TOBACCO) 
                && !(items & PAPER) 
                && (items & MATCHES)
            );
        }

        items = 0;
        smoke();
        #if PRINT_TO_STDOUT
        printf("smoker %d finished smoking\n", item_owned);
        #endif
        sem_post(&smoke);
    }

    return NULL;
}

int main(void)
{
    srand(1337);

    sem_init(&smoke, 1);
    sem_init(&tobacco, 0);
    sem_init(&paper, 0);
    sem_init(&matches, 0);

    sem_init(&watcher_critsec, 1);

    if(pthread_create(&agent_thread, NULL, agent, NULL) != 0)
        handle_error("pthread_create");
    if(pthread_create(&tobacco_watcher_thread, NULL, tobacco_watcher, NULL) != 0)
        handle_error("pthread_create");
    if(pthread_create(&paper_watcher_thread, NULL, paper_watcher, NULL) != 0)
        handle_error("pthread_create");
    if(pthread_create(&matches_watcher_thread, NULL, matches_watcher, NULL) != 0)
        handle_error("pthread_create");
    int data[3];
    for(int i = 0; i < 3; ++i)
    {
        data[i] = (1 << i);
        if(pthread_create(&smoker_thread[i], NULL, smoker, &data[i]) != 0)
            handle_error("pthread_create");
    }

    if(pthread_join(agent_thread, NULL) != 0)
        handle_error("pthread_join");
    if(pthread_join(tobacco_watcher_thread, NULL) != 0)
        handle_error("pthread_join");
    if(pthread_join(paper_watcher_thread, NULL) != 0)
        handle_error("pthread_join");
    if(pthread_join(matches_watcher_thread, NULL) != 0)
        handle_error("pthread_join");
    for(int i = 0; i < 3; ++i)
        if(pthread_join(smoker_thread[i], NULL) != 0)
            handle_error("pthread_join");

    return 0;
}