#include "comparators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAIL -2
#define SORT_FAIL 1
#define SORT_SUCCESS 0

int comp_int(const void *ptr1, const void *ptr2)
{
    if (ptr1 == NULL || ptr2 == NULL)
        return FAIL;

    return *(int *)ptr1 > *(int *)ptr2 ? 1 : *(int *)ptr1 == *(int *)ptr2 ? 0 : -1;
}

int comp_double(const void *ptr1, const void *ptr2)
{
    if (ptr1 == NULL || ptr2 == NULL)
        return FAIL;

    return *(double *)ptr1 > *(double *)ptr2 ? 1 : *(double *)ptr1 == *(double *)ptr2 ? 0 : -1;
}

int comp_point(const void *ptr1, const void *ptr2)
{
    if (ptr1 == NULL || ptr2 == NULL)
        return FAIL;

    struct point_t *point_ptr1 = (struct point_t *)ptr1;
    struct point_t *point_ptr2 = (struct point_t *)ptr2;

    return point_ptr1->x > point_ptr2->x ? 1 : point_ptr1->x == point_ptr2->x ? point_ptr1->y == point_ptr2->y ? 0 : point_ptr1->y > point_ptr2->y ? 1 : -1 : -1;
}

void swap(void *ptr1, void *ptr2, int _sizeof)
{
    if (ptr1 == NULL || ptr2 == NULL)
        return;

    char *tmp = (char *)calloc(_sizeof, sizeof(char));
    memcpy(tmp, ptr1, _sizeof);
    memcpy(ptr1, ptr2, _sizeof);
    memcpy(ptr2, tmp, _sizeof);
    free(tmp);
}

int sort(void *tab, int size, int _sizeof, int (*comparator)(const void *, const void *))
{
    if (tab == NULL || comparator == NULL || size < 1)
        return SORT_FAIL;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if ((*comparator)((char *)tab + j * _sizeof, (char *)tab + (j + 1) * _sizeof) > 0)
                swap((char *)tab + j * _sizeof, (char *)tab + (j + 1) * _sizeof, _sizeof);
        }
    }

    return SORT_SUCCESS;
}