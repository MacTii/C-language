#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAIL 1
#define ALLOCATED_MEMORY_FAIL 2

/*0 - je�eli operacja si� powiod�a
2 - je�li nie uda�o si� przydzieli� pami�ci
1 - je�eli dane wej�ciowe by�y niew�a�ciwe.
*/

struct dictionary_t *create_dictionary(int N, int *err_code)
{
    if (N < 1)
    {
        if (err_code)
            *err_code = FAIL;
        return NULL;
    }

    struct dictionary_t *d = (struct dictionary_t *)calloc(1, sizeof(struct dictionary_t));
    if (d == NULL)
    {
        if (err_code)
            *err_code = ALLOCATED_MEMORY_FAIL;
        return NULL;
    }

    d->wc = (struct word_count_t *)calloc(N, sizeof(struct word_count_t));
    if (d->wc == NULL)
    {
        if (err_code)
            *err_code = ALLOCATED_MEMORY_FAIL;
        return free(d), NULL;
    }

    d->size = 0;
    d->capacity = N;

    if (err_code)
        *err_code = SUCCESS;

    return d;
}

void destroy_dictionary(struct dictionary_t **d)
{
    if (d == NULL)
        return;

    for (int i = 0; i < (*d)->size; i++)
        free(((*d)->wc + i)->word);

    free((*d)->wc);
    free(*d);

    *d = NULL;
}

size_t my_strlen(const char *s)
{
    const char *p = s;

    while (*p)
        ++p;

    return p - s;
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

int dictionary_add_word(struct dictionary_t *d, const char *word)
{
    if (d == NULL || d->capacity < 1 || d->size < 0 || d->wc == NULL || word == NULL || d->size > d->capacity)
        return FAIL;

    struct word_count_t *reallocated = NULL;
    struct word_count_t *w = dictionary_find_word(d, word);
    if (w != NULL)
        w->counter++;

    else
    {
        if (d->size == d->capacity)
        {
            reallocated = (struct word_count_t *)realloc(d->wc, sizeof(struct word_count_t) * 2 * d->capacity);
            if (reallocated == NULL)
                return ALLOCATED_MEMORY_FAIL;

            d->wc = reallocated;
            d->capacity *= 2;
        }

        int len = my_strlen(word);
        (d->wc + d->size)->word = (char *)calloc(len + 1, sizeof(char));

        if ((d->wc + d->size)->word == NULL)
            return ALLOCATED_MEMORY_FAIL;

        my_strcpy((d->wc + d->size)->word, word);
        *((d->wc + d->size)->word + len) = '\0';

        (d->wc + d->size)->counter = 1;
        d->size += 1;
    }

    return SUCCESS;
}

int my_strcmp(char *strg1, const char *strg2)
{
    while ((*strg1 != '\0' && *strg2 != '\0') && *strg1 == *strg2)
    {
        strg1++;
        strg2++;
    }

    if (*strg1 == *strg2)
        return 0; // strings are identical

    else
        return *strg1 - *strg2;
}

struct word_count_t *dictionary_find_word(const struct dictionary_t *d, const char *word)
{
    if (d == NULL || d->capacity < 1 || d->size < 0 || d->wc == NULL || word == NULL || d->size > d->capacity)
        return NULL;

    for (int i = 0; i < d->size; i++)
    {
        if (my_strcmp((d->wc + i)->word, word) == 0)
            return d->wc + i;
    }

    return NULL;
}

void dictionary_display(const struct dictionary_t *d)
{
    if (d == NULL || d->size < 0 || d->capacity < 1 || d->size > d->capacity || d->wc == NULL)
        return;

    for (int i = 0; i < d->size; i++)
        printf("%s %d\n", (d->wc + i)->word, (d->wc + i)->counter);
}