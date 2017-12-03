#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#include "./include/mylist.h"

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define N 10000
#define NUM_THREADS 100
#define LIST_TEST 0
#define PRINT_TO_STDOUT 0

typedef struct
{
    list_t *list;
    int readers;
    bool writing;
    pthread_mutex_t critsec;
    pthread_cond_t no_readers;
    pthread_cond_t no_writer;
} sync_list_t;

void rd_lock(sync_list_t *sc_list)
{
    if(pthread_mutex_lock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_lock");

    while(sc_list->writing)
        pthread_cond_wait(&sc_list->no_writer, &sc_list->critsec);
    ++sc_list->readers;

    if(pthread_mutex_unlock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_unlock");
}

void rd_unlock(sync_list_t *sc_list)
{
    if(pthread_mutex_lock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_lock");

    --sc_list->readers;
    if(sc_list->readers == 0)
        if(pthread_cond_signal(&sc_list->no_readers) != 0)
            handle_error("pthread_cond_signal");

    if(pthread_mutex_unlock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_unlock");
}

void wr_lock(sync_list_t *sc_list)
{
    if(pthread_mutex_lock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_lock");

    while(sc_list->readers > 0 || sc_list->writing)
    {
        if(sc_list->readers > 0)
            if(pthread_cond_wait(&sc_list->no_readers, &sc_list->critsec) != 0)
                handle_error("pthread_cond_wait");
        if(sc_list->writing)
            if(pthread_cond_wait(&sc_list->no_writer, &sc_list->critsec) != 0)
                handle_error("pthread_cond_wait");
    }
    sc_list->writing = true;

    if(pthread_mutex_unlock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_unlock");
}

void wr_unlock(sync_list_t *sc_list)
{
    if(pthread_mutex_lock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_lock");

    sc_list->writing = false;
    if(pthread_cond_broadcast(&sc_list->no_writer) != 0)
        handle_error("pthread_cond_broadcast");

    if(pthread_mutex_unlock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_unlock");
}

void sync_list_init(sync_list_t *sc_list)
{
    sc_list->list = malloc(sizeof(list_t));
    list_init(sc_list->list);
    sc_list->readers = 0;
    sc_list->writing = false;

    pthread_mutexattr_t attr;
    if(pthread_mutexattr_init(&attr) != 0)
        handle_error("pthread_mutexattr_init");
    if(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK) != 0)
        handle_error("pthread_mutexattr_settype");

    if(pthread_mutex_init(&sc_list->critsec, &attr) != 0)
        handle_error("pthread_mutex_init");

    if(pthread_cond_init(&sc_list->no_readers, NULL) != 0)
        handle_error("pthread_cond_init");
    if(pthread_cond_init(&sc_list->no_writer, NULL) != 0)
        handle_error("pthread_cond_init");
}

bool sync_list_search(sync_list_t *sc_list, int value)
{
    rd_lock(sc_list);
    bool ret_val = list_search(sc_list->list, value);
    rd_unlock(sc_list);
    return ret_val;
}

void sync_list_append(sync_list_t *sc_list, int value)
{
    wr_lock(sc_list);
    list_append(sc_list->list, value);
    wr_unlock(sc_list);
}

void sync_list_remove(sync_list_t *sc_list, int value)
{
    wr_lock(sc_list);
    list_remove(sc_list->list, value);
    wr_unlock(sc_list);
}

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
        puts("reading...");
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
        #if PRINT_TO_STDOUT
        puts("writing...");
        #endif
        if(rand()%3 == 0)
            sync_list_append(&mylist, rand()%N);
        else
            sync_list_remove(&mylist, rand()%N);
    }

    return NULL;
}

#endif

int main(void)
{
    #if LIST_TEST
    list_append(&mylist, 1);
    list_print(&mylist);
    list_append(&mylist, 2);
    list_print(&mylist);
    list_append(&mylist, 3);
    list_print(&mylist);
    list_append(&mylist, 4);
    list_print(&mylist);

    list_remove(&mylist, 100);
    list_print(&mylist);
    list_remove(&mylist, 4);
    list_print(&mylist);
    list_remove(&mylist, 1);
    list_print(&mylist);
    list_remove(&mylist, 2);
    list_print(&mylist);
    list_remove(&mylist, 3);
    list_print(&mylist);
    #else

    // srand(1337);
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