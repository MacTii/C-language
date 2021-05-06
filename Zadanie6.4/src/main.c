#include "for_loop.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2

int main()
{
	int error;
	double begin, step, end;
	printf("Podaj poczatek, krok i koniec przedzialu: ");
	error = scanf("%lf %lf %lf", &begin, &step, &end);
	if (error != 3)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (step == 0 || (begin < end && step < 0) || (begin > end && step > 0))
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	int op;
	printf("Podaj rodzaj operacji: ");
	error = scanf("%d", &op);
	if (!error)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (op < 0 || op > 3)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	void (**fun)(double) = (void (**)(double))calloc(4, sizeof(void (*)(double)));

	*fun = print_value;
	*(fun + 1) = print_accumulated;
	*(fun + 2) = print_square;
	*(fun + 3) = print_abs;

	switch (op)
	{
	case 0:
		for_loop(begin, step, end, *fun);
		break;

	case 1:
		for_loop(begin, step, end, *(fun + 1));
		break;

	case 2:
		for_loop(begin, step, end, *(fun + 2));
		break;

	case 3:
		for_loop(begin, step, end, *(fun + 3));
		break;

	default:
		break;
	}

	free(fun);

	return SUCCESS;
}