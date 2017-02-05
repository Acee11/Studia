#include <stdio.h>
#include <stdint.h>

void secret(uint8_t *to, uint8_t *from, size_t count){
    size_t n = (count + 7) / 8;
    switch (count % 8) {
    case 0: do{ *to++ = *from++;
    case 7:     *to++ = *from++;
    case 6:     *to++ = *from++;
    case 5:     *to++ = *from++;
    case 4:     *to++ = *from++;
    case 3:     *to++ = *from++;
    case 2:     *to++ = *from++;
    case 1:     *to++ = *from++;
              }while (--n > 0);
    }
}

int main()
{
    uint8_t a=2,b=4;
    size_t count = 8;

    secret(&a, &b, count);

    printf("%d %d",a,b);

    return 0;
}
