#pragma once

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>

#define UNLINK 1

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

typedef struct
{
    int n;
    int *waiting;
    sem_t *outer_lock;
    sem_t *inner_lock;
    sem_t *critsec;
} barrier_t;

int bar_init(barrier_t *barrier, int id, int n);
void bar_wait(barrier_t *barrier);
void bar_destroy(barrier_t *barrier, int id);
