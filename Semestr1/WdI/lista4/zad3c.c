#include <stdio.h>

int main()
{
    int n,x,i,suma;

    scanf("%d %d",&n,&x);

    for (i = n; i > 0; i--)
    {
        n *= x;
        n += i - 1;
    }

    printf("%d",suma);

    return 0;
}
