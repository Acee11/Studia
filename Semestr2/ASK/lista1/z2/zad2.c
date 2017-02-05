#include <stdio.h>

void write(unsigned int x)
{
    char tab[32];
    int i = 31,j;
    for(;i>=0;i--)
    {
        tab[i]=x&1;
        x>>=1;
    }
    for(i=24;i>=0;i-=8)
    {
        for(j=0;j<8;j++)
        {
            printf("%d",tab[i+j]);
            if(j==3)printf(" ");
        }
        printf(" ");
    }
    printf("\n");
}

int main()
{
    unsigned int i;
    i = 0xffffffff;
    write(i);
    i = ((i & 0xAAAAAAAA) >>  1) + (i & 0x55555555);
    write(i);
    i = ((i & 0xCCCCCCCC) >>  2) + (i & 0x33333333);
    write(i);
    i = ((i & 0xF0F0F0F0) >>  4) + (i & 0x0F0F0F0F);
    write(i);
    i = ((i & 0xFF00FF00) >>  8) + (i & 0x00FF00FF);
    write(i);
    i = ((i & 0xFFFF0000) >> 16) + (i & 0x0000FFFF);
    write(i);
    printf("%u",i);

    return 0;
}
