#include "big_numbers.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SUCCESS 0
#define FAIL 1
#define ALLOCATED_MEMORY_FAIL 2
#define BUFFER_FULL 3

size_t my_strlen(const char *s)
{
    const char *p = s;

    while (*p)
        ++p;

    return p - s;
}

int validate(const char *number)
{
    if (number == NULL)
        return FAIL;

    bool is_negative = 0;
    int len = my_strlen(number);

    if (len < 1)
        return FAIL;

    if (*number == '-')
        is_negative = 1;

    if (is_negative && len < 2)
        return FAIL;

    if (*number == '0' && len > 1)
        return FAIL;

    for (int i = is_negative ? 1 : 0; i < len; i++)
        if (*(number + i) < '0' || *(number + i) > '9')
            return FAIL;

    return SUCCESS;
}

int create(struct big_numbers_t *bn, int capacity)
{
    if (bn == NULL || capacity < 1)
        return FAIL;

    bn->big_number = (char **)calloc(capacity, sizeof(char *));

    if (bn->big_number == NULL)
        return ALLOCATED_MEMORY_FAIL;

    bn->size = 0;
    bn->capacity = capacity;

    return SUCCESS;
}

int create_big_numbers(struct big_numbers_t **bn, int capacity)
{
    if (bn == NULL || capacity < 1)
        return FAIL;

    *bn = (struct big_numbers_t *)calloc(1, sizeof(struct big_numbers_t));
    if (*bn == NULL)
        return ALLOCATED_MEMORY_FAIL;

    int error = create(*bn, capacity);
    if (error == FAIL || error == ALLOCATED_MEMORY_FAIL)
        return free(*bn), *bn = NULL, ALLOCATED_MEMORY_FAIL;

    return SUCCESS;
}

void destroy(struct big_numbers_t *bn)
{
    if (bn == NULL || bn->size < 0 || bn->capacity < 1 || bn->big_number == NULL || bn->size > bn->capacity)
        return;

    for (int i = 0; i < bn->size; i++)
        free(*(bn->big_number + i));

    free(bn->big_number);
}

void destroy_big_numbers(struct big_numbers_t **bn)
{
    if (*bn == NULL || (*bn)->size < 0 || (*bn)->capacity < 1 || (*bn)->size > (*bn)->capacity || (*bn)->big_number == NULL)
        return;

    destroy(*bn);
    free(*bn);
    *bn = NULL;
}

char *my_strcpy(char *destination, const char *source)
{
    char *start = destination;

    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }

    *destination = '\0'; // add '\0' at the end
    return start;
}

int add_big_number(struct big_numbers_t *bn, const char *big_number)
{
    if (bn == NULL || big_number == NULL || bn->big_number == NULL || bn->size < 0 || bn->capacity < 1 || bn->size > bn->capacity || validate(big_number))
        return FAIL;

    if (bn->size == bn->capacity)
        return BUFFER_FULL;

    *(bn->big_number + bn->size) = (char *)calloc(my_strlen(big_number) + 1, sizeof(char));
    if (*(bn->big_number + bn->size) == NULL)
        return ALLOCATED_MEMORY_FAIL;

    my_strcpy(*(bn->big_number + bn->size), big_number);

    bn->size++;

    return SUCCESS;
}

void display(const struct big_numbers_t *bn)
{
    if (bn == NULL || bn->size < 0 || bn->capacity < 1 || bn->big_number == NULL || bn->size > bn->capacity)
        return;

    for (int i = 0; i < bn->size; i++)
        printf("%s\n", *(bn->big_number + i));
}