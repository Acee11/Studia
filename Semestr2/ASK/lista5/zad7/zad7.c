#include <stdio.h>

typedef struct 
{
	long a[2];
	long *p;
} strA;

typedef struct 
{
	long u[2];
	long q;
} strB;

strB process(strA s)	//%rdi = s
{
	strB b;
	return b;
}

long eval(long x, long y, long z)
{
	strA s;
	s.a[0] = x;
	s.a[1] = y;
}

int main()
{
	printf("%x\n",0x400590 + 0x33);
	strA a;
	//process(a);

	return 0;
}