/*
%rsi = &str2
%rsi + 8 = &str2->t
%rsi + 32 = &str2->u

%rdi = &str1
%rdi + 184 = &str1->y

4 < B <= 8
################################################################################

%rax = *(%rsi + 8);
%rax += *(%rsi + 32);
*(%rdi + 184) = %rax;
return %rax;

*/
#include <stdio.h>



long A[5][7][10];

int main()
{
	int i,j,k;
	i = 1;
	j = 2;
	k = 3;
	printf("%d\n%d",&A[1][1][1],	A + (5*7 + 10 + 1));
}
