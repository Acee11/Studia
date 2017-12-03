#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <func_wrap.h>

void filter(char *str)
{
    int i, pos = 0, len = strlen(str);
    for(i = 0; i < len; ++i)
        if(isalnum(str[i]))
            str[pos++] = str[i];
    str[pos] = '\0';
}

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
    while(read_word(read_pipe, buf, 100))
    {
        filter(buf);
        write_(write_pipe, buf, strlen(buf));
        write_(write_pipe, " ", 1);
    }
    close_(read_pipe);
    close_(write_pipe);

    exit(EXIT_SUCCESS);
}