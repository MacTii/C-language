#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FAIL 1
#define ALLOCATE_MEM_FAIL 2
#define SUCCESS 0
#define EMPTY_STACK 1
#define INPUT_FAIL_2 2

int stack_init(struct stack_t **stack)
{
    if (!stack)
        return INPUT_FAIL;

    *stack = (struct stack_t *)calloc(1, sizeof(struct stack_t));
    if (!*stack)
        return ALLOCATE_MEM_FAIL;

    (*stack)->head = NULL;

    return SUCCESS;
}

int stack_push(struct stack_t *stack, int value)
{
    if (!stack)
        return INPUT_FAIL;

    struct node_t *node = (struct node_t *)malloc(sizeof(struct node_t));
    if (!node)
        return ALLOCATE_MEM_FAIL;

    node->data = value;

    if (stack->head) // 1 element lub wiecej
    {
        node->next = stack->head;
        stack->head = node;
    }

    else // pusty stos
    {
        stack->head = node;
        node->next = NULL;
    }

    //stack->head->next = NULL;
    return SUCCESS;
}

void stack_display(const struct stack_t *stack)
{
    if (!stack || !stack->head)
        return;
    struct node_t *node = stack->head;
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int stack_pop(struct stack_t *stack, int *err_code)
{
    if (!stack || !stack->head)
    {
        if (err_code)
            *err_code = INPUT_FAIL;
        return INPUT_FAIL;
    }

    struct node_t *node = stack->head;
    int value = node->data;

    stack->head = node->next;
    free(node);

    if (err_code)
        *err_code = SUCCESS;
    return value;
}

void stack_destroy(struct stack_t **stack)
{
    if (!stack)
        return;
    struct node_t *node = (*stack)->head;
    while (node)
    {
        struct node_t *n = node->next; //zapisanie adresu kolejnego elementu
        free(node);                    // czyszczenie pamieci z node
        node = n;                      // zapisanie node jako kolejny element
    }
    free(*stack);
    *stack = NULL;
}

int stack_empty(const struct stack_t *stack)
{
    if (!stack)
        return INPUT_FAIL_2;
    if (!stack->head)
        return EMPTY_STACK;
    return SUCCESS;
}