#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#define FAILED_ALLOCATE 8
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2
#define NOT_ENOUGH_DATA_AVAILABLE 3

int main()
{
	printf("Podaj rozmiar tablicy: ");
	int size;
	int x = scanf("%d", &size);
	if (x != 1)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (size <= 0)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;
	struct array_t arr;
	int wsk = array_create(&arr, size);
	if (wsk == 2)
		return printf("Failed to allocate memory"), FAILED_ALLOCATE;
	printf("Podaj liczby do zapisania:\n");
	int number, suma = 0, full = 0;
	while (1)
	{
		int x = scanf("%d", &number);
		if (x != 1)
		{
			printf("Incorrect input");
			array_destroy(&arr);
			return INCORRECT_INPUT;
		}
		if (number == 0)
			break;
		if (array_push_back(&arr, number) == 2)
			full = 1;
		suma++;
	}
	if (full == 1)
		printf("Buffer is full\n");
	if (suma == 0)
	{
		array_destroy(&arr);
		printf("Not enough data available");
		return NOT_ENOUGH_DATA_AVAILABLE;
	}
	struct array_t odd, even;
	int y = array_separate(&arr, &odd, &even);
	if (!y)
	{
		array_destroy(&arr);
		printf("Failed to allocate memory");
		return FAILED_ALLOCATE;
	}
	if (y == 1 || y == 3)
	{
		array_display(&odd);
		printf("\n");
	}
	else
		printf("Buffer is empty\n");
	if (y == 2 || y == 3)
		array_display(&even);
	else
		printf("Buffer is empty\n");
	array_destroy(&even);
	array_destroy(&odd);
	array_destroy(&arr);
	return 0;
}
