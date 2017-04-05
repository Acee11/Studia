//Wojciech Balik
//280254
//KPI

#include <cstdio>

int main()
{
	int a,b;
	scanf("%d %d", &a, &b);

	if(a%2 == 0)
		++a;
	for(; a <= b; a += 2)
		printf("%d ", a);

	return 0;
}