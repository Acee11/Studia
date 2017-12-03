#include <strcnt.h>

int strcnt(const char *str, const char *set)
{
    int cnt = 0, len = strlen(str);
    for(int i = 0; i < len; ++i)
        if(strchr(set, str[i]))
            ++cnt;
    return cnt;
}