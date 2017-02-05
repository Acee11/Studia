%rdi = long i;
%rsi = b_struct *bp;

&b_struct->last = 120;

sizeof(a_struct) = 40;

n = bp->last;
n += bp->first;
a_struct *ap = &bp->first + 5*8*i;	//%rax = &bp->a[i]
%rdx = *(ap + 8);
%rcx = n;
*(bp->a[i] + 8*%rdx + 10) = n;


104 < CNT * sizeof(a_struct) <= 112;

typedef struct 
{
	int first;
	a_struct a[CNT]; &first + 8;
	int last; &first + 120
} b_struct;

void test (long i, b_struct *bp) 
{
	int n = bp->first + bp->last;
	a_struct *ap = &bp->a[i];
	ap->x[ap->idx] = n;
}