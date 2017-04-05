//Wojciech Balik
//280254
//KPI
#include <cstdio>
#include <algorithm>


unsigned long fast_fib(unsigned long n, unsigned long m)
{
	unsigned long a[2][2][2] = {{{1, 1}, {1, 0}}};
	unsigned long curr_a = 0, sec_a = 1;

	unsigned long r[2][2][2] = {{{1, 0}, {0, 1}}};
	unsigned long curr_r = 0, sec_r = 1;
	while(n > 0)
	{
		if(n & 1)
		{
			//r *= a;
			r[sec_r][0][0] = (r[curr_r][0][0] * a[curr_a][0][0] + r[curr_r][0][1] * a[curr_a][1][0]) % m; 
			r[sec_r][0][1] = (r[curr_r][0][0] * a[curr_a][0][1] + r[curr_r][0][1] * a[curr_a][1][1]) % m;
			r[sec_r][1][0] = (r[curr_r][1][0] * a[curr_a][0][0] + r[curr_r][1][1] * a[curr_a][1][0]) % m;
			r[sec_r][1][1] = (r[curr_r][1][0] * a[curr_a][0][1] + r[curr_r][1][1] * a[curr_a][1][1]) % m;
			std::swap(sec_r, curr_r);
		}
		//a *= a
		a[sec_a][0][0] = (a[curr_a][0][0] * a[curr_a][0][0] + a[curr_a][0][1] * a[curr_a][1][0]) % m; 
		a[sec_a][0][1] = (a[curr_a][0][0] * a[curr_a][0][1] + a[curr_a][0][1] * a[curr_a][1][1]) % m;
		a[sec_a][1][0] = (a[curr_a][1][0] * a[curr_a][0][0] + a[curr_a][1][1] * a[curr_a][1][0]) % m;
		a[sec_a][1][1] = (a[curr_a][1][0] * a[curr_a][0][1] + a[curr_a][1][1] * a[curr_a][1][1]) % m;
		std::swap(sec_a, curr_a);
		n >>= 1;
	}
	return r[curr_r][1][0];
}

int main()
{
	unsigned long t, n, m;
	scanf("%lu", &t);

	for(unsigned long i = 0; i < t; ++i)
	{
		scanf("%lu %lu", &n, &m);
		printf("%lu\n", fast_fib(n, m));
	}

	return 0;
}