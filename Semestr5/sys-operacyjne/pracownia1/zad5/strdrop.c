#include <strdrop.h>

int strdrop(char *str, const char *set)
{
    int i;
    int pos = 0, len = strlen(str);
    for(i = 0; i < len; ++i)
        if(!strchr(set, str[i]))
            str[pos++] = str[i];
    str[pos] = '\0';
    return pos;
}