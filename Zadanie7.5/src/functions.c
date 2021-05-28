#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

char **text_modifier(const char *text, int args, ...)
{
    if (!text || args < 1)
        return NULL;

    char **res = (char **)calloc(args + 1, sizeof(char *));
    if (!res)
        return NULL;

    va_list ap;
    va_start(ap, args);

    typedef char *(*fun_mod)(const char *);

    for (int i = 0; i < args; i++)
    {
        fun_mod current = va_arg(ap, fun_mod);
        *(res + i) = current(text);
        if (!*(res + i))
        {
            free_texts(res);
            return va_end(ap), NULL;
        }
    }
    va_end(ap);
    return res;
}

char *lower_to_upper(const char *in)
{
    if (!in)
        return NULL;

    char *res = (char *)calloc((int)strlen(in) + 1, sizeof(char));
    if (!res)
        return NULL;

    int tmp = 0;
    for (int i = 0; i < (int)strlen(in); i++)
    {
        if (isalpha(*(in + i)) && islower(*(in + i)))
        {
            *(res + i) = toupper(*(in + i));
            tmp = 1;
        }
        if (tmp == 0)
            *(res + i) = *(in + i);
        tmp = 0;
    }
    //*(res+strlen(in)) = '\0';
    return res;
}

char *upper_to_lower(const char *in)
{
    if (!in)
        return NULL;

    char *res = (char *)calloc((int)strlen(in) + 1, sizeof(char));
    if (!res)
        return NULL;

    int tmp = 0;
    for (int i = 0; i < (int)strlen(in); i++)
    {
        if (isalpha(*(in + i)) && isupper(*(in + i)))
        {
            *(res + i) = tolower(*(in + i));
            tmp = 1;
        }
        if (tmp == 0)
            *(res + i) = *(in + i);
        tmp = 0;
    }

    return res;
}

char *space_to_dash(const char *in)
{
    if (!in)
        return NULL;

    char *res = (char *)calloc((int)strlen(in) + 1, sizeof(char));
    if (!res)
        return NULL;

    int tmp = 0;
    for (int i = 0; i < (int)strlen(in); i++)
    {
        if (*(in + i) == ' ')
        {
            *(res + i) = '_';
            tmp = 1;
        }
        if (tmp == 0)
            *(res + i) = *(in + i);
        tmp = 0;
    }

    return res;
}

char *reverse_letter(const char *in)
{
    if (!in)
        return NULL;

    char *res = (char *)calloc((int)strlen(in) + 1, sizeof(char));
    if (!res)
        return NULL;

    int tmp = 0;
    for (int i = 0; i < (int)strlen(in); i++)
    {
        if (isalpha(*(in + i)) && islower(*(in + i)))
        {
            *(res + i) = 'z' - (*(in + i) - 'a');
            tmp = 1;
        }
        if (isalpha(*(in + i)) && isupper(*(in + i)) && tmp == 0)
        {
            *(res + i) = 'Z' - (*(in + i) - 'A');
            tmp = 1;
        }
        if (tmp == 0)
            *(res + i) = *(in + i);
        tmp = 0;
    }

    return res;
}

void free_texts(char **text)
{
    if (!text)
        return;

    for (int i = 0; *(text + i); i++)
        free(*(text + i));
    free(text);
}