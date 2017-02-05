#include <stdio.h>

int main()
{
    unsigned int x,i,j,y;
    scanf("%u %u %u",&x, &i, &j);
    x = 0xf;
    printf("%u\n",x);
    y = (~0 & (x & (1 << i))) >> i;
    x = (x & ~(1 << j)) | (y<<j);

    printf("%u\n",x);

    return 0;
}
