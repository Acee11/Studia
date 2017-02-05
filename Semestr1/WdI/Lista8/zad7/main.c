#include <stdio.h>


void Hanoi1(int src, int dst, int n)
{
    int helper = 6 - (src + dst);   // calculate helper

    if (n == 1)
        printf("%d => %d\n", src, dst);
    else
    {

        Hanoi1(src, helper, n-1);
        Hanoi1(src, dst, 1);
        Hanoi1(helper, dst, n-1);
    }
}

void hanoi(int n ,int *a, int *b, int *c)
{
    int i;
    for(i = 0; i < n; i++) printf("%d ",a[i]);
    putchar('\n');
    for(i = 0; i < n; i++) printf("%d ",b[i]);
    putchar('\n');
    for(i = 0; i < n; i++) printf("%d ",c[i]);
    putchar('\n');

    for(i = 0; i < n && a[i] != n; i++);
    int j;

    if(i == n-1)
    {
        for(j = 1; j < n; j++)
        {
            if (c[j] == 0 && c[j-1] > a[i])
                break;
        }
        if (j != n-1)
        {
            c[j] = a[i];
            a[i] = 0;
        }
    }
    else




}

int main()
{
    /*
    int n, i;
    scanf("%d", &n);
    int a[n], b[n], c[n];
    for (i=0; i<n; i++)
    {
        a[i] = n-i;
        b[i] = 0;
        c[i] = 0;
    }

    hanoi(n, a, b, c);
    */
    int i;

    printf("1 - palik zrodlowy\n");
    printf("2 - palik pomocniczy\n");
    printf("3 - palik docelowy\n");
    printf("Ile krazkow przeniesc? ");
    scanf("%d", &i);

    Hanoi1(1, 3, i);


    return 0;
}
