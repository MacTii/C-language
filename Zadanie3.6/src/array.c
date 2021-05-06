#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#define INCORRECT 1
#define FAILED_ALLOCATE_MEMORY 2
#define ADD_FAILED 2
#define CORRECT 0

int array_create(struct array_t *a, int N)
{
    if (a == NULL || N <= 0)
        return INCORRECT;
    a->ptr = (int *)malloc(sizeof(int) * N);
    if (a->ptr == NULL)
        return FAILED_ALLOCATE_MEMORY;
    a->capacity = N;
    a->size = 0;
    return CORRECT;
}

int array_push_back(struct array_t *a, int value)
{
    if (a == NULL || a->ptr == NULL || a->size < 0 || a->capacity <= 0 || a->capacity < a->size)
        return INCORRECT;
    if (a->capacity <= a->size)
        return ADD_FAILED;
    *(a->ptr + a->size) = value;
    a->size += 1;
    return CORRECT;
}

void array_display(const struct array_t *a)
{
    if (a == NULL || a->ptr == NULL || a->size <= 0 || a->capacity <= 0 || a->capacity < a->size)
        return;
    int i;
    for (i = 0; i < a->size; i++)
        printf("%d ", *(a->ptr + i));
}

void array_destroy(struct array_t *a)
{
    if (a == NULL)
        return;
    free(a->ptr);
}
