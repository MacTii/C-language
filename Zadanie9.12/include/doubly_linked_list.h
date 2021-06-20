#ifndef __DOUBLY_LINKED_LIST_H__
#define __DOUBLY_LINKED_LIST_H__

struct doubly_linked_list_t
{
    struct node_t *head;
    struct node_t *tail;
};

struct node_t
{
    int data;
    struct node_t *next;
    struct node_t *prev;
};

struct doubly_linked_list_t *dll_create();

int dll_push_back(struct doubly_linked_list_t *dll, int value);

int dll_size(const struct doubly_linked_list_t *dll);
int dll_is_empty(const struct doubly_linked_list_t *dll);

void dll_clear(struct doubly_linked_list_t *dll);

void dll_display(const struct doubly_linked_list_t *dll);
void dll_display_reverse(const struct doubly_linked_list_t *dll);

int dll_sort_asc(struct doubly_linked_list_t *dll);
int dll_sort_desc(struct doubly_linked_list_t *dll);

#endif // !__DOUBLY_LINKED_LIST_H__