#include <stdio.h>
#include <stdlib.h>
#include "array.h"

#define FAILED_ALLOCATE 8
#define INCORRECT_INPUT 1
#define INCORRECT_INPUT_DATA 2

int main()
{
	printf("Podaj rozmiar tablicy: ");
	int size;
	int x = scanf("%d", &size);
	if (x != 1)
		return printf("Incorrect input"), INCORRECT_INPUT;
	if (size <= 0)
		return printf("Incorrect input data"), INCORRECT_INPUT_DATA;
	struct array_t *arr;
	int wsk = array_create_struct(&arr, size);
	if (wsk == 2)
		return printf("Failed to allocate memory"), FAILED_ALLOCATE;
	int number, suma = 0;
	while (1)
	{
		printf("Co chcesz zrobic?: ");
		int choice = 0;
		x = scanf("%d", &choice);
		if (x != 1)
		{
			printf("Incorrect input");
			array_destroy_struct(&arr);
			return INCORRECT_INPUT;
		}
		if (choice == 0)
			break;
		switch (choice)
		{
		case 0:
			break;
		case 1:
			printf("Podaj liczby do zapisania: ");
			do
			{
				int x = scanf("%d", &number);
				if (x != 1)
				{
					printf("Incorrect input");
					array_destroy_struct(&arr);
					return INCORRECT_INPUT;
				}
				if (number == 0 || suma >= size)
					break;
				array_push_back(arr, number);
				suma++;
			} while (number || (arr->size == arr->capacity));
			if (suma == 0)
				printf("Buffer is empty\n");
			else
			{
				if (arr->size == arr->capacity)
					printf("Buffer is full\n");
				array_display(arr);
				printf("\n");
				suma = 0;
			}
			break;
		case 2:
			printf("Podaj liczby do usuniecia: ");
			while (1)
			{
				int x = scanf("%d", &number);
				if (x != 1)
				{
					printf("Incorrect input");
					array_destroy_struct(&arr);
					return INCORRECT_INPUT;
				}
				if (number == 0)
					break;
				array_remove_item(arr, number);
				suma++;
			}
			if (arr->size == 0)
				printf("Buffer is empty\n");
			else
			{
				if (arr->size == arr->capacity)
					printf("Buffer is full\n");
				array_display(arr);
				printf("\n");
			}
			break;
		default:
			printf("Incorrect input data\n");
		}
	}
	array_destroy_struct(&arr);
	return 0;
}
