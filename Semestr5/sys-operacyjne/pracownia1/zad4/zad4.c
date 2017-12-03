#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 100
#define BT_BUF_SIZE 100

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

void segv_handler(int signum, siginfo_t *siginfo, void *context)
{
    (void)(signum);
    (void)(context);

    char buf[BUF_SIZE];
    snprintf(buf, BUF_SIZE-1, 
        "SEGV at address %p\n"
        "Error type(si_code): %d\n",
        siginfo->si_addr, siginfo->si_code);
    int len = strlen(buf);
    write(STDERR_FILENO, buf, len);

    int nptrs;
    void *backtrace_buf[BT_BUF_SIZE];
    char **strings;

    nptrs = backtrace(backtrace_buf, BT_BUF_SIZE);
    strings = backtrace_symbols(backtrace_buf, nptrs);
    if (strings == NULL) 
        handle_error("backtrace_symbols");
    for (int j = 0; j < nptrs; j++)
    {
        snprintf(buf, BUF_SIZE-1, "%s\n", strings[j]);
        if(write(STDERR_FILENO, buf, strlen(buf)) == -1)
            handle_error("write");
    }

    free(strings);

    exit(1);
}

int main(void)
{
    struct sigaction new_action;
    memset(&new_action, 0, sizeof(struct sigaction));
    if(sigemptyset(&new_action.sa_mask) == -1)
        handle_error("sigemptyset");
    new_action.sa_sigaction = segv_handler;
    new_action.sa_flags = SA_SIGINFO;

    if(sigaction(SIGSEGV, &new_action, NULL) == -1)
        handle_error("sigaction");


    // *((int*)0xdeadbeef) = 1234;
    *((int*)main) = 1234;

    return 0;
}