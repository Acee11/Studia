#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void transpose(int *dst, int *src, int n) 
{
	for (long i = 0; i < n; i++)
		for (long j = 0; j < n; j++)
			dst[j * n + i] = src[i * n + j];
}

void transpose2(int *dst, int *src, int n) 
{
	for (long i = 0; i < n; i += 8)
	{
		for (long j = 0; j < n; j += 8)
		{
			for (long Xi = i; Xi + i < n && Xi < i + 8; Xi++)
			{
				for(long Xj = j; Xj + j < n && Xj < j + 8; Xj++)
				{
					dst[(j + Xj)*n + i + Xi] = src[(i + Xi)*n + j + Xj];
				}
			}
		}
	}
}


int main()
{
	int n = 10000;

	int *m1 = malloc(n * n * 4);
	int *m2 = malloc(n * n * 4);

	clock_t t = clock();
	transpose(m2, m1, n);
	t = clock() - t;
	printf("Unoptimized transpose: %fs\n",((double)t) / CLOCKS_PER_SEC);

	t = clock();
	transpose2(m2, m1, n);
	t = clock() - t;
	printf("Optimized transpose: %fs\n",((double)t) / CLOCKS_PER_SEC);


	return 0;
}