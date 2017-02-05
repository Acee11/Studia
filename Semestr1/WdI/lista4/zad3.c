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

int NWW(int a, int b)
{
    return (a*b)/NWD(a,b);
}

int main()
{
    int a,b,c;

    scanf("%d %d",&a,&b);

    printf("%d\n",(a*b)/NWD(a,b));

    c = NWD(a,b);
    a /= c;
    b /= c;

    printf("%d / %d",a,b);


    return 0;
}
