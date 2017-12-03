#include <fcntl.h>
#include <syslog.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>

#define handle_error(str) \
    do {perror(str); exit(EXIT_FAILURE);} while(0)

int sig_cnt = 0;
bool terminate = false;

// source: Advanced Programming in the UNIX Enviroment 13
void daemonize(const char *cmd)
{
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;
    /*
    * Clear file creation mask.
    */
    umask(0);
    /*
    * Get maximum number of file descriptors.
    */
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        handle_error("getrlimit");
    /*
    * Become a session leader to lose controlling TTY.
    */
    if ((pid = fork()) < 0)
        handle_error("fork");
    else if (pid != 0) /* parent */
        exit(0);
    setsid();
    /*
    * Ensure future opens won’t allocate controlling TTYs.
    */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        handle_error("sigaction");
    if ((pid = fork()) < 0)
        handle_error("fork");
    else if (pid != 0) /* parent */
        exit(0);
    /*
    * Change the current working directory to the root so
    * we won’t prevent file systems from being unmounted.
    */
    if (chdir("/") < 0)
        handle_error("chdir");
    /*
    * Close all open file descriptors.
    */
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < (int)rl.rlim_max; i++)
        close(i);
    /*
    * Attach file descriptors 0, 1, and 2 to /dev/null.
    */
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    /*
    * Initialize the log file.
    */
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) 
    {
        syslog(LOG_ERR, "unexpected file descriptors %d %d %d",
               fd0, fd1, fd2);
        exit(1);
    }
}

void sigusr1_handler(int signum)
{
    (void)signum;
    ++sig_cnt;
    syslog(LOG_INFO, "SIGUSR1 counter = %d", sig_cnt);
}

void sighup_handler(int signum)
{
    (void)signum;
    sig_cnt = 0;
    syslog(LOG_INFO, "Resetting SIGUSR1 counter");
}

void sigterm_handler(int signum)
{
    (void)signum;
    terminate = true;
    syslog(LOG_INFO, "Exiting with sig_cnt = %d", sig_cnt);
}


int main()
{
    sigset_t mask, oldmask;
    struct sigaction sa;
    daemonize("zad6log");

    sa.sa_handler = sigusr1_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, NULL) < 0)
        handle_error("sigaction");

    sa.sa_handler = sighup_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        handle_error("sigaction");

    sa.sa_handler = sigterm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGTERM, &sa, NULL) < 0)
        handle_error("sigaction");

    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGHUP);
    sigaddset(&mask, SIGTERM);

    sigprocmask(SIG_BLOCK, &mask, &oldmask);
    while(!terminate)
        sigsuspend(&oldmask);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    return 0;
}