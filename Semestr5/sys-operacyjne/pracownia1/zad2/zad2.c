#include <ucontext.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE 0x4000
#define WORD_MAX_SIZE 100
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

int word_cnt;
int char_cnt;
bool got_word;
char input_word[WORD_MAX_SIZE];
ucontext_t uctx_main, uctx_word_reader, 
    uctx_word_filter, uctx_word_printer;

void word_reader(void)
{
    while(scanf("%99s", input_word) && !feof(stdin))
    {
        got_word = true;
        ++word_cnt;
        if (swapcontext(&uctx_word_reader, &uctx_word_filter) == -1)
            handle_error("swapcontext");
        got_word = false;
    }
}

void word_filter(void)
{
    while(got_word)
    {
        int i, pos = 0, len = strlen(input_word);
        for(i = 0; i < len; ++i)
            if(isalnum(input_word[i]))
                input_word[pos++] = input_word[i];
        input_word[pos] = '\0';

        if (swapcontext(&uctx_word_filter, &uctx_word_printer) == -1)
            handle_error("swapcontext");
    }
    printf("Words: %d\n", word_cnt);
}

void word_printer(void)
{
    while(got_word)
    {
        puts(input_word);
        char_cnt += strlen(input_word);
        if (swapcontext(&uctx_word_printer, &uctx_word_reader) == -1)
            handle_error("swapcontext");
    }
    printf("Characters in words: %d\n", char_cnt);
}

int main(void)
{
    char stack1[STACK_SIZE];
    char stack2[STACK_SIZE];
    char stack3[STACK_SIZE];

    if (getcontext(&uctx_word_reader) == -1)
        handle_error("getcontext");
    uctx_word_reader.uc_stack.ss_sp = stack1;
    uctx_word_reader.uc_stack.ss_size = sizeof(stack1);
    uctx_word_reader.uc_link = &uctx_word_filter;
    makecontext(&uctx_word_reader, word_reader, 0);

    if (getcontext(&uctx_word_filter) == -1)
        handle_error("getcontext");
    uctx_word_filter.uc_stack.ss_sp = stack2;
    uctx_word_filter.uc_stack.ss_size = sizeof(stack2);
    uctx_word_filter.uc_link = &uctx_word_printer;
    makecontext(&uctx_word_filter, word_filter, 0);

    if (getcontext(&uctx_word_printer) == -1)
        handle_error("getcontext");
    uctx_word_printer.uc_stack.ss_sp = stack3;
    uctx_word_printer.uc_stack.ss_size = sizeof(stack3);
    uctx_word_printer.uc_link = &uctx_main;
    makecontext(&uctx_word_printer, word_printer, 0);

    if (swapcontext(&uctx_main, &uctx_word_reader) == -1)
        handle_error("swapcontext");

    return 0;
}