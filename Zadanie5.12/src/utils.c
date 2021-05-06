#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define FAIL 1
#define SUCCESS 0

size_t my_strlen(const char *s)
{
    const char *p = s;

    while (*p)
        ++p;

    return p - s;
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

void destroy(char **words)
{
    if (words == NULL)
        return;

    for (int i = 0; *(words + i); i++)
        free(*(words + i));

    free(words);
}

char **split_words(const char *text)
{
    if (text == NULL || (int)my_strlen(text) == 0)
        return NULL;

    char **result = (char **)calloc(1, sizeof(char *));
    if (result == NULL)
        return NULL;

    int len_word = 0, count = 0;
    for (int i = 0;; i++)
    {
        if (isalpha(*(text + i)))
            len_word++;

        else if (!isalpha(*(text + i)) && len_word > 0)
        {
            char **re_result = (char **)realloc(result, sizeof(char *) * (count + 2));
            if (re_result == NULL)
                return *(result + count) = NULL, destroy(result), NULL;

            result = re_result;

            *(result + count) = (char *)calloc(len_word + 1, sizeof(char));
            if (*(result + count) == NULL)
                return destroy(result), NULL;

            count++;
            len_word = 0;
        }
        if (*(text + i) == '\0')
            break;
    }
    if (count == 0)
        return free(result), NULL;

    *(result + count) = NULL;

    len_word = 0, count = 0;
    for (int i = 0; *(text + i); i++)
    {
        if (isalpha(*(text + i)))
            *(*(result + count) + len_word++) = *(text + i);

        else if (!isalpha(*(text + i)) && len_word > 0)
        {
            *(*(result + count++) + len_word) = '\0';
            len_word = 0;
        }
    }

    return result;
}

int sort_words(char **words)
{
    if (words == NULL)
        return FAIL;

    int len = 0;
    for (int i = 0; *(words + i); i++)
        len++;

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - 1; j++)
        {
            if (my_strcmp(*(words + j), *(words + j + 1)) > 0)
            {
                char *tmp = *(words + j);
                *(words + j) = *(words + j + 1);
                *(words + j + 1) = tmp;
            }
        }
    }

    return SUCCESS;
}