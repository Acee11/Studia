#include "./include/mylist.h"

void list_init(list_t *list)
{
    list->begin = list->end = NULL;
    list->size = 0;
}

bool list_search(list_t *list, int value)
{
    if (list->size == 0)
        return false;
    if(list->size > 1)
        assert(list->begin != list->end);
    const node_t *curr;
    for (curr = list->begin; curr != NULL; curr = curr->next)
        if (curr->value == value)
            return true;
    return false;
}

void list_append(list_t *list, int value)
{
    if(list->size > 1)
        assert(list->begin != list->end);
    node_t *new_node = malloc(sizeof(node_t));
    if(!new_node)
        handle_error("malloc");
    new_node->value = value;
    new_node->next = NULL;

    if (list->end == NULL)
    {
        assert(list->begin == NULL);
        assert(list->size == 0);
        list->begin = list->end = new_node;
        list->size = 1;
    }
    else
    {
        assert(list->size >= 1);
        assert(list->begin != NULL);
        list->end->next = new_node;
        list->end = new_node;
        ++list->size;
    }
}

void list_remove(list_t *list, int value)
{
    if(list->size == 0)
    {
        assert(list->begin == NULL && list->end == NULL);
        return;
    }

    node_t *curr = list->begin;
    node_t *prev = NULL;

    while(curr)
    {
        if(curr->value == value)
            break;
        prev = curr;
        curr = curr->next;
    }
    if(!curr) //not found
        return;
    if(!prev)
    {
        if(list->size == 1)
        {
            assert(list->begin == list->end);
            free(list->begin);
            list->begin = list->end = NULL;
        }
        else
        {
            assert(list->begin != list->end);
            node_t *second = list->begin->next;
            free(list->begin);
            list->begin = second;

        }
        --list->size;
        return;
    }

    if(curr == list->end)
        list->end = prev;
    prev->next = curr->next;
    free(curr);
    --list->size;
}

void list_remove1(list_t *list, int value)
{
    if (list->size == 0)
        return;
    if(list->size > 1)
        assert(list->begin != list->end);
    if (list->begin->value == value)
    {
        if (list->begin == list->end)
        {
            assert(list->size == 1);
            free(list->begin);
            list->begin = list->end = NULL;
        }
        else
        {
            assert(list->begin != NULL);
            assert(list->begin->next != NULL);
            node_t *second = list->begin->next;
            free(list->begin);
            list->begin = second;
        }
        --list->size;
        return;
    }

    if (list->end->value == value)
    {
        if (list->begin == list->end)
        {
            assert(list->size == 1);
            free(list->begin);
            list->begin = list->end = NULL;
        }
        else
        {
            node_t *curr = list->begin;
            while(curr->next != list->end)
                curr = curr->next;
            free(list->end);
            curr->next = NULL;
            list->end = curr;
        }
        --list->size;
        return;
    }
    if (list->size < 3)
        return;

    node_t *curr = list->begin;
    for (; curr->next != list->end; curr = curr->next)
    {
        if (curr->next->value == value)
        {
            node_t *next = curr->next->next;
            free(curr->next);
            curr->next = next;
            break;
        }
    }

}

void list_print(list_t *list)
{
    node_t *curr = list->begin;
    for (; curr != NULL; curr = curr->next)
        printf("%d ", curr->value);
    putchar('\n');
    fflush(stdout);
}