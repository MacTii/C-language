#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define INCORRECT 1
#define ERR_MEM 2
#define ERR_FILE 2
#define ALLOCATE_FAIL 3

int stack_push(struct stack_t **stack, char *value)
{
    if (!stack || !value)
        return INCORRECT;

    struct stack_t *node = (struct stack_t *)malloc(sizeof(struct stack_t));
    if (!node)
        return ERR_MEM;

    if (*stack)
    {
        node->prev = *stack;
        node->sentence = value;
        *stack = node;
    }

    else
    {
        node->sentence = value;
        *stack = node;
        (*stack)->prev = NULL;
    }

    return SUCCESS;
}

char *stack_pop(struct stack_t **stack, int *err_code)
{
    if (!stack || !*stack)
    {
        if (err_code)
            *err_code = INCORRECT;
        return NULL;
    }

    char *val = (*stack)->sentence;

    struct stack_t *node = *stack;
    *stack = node->prev;

    free(node);

    if (err_code)
        *err_code = SUCCESS;
    return val;
}

void stack_destroy(struct stack_t **stack)
{
    if (!stack)
        return;

    struct stack_t *previous;
    while (*stack)
    {
        free((*stack)->sentence);
        previous = (*stack)->prev;
        free(*stack);
        *stack = previous;
    }
    *stack = NULL;
}

int stack_load(struct stack_t **stack, const char *filename)
{
    if (!stack || !filename || *stack)
        return INCORRECT;

    FILE *f;
    f = fopen(filename, "r");
    if (!f)
        return ERR_FILE;

    char *sntc = (char *)calloc(1, sizeof(char));
    if (!sntc)
    {
        fclose(f);
        return ALLOCATE_FAIL;
    }

    char *buff = NULL;
    int size = 0;

    while (!feof(f))
    {
        size += 1;
        buff = realloc(sntc, sizeof(char) * (size + 1));

        if (!buff)
        {
            stack_destroy(stack);
            free(sntc);
            fclose(f);
            return ALLOCATE_FAIL;
        }

        sntc = buff;

        char c = fgetc(f);

        if (c == '.')
        {
            *(sntc + size - 1) = '.';
            *(sntc + size) = '\0';
            if (stack_push(stack, sntc) > 0 ? 1 : 0) // == !!
            {
                stack_destroy(stack);
                free(sntc);
                fclose(f);
                return ALLOCATE_FAIL;
            }
            sntc = (char *)malloc(sizeof(char));
            size = 0;
        }
        else
            *(sntc + size - 1) = c;
    }

    free(sntc);
    fclose(f);

    return SUCCESS;
}

int stack_save(const struct stack_t *stack, const char *filename)
{
    if (!stack || !filename)
        return INCORRECT;

    FILE *f;
    f = fopen(filename, "w");
    if (!f)
        return ERR_FILE;

    while (stack)
    {
        fprintf(f, "%s", stack->sentence);
        stack = stack->prev;
    }

    fclose(f);

    return SUCCESS;
}
