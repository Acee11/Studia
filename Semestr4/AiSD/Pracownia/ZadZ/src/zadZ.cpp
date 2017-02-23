#include <cstdio>
#include <algorithm>

int main()
{
	int a,b;
	scanf("%d %d", &a, &b);
	if(a > b)
		std::swap(a,b);

	for(int i = a; i <= b; ++i)
		printf("%d\n",i);

	return 0;
}