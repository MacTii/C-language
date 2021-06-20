#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

#define INCORRECTv -1
#define CORRECT 0
#define NOT_EMPTY 0
#define INCORRECT 1
#define EMPTY 1
#define FAIL_ALLOCATE 2

struct linked_list_t *ll_create()
{
    struct linked_list_t *list = (struct linked_list_t *)malloc(sizeof(struct linked_list_t));
    if (!list)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

int ll_push_back(struct linked_list_t *ll, int value)
{
    if (!ll)
        return INCORRECT;

    struct node_t *ptr = (struct node_t *)malloc(sizeof(struct node_t));
    if (!ptr)
        return FAIL_ALLOCATE;

    ptr->data = value;

    if (!ll->head)
    {
        ll->head = ptr;
        ll->tail = ptr;
        ptr->next = NULL;
    }
    else
    {
        ll->tail->next = ptr;
        ll->tail = ptr;
        ptr->next = NULL;
    }
    return CORRECT;
}

int ll_push_front(struct linked_list_t *ll, int value)
{
    if (!ll)
        return INCORRECT;
    struct node_t *ptr = (struct node_t *)malloc(sizeof(struct node_t));
    if (!ptr)
        return FAIL_ALLOCATE;

    ptr->data = value;

    if (!ll->head)
    {
        ll->head = ptr;
        ll->tail = ptr;
        ptr->next = NULL;
    }
    else
    {
        ptr->next = ll->head;
        ll->head = ptr;
    }
    return CORRECT;
}

int ll_pop_front(struct linked_list_t *ll, int *err_code)
{
    if (!ll)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    struct node_t *node = ll->head;
    int value, ctrl = 0;
    if (node)
    {
        if (node->next) // 2 lub wiecej
        {
            ll->head = node->next;
            value = node->data;
            free(node);
            ctrl = 1;
        }
        if (!node->next && ctrl == 0) // jak jest 1 element
        {
            value = node->data;
            free(node);
            ll->head = NULL;
            ll->tail = NULL;
        }
    }
    else
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    if (err_code)
        *err_code = CORRECT;
    return value;
}

int ll_pop_back(struct linked_list_t *ll, int *err_code)
{
    if (!ll)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    struct node_t *node = ll->head;
    int value, ctrl = 0;
    if (node) // jak jest jakis element
    {
        if (node->next) // jak sa 2 elementy lub wiecej
        {
            while (node->next->next)
                node = node->next;
            value = node->next->data;
            free(node->next);
            ll->tail = node;
            node->next = NULL;
            ctrl = 1;
        }
        if (!node->next && ctrl == 0) // jak jest 1 element
        {
            value = node->data;
            free(node);
            ll->head = NULL;
            ll->tail = NULL;
        }
    }
    else
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    if (err_code)
        *err_code = CORRECT;
    return value;
}

int ll_back(const struct linked_list_t *ll, int *err_code)
{
    if (!ll || !ll->head || !ll->tail)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    int value = ll->tail->data;
    if (err_code)
        *err_code = CORRECT;
    return value;
}

int ll_front(const struct linked_list_t *ll, int *err_code)
{
    if (!ll || !ll->head || !ll->tail)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    int value = ll->head->data;
    if (err_code)
        *err_code = CORRECT;
    return value;
}

struct node_t *ll_begin(struct linked_list_t *ll)
{
    if (!ll)
        return NULL;
    struct node_t *ptr = ll->head;
    return ptr;
}

struct node_t *ll_end(struct linked_list_t *ll)
{
    if (!ll)
        return NULL;
    struct node_t *ptr = ll->tail;
    return ptr;
}

int ll_size(const struct linked_list_t *ll)
{
    if (!ll)
        return INCORRECTv;
    int size = 0;
    struct node_t *node = ll->head;
    while (node)
    {
        size++;
        node = node->next;
    }
    return size;
}

int ll_is_empty(const struct linked_list_t *ll)
{
    if (!ll)
        return INCORRECTv;
    if (ll_size(ll) == 0)
        return EMPTY;
    return NOT_EMPTY;
}

int ll_at(const struct linked_list_t *ll, unsigned int index, int *err_code)
{
    if (!ll || (int)index >= ll_size(ll) || (int)index < 0)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT;
    }
    if (index == 0)
        return ll_front(ll, err_code);
    if ((int)index == ll_size(ll) - 1)
        return ll_back(ll, err_code);
    struct node_t *node = ll->head;
    int i = 0;
    while (i < (int)index && node)
    {
        node = node->next;
        i++;
    }
    int value = node->data;
    if (err_code)
        *err_code = CORRECT;
    return value;
}

int ll_insert(struct linked_list_t *ll, unsigned int index, int value)
{
    if (!ll || (int)index > ll_size(ll) || (int)index < 0)
        return INCORRECT;

    if (index == 0)
        return ll_push_front(ll, value);
    if ((int)index == ll_size(ll))
        return ll_push_back(ll, value);

    struct node_t *node = ll->head;
    int i = 0;
    while (i < (int)index - 1 && node)
    {
        node = node->next;
        i++;
    }

    struct node_t *ptr = (struct node_t *)calloc(1, sizeof(struct node_t));
    if (!ptr)
        return FAIL_ALLOCATE;

    ptr->next = node->next;
    node->next = ptr;
    ptr->data = value;

    return CORRECT;
}

int ll_remove(struct linked_list_t *ll, unsigned int index, int *err_code)
{
    if (!ll || (int)index >= ll_size(ll) || (int)index < 0)
    {
        if (err_code)
            *err_code = INCORRECT;
        return INCORRECT; // 1
    }

    if (index == 0)
        return ll_pop_front(ll, err_code);
    if ((int)index == ll_size(ll) - 1)
        return ll_pop_back(ll, err_code);

    struct node_t *node = ll->head;
    int i = 0;
    while (i < (int)index - 1 && node)
    {
        node = node->next; //index 7 node na 6 -> 7 [6] node[5] value=node[6]
        i++;
    }
    //4
    int value = node->next->data;
    struct node_t *tmp = node->next; // 4->5 value[5]
    node->next = node->next->next;   //
    free(tmp);                       // 0 1 2 3 4 5 6 indexy node[5]

    if (err_code)
        *err_code = CORRECT;
    return value;
}

void ll_clear(struct linked_list_t *ll)
{
    if (!ll)
        return;
    struct node_t *node = ll->head;
    while (node)
    {
        ll->head = node->next;
        free(node);
        node = ll->head;
    }
    ll->head = NULL;
    ll->tail = NULL;
}

void ll_display(const struct linked_list_t *ll)
{
    if (!ll)
        return;
    struct node_t *node = ll->head;
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
}