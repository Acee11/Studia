#include <stdio.h>

typedef struct 
{
	unsigned long lcm, gcd;
} result_t;

result_t lcm_gcd(unsigned long,unsigned long);

int main()
{
	result_t r = lcm_gcd(3,5);
	printf("%ld %ld\n",r.lcm, r.gcd);

	r = lcm_gcd(1,1);
	printf("%ld %ld\n",r.lcm, r.gcd);

	r = lcm_gcd(1,2);
	printf("%ld %ld\n",r.lcm, r.gcd);

	r = lcm_gcd(13 * 5,13);
	printf("%ld %ld\n",r.lcm, r.gcd);

	r = lcm_gcd(1337,7331);
	printf("%ld %ld\n",r.lcm, r.gcd);

	return 0;
}