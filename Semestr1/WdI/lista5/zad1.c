#include <stdio.h>

int pot1(int a, int b, int licznik)
{
    if (!b) return licznik;
    if (b%2) return a* pot(a*a,b/2,licznik+2);
    return pot(a*a, b/2, licznik+1);
}

int pot(int a, int b)
{
    int rez,licznik = 0;
    rez = 1;
    while (b>0)
    {
        if (b%2)
        {
            rez = rez * a;
            licznik++;
        }
        b = b / 2;
        a = a * a;
        licznik++;
    }
    return licznik;
}


main()
{
    int licznik = 0;
    int i;
    for (i = 2; i < 10000; i*=2)
    {
        printf("2^%d   (rek)|||   %d\n", i-1, pot1(2,i-1,0) );
        printf("2^%d   (nierek)|||   %d\n", i-1, pot(2,i-1));
    }
}
