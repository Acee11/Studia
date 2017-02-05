#include <stdio.h>

long switch_prob(long x, long n)	// %rdi = x		%rsi = n
{
	long res;
	n -= 0x3c;
	switch(n)
	{
		case 0:
		case 1:
			return 8*x;
		case 4:
			res = x;
			res >>= 3;
			return res;
		case 2:
			res = x;
			res <<= 4;
			res -= x;
			x = res;
		case 5:
			x *= x;
		case 3:
		default:
			res = x + 0x4b;
	}
	return res;
}


int main()
{
	long r = switch_prob(1,0x3c);
	printf("%ld\n",r);

	return 0;
}