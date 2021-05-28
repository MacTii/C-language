#include "function.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define FAIL 1
#define SUCCESS 0

unsigned long long int bits_to_number(int *err, int args, ...)
{
    if (args < 1 || args > 64)
    {
        if (err)
            *err = FAIL;
        return 0;
    }

    va_list ap;
    va_start(ap, args);

    unsigned long long int number = 0;
    for (int i = args - 1; i >= 0; i--) //args = 8 to i=7
    {
        int current_bit = va_arg(ap, int);
        if (current_bit < 0 || current_bit > 1)
        {
            if (err)
                *err = FAIL;
            return va_end(ap), 0;
        }
        if (current_bit)
            number += (unsigned long long int)pow(2, i);
    }
    va_end(ap);
    if (err)
        *err = SUCCESS;
    return number;
}