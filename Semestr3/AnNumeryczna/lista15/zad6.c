#include <lapacke.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5000000

void print_mtrx(double * mtrx, int n, int m)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%f ", mtrx[i*m+j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    clock_t t;
    srand(time(NULL));

    double* diagonal = malloc(N * sizeof(double));
    double* subdiagonal = malloc((N-1) * sizeof(double));
    double* solution = malloc(N * sizeof(double));
    for(size_t i = 0; i < N-1; ++i)
    {
        diagonal[i] = 7.0;
        subdiagonal[i] = 2.0;
        solution[i] = (double)i;
    }
    diagonal[N-1] = 2;
    solution[N-1] = N-1;

    int info;

    t = clock();
    info = LAPACKE_dptsv(LAPACK_ROW_MAJOR, N /*size of matrix*/, 1 /*number of columns in solution*/,
                  diagonal, subdiagonal, solution, 1 /*leading dimension of solution vector*/);
    t = clock() - t;
    printf("N = %d\nTime:  %f\n", N, ((float)t)/CLOCKS_PER_SEC);
    //print_mtrx(solution, N, 1);
    //printf("%d\n", info);
}  