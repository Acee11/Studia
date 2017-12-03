#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <func_wrap.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage: %s <read_pipe> <write_pipe>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int read_pipe = atoi(argv[1]);

    char buf[100];
    int char_cnt = 0;
    while(read_word(read_pipe, buf, 100))
    {
        puts(buf);
        char_cnt += strlen(buf);
    }
    close_(read_pipe);

    printf("Characters read: %d\n", char_cnt);

    exit(EXIT_SUCCESS);
}