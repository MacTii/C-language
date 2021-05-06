#include "for_loop.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_value(double value)
{
    printf("%lf ", value);
}

void print_accumulated(double value)
{
    static double sum = 0;
    sum += value;
    printf("%lf ", sum);
}

void print_square(double value)
{
    printf("%lf ", pow(value, 2));
}

void print_abs(double value)
{
    printf("%lf ", fabs(value));
}

void for_loop(double begin, double step, double end, void (*funcs)(double))
{
    if (!funcs || step == 0 || (begin < end && step < 0) || (begin > end && step > 0))
        return;

    if ((begin <= end && step > 0) || (begin >= end && step < 0))
    {
        (*funcs)(begin);
        for_loop(begin + step, step, end, funcs);
    }
}