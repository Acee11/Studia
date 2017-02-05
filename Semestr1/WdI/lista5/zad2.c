#include <stdio.h>

int main()
{
    int n,k = 2;
    char silnia[30];

    scanf("%d",&n);

    while(n)
    {
        silnia[k-2] = n%k;
        n /= k;
        k++;
    }

    k-=3;

    for(; k >= 0; k--)
    {
        printf("%d ",silnia[k]);
    }



    return 0;
}
