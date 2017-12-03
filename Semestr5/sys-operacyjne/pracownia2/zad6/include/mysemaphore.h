#pragma once

#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct
{
    pthread_mutex_t critsec;
    pthread_cond_t gt_zero;
    int count;
    int wakeups;

} sem_t;

void sem_init(sem_t *sem, unsigned value);
void sem_wait(sem_t *sem);
void sem_post(sem_t *sem);
void sem_getvalue(sem_t *sem, int *sval);