#include <stdio.h>

union elem 
{
	struct
	{
		long *p;
		long y;
	} e1;

	struct 
	{
		long x;
		union elem *next;
	} e2;
};

void proc(union elem *p)
{
/*
	union elem *n = p->e2.next;//	movq 8(%rdi), %rax		%rax - adres jakiejś unii
	long *pointer = n->e1.p;//		movq (%rax),  %rdx		%rdx - 
	long l = *pointer;
	l -= n->e1.y;
	p->e2.x = l;
*/
	p->e2.x = *p->e2.next->e1.p;
	return;
}

int main()
{
	//printf("%d", sizeof(union elem));   16
	long k = 1337;
	union elem b;
	b.e1.p = &k;
	b.e1.y = 4;
	union elem e;
	e.e2.x = 20;
	e.e2.next = &b;
	printf("%u  %u\n%u  %u\n\n",e.e2.x, e.e2.next, b.e1.p, b.e1.y);
	proc(&e);
	printf("%u  %u\n%u  %u",e.e2.x, e.e2.next, b.e1.p, b.e1.y);

	return 0;
}