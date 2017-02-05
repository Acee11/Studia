#include <stdio.h>
#include <stdint.h>
#include <time.h>
#define METHOD_A
#define METHOD_B
#define METHOD_C
#define LEN 0xffffffe

extern uint16_t tab[65536];


void precalc()
{
	FILE *f = fopen("precalc.c", "wb");
	fprintf(f, "tab[65536] = {\n");
	for(uint32_t i = 0; i < 65536; ++i)
	{
		uint16_t x = (uint16_t)i;
		x = ((x>>1)  & 0x5555) | ((x & 0x5555) << 1);
		x = ((x>>2)  & 0x3333) | ((x & 0x3333) << 2);
		x = ((x>>4)  & 0x0F0F) | ((x & 0x0F0F) << 4);
		x = ((x>>8)  & 0x00FF) | ((x & 0x00FF) << 8);
		fprintf(f, "%u, ", x);
		if((i+1)%16 == 0)
			fprintf(f, "\n");
	}
	fclose(f);
}

int main()
{
	clock_t t;
	#ifdef METHOD_A
	t = clock();
	for(uint32_t j = 0; j < LEN; ++j)
	{
		//printf("0x%X\n",j);
		uint32_t res = 0;
		uint32_t sh = 31;
		for(uint32_t i = j; i != 0; i >>= 1)
		{
			res |= (i&1) << sh;
			--sh;
		}
		//printf("0x%X\n",res);
	} 
	t = clock() - t;
	printf("MethodA   |   %f\n", ((float)t)/CLOCKS_PER_SEC);
	#endif

	#ifdef METHOD_B
	t = clock();
	for(uint32_t j = 0; j < LEN; ++j)
	{
		volatile uint32_t i = j;
		//printf("0x%X\n",i);
		
		i = ((i>>1)  & 0x55555555) | ((i & 0x55555555) << 1);
		i = ((i>>2)  & 0x33333333) | ((i & 0x33333333) << 2);
		i = ((i>>4)  & 0x0F0F0F0F) | ((i & 0x0F0F0F0F) << 4);
		i = ((i>>8)  & 0x00FF00FF) | ((i & 0x00FF00FF) << 8);
		i = ((i>>16) & 0x0000FFFF) | ((i & 0x0000FFFF) << 16);
		//printf("0x%X\n\n",i);
	}
	t = clock() - t;
	printf("MethodB   |   %f\n", ((float)t)/CLOCKS_PER_SEC);
	#endif

	#ifdef METHOD_C
	t = clock();
	for(uint32_t j = 0; j < LEN; ++j)
	{
		volatile uint32_t i = j;
		//printf("0x%X\n",i);
		uint32_t h = (uint32_t)tab[i>>16];
		uint32_t l = (uint32_t)tab[i&0xFFFF];
		i = (l<<16) | h;
		//printf("0x%X\n",i);
	}
	t = clock() - t;
	printf("MethodC   |   %f\n", ((float)t)/CLOCKS_PER_SEC);
	#endif

	return 0;
}