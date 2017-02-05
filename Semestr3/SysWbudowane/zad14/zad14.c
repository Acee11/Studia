/*
Napisz program, który z ciągu liczb typu int bez znaku podanych na standardowe wejście (ciąg kończy się EOF) wypiszę wszystkie te, których negacja bitowa ma co najmniej dwa bity ustawione na jedynkę.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <memory.h>
#define NOSTDIN
#define NOPRINT

int main()
{
	srand(time(NULL));
	size_t size = 100000000;
	unsigned int x;
	unsigned int* buffer = (unsigned int*) malloc(sizeof(int) * size);
	clock_t time1, time2;
	#ifdef STDIN
	size_t n = 0;
	while(scanf("%u", &buffer[n]) != EOF)
		++n;
	#else
	for(size_t i = 0; i < size; ++i)
		buffer[i] = ~(rand()%100);
	#endif

	unsigned int sum1 = 0, sum2 = 0;

	time1 = clock();
	for(size_t i = 0; i < size; ++i)
	{
//		x = buffer[i];
		sum1 += ((buffer[i] | (buffer[i] + 1)) != 0xffffffff);
		//if((x | (x + 1)) != 0xffffffff)
		//{
		//	sum1 += 1;		
		//}

	}
	time1 = clock() - time1;

	time2 = clock();
	for(size_t i = 0; i < size; ++i)
	{
		x = buffer[i];
		char sum = 0;
		unsigned int mask = 1;
		while(mask != 0)
		{
			if((x & mask) == 0)
				sum += 1;
			if(sum == 2)
			{
				sum2 += 1;
				break;
			}
			mask <<= 1;
		}
	}
	time2 = clock() - time2;
	printf("\nMethodA   |    %u    |   %f\n", sum1, ((float)time1)/CLOCKS_PER_SEC);
	printf("\nMethodB   |    %u    |   %f\n", sum2, ((float)time2)/CLOCKS_PER_SEC);
	free(buffer);
	return 0;
}