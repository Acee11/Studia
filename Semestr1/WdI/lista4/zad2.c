#include <stdio.h>

int pow(int a, int b)
{
    int wynik;
    wynik = 1;
    while (b)
    {
        if (b%2) wynik *= a;
        b /= 2;
        a *= a;
    }
    return wynik;
}


int main()
{
    int n,x,suma=0,b,i;
    scanf("%d %d",&n,&x);
    for(i = 1; i <= n; i++)
    {
        b = i*pow(x,i);
        suma += b;
    }

    printf("\n\n%d",suma);

    return 0;
}
