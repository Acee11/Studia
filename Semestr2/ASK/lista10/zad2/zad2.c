#include <stdint.h>
#include <stdint.h>

int randwalk(uint8_t *arr, int n, int len);

int randwalk2(uint8_t *arr, int n, int len) 
{
	int sum = 0, k = 0;
	uint64_t dir = 0;
	int i = fast_random() % n;
	int j = fast_random() % n;
	

	do 
	{
		k -= 2;
		if (k < 0) 
		{
			k = 62;
			dir = fast_random();
		}

		int	d = (dir >> k) & 3;

		sum += arr[i * n + j];

		if (d == 0)  ////////////
		{
			if (i > 0)
			i--;
		} 
		else if (d == 1) ///////////
		{	
			if (i < n - 1)
			i++;
		} 
		else if (d == 2) /////////
		{
			if (j > 0)
				j--;
		} 
		else 
		{
			if (j < n - 1)
				j++;
		}
	} while (--len);

	return sum;
}


int main()
{
	int n = 1000;
	uint8_t *ptr = malloc(n);

	randwalk2(ptr, 100, n);



	return 0;
}