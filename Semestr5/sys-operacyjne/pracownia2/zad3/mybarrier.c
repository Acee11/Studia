#include "./include/mybarrier.h"



int bar_init(barrier_t *barrier, int id, int n, int create) 
{
    barrier->n = n;
    char name[50] = {0};

    sprintf(name, "/barrier.critsec.%d", id);
    if(create)
    {
        barrier->critsec = sem_open(
            name, 
            O_CREAT, 
            0644, 
            1
        );
    }
    else
    {
        barrier->critsec = sem_open(
            name,
            O_RDWR
        );
    }

    if (barrier->critsec == SEM_FAILED)
        handle_error("sem_open");

    sprintf(name, "/barrier.inner.%d", id);
    if(create)
    {
        barrier->inner_lock = sem_open(
            name, 
            O_CREAT, 
            0644, 
            n
        );
    }
    else
    {
        barrier->inner_lock = sem_open(
            name,
            O_RDWR
        );
    }
    if(barrier->inner_lock == SEM_FAILED)
        handle_error("sem_open");

    sprintf(name, "/barrier.outer.%d", id);
    if(create)
    {
        barrier->outer_lock = sem_open(
            name, 
            O_CREAT, 
            0644, 
            0
        );
    }
    else
    {
        barrier->outer_lock = sem_open(
            name,
            O_RDWR
        );
    }
    if(barrier->outer_lock == SEM_FAILED)
        handle_error("sem_open");

    return id;
}



void bar_wait(barrier_t *barrier)
{
    if(sem_wait(barrier->inner_lock) != 0)
        handle_error("sem_wait");
    if(sem_wait(barrier->critsec) != 0)
        handle_error("sem_wait");

    assert(*barrier->waiting >= 0);
    assert(*barrier->waiting <= barrier->n);

    if(++(*barrier->waiting) == barrier->n) // last one in
    {
        for(int i = 0; i < barrier->n; ++i)
            if(sem_post(barrier->outer_lock) != 0)
                handle_error("sem_post");
    }

    if(sem_post(barrier->critsec) != 0)
        handle_error("sem_post");

    if(sem_wait(barrier->outer_lock) != 0)
        handle_error("sem_wait");

    if(sem_wait(barrier->critsec) != 0)
        handle_error("sem_wait");

    assert(*barrier->waiting >= 0);
    assert(*barrier->waiting <= barrier->n);

    if(--(*barrier->waiting) == 0) // last one out
    {
        for(int i = 0; i < barrier->n; ++i)
            if(sem_post(barrier->inner_lock) != 0)
                handle_error("sem_post");
    }

    if(sem_post(barrier->critsec) != 0)
        handle_error("sem_post");
}

void bar_destroy(barrier_t *barrier, int id)
{
    if(sem_close(barrier->critsec) != 0)
        handle_error("sem_close");

    if(sem_close(barrier->inner_lock) != 0)
        handle_error("sem_close");

    if(sem_close(barrier->outer_lock) != 0)
        handle_error("sem_close");


    char name[50] = {0};
    sprintf(name, "/barrier.critsec.%d", id);
    if(sem_unlink(name) != 0)
        handle_error("sem_unlink");

    sprintf(name, "/barrier.inner.%d", id);
    if (sem_unlink(name) != 0)
        handle_error("sem_unlink");

    sprintf(name, "/barrier.outer.%d", id);
    if (sem_unlink(name) != 0)
        handle_error("sem_unlink");
}