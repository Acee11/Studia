#include <stdio.h>

#define abs(x) if ((x)<0

int isfree(int x, int y, int *b)
{
    int i;
    for (i=0; i<x; i++)
        if (b[i]-i==y-x || b[i]+i==y+x || b[i]==y) return 0;
    return 1;
}


int queens(int n)
{
    int k,c=0;
    int b[n];
    int i;
    for(i=0; i<n; i++) b[i] = 0;
    k=1;
    while (k>=0)
    {
        do
        {
            b[k]++;
        }
        while (b[k]<n && !isfree(k,b[k],b));
        if (b[k]<n)
        {
            if (k == n-1)
            {
                c++;
                continue;
            }
            k++;
        }

        else
        {
            b[k]=-1;
            k--;
        }
    }
    return c;
}

int poprawne(int a[],int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        int j;
        for (j = i+1; j < n; j++)
            if(a[j] == a[i]  ||  j - i == a[j] - a[i] || j - i == a[i] - a[j]) return 0;

    }
    return 1;
}

int hetmany(int n, int k, int a[])
{
    if (k==n) return poprawne(a,n);
    int i;
    for(i=0; i<n; i++)g
    {
        a[k]=i;
        if (hetmany(n,k+1,a)) return 1;
    }
    return 0;
}

int main()
{
    int a[4] = {0};
    printf("%d\n", hetmany(4,0,a));
    int i;
    for (i = 0; i < 4; i++) printf("%d ",a[i]);

    return 0;
}
