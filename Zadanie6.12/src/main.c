#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define FAILED_TO_ALLOCATE_MEMORY 8
#define SUCCESS 0

int main()
{
	int size;

	printf("Podaj liczbe funkcji do wygenerowania: ");
	int x = scanf("%d", &size);
	if (x != 1)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (size < 1)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;

	void (**funcs)(void) = easter(size, print_chicken, print_egg, print_rabbit);
	if (funcs == NULL)
		return printf("Failed to allocate memory"), FAILED_TO_ALLOCATE_MEMORY;

	for (int i = 0; i < size; i++)
		(*(funcs + i))(), printf("\n");
	free(funcs);

	return SUCCESS;
}