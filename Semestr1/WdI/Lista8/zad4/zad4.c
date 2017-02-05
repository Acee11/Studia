#include <stdio.h>
#include <stdlib.h>

int min(int *tab,int l, int r)
{
    if (l==r) return tab[l];
    int a = min(tab,l,(l+r)/2),b = min(tab,((l+r)/2)+1,r);
    if (a < b) return a;
    else return b;
}

int main()
{
    int tab[10] = {4,5,6,7,8,9,-100,88,55,33};
    printf("%d",min(tab,0,9));


    return 0;
}
