#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    char negative = (n<0);
    if(negative) n =- n;
    char bin[24] = {0};
    int i = 23,j=23;
	
    while(n)
    {
        bin[i] = n%2;
        n /= 2;
        i--;
    }
    if(negative)
    {
        for(i = 0; i < 24; i++)
        {
            if(bin[i] == 0) bin[i] = 1;
            else if(bin[i] == 1) bin[i] = 0;
        }
        i = 23;
        char carry = (bin[23]+1)/2;
        if(!carry) bin[23]++;
        while(carry)
        {
            bin[i]+=carry;
            carry = bin[i]/2;
            bin[i] %= 2;
            i--;
        }
    }
    for(i = 0; i < 24; i++)
    {
        printf("%d",(int)bin[i]);
    }
    return 0;
}
