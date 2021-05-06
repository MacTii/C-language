#ifndef __FOR_LOOP_H__
#define __FOR_LOOP_H__

void print_value(double value);
void print_accumulated(double value);
void print_square(double value);
void print_abs(double value);

void for_loop(double begin, double step, double end, void (*)(double));

#endif // !__FOR_LOOP_H__