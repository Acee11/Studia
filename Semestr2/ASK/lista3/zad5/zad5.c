#include <stdio.h>

int mul_by_2(int* x)
{
	if ((*x & 0x7f8000000 == 0x7f8000000) && (*x & 0x7fffff) != 0)
	{
		printf("NAN ERROR");
		return *x;
	}
	if (*x == 0 || *x == 0x80000000 || *x == 0xff800000 || *x == 0x7f800000) return *x;

	int z = (*x & 0x7f800000) + 0x800000;
	z &= 0x7f800000;

	*x = (*x & ~0x7f800000) | z;
	return *x;
}

int main(int argc, char **argv)
{
	float f;
	f = 4.0;
	int *x;
	x = &f;
	printf("%x\n",*x);
	printf("%x\n",f);
	*x = mul_by_2(x);

	printf("%x\n",*x);


	return 0;
}