#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <func_wrap.h>

#define handle_error(str) \
    do {perror(str); exit(EXIT_FAILURE);} while(0)
#define READ 0
#define WRITE 1



int main()
{
    int pipe_reader_fd[2];
    pid_t reader_pid;
    int pipe_filter_fd[2];
    pid_t filter_pid;
    int pipe_printer_fd[2];
    pid_t printer_pid;
    int status;

    pipe_(pipe_reader_fd);
    pipe_(pipe_filter_fd);
    
    dup2(STDIN_FILENO, pipe_reader_fd[READ]);
    close_(pipe_reader_fd[WRITE]);

    if((reader_pid = fork_()) == 0)
    {
        close_(pipe_filter_fd[READ]);

        char read_pipe[11], write_pipe[11];
        if(snprintf(read_pipe, 10, "%d", pipe_reader_fd[READ]) < 0)
            handle_error("snprintf");
        if(snprintf(write_pipe, 10, "%d", pipe_filter_fd[WRITE]) < 0)
            handle_error("snprintf");

        char *const reader_argv[] = {"./reader.out", read_pipe, write_pipe, NULL};
        execv("./reader.out", reader_argv);
        handle_error("execv");
    }

    close_(pipe_reader_fd[READ]);
    close_(pipe_filter_fd[WRITE]);

    pipe_(pipe_printer_fd);
    if((filter_pid = fork_()) == 0)
    {
        close_(pipe_printer_fd[READ]);

        char read_pipe[11], write_pipe[11];
        if(snprintf(read_pipe, 10, "%d", pipe_filter_fd[READ]) < 0)
            handle_error("snprintf");
        if(snprintf(write_pipe, 10, "%d", pipe_printer_fd[WRITE]) < 0)
            handle_error("snprintf");

        char *const filter_argv[] = {"./filter.out", read_pipe, write_pipe, NULL};
        execv("./filter.out", filter_argv);
        handle_error("execv");
    }
    
    close_(pipe_filter_fd[READ]);
    close_(pipe_printer_fd[WRITE]);

    if((printer_pid = fork_()) == 0)
    {
        char read_pipe[11];
        if(snprintf(read_pipe, 10, "%d", pipe_printer_fd[READ]) < 0)
            handle_error("snprintf");
        char *const printer_argv[] = {"./printer.out", read_pipe, NULL};
        execv("./printer.out", printer_argv);
        handle_error("execv");
    }
    close_(pipe_printer_fd[READ]);
    int w;
    while((w = wait(&status)) > 0)
    {
        if(w < 0)
            handle_error("wait");
        if (WIFEXITED(status))
            printf("process exited with status %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("process killed by signal %d\n", WTERMSIG(status));
    }

    exit(EXIT_SUCCESS);
}