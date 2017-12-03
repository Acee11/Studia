#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int main(int argc, char *argv[])
{
    if(argc > 1 && !strcmp(argv[1], "--ignore"))
    {
        struct sigaction new_action;
        new_action.sa_handler = SIG_IGN;
        if(sigemptyset(&new_action.sa_mask) == -1)
            handle_error("sigemptyset");
        new_action.sa_flags = 0;
        if(sigaction(SIGCHLD, &new_action, NULL) == -1)
            handle_error("sigaction");
    }

    pid_t pid;
    if((pid = fork()) == -1)
        handle_error("fork");
    if(pid != 0)
    {
        char *const ps_argv[] = {"/bin/ps", "-o", "pid,time,stat,cmd", NULL};
        char *const ps_envp[] = {NULL};
        if(execve("/bin/ps", ps_argv, ps_envp) == -1)
            handle_error("execve");

    }

    return 0;
}