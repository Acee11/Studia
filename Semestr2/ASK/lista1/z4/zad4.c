#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

pthread_t t1,t2;

static int a=90;

void do_something()
{
    a = 1;
    printf(" %d",a);

    while(a != 255)
    ;
}

void set_a()
{
    a=255;
    printf(" %d",a);
}

int main()
{
    int err;
    err = pthread_create(&t1, NULL, (void*)&do_something, NULL);
    pthread_create(&t2, NULL, (void*)&set_a, NULL);
    printf(" %d",a);

    pthread_join(t1,NULL);

    return 0;
}
/*
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];

void* doSomeThing(void *arg)
{
    unsigned long i = 0;
    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0]))
    {
        printf("\n First thread processing\n");
    }
    else
    {
        printf("\n Second thread processing\n");
    }

    for(i=0; i<(0xFFFFFFFF);i++);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;

    while(i < 2)
    {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");

        i++;
    }

    sleep(5);
    return 0;
}
*/
