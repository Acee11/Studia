#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node
{
    int value;
    struct node *next;

} node_t;

typedef struct
{
    size_t size;
    node_t *begin;
    node_t *end;
} list_t;

void list_init(list_t *list);
bool list_search(list_t *list, int value);
void list_append(list_t *list, int value);
void list_remove(list_t *list, int value);
void list_print(list_t *list);