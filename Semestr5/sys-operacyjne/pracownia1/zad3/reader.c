#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <func_wrap.h>

#define handle_error(str) \
    do {perror(str); exit(EXIT_FAILURE);} while(0)

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: %s <read_pipe> <write_pipe>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int read_pipe = atoi(argv[1]);
    int write_pipe = atoi(argv[2]);

    char buf[100];
    int word_cnt = 0;
    while(read_word(read_pipe, buf, 100))
    {
        ++word_cnt;
        write_(write_pipe, buf, strlen(buf));
        write_(write_pipe, " ", 1);
    }
    close_(read_pipe);
    close_(write_pipe);

    printf("Words read: %d\n", word_cnt);

    exit(EXIT_SUCCESS);
}