#include <stdio.h>

int G(int n)
{
    int n1,n2,n3;
    n1=n2=n3=1;

    while(n>3)

    {
        int c = n3;

        n3 += n1 + n2;
        n1 = n2;
        n2 = c;

        n--;
    }

    return n3;
}

int fTrec(int n, int m)
{
    if(!m) return n;
    if(!n) return m;
    return fTrec(n-1,m) + (2 * fTrec(n,m-1));
}

int fTiter(int n, int m)
{
    int c;
    c = n;
    if(m < n)
        c = m;
    int suma[c];



}


int main()
{
    int a,b;
    while(1)
    {
        scanf("%d %d",&a,&b);
        printf("%d\n",fTrec(a,b));
    }



    return 0;
}
