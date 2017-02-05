#include <stdio.h>

int main()
{
    int n,k;

    scanf("%d",&n);
    char c[10] = {0};

    while(n)
    {
        k = n%10;
        n /= 10;
        c[k] = 1;
    }

    k = 0;

    for(;n<10;n++)
    {
        k += c[n];
    }

    printf("%d",k);

    return 0;
}
