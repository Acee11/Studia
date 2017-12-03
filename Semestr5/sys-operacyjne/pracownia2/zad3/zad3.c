#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "./include/mybarrier.h"

#define NUM_PROC 10
#define ON_BARRIER 3


#define run() usleep(1000 * ((int)rand() % 300 + 1000))

barrier_t barrier;

bool terminate = false;

void sigint_handler(int signum)
{
    (void)signum;
    terminate = true;
}

void race(barrier_t *barrier)
{
    while(1)
    {
        puts("RUNNING!");
        fflush(stdout);
        run();
        bar_wait(barrier);
    }
}

int create_process(barrier_t *barrier)
{
    int pid;
    
    if((pid = fork()) == -1)
        handle_error("fork");
    
    if(pid == 0)
    {
        struct sigaction new_action;
        memset(&new_action, 0, sizeof(struct sigaction));
        if (sigemptyset(&new_action.sa_mask) == -1)
            handle_error("sigemptyset");
        new_action.sa_handler = SIG_IGN;

        if (sigaction(SIGINT, &new_action, NULL) == -1)
            handle_error("sigaction");

        bar_init(barrier, 0, ON_BARRIER, 0);
        race(barrier);
    }

    return pid;
}

int main(void)
{
    srand(1337);

    struct sigaction new_action;
    memset(&new_action, 0, sizeof(struct sigaction));
    if (sigemptyset(&new_action.sa_mask) == -1)
        handle_error("sigemptyset");
    new_action.sa_handler = sigint_handler;

    if (sigaction(SIGINT, &new_action, NULL) == -1)
        handle_error("sigaction");

    barrier.waiting = mmap(
        NULL,
        sizeof(int), 
        PROT_READ | PROT_WRITE, 
        MAP_ANONYMOUS | MAP_SHARED,
        0,
        0
    );
    *barrier.waiting = 0;

    bar_init(&barrier, 0, ON_BARRIER, CREATE);
    int pids[NUM_PROC];
    for(int i = 0; i < NUM_PROC; ++i)
        pids[i] = create_process(&barrier);

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    while (!terminate)
        sigsuspend(&oldmask);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    for(int i = 0; i < NUM_PROC; ++i)
        if(kill(pids[i], SIGKILL) == -1)
            handle_error("kill");

    bar_destroy(&barrier, 0);

    return 0;
}