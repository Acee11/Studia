//Wojciech Balik
//280254
//KPI
#include <cstdio>

unsigned long long power(unsigned long long a, unsigned long long b, unsigned long long m)
{
	a %= m;
	unsigned long long r = 1;
	while(b > 0)
	{
		if(b & 1)
			r = (r * a) % m;
		a = (a * a) % m;
		b >>= 1;
	}
	return r % m;
}

int main()
{
	unsigned long long t, a, b, m;
	scanf("%llu", &t);

	for(unsigned long long i = 0; i < t; ++i)
	{
		scanf("%llu %llu %llu", &a, &b, &m);
		printf("%llu\n", power(a, b, m));
	}

	return 0;
}