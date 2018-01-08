#pragma once

#include <pthread.h>
#include <stdbool.h>
#include "./mylist.h"

#define handle_error(msg) do { perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct
{
    list_t *list;
    pthread_mutex_t critsec;
    pthread_mutex_t write_mutex;
    pthread_cond_t no_writer;
    pthread_cond_t can_remove;
    int readers, waiting_writers;
    bool writing;
} sync_list_t;

void rd_lock(sync_list_t *sc_list);
void rd_unlock(sync_list_t *sc_list);
void wr_lock(sync_list_t *sc_list);
void wr_unlock(sync_list_t *sc_list);
void sync_list_init(sync_list_t *sc_list);
bool sync_list_search(sync_list_t *sc_list, int value);
void sync_list_append(sync_list_t *sc_list, int value);
void sync_list_remove(sync_list_t *sc_list, int value);