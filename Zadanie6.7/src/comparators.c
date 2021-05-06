#include "comparators.h"
#include <stdio.h>
#include <stdlib.h>

#define BIGGER 1
#define EQUAL 0
#define SMALLER -1
#define FAIL 2

#define INCORRECT 1
#define SUCCESS 0

//width wiersze
//height kolumny

int comp_min(const int *ptr1, const int *ptr2, int width)
{
    if (ptr1 == NULL || ptr2 == NULL || width < 1)
        return FAIL;

    int min_ptr1 = *ptr1;
    int min_ptr2 = *ptr2;
    for (int i = 0; i < width; i++)
    {
        if (*(ptr1 + i) < min_ptr1)
            min_ptr1 = *(ptr1 + i);
        if (*(ptr2 + i) < min_ptr2)
            min_ptr2 = *(ptr2 + i);
    }

    return min_ptr1 > min_ptr2 ? BIGGER : min_ptr1 == min_ptr2 ? EQUAL : SMALLER;
}

int comp_max(const int *ptr1, const int *ptr2, int width)
{
    if (ptr1 == NULL || ptr2 == NULL || width < 1)
        return FAIL;

    int max_ptr1 = *ptr1;
    int max_ptr2 = *ptr2;
    for (int i = 0; i < width; i++)
    {
        if (*(ptr1 + i) > max_ptr1)
            max_ptr1 = *(ptr1 + i);
        if (*(ptr2 + i) > max_ptr2)
            max_ptr2 = *(ptr2 + i);
    }

    return max_ptr1 > max_ptr2 ? BIGGER : max_ptr1 == max_ptr2 ? EQUAL : SMALLER;
}

int comp_sum(const int *ptr1, const int *ptr2, int width)
{
    if (ptr1 == NULL || ptr2 == NULL || width < 1)
        return FAIL;

    int sum_ptr1 = 0;
    int sum_ptr2 = 0;
    for (int i = 0; i < width; i++)
    {
        sum_ptr1 += *(ptr1 + i);
        sum_ptr2 += *(ptr2 + i);
    }

    return sum_ptr1 > sum_ptr2 ? BIGGER : sum_ptr1 == sum_ptr2 ? EQUAL : SMALLER;
}

int sort_rows(int **tab, int width, int height, int (*func_name)(const int *ptr1, const int *ptr2, int width))
{
    if (tab == NULL || width < 1 || height < 1 || func_name == NULL)
        return INCORRECT;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - 1; j++)
        {
            if (func_name(*(tab + j), *(tab + j + 1), width) > 0)
            {
                int *tmp = *(tab + j);
                *(tab + j) = *(tab + j + 1);
                *(tab + j + 1) = tmp;
            }
        }
    }

    return SUCCESS;
}