#include <func_wrap.h>

#define handle_error(str) \
    do {perror(str); exit(EXIT_FAILURE);} while(0)

pid_t fork_()
{
    pid_t pid;
    if((pid = fork()) == -1)
        handle_error("fork");
    return pid;
}

void close_(int fd)
{
    if(close(fd) == -1)
        handle_error("close");
}

void pipe_(int *fd)
{
    if(pipe(fd) == -1)
        handle_error("pipe");
}

int read_(int fd, void *buf, size_t count)
{
    int ret;
    if((ret = read(fd, buf, count)) == -1)
        handle_error("read");
    return ret;
}

void write_(int fd, const void *buf, size_t count)
{
    if(write(fd, buf, count) == -1)
        handle_error("write");
}

int read_word(int fd, char *buf, int buf_size)
{
    int i = 0;
    while(i < buf_size-1 && read_(fd, &buf[i], 1) && buf[i] != ' ')
        ++i;
    buf[i] = '\0';
    return i;


}