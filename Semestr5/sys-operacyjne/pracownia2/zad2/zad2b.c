#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/mman.h>


#define think() usleep(1000*((int)rand()%500 + 300))
#define eat() usleep(1000*((int)rand()%500 + 300))

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define NUM_PHIL 5
#define PRINT_TO_STDOUT 0

sem_t *forks[NUM_PHIL];
int phil_pid[NUM_PHIL];
int phil_idx;

unsigned *deadlock_check;
bool terminate = false;

void sigint_handler(int signum)
{
    (void)signum;
    terminate = true;
}

void take_forks(int i)
{
    if(i%2)
    {
        if(sem_wait(forks[i]) != 0)
            handle_error("sem_wait");
        if(sem_wait(forks[(i+1)%NUM_PHIL]) != 0)
            handle_error("sem_wait");
    }
    else
    {
        if(sem_wait(forks[(i+1)%NUM_PHIL]) != 0)
            handle_error("sem_wait");
        if(sem_wait(forks[i]) != 0)
            handle_error("sem_wait");
    }
}

void put_forks(int i)
{
    if(i%2)
    {
        if(sem_post(forks[(i+1)%NUM_PHIL]) != 0)
            handle_error("sem_post");
        if(sem_post(forks[i]) != 0)
            handle_error("sem_post");
    }
    else
    {
        if(sem_post(forks[i]) != 0)
            handle_error("sem_post");
        if(sem_post(forks[(i+1)%NUM_PHIL]) != 0)
            handle_error("sem_post");
    }
}

void philosopher(int i)
{
    while(1)
    {
        think();
        take_forks(i);
        eat();
        #if PRINT_TO_STDOUT
        printf("Philosopher %d finished eating\n", i);
        #endif
        put_forks(i);

        ++(*deadlock_check);
    }
}

int create_phil_process(int i)
{
    int pid;
    if((pid = fork()) == -1)
        handle_error("fork");
    if(pid == 0)
    {

        char sem_name[25] = {0};
        sprintf(sem_name, "/forks_%d", i);
        if((forks[i] = sem_open(sem_name, O_RDWR)) == SEM_FAILED)
            handle_error("sem_open");
        sprintf(sem_name, "/forks_%d", (i+1)%NUM_PHIL);
        if((forks[(i+1)%NUM_PHIL] = sem_open(sem_name, O_RDWR)) == SEM_FAILED)
            handle_error("sem_open");

        struct sigaction new_action;
        memset(&new_action, 0, sizeof(struct sigaction));
        if(sigemptyset(&new_action.sa_mask) == -1)
            handle_error("sigemptyset");
        new_action.sa_handler = SIG_IGN;

        if(sigaction(SIGINT, &new_action, NULL) == -1)
            handle_error("sigaction");

        phil_idx = i;
        philosopher(i);
        if(sem_close(forks[i]) != 0)
            handle_error("sem_close");
        if(sem_close(forks[(i+1)%NUM_PHIL]) != 0)
            handle_error("sem_close");
        exit(0);
    }
    return pid;
}

int main()
{
    deadlock_check = mmap(
        NULL,
        sizeof(unsigned),
        PROT_READ | PROT_WRITE,
        MAP_SHARED | MAP_ANONYMOUS,
        0,
        0
    );
    *deadlock_check = 0;

    struct sigaction new_action;
    memset(&new_action, 0, sizeof(struct sigaction));
    if(sigemptyset(&new_action.sa_mask) == -1)
        handle_error("sigemptyset");
    new_action.sa_handler = sigint_handler;

    if(sigaction(SIGINT, &new_action, NULL) == -1)
        handle_error("sigaction");

    for(int i = 0; i < NUM_PHIL; ++i)
    {
        char sem_name[24] = {0};
        sprintf(sem_name, "/forks_%d", i);
        if((forks[i] = sem_open(sem_name, O_CREAT, 0644, 1)) == SEM_FAILED)
            handle_error("sem_open");
        if(sem_close(forks[i]) != 0)
            handle_error("sem_close");

    }
    for(int i = 0; i < NUM_PHIL; ++i)
        phil_pid[i] = create_phil_process(i);

    // aktywne czekanie uzyte jest celowo by wykryc deadlocka
    while(!terminate)
    {
        unsigned old_dl_check = *deadlock_check;
        sleep(3);
        if(*deadlock_check == old_dl_check)
        {
            fprintf(stderr, "Possible deadlock");
            break;
        }
    }

    for(int i = 0; i < NUM_PHIL; ++i)
        if(kill(phil_pid[i], SIGKILL) == -1)
            handle_error("kill");    

    for(int i = 0; i < NUM_PHIL; ++i)
    {
        char sem_name[24] = {0};
        sprintf(sem_name, "/forks_%d", i);
        if(sem_unlink(sem_name) != 0)
            handle_error("sem_unlink");
    }

    return 0;

}