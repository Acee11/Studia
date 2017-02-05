#include "kolekcja.h"
#include <stdio.h>

int main()
{
	struct Kolekcja zb,t;
	zbior(&zb);
	torba(&t);

    int i;
	for(i = 0; i < 10; i++)
	{
		wstaw(&zb, i);
		wstaw(&t, i);
	}
	printf("Rozmiar zbioru: %d\nRozmiar torby: %d\n\n",rozmiar(&zb),rozmiar(&t));

    for(i = 9; i >= 0; i--)
	{
		wstaw(&zb,i);
		wstaw(&t, i);
	}
	printf("Rozmiar zbioru:%d\nRozmiar torby: %d\n",rozmiar(&zb),rozmiar(&t));

	printf("Ilosc jedynek w zbiorze: %d\nIlosc jedynek w torbie: %d",szukaj(&zb,1), szukaj(&t,1));



	return 0;
}
