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

int array_copy(const struct array_t *src, struct array_t *dest)
{
    if (src == NULL || dest == NULL || src->ptr == NULL || src->size < 0 || src->capacity <= 0 || src->size > src->capacity || src == dest)
        return INCORRECT;
    if (!!array_create(dest, src->capacity))
        return ADD_FAILED;
    int i;
    for (i = 0; i < src->size; i++)
        array_push_back(dest, *(src->ptr + i));
    return CORRECT;
}

int array_separate(const struct array_t *a, struct array_t *odd, struct array_t *even)
{
    if (a == NULL || a->ptr == NULL || a->size < 0 || a->capacity <= 0 || a->size > a->capacity || odd == NULL || even == NULL || a == odd || a == even || odd == even)
        return -1;
    int suma_even = 0, suma_odd = 0, i;
    for (i = 0; i < a->size; i++)
    {
        if ((*(a->ptr + i)) % 2 == 0)
            suma_even++;
        else
            suma_odd++;
    }
    if (!(suma_odd && suma_even))
    {
        if (suma_odd)
        {
            if (array_copy(a, odd) == 2)
                return 0;
            return 1;
        }
        if (array_copy(a, even) == 2)
            return 0;
        return 2;
    }
    odd->ptr = (int *)malloc(sizeof(int) * suma_odd);
    if (odd->ptr == NULL)
        return 0;
    even->ptr = (int *)malloc(sizeof(int) * suma_even);
    if (even->ptr == NULL)
    {
        if (suma_odd)
            free(odd->ptr);
        return 0;
    }
    even->capacity = suma_even;
    even->size = suma_even;
    odd->capacity = suma_odd;
    odd->size = suma_odd;
    suma_odd = 0;
    suma_even = 0;
    for (i = 0; i < a->size; ++i)
    {
        if ((*(a->ptr + i)) % 2 == 0)
            *(even->ptr + suma_even++) = *(a->ptr + i);
        else
            *(odd->ptr + suma_odd++) = *(a->ptr + i);
    }
    return 3;
}
