#include <stdio.h>

int main(int argc, char **argv)
{
	unsigned int x = 3;
	x *= 0x55555556;
	printf("%u\n",x>>1);


	return 0;
}