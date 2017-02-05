#include <stdio.h>


typedef struct 
{	
	int x;
	short a[3];
}a_struct;

typedef struct 
{
	long first;
	a_struct a[2];
	long last;
}b_struct;


int main()
{
	a_struct a[4];
	b_struct b;
	int n = (int)&b.last;
	n -= (int) &b.first;

	printf("%d", sizeof(a));	

	return 0;
}