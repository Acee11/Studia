#include <stdio.h>

int isFree(int *t, int n, int p)
{
    int i;
    for(i=0; i<n; i++)
        if(t[i] == p)
            return 0;
    return 1;
}

int check(int **tab, int n, int s)
{
    int i,j,suma=0;
    int wybor[n];
    for(i=0; i<n; i++)
        wybor[i] = -1;
    i = 0;

    while(wybor[n-1] == -1)
    {
        if(wybor[i] != -1)
        {
            suma -= tab[wybor[i]][i];
            wybor[i]++;
        }
        while(wybor[i] != n && !isFree(wybor,wybor[i],i))
            wybor[i]++;
        if(wybor[i] == n)
        {
            wybor[i] = -1;
            i--;
            continue;
        }

        suma += tab[wybor[i]][i];
        if(suma > s)
            continue;
        i++;
    }

    return 1;
}



int main()
{
    int n,s;
    scanf("%d %d",&n, &s);
    int tab[n][n];

    int i,j;
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            scanf("%d",&tab[i][j]);


    printf("%d", check(tab,n,s));

    return 0;
}
