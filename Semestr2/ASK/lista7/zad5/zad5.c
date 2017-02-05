#include "stdio.h"

unsigned mulf(unsigned a, unsigned b);

int main()
{
	float t = 2.0;

	// 2.0 = 0x40000000 

	unsigned p;
	p = mulf(0x43CD0800, 0x43CD0800);
	printf("%x\n", p);

	return 0;
}