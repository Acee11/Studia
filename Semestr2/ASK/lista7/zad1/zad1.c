#include <stdio.h>

long clz(long);

int main()
{
	printf("%ld\n", clz(~0));

	return 0;
}