#include <stdio.h>
#include <stdint.h>
#include <sys/queue.h>

typedef struct lst_node
{
    LIST_ENTRY(lst_node) mb_node;
    int32_t value;
} lst_node_t;

typedef struct lst
{
    LIST_HEAD(, lst_node) ma_freeblks;
    int32_t size;
} lst_t;

int main(void)
{
    int i;
    lst_t mylist;
    lst_node_t n1, n2, n3;
    lst_node_t *it;
    LIST_INIT(&mylist.ma_freeblks);
    LIST_INSERT_HEAD(&mylist.ma_freeblks, &n1, mb_node);
    LIST_INSERT_AFTER(&n1, &n2, mb_node);
    LIST_INSERT_AFTER(&n2, &n3, mb_node);

    i = 0;
    LIST_FOREACH(it, &mylist.ma_freeblks, mb_node)
        it->value = ++i;
    LIST_FOREACH(it, &mylist.ma_freeblks, mb_node)
        printf("%d\n", it->value);

        return 0;
}