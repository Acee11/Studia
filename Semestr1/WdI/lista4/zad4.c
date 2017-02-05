#include <stdio.h>

int NWD(int a, int b)
{
    int c;
    if (a<b)
    {
        c = a;
        a = b;
        b = c;
    }

    while(b)
    {
        c = a%b;
        a = b;
        b = c;
    }

    return a;
}

int main()
{
    int n,i,c;

    scanf("%d",&n);

    int *a = malloc(4 * n);

    scanf("%d",&a[0]);

    if(n == 1)
    {
        printf("%d",a[0]);
        return 0;
    }

    scanf("%d",&a[1]);
    c = NWD(a[0],a[1]);
    for(i = 2; i < n; i++)
    {
        scanf("%d",&a[i]);

        c = NWD(NWD(a[i],a[i-1]),c);

    }

    printf("%d",c);

    return 0;
}
