#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define INCORRECT 1
#define FAILED_MEMORY 2
#define FAIL -1
#define EMPTY 1

struct doubly_linked_list_t *dll_create()
{
    struct doubly_linked_list_t *ptr = (struct doubly_linked_list_t *)malloc(sizeof(struct doubly_linked_list_t));
    if (!ptr)
        return NULL;
    ptr->head = NULL;
    ptr->tail = NULL;
    return ptr;
}

int dll_push_back(struct doubly_linked_list_t *dll, int value)
{
    if (!dll)
        return INCORRECT;
    struct node_t *ptr = (struct node_t *)malloc(sizeof(struct node_t));
    if (!ptr)
        return FAILED_MEMORY;
    ptr->data = value;
    ptr->prev = dll->tail;
    if (dll->tail)
    {
        dll->tail->next = ptr;
        ptr->next = NULL;
    }
    dll->tail = ptr;
    if (!dll->head)
    {
        dll->head = ptr;
        ptr->next = NULL;
    }
    return SUCCESS;
}

int dll_size(const struct doubly_linked_list_t *dll)
{
    if (!dll || (!dll->head && dll->tail) || (dll->head && !dll->tail))
        return FAIL;
    int count = 0;
    if (!dll->head && !dll->tail)
        return count;
    struct node_t *ptr = dll->head;
    count++;
    while (ptr->next)
    {
        count++;
        ptr = ptr->next;
    }
    return count;
}

int dll_is_empty(const struct doubly_linked_list_t *dll)
{
    if (!dll)
        return FAIL; //-1
    if (dll_size(dll) == 0)
        return EMPTY; //1
    return SUCCESS;   //0
}

void dll_clear(struct doubly_linked_list_t *dll)
{
    if (!dll)
        return;
    struct node_t *ptr = dll->head;
    while (ptr)
    {
        dll->head = ptr->next;
        free(ptr);
        ptr = dll->head;
    }
    dll->tail = NULL;
    dll->head = NULL;
}

void dll_display(const struct doubly_linked_list_t *dll)
{
    if (!dll)
        return;
    struct node_t *ptr = dll->head;
    while (ptr)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
}

void dll_display_reverse(const struct doubly_linked_list_t *dll)
{
    if (!dll)
        return;
    struct node_t *ptr = dll->tail;
    while (ptr)
    {
        printf("%d ", ptr->data);
        ptr = ptr->prev;
    }
}

void node_swap(struct node_t *left, struct node_t *right)
{
    if (!left || !right)
        return;

    if (left->prev)
        left->prev->next = right;

    if (right->next)
        right->next->prev = left;

    left->next = right->next;
    right->prev = left->prev;

    right->next = left;
    left->prev = right;
}

int dll_sort_asc(struct doubly_linked_list_t *dll)
{
    if (!dll || dll_is_empty(dll))
        return INCORRECT;

    struct node_t *node = dll->head;
    int n = dll_size(dll);

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n - i; j++)
        {
            if (node->data > node->next->data)
            {
                if (dll->head == node)
                    dll->head = node->next;
                if (dll->tail == node->next)
                    dll->tail = node;
                node_swap(node, node->next);
            }
            else
                node = node->next;
        }
        node = dll->head;
    }

    return SUCCESS;
}

int dll_sort_desc(struct doubly_linked_list_t *dll)
{
    if (!dll || dll_is_empty(dll))
        return INCORRECT;

    struct node_t *node = dll->head;
    int n = dll_size(dll);

    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n - i; j++)
        {
            if (node->data < node->next->data)
            {
                if (dll->head == node)
                    dll->head = node->next;
                if (dll->tail == node->next)
                    dll->tail = node;
                node_swap(node, node->next);
            }
            else
                node = node->next;
        }
        node = dll->head;
    }

    return SUCCESS;
}