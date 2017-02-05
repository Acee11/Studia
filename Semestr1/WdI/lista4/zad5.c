#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    char bin[32] = {0};
    int i = 0,j = 0;
    while(n)
    {
        bin[i] = n%2;
        n /= 2;
        i++;
    }
    i--;

    int c = i/2;

    for(;i > c; i--,j++)
    {
        if(bin[i] != bin[j])
            n = 1;
        if(n)
            break;
    }

    if(!n)
        printf("TAK");
    else
        printf("NIE");

    return 0;
}
