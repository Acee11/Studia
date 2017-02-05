#include <stdio.h>
#include <stdint.h>

struct P
{
    char a;
    int b;
    char c;
};

struct
{
    int8_t a;
    void *b;
    int8_t c;
    int16_t d;
}A;

struct
{
    int16_t d;
    int8_t a;
    int8_t c;
    void *b;
}Ap;

struct
{
    int c;
    double b;

    uint16_t a;
}B;

int main()
{
    printf("%d %d %d %d %d\n",sizeof(double), sizeof(A.a), sizeof(A.b), sizeof(A.c), sizeof(A.d));
    printf("%d %d %d %d %d\n",sizeof(B), &Ap.a, &Ap.c, &Ap.d, &Ap.b);

    return 0;
}
