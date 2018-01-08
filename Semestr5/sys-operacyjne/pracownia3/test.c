#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

__thread int x = 0;

void *f()
{
    x = 1;
    printf("%d\n", x);

    return NULL;
}

int main()
{
    pthread_t t1;
    pthread_create(&t1, NULL, f, NULL);
    pthread_join(t1, NULL);
    printf("%d\n", x);

    return 0;
}