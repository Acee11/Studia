#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include <limits.h>

int main(int argc, char **argv)
{
	unsigned int x = -10;
	float f = 256.0;
	x = *(&f);
	x ^= 0x80000000;
	f = *(&x);

	printf("%f",f);
	/*
	f ^= 0x80000000;
	printf("%f\n\n\n",f);
	double d = 0.1;
	//printf("%f\n",d);
	//printf("%d\n", (f + d) - f == d);
	printf("%d\n",d == (double)(float)d);

	while(1)
	{
		if (!(d == (double)(float)d))
			{
				printf("%f %f",d, (double)(float)d);	
				break;
			}
		d+=0.1;
	}
	
*/
	return 0;
}