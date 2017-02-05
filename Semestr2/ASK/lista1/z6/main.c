#include <stdio.h>

int main()
{
    int s = 0, j = 2;
    int b[4];
    b[0] = 0;
    b[1] = 1;
    b[2] = 2;
    b[3] = 3;
    int tmp1 = j;
    tmp1 -= 1;
    tmp1 = *(b + tmp1);
    int tmp2 = j;
    tmp2 += 1;
    tmp2 = *(b + tmp2);
    j++;
    s += tmp1;
    s += tmp2;
    printf("%d\n",s);

    int a[4];
    int c[4];
    a[0] = 0;
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    c[0] = 0;
    c[1] = 1;
    c[2] = 2;
    c[3] = 3;
    int i=0;
    int d=2; //b
    j = 1;
    tmp1 = i + 1;
    tmp2 = j;
    tmp2 *= 2;
    tmp2 = *(c + tmp2);
    tmp2 += 1;
    tmp2 *= d;
    *(a + tmp1) -= tmp2;
    i++;

    printf("%d",*(a + tmp1));




    return 0;
}
