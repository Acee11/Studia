#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <stdio.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    if(argc > 1 && !strcmp(argv[1], "--reaper"))
    {
        if(prctl(PR_SET_CHILD_SUBREAPER) == -1)
            handle_error("prctl");
    }

    pid_t pid1;
    if((pid1 = fork()) == -1)
        handle_error("fork");
    if(pid1 == 0)
    {
        pid_t pid2;
        if((pid2 = fork()) == -1)
            handle_error("fork");
        if(pid2 == 0) // child child
            sleep(100);
        else // child
        {
            printf("child child pid: %d\n", pid2);
            fflush(stdout);
            exit(0);
        }
    }
    else // parent
    {
        printf("child pid: %d\n", pid1);
        fflush(stdout);
        sleep(1);
        char *const ps_argv[] = {"/bin/ps", "-o", "pid,ppid,time,stat,cmd", NULL};
        execv("/bin/ps", ps_argv);
    }

    return 0;
}