/*

*/
#include <stdio.h>

//  B=5    A=9
//

long A[7][5][13];

long store_elem(register long i,register long j,register long k,register long *dest)
{
	*dest = A[i][j][k];
	return sizeof(A);
}

int main()
{
	return 0;
}
