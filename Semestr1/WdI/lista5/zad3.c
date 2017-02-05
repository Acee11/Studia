#include <stdio.h>

int gcd(int n, int m)
{
    int ilenp,c,r=1;

    while(m)
    {
        if(n < m)
        {
            c = n;
            n = m;
            m = c;
        }

        ilenp = n%2 + m%2;

        if(ilenp == 2)
            n -= m;

        else if(!ilenp)
        {
            n /= 2;
            m /= 2;
            r *= 2;
        }

        else if(n%2 == 0)
            n /= 2;
        else
            m /= 2;

    }

    return n * r;


}

int main()
{
    int a,b;
    while(1)
    {
        scanf("%d %d",&a,&b);
        printf("%d\n",gcd(a,b));
    }


    return 0;
}
