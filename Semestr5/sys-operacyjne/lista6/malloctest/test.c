#include <stdlib.h>

#define SZ 8

int main()
{
    void *p[6];

    p[0] = malloc(SZ);
    p[1] = malloc(SZ);
    p[2] = malloc(SZ);
    p[3] = malloc(SZ);
    p[4] = malloc(SZ);
    p[5] = malloc(SZ);

    free(p[1]);
    free(p[3]);
    free(p[2]);
    // free(p[2]);
    // free(p[1]);
    // free(p[0]);
    // free(p[0]);

    p[3] = malloc(SZ);
    p[4] = malloc(SZ);

    free(p[3]);

    return 0;
}