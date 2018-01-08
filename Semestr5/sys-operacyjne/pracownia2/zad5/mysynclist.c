#include "./include/mysynclist.h"

void rd_lock(sync_list_t *sc_list)
{
    if(pthread_mutex_lock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_lock");

    while(sc_list->writing)
        if(pthread_cond_wait(&sc_list->no_writer, &sc_list->critsec) != 0)
            handle_error("pthread_cond_wait");
    ++sc_list->readers;

    if (pthread_mutex_unlock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_unlock");
}

void rd_unlock(sync_list_t *sc_list)
{
    if (pthread_mutex_lock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_lock");

    --sc_list->readers;
    if (sc_list->readers == 0)
        if (pthread_cond_signal(&sc_list->can_remove) != 0)
            handle_error("pthread_cond_signal");

    if (pthread_mutex_unlock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_unlock");
}

void append_lock(sync_list_t *sc_list)
{
    if (pthread_mutex_lock(&sc_list->write_mutex) != 0)
        handle_error("pthread_mutex_lock");
}

void append_unlock(sync_list_t *sc_list)
{
    if (pthread_mutex_unlock(&sc_list->write_mutex) != 0)
        handle_error("pthread_mutex_unlock");
}

void wr_lock(sync_list_t *sc_list)
{
    if (pthread_mutex_lock(&sc_list->write_mutex) != 0)
        handle_error("pthread_mutex_lock");
    if (pthread_mutex_lock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_lock");

    while (sc_list->readers > 0 || sc_list->writing)
    {
        ++sc_list->waiting_writers;
        if (pthread_cond_wait(&sc_list->can_remove, &sc_list->critsec) != 0)
            handle_error("pthread_cond_wait");
        --sc_list->waiting_writers;
    }
    sc_list->writing = true;

    if (pthread_mutex_unlock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_unlock");
}

void wr_unlock(sync_list_t *sc_list)
{
    if (pthread_mutex_lock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_lock");

    sc_list->writing = false;
    if(sc_list->waiting_writers)
    {
        if (pthread_cond_signal(&sc_list->can_remove) != 0)
            handle_error("pthread_cond_signal");
    }
    else
    {
    if (pthread_cond_broadcast(&sc_list->no_writer) != 0)
        handle_error("pthread_cond_broadcast");
    }

    if (pthread_mutex_unlock(&sc_list->write_mutex) != 0)
        handle_error("pthread_mutex_unlock");
    if (pthread_mutex_unlock(&sc_list->critsec) != 0)
        handle_error("pthread_mutex_unlock");
}

void sync_list_init(sync_list_t *sc_list)
{
    sc_list->list = malloc(sizeof(list_t));
    list_init(sc_list->list);
    sc_list->readers = 0;
    sc_list->waiting_writers = 0;
    sc_list->writing = false;

    pthread_mutexattr_t attr;
    if (pthread_mutexattr_init(&attr) != 0)
        handle_error("pthread_mutexattr_init");
    if (pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK) != 0)
        handle_error("pthread_mutexattr_settype");

    if (pthread_mutex_init(&sc_list->critsec, &attr) != 0)
        handle_error("pthread_mutex_init");
    if (pthread_mutex_init(&sc_list->write_mutex, &attr) != 0)
        handle_error("pthread_mutex_init");
    if (pthread_cond_init(&sc_list->no_writer, NULL) != 0)
        handle_error("pthread_cond_init");
    if (pthread_cond_init(&sc_list->can_remove, NULL) != 0)
        handle_error("pthread_cond_init");
}

bool sync_list_search(sync_list_t *sc_list, int value)
{
    rd_lock(sc_list);
    assert(!sc_list->writing);
    bool ret_val = list_search(sc_list->list, value);
    rd_unlock(sc_list);
    return ret_val;
}

void sync_list_append(sync_list_t *sc_list, int value)
{
    append_lock(sc_list);
    assert(!sc_list->writing);
    list_append(sc_list->list, value);
    append_unlock(sc_list);
}

void sync_list_remove(sync_list_t *sc_list, int value)
{
    wr_lock(sc_list);
    assert(!sc_list->readers);
    list_remove(sc_list->list, value);
    wr_unlock(sc_list);
}