#include <stdio.h>

unsigned long fibbonaci(unsigned long n);


int main()
{
	unsigned long x = fibbonaci(8);
	for(int i = 1; i <= 20; i++)
		printf("%lu\n", fibbonaci(i));

	return 0;
}