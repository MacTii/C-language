#include "circular_buffer.h"
#include <stdlib.h>
#include <stdio.h>

#define CORRECT 0
#define FAILED_INPUT 1
#define FAILED_ALLOCATE 2
#define INCORRECT -1
#define FULL_BUFFER 1
#define EMPTY 1
#define ERR_CODE_1 1
#define ERR_CODE_2 2

int circular_buffer_create(struct circular_buffer_t *a, int N)
{
    if (a == NULL || N <= 0)
        return FAILED_INPUT;
    a->ptr = (int *)calloc(N, sizeof(int));
    if (a->ptr == NULL)
        return FAILED_ALLOCATE;
    a->begin = 0;
    a->end = 0;
    a->capacity = N;
    a->full = 0;
    return CORRECT;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N)
{
    if (cb == NULL || N <= 0)
        return FAILED_INPUT;
    *cb = (struct circular_buffer_t *)malloc(sizeof(struct circular_buffer_t));
    if (*cb == NULL)
        return FAILED_ALLOCATE;
    if (circular_buffer_create(*cb, N))
    {
        free(*cb);
        return FAILED_ALLOCATE;
    }
    return CORRECT;
}

void circular_buffer_destroy(struct circular_buffer_t *a)
{
    if (a != NULL)
        free(a->ptr);
}

void circular_buffer_destroy_struct(struct circular_buffer_t **a)
{
    if (a != NULL)
    {
        circular_buffer_destroy(*a);
        free(*a);
    }
}

int circular_buffer_push_back(struct circular_buffer_t *cb, int value)
{
    if (cb == NULL || cb->ptr == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity <= 0 || cb->capacity <= cb->end || cb->capacity <= cb->begin)
        return FAILED_INPUT;
    *((cb->ptr) + (cb->end)) = value;
    cb->end = (cb->end + 1) % cb->capacity;
    if (circular_buffer_full(cb))
        cb->begin = (cb->begin + 1) % cb->capacity;
    if (cb->begin == cb->end)
        cb->full = 1;
    return CORRECT;
}

int circular_buffer_pop_front(struct circular_buffer_t *a, int *err_code)
{
    if (a == NULL || a->ptr == NULL || a->begin < 0 || a->end < 0 || a->capacity <= 0 || a->capacity <= a->end || a->capacity <= a->begin)
    {
        if (err_code != NULL)
            *err_code = 1;
        return ERR_CODE_1;
    }
    if (circular_buffer_empty(a))
    {
        if (err_code != NULL)
            *err_code = 2;
        return ERR_CODE_2;
    }
    int number = *(a->ptr + a->begin);
    a->begin = (a->begin + 1) % a->capacity;
    if (circular_buffer_full(a))
        a->full = 0;
    if (err_code != NULL)
        *err_code = 0;
    return number;
}

int circular_buffer_pop_back(struct circular_buffer_t *a, int *err_code)
{
    if (a == NULL || a->ptr == NULL || a->begin < 0 || a->end < 0 || a->capacity <= 0 || a->capacity <= a->end || a->capacity <= a->begin)
    {
        if (err_code != NULL)
            *err_code = 1;
        return ERR_CODE_1;
    }
    if (circular_buffer_empty(a))
    {
        if (err_code != NULL)
            *err_code = 2;
        return ERR_CODE_2;
    }
    a->end = (a->end + a->capacity - 1) % a->capacity;
    int number = *(a->ptr + a->end);
    if (circular_buffer_full(a))
        a->full = 0;
    if (err_code != NULL)
        *err_code = 0;
    return number;
}

int circular_buffer_empty(const struct circular_buffer_t *a)
{
    if (a == NULL || a->ptr == NULL || a->capacity <= 0 || a->begin < 0 || a->end < 0 || a->begin >= a->capacity || a->end >= a->capacity)
        return INCORRECT;
    if (a->full == 0 && a->begin == a->end)
        return EMPTY;
    return CORRECT;
}

int circular_buffer_full(const struct circular_buffer_t *a)
{
    if (a == NULL || a->ptr == NULL || a->capacity <= 0 || a->begin < 0 || a->end < 0 || a->begin >= a->capacity || a->end >= a->capacity)
        return INCORRECT;
    return a->full;
}

void circular_buffer_display(const struct circular_buffer_t *a)
{
    if (a == NULL || a->ptr == NULL || a->capacity <= 0 || a->begin < 0 || a->end < 0 || a->begin >= a->capacity || a->end >= a->capacity || circular_buffer_empty(a))
        return;
    int i;
    if (a->begin < a->end)
    {
        for (i = a->begin; i < a->end; i++)
            printf("%d ", *(a->ptr + i));
    }
    else
    {
        for (i = a->begin; i < a->capacity; i++)
            printf("%d ", *(a->ptr + i));
        for (i = 0; i < a->end; i++)
            printf("%d ", *(a->ptr + i));
    }
}
