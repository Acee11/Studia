#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define handle_error(str) \
    do {perror(str); exit(EXIT_FAILURE);} while(0)

typedef int (*func_strdrop)(char *str, const char *set);
typedef int (*func_strcnt)(const char *str, const char *set);


int main()
{
    void *libstr;
    if(!(libstr = dlopen("./lib/libstr.so", RTLD_LAZY)))
        handle_error("dlopen");

    func_strdrop strdrop;
    func_strcnt strcnt;

    if(!(strdrop = dlsym(libstr, "strdrop")))
        handle_error("dlsym strdrop");

    if(!(strcnt = dlsym(libstr, "strcnt")))
        handle_error("dlsym strcnt");

    char str1[] = "aqwsedrf";    
    char str2[] = "qwer";   
    char str3[] = "asdf";  
    char set[] = "asdf";
    int ret;

    puts("----------------------- strdrop TEST 1 -----------------------");
    printf("set: %s\n", set);
    printf("before: %s\n", str1);
    ret = strdrop(str1, set);
    printf("after: %s\n", str1);
    printf("return value: %d\n", ret);
    puts("----------------------- strdrop TEST 2 -----------------------");
    printf("set: %s\n", set);
    printf("before: %s\n", str2);
    ret = strdrop(str2, set);
    printf("after: %s\n", str2);
    printf("return value: %d\n", ret);
    puts("----------------------- strdrop TEST 3 -----------------------");
    printf("set: %s\n", set);
    printf("before: %s\n", str3);
    ret = strdrop(str3, set);
    printf("after: %s\n", str3);
    printf("return value: %d\n", ret);


    char str4[] = "aqwsedrffff";    
    char str5[] = "qwer";   
    char str6[] = "asdf"; 

    puts("----------------------- strcnt TEST 1 -----------------------");
    printf("set: %s\n", set);
    printf("str: %s\n", str4);
    ret = strcnt(str4, set);
    printf("return value: %d\n", ret);
    puts("----------------------- strcnt TEST 2 -----------------------");
    printf("set: %s\n", set);
    printf("str: %s\n", str5);
    ret = strcnt(str5, set);
    printf("return value: %d\n", ret);
    puts("----------------------- strcnt TEST 3 -----------------------");
    printf("set: %s\n", set);
    printf("str: %s\n", str6);
    ret = strcnt(str6, set);
    printf("return value: %d\n", ret); 

    sleep(100);

}