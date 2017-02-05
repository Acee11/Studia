#include <stdio.h>
#define tab(x,y) tab[n*(x) + (y)]



int *kwadrat(int *tab,int *used, int n, int x, int y)
{
    if (x == n)
    {
        x = 0;
        y++;
    }
    if (y == n) return tab;
    int i;
    for(i = 1; i <= n*n; i++)
    {
        if (used[i-1] == 1) continue;
        , j;
        for(j=0; j<n; j++)
        {
            sumaK += tab(j,x);
            sumaW += tab(y,j);
        }

        if (((sumaK + i) > ((n*((n*n)+1))/2)) || ((sumaW + i) > ((n*((n*n)+1))/2))) continue;
        sumaK = 0;
        sumaW = 0;
        if(x == y)
            for(j=0; j<n; j++) sumaK += tab(j,j);
        if (x == n-y-1)
            for(j=0; j<n; j++) sumaW += tab(j,n-j-1);
        if (((sumaK + i) > ((n*((n*n)+1))/2)) || ((sumaW + i) > ((n*((n*n)+1))/2))) continue;



        tab(y,x) = i;
        used[i-1] = 1;
        int *k = kwadrat(tab, used, n, x+1, y);
        if (k != NULL) return k;
        else
        {
            tab(y,x) = 0;
            used[i-1] = 0;
        }
    }
    return NULL;
}

int main()
{
    int n,i,j;
    scanf("%d",&n);

    int tab[n*n];
    int used[n*n];
    for(i=0; i<n*n; i++)
        tab[i] = 0;
    used[i] = 0;

    kwadrat(tab,used,n,0,0);

    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
            printf("%d ",tab(i,j));
        putchar('\n');
    }

    return 0;
}
