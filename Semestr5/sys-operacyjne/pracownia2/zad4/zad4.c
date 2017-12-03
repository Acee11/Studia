#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define eat() usleep(1000*((int)rand()%1000 + 300))
#define fill() usleep(1000*((int)rand()%1000 + 300))

#define M 1
#define N 2

#define COOK 0
#define SAVAGE 1

int *portions;
sem_t *full;
sem_t *empty;
sem_t *critsec;

int cook_pid;
int savage_pid[N];

bool terminate = false;

void sigint_handler(int signum)
{
    (void)signum;
    terminate = true;
}

void cook()
{
    while(1)
    {
        if(sem_wait(empty) != 0)
            if(errno != EINTR)
                handle_error("sem_wait");
        printf("filling up the cauldron...\n");
        fflush(stdout);
        fill();
        *portions = M;
        if(sem_post(full) != 0)
            handle_error("sem_post");

        if(terminate)
            break;
    }
}

void savage()
{
    while(1)
    {
        if(sem_wait(critsec) != 0)
            if(errno != EINTR)
                handle_error("sem_wait");

        if(*portions == 0)
        {
            if(sem_post(empty) != 0)
                handle_error("sem_post");
            if(sem_wait(full) != 0)
                if(errno != EINTR)
                    handle_error("sem_wait");
        }
        int curr_portion = (*portions)--;
        printf("eaten portion %d\n", curr_portion);
        if(sem_post(critsec) != 0)
            handle_error("sem_post"); 

        eat(); 
        fflush(stdout);

        if(terminate)
            break;
    }
}

int make_process(int type)
{
    int pid;
    if((pid = fork()) == -1)
        handle_error("fork");
    if(pid == 0)
    {


        if((critsec = sem_open("/zad4.critsec", O_RDWR)) == SEM_FAILED)
            handle_error("sem_open");
        if((empty = sem_open("/zad4.empty", O_RDWR)) == SEM_FAILED)
            handle_error("sem_open");
        if((full = sem_open("/zad4.full", O_RDWR)) == SEM_FAILED)
            handle_error("sem_open");

        struct sigaction new_action;
        memset(&new_action, 0, sizeof(struct sigaction));
        if(sigemptyset(&new_action.sa_mask) == -1)
            handle_error("sigemptyset");
        new_action.sa_handler = sigint_handler;

        if(sigaction(SIGUSR1, &new_action, NULL) == -1)
            handle_error("sigaction");

        if(type == SAVAGE)
            savage();   
        else
            cook();

        if(sem_close(critsec) != 0)
            handle_error("sem_close");
        if(sem_close(empty) != 0)
            handle_error("sem_close");
        if(sem_close(full) != 0)
            handle_error("sem_close");

        exit(0);
    }   

    return pid;
}

int main(void)
{
    srand(1338);



    if((critsec = sem_open("/zad4.critsec", O_CREAT, 0644, 1)) == SEM_FAILED)
        handle_error("sem_open");
    if((full = sem_open("/zad4.full", O_CREAT, 0644, 0)) == SEM_FAILED)
        handle_error("sem_open");
    if((empty = sem_open("/zad4.empty", O_CREAT, 0644, 0)) == SEM_FAILED)
        handle_error("sem_open");

    struct sigaction new_action;
    memset(&new_action, 0, sizeof(struct sigaction));
    if(sigemptyset(&new_action.sa_mask) == -1)
        handle_error("sigemptyset");
    new_action.sa_handler = sigint_handler;

    if(sigaction(SIGINT, &new_action, NULL) == -1)
        handle_error("sigaction");

    portions = mmap(
        NULL, 
        sizeof(int), 
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        0,
        0
    );
    if(portions == MAP_FAILED)
        handle_error("mmap");
    *portions = 0;

    if(sem_close(critsec) != 0)
        handle_error("sem_close");
    if(sem_close(full) != 0)
        handle_error("sem_close");
    if(sem_close(empty) != 0)
        handle_error("sem_close");

    cook_pid = make_process(COOK);
    for(int i = 0; i < N; ++i)
        savage_pid[i] = make_process(SAVAGE);

    sigset_t mask, oldmask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    while(!terminate)
        sigsuspend(&oldmask);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    for(int i = 0; i < N; ++i)
        if(kill(savage_pid[i], SIGUSR1 == -1))
            handle_error("kill");  
    if(kill(cook_pid, SIGUSR1) == -1)
        handle_error("kill");

    if(sem_unlink("/zad4.critsec") != 0)
        handle_error("sem_unlink");
    if(sem_unlink("/zad4.full") != 0)
        handle_error("sem_unlink");
    if(sem_unlink("/zad4.empty") != 0)
        handle_error("sem_unlink");

    return 0;
}