#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insert_sort(long *first, long *last);

long tab[3] = {2,3,1};

int main()
{
	int i,n;
	srand(time(NULL));
	n = 100;
	long tab[n];
	for(i = 0; i < n; i++)
		tab[i] = rand() % 200;
	for(i = 0; i < n; i++)
	{
		printf("%ld ", tab[i]);
		if(!(i%9))
			printf("\n");
	}

	printf("\nAfter sorting: \n");

	insert_sort(&tab[0], &tab[n-1]);
	for(i = 0; i < n; i++)
	{
		printf("%ld ", tab[i]);
		if(!(i%9))
			printf("\n");
	}
	printf("\n");
	return 0;
}