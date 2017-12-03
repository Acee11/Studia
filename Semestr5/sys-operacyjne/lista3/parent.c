#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if(pid) // parent
        sleep(10000);
    else // child
        execve("./child", NULL, NULL);

    return 0;
}