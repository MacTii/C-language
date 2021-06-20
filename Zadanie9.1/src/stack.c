#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1
#define ALLOCATE_MEM_FAIL 2
#define EMPTY_STACK 2

int stack_init(struct stack_t **stack, int N)
{
    if (!stack || N < 1)
        return FAIL;

    *stack = (struct stack_t *)calloc(1, sizeof(struct stack_t));
    if (!*stack)
        return ALLOCATE_MEM_FAIL;

    (*stack)->data = (int *)calloc(N, sizeof(int));
    if (!(*stack)->data)
    {
        free(*stack);
        *stack = NULL;
        return ALLOCATE_MEM_FAIL;
    }

    (*stack)->head = 0;
    (*stack)->capacity = N;

    return SUCCESS;
}

int stack_push(struct stack_t *stack, int value)
{
    if (!stack || !stack->data || stack->head < 0 || stack->capacity < 1 || stack->head > stack->capacity)
        return FAIL;

    if (stack->capacity == stack->head)
    {
        size_t cap = stack->capacity * 2;

        int *p = (int *)realloc(stack->data, sizeof(int) * cap);
        if (!p)
            return ALLOCATE_MEM_FAIL;

        stack->capacity = cap;
        stack->data = p;
    }

    *(stack->data + stack->head) = value;
    ++stack->head;

    return SUCCESS;
}

int stack_pop(struct stack_t *stack, int *err_code)
{
    if (!stack || !stack->data || stack->head < 0 || stack->capacity < 1 || stack->head > stack->capacity)
    {
        if (err_code)
            *err_code = FAIL;
        return FAIL;
    }

    if (stack->head == 0)
    {
        if (err_code)
            *err_code = EMPTY_STACK;
        return EMPTY_STACK;
    }

    int value = *(stack->data + stack->head - 1);
    --stack->head;

    if (err_code)
        *err_code = SUCCESS;
    return value;
}

void stack_display(const struct stack_t *stack)
{
    if (!stack || !stack->data || stack->head <= 0 || stack->capacity < 1 || stack->head > stack->capacity)
        return;
    for (int i = stack->head - 1; i >= 0; i--)
        printf("%d ", *(stack->data + i));
    printf("\n");
}

void stack_free(struct stack_t *stack)
{
    if (!stack || !stack->data || stack->head < 0 || stack->capacity < 1 || stack->head > stack->capacity)
        return;
    free(stack->data);
    free(stack);
    stack = NULL;
}
