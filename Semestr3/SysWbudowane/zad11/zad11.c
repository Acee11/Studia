#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <memory.h>
#define VER

#ifdef VER
#include "tab256.c"
#include "tab65536.c"
#endif

char bitcnt16(uint16_t c)
{
	c = (c & 0x5555) + ((c & 0xAAAA) >> 1);
	c = (c & 0x3333) + ((c & 0xCCCC) >> 2);
	c = (c & 0x0F0F) + ((c & 0xF0F0) >> 4);
	c = (c & 0x00FF) + ((c & 0xFF00) >> 8);
	return c;
}

char bitcnt64(uint64_t c)
{
	c = (c & 0x5555555555555555) + ((c & 0xAAAAAAAAAAAAAAAA) >> 1);
	c = (c & 0x3333333333333333) + ((c & 0xCCCCCCCCCCCCCCCC) >> 2);
	c = (c & 0x0F0F0F0F0F0F0F0F) + ((c & 0xF0F0F0F0F0F0F0F0) >> 4);
	c = (c & 0x00FF00FF00FF00FF) + ((c & 0xFF00FF00FF00FF00) >> 8);
	c = (c & 0x0000FFFF0000FFFF) + ((c & 0xFFFF0000FFFF0000) >> 16);
	c = (c & 0x00000000FFFFFFFF) + ((c & 0xFFFFFFFF00000000) >> 32);
	return c;
}

void precalc256()
{
	FILE *f = fopen("tab256.c", "wb");
	fprintf(f, "tab256[256] = {\n");
	for(int i = 1; i <= 256; ++i)
	{
		fprintf(f, "%u, ", bitcnt16((uint16_t)(i-1)));
		if(i%16 == 0)
			fprintf(f, "\n");
	}
	fclose(f);
}

void precalc65536()
{
	FILE *f = fopen("tab65536.c", "wb");
	fprintf(f, "tab65536[65536] = {\n");
	for(int i = 1; i <= 65536; ++i)
	{
		fprintf(f, "%u, ", bitcnt16((uint16_t)(i-1)));
		if(i%32 == 0)
			fprintf(f, "\n");
	}
	fclose(f);
}

unsigned long createFile(size_t fSize)
{

	srand(time(NULL));
	unsigned long sum = 0;
	uint16_t *mem = (uint16_t*) malloc(fSize);
	for(unsigned int i = 0; i < fSize/sizeof(uint16_t); ++i)
	{
		uint16_t r = rand();
		sum += bitcnt16(r);
		mem[i] = rand();
	}
	FILE *f = fopen("file", "wb");
	fwrite((uint64_t*)mem, sizeof(uint64_t), fSize/sizeof(uint64_t), f);
	fclose(f);
	free(mem);
	return sum;
}

unsigned long methodA(const uint64_t* buffer, const size_t fSize)
{

	unsigned long sum = 0;
	for(size_t i = 0; i < fSize/sizeof(uint64_t); ++i)
	{
		uint64_t c = i;
		c = (c & 0x5555555555555555) + ((c & 0xAAAAAAAAAAAAAAAA) >> 1);
		c = (c & 0x3333333333333333) + ((c & 0xCCCCCCCCCCCCCCCC) >> 2);
		c = (c & 0x0F0F0F0F0F0F0F0F) + ((c & 0xF0F0F0F0F0F0F0F0) >> 4);
		c = (c & 0x00FF00FF00FF00FF) + ((c & 0xFF00FF00FF00FF00) >> 8);
		c = (c & 0x0000FFFF0000FFFF) + ((c & 0xFFFF0000FFFF0000) >> 16);
		c = (c & 0x00000000FFFFFFFF) + ((c & 0xFFFFFFFF00000000) >> 32);
		sum += c;
	}
	return sum;
}

unsigned long methodB(const uint8_t* buffer, const size_t fSize)
{
	unsigned long sum = 0;
	char tab2562[256];
	#ifndef VER
	for(uint16_t i = 0; i < 256; ++i)
		tab256[i] = bitcnt16(i);
	#else
	memcpy(tab2562, tab256, 256);
	#endif
	for(size_t i = 0; i < fSize/sizeof(uint8_t); ++i)
		sum += tab2562[buffer[i]];
	return sum;
}

unsigned long methodC(const uint16_t* buffer, const size_t fSize)
{
	unsigned long sum = 0;
	char tab655362[65536];
	#ifndef VER
	for(uint32_t i = 0; i < 65536; ++i)
		tab6553/6[i] = bitcnt16((uint16_t)i);
	#else
	memcpy(tab655362, tab65536, 65536);
	#endif
	for(size_t i = 0; i < fSize/sizeof(uint16_t); ++i)
		sum += tab655362[buffer[i]];
	return sum;
}

int main()
{
	clock_t t;
 	
	FILE *f = fopen("file", "rb");
	fseek (f, 0, SEEK_END);
 	unsigned long fSize = ftell(f);
 	unsigned long* buffer = (unsigned long*) malloc (fSize);
    rewind(f);
 	fread(buffer, 1, fSize, f);
 	fclose(f);

 	unsigned long res;

 	t = clock();
 	res = methodA(buffer, fSize);
 	t = clock() - t;
	printf("MethodA   |   %lu  |  %f\n", res, ((float)t)/CLOCKS_PER_SEC);

	t = clock();
 	res = methodB((uint8_t*)buffer, fSize);
 	t = clock() - t;
	printf("MethodB   |   %lu  |  %f\n", res, ((float)t)/CLOCKS_PER_SEC);
	
	t = clock();
 	res = methodC((uint16_t*)buffer, fSize);
 	t = clock() - t;
	printf("MethodA   |   %lu  |  %f\n", res, ((float)t)/CLOCKS_PER_SEC);
	
	free(buffer);
	return 0;
}