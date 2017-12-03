#include <mysemaphore.h>

void sem_init(sem_t *sem, unsigned value)
{
    pthread_mutexattr_t attr;
    assert(pthread_mutexattr_init(&attr) == 0);
    assert(pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK) == 0);

    assert(pthread_mutex_init(&sem->critsec, &attr) == 0);

    assert(pthread_cond_init(&sem->gt_zero, NULL) == 0);

    assert(value < 0x80000000);
    sem->count = (int)value;
    sem->wakeups = 0;
}

void sem_wait(sem_t *sem)
{
    assert(pthread_mutex_lock(&sem->critsec) == 0);
    --sem->count;

    if(sem->count < 0)
    {
        do
        {
            assert(pthread_cond_wait(&sem->gt_zero, &sem->critsec) == 0);
        } while(sem->wakeups < 1);
        --sem->wakeups;
    }

    assert(pthread_mutex_unlock(&sem->critsec) == 0);
}

void sem_post(sem_t *sem)
{
    // assert(pthread_mutex_lock(&sem->critsec) == 0);
    assert(pthread_mutex_lock(&sem->critsec) == 0);

    ++sem->count;
    if(sem->count <= 0)
    {
        ++sem->wakeups;
        assert(pthread_cond_signal(&sem->gt_zero) == 0);
    }

    assert(pthread_mutex_unlock(&sem->critsec) == 0);
}

void sem_getvalue(sem_t *sem, int *sval)
{
    assert(pthread_mutex_lock(&sem->critsec) == 0);
    *sval = sem->count;
    assert(pthread_mutex_unlock(&sem->critsec) == 0);
}