#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "./include/mylist.h"
#include "./include/mysynclist.h"

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define N 2000
#define NUM_THREADS 35
#define LIST_TEST 0
#define PRINT_TO_STDOUT 0

#if LIST_TEST
list_t mylist;
#else
sync_list_t mylist;


void *reader(void *data)
{
    (void)data;
    #if PRINT_TO_STDOUT
    puts("reader joined");
    #endif
    while(1)
    {
        usleep(rand()%500);
        #if PRINT_TO_STDOUT
        puts("searching...");
        #endif
        sync_list_search(&mylist, rand() % N);
    }

    return NULL;
}

void *writer(void *data)
{
    (void)data;
    #if PRINT_TO_STDOUT
    puts("writer joined");
    #endif
    while(1)
    {
        usleep(rand()%1000);
        
        if(rand()%3 == 0)
        {
            #if PRINT_TO_STDOUT
            puts("appending...");
            #endif
            sync_list_append(&mylist, rand()%N);
        }
        else
        {
            #if PRINT_TO_STDOUT
            puts("removing...");
            #endif
            sync_list_remove(&mylist, rand()%N);
        }
    }

    return NULL;
}

#endif

int main(void)
{
    #if LIST_TEST
    list_init(&mylist);
    while(1)
    {
        int x = rand()%3;
        int n = rand() % N;
        if(x == 0)
            list_append(&mylist, n);
        else if(x == 1)
            list_remove(&mylist, n);
        else
            list_search(&mylist, n);
    }
    #else

    srand(time(NULL));

    sync_list_init(&mylist);
    pthread_t pthr[N];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        if(rand()%3)
        {
            if(pthread_create(&pthr[i], NULL, reader, NULL) != 0)
                handle_error("pthread_create");
        }
        else
        {
            if(pthread_create(&pthr[i], NULL, writer, NULL) != 0)
                handle_error("pthread_create");
        }
    }


    for(int i = 0; i < NUM_THREADS; ++i)
        if(pthread_join(pthr[i], NULL) != 0)
            handle_error("pthread_join");

    #endif
    return 0;
}