#include <stdio.h>
#include <stdlib.h>
#include "big_numbers.h"

#define ELEMENTS 10
#define N 200

#define SUCCESS 0
#define FAIL 1
#define FAILED_TO_ALLOCATE_MEMORY 8

int main()
{
    struct big_numbers_t* bn;
    int error;

    error = create_big_numbers(&bn, ELEMENTS);

    if (error!=0)
        return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

    char *number = (char*)calloc(N + 1, sizeof(char));
    if (!number)
        return destroy_big_numbers(&bn), printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

    printf("Podaj liczby: ");
    while (1)
    {
        if (bn->capacity == bn->size)
        {
            printf("Buffer is full\n");
            break;
        }

        char c = getchar();
        if (c == '\n')
            break;

        ungetc(c, stdin);

        scanf("%200s", number);

        while (getchar() != '\n');

        if (validate(number) == FAIL)
        {
            printf("Incorrect input\n");
            continue;
        }
        error = add_big_number(bn, number);
        if (error != 0)
        {
            printf("Failed to allocate memory\n");
            break;
        }
    }

    if (bn->size == 0)
        printf("Buffer is empty");
    else
        display(bn);

    destroy_big_numbers(&bn);
    free(number);

    return SUCCESS;
}