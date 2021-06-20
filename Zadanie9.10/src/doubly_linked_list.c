#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

#define CORRECT 0
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
    return CORRECT;
}

int dll_push_front(struct doubly_linked_list_t *dll, int value)
{
    if (!dll)
        return INCORRECT;
    struct node_t *ptr = (struct node_t *)malloc(sizeof(struct node_t));
    if (!ptr)
        return FAILED_MEMORY;
    ptr->data = value;
    ptr->next = dll->head;
    if (dll->head)
    {
        dll->head->prev = ptr;
        ptr->prev = NULL;
    }
    dll->head = ptr;
    if (!dll->tail)
    {
        dll->tail = ptr;
        ptr->prev = NULL;
    }
    return CORRECT;
}

int dll_pop_front(struct doubly_linked_list_t *dll, int *err_code)
{
    if (!dll || !dll->head || !dll->tail)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    struct node_t *ptr = dll->head;
    int value = ptr->data;
    dll->head = ptr->next;
    if (dll->head != 0)
        dll->head->prev = NULL;
    if (ptr->next == 0)
        dll->tail = NULL;
    free(ptr);
    if (err_code)
        *err_code = CORRECT;
    return value;
}

int dll_pop_back(struct doubly_linked_list_t *dll, int *err_code)
{
    if (!dll || !dll->head || !dll->tail)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    struct node_t *ptr = dll->tail;
    int value = ptr->data;
    dll->tail = ptr->prev;
    if (dll->tail != 0)
        dll->tail->next = NULL;
    if (ptr->prev == 0)
        dll->head = NULL;
    free(ptr);
    if (err_code)
        *err_code = CORRECT;
    return value;
}

int dll_back(const struct doubly_linked_list_t *dll, int *err_code)
{
    if (!dll || !dll->head || !dll->tail)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    struct node_t *ptr = dll->tail;
    int value = ptr->data;
    if (err_code)
        *err_code = CORRECT;
    return value;
}

int dll_front(const struct doubly_linked_list_t *dll, int *err_code)
{
    if (!dll || !dll->head || !dll->tail)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    struct node_t *ptr = dll->head;
    int value = ptr->data;
    if (err_code)
        *err_code = CORRECT;
    return value;
}

struct node_t *dll_begin(struct doubly_linked_list_t *dll)
{
    if (!dll)
        return NULL;
    struct node_t *ptr = dll->head;
    return ptr;
}

struct node_t *dll_end(struct doubly_linked_list_t *dll)
{
    if (!dll)
        return NULL;
    struct node_t *ptr = dll->tail;
    return ptr;
}

int dll_size(const struct doubly_linked_list_t *dll)
{
    if (!dll || (!dll->head && dll->tail) || (dll->head && !dll->tail))
        return FAIL; //-1
    int count = 0;
    if (!dll->head && !dll->tail)
        return count;
    struct node_t *ptr = dll->head;
    //if (!ptr->next) return 0;
    count++;
    while (ptr->next)
    {
        count++;
        /*if(ptr->next)*/ ptr = ptr->next;
    }
    return count;
}

int dll_is_empty(const struct doubly_linked_list_t *dll)
{
    if (!dll)
        return FAIL; //-1
    if (dll_size(dll) == 0)
        return EMPTY; //1
    return CORRECT;   //0
}

int dll_at(const struct doubly_linked_list_t *dll, unsigned int index, int *err_code)
{
    if (!dll || !dll->head || !dll->tail)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }

    struct node_t *ptr = dll->head;
    unsigned int i = 0;
    while (i < index && ptr)
    {
        ptr = ptr->next;
        i++;
    }

    if (i != index || !ptr)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }

    int value = ptr->data;

    if (err_code)
        *err_code = CORRECT;
    return value;
}

int dll_insert(struct doubly_linked_list_t *dll, unsigned int index, int value)
{
    if (!dll || (int)index > dll_size(dll) || (int)index < 0)
        return INCORRECT;

    int i;
    struct node_t *node = dll->head;
    //struct node_t* node1=dll->tail;

    for (i = 0; i < (int)index - 1 && node->next; i++)
        node = node->next;

    if (index == 0)
        return dll_push_front(dll, value);
    if ((int)index == dll_size(dll))
        return dll_push_back(dll, value);

    struct node_t *ptr = (struct node_t *)malloc(sizeof(struct node_t));
    if (!ptr)
        return FAILED_MEMORY;

    ptr->data = value;
    ptr->prev = node; // ABCxDEF
    ptr->next = node->next;

    if (node->next)
        node->next->prev = ptr;
    node->next = ptr;

    return CORRECT;
}

int dll_remove(struct doubly_linked_list_t *dll, unsigned int index, int *err_code)
{
    if (!dll || (int)index > dll_size(dll) || (int)index < 0)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }

    int i = 0;
    struct node_t *node = dll->head;

    while (i < (int)index && node)
    {
        i++;
        node = node->next;
    }

    if (index == 0)
        return dll_pop_front(dll, err_code);
    if (!node->next)
        return dll_pop_back(dll, err_code);

    int value = node->data;
    if (node->prev)
        node->prev->next = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node);

    if (err_code)
        *err_code = CORRECT;
    return value;
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