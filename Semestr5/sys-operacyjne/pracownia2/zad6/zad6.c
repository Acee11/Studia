#include <pthread.h>
#include <stdio.h>
#include <mysemaphore.h>
#include <stdlib.h>
#include <unistd.h>

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
        {
            items = 0;
            sem_post(&matches_wakeup);
        }
        else if(items & MATCHES)
        {
            items = 0;
            sem_post(&paper_wakeup);
        }

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
        {
            items = 0;
            sem_post(&matches_wakeup);
        }
        else if(items & MATCHES)
        {
            items = 0;
            sem_post(&tobacco_wakeup);
        }

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
        {
            items = 0;
            sem_post(&paper_wakeup);
        }
        else if(items & PAPER)
        {
            items = 0;
            sem_post(&tobacco_wakeup);
        }
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
            sem_wait(&matches_wakeup);
        else if(item_owned == TOBACCO)
            sem_wait(&tobacco_wakeup);
        else
            sem_wait(&paper_wakeup);

        smoke();
        printf("smoker %d finished smoking\n", item_owned);
        sem_post(&smoke);
    }

    return NULL;
}

int main(void)
{
    // TODO obsluga bledow
    srand(1337);

    sem_init(&smoke, 1);
    sem_init(&tobacco, 0);
    sem_init(&paper, 0);
    sem_init(&matches, 0);

    sem_init(&watcher_critsec, 1);

    pthread_create(&agent_thread, NULL, agent, NULL);
    pthread_create(&tobacco_watcher_thread, NULL, tobacco_watcher, NULL);
    pthread_create(&paper_watcher_thread, NULL, paper_watcher, NULL);
    pthread_create(&matches_watcher_thread, NULL, matches_watcher, NULL);
    int data[3];
    for(int i = 0; i < 3; ++i)
    {
        data[i] = (1 << i);
        pthread_create(&smoker_thread[i], NULL, smoker, &data[i]);
    }

    pthread_join(agent_thread, NULL);
    pthread_join(tobacco_watcher_thread, NULL);
    pthread_join(paper_watcher_thread, NULL);
    pthread_join(matches_watcher_thread, NULL);
    for(int i = 0; i < 3; ++i)
        pthread_join(smoker_thread[i], NULL);

    return 0;
}