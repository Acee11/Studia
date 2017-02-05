#include <stdio.h>

long loop(long x, int n)	//%rdi = x		%esi = n
{
	long res = 0;
	long i;
	for(i = 1; i != 0; i <<= n & 0xff)
		res |= x&i;
	return res;
}

int main()
{
	long i;
	int j;
	for(i = 1; i < 20; i++)
	{
		for(j = 1; j < 20; j++)
		{
			printf("\n");
			long x = loop(i,j);
			printf("loop(%u, %d) = %u\n",i, j, x);
		}
	}

	return 0;
}